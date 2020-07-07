#ifndef __XX_COMM_H__
#define __XX_COMM_H__

#include <iostream>
#include <sstream>
#include <sstream>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <functional>
#include <chrono>
#include <memory>
#include <condition_variable>
#include <algorithm>

#define USE_SELF_DEFINED_QUEUE_CLASS 1

typedef std::string MsgQueueT;

using QueueMsgType = MsgQueueT;

//#define print(x) std::cout << __func__ << ">>" << __LINE__ << ">>" << #x << "# " << x << std::endl

template <class T>
T stringToNumber(const std::string &str)
{
    /* can auto remove leading 0 */
    std::istringstream iss(str);
    T number {};
    iss >> number;
    return number;
}

template <class T>
std::string toString(T value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template <class T>
class Singleton
{
private:
    static std::mutex ms_MuxLock_Singleton;
    using MuxGuard = std::lock_guard<std::mutex>;
    static T* ms_pInstance;
    Singleton(const Singleton& src){(void)src;}
    Singleton &operator=(const Singleton& src){(void)src;};

    class Garbo
    {
    public:
        ~Garbo()
        {
            // std::cout<<"Singleton<"<<typeid(T).name()<<">::Garbo::~Garbo()" << std::endl;
            if (Singleton::ms_pInstance)
            {
                delete Singleton::ms_pInstance;
                Singleton::ms_pInstance = NULL;
            }
        }
        void touch() { return; }
    };
    static Garbo ms_garbo;

protected:
    Singleton() {
        ms_garbo.touch(); //prevent optimised and no garbo instance to trigger deconstruct
    }
    ~Singleton() {}

public:
    static T* getInstance()
    {
        if (ms_pInstance == NULL)
        {
            MuxGuard mlk(ms_MuxLock_Singleton);
            if (ms_pInstance == NULL)
            {
                ms_pInstance = new T();
            }
        }
        return ms_pInstance;
    }
};

template <class T> std::mutex Singleton<T>::ms_MuxLock_Singleton;
template <class T> typename Singleton<T>::Garbo Singleton<T>::ms_garbo;
template <class T> T* Singleton<T>::ms_pInstance = NULL;


template<typename T>
class ConcurrentQueue {
public:
    ConcurrentQueue() {}
    ConcurrentQueue(int wait) : mWait{wait} {}

    void waitForItems() {
        std::unique_lock<std::mutex> gul(mLock);
        if (mWait > 0) {
            // block here until be notified or timeout
            if (mQueue.empty() && mIsActive) {
                mCond.wait_for(gul, std::chrono::milliseconds(mWait));
            }
        } else if (mWait == 0) {
            // unblock
            return;
        } else {
            // block here until be notified and valid item exist
            while (mQueue.empty() && mIsActive) {
                mCond.wait(gul);
            }
        }
    }

   bool pullAll(std::vector<T> &items) {
        MuxGuard g(mLock);
        if (mQueue.empty()) {
            return false;
        }
        while (!mQueue.empty()) {
            items.push_back(std::move(mQueue.front()));
            mQueue.pop();
        }
        return true;
    }

    bool pull(T &item) {
        MuxGuard g(mLock);
        if (mQueue.empty()) {
            return false;
        }
        if (!mQueue.empty()) {
            item = std::move(mQueue.front());
            mQueue.pop();
        }
        return true;
    }

    void push(T&& item) {
        {
            MuxGuard g(mLock);
            if (mQueue.size() >= mMaxQueueSize)
            {
                /* pop queue head when queue is full */
                mQueue.pop();
            }
            mQueue.push(std::move(item));
        }
        mCond.notify_one();
    }

    /* Deactivates the queue, thus no one can push items to it, also
     * notifies all waiting thread.
     */
    void deactivate() {
        {
            MuxGuard g(mLock);
            mIsActive = false;
        }
        mCond.notify_all();  // To unblock all waiting consumers.
    }

    //ConcurrentQueue() = default;
    ConcurrentQueue(const ConcurrentQueue &) = delete;
    ConcurrentQueue &operator=(const ConcurrentQueue &) = delete;
private:
    using MuxGuard = std::lock_guard<std::mutex>;
    int mWait = -1; // wait_for time, negtive for always block, 0 for unblock.
    bool mIsActive = true;
    size_t mMaxQueueSize = 5000;
    mutable std::mutex mLock;
    std::condition_variable mCond;
    std::queue<T> mQueue;
};


class MessageQueueBase:public Singleton<MessageQueueBase>
{
    friend class Singleton<MessageQueueBase>;
private:
    MessageQueueBase();
    std::unique_ptr<ConcurrentQueue<QueueMsgType>> m_Queue;

public:
    virtual ~MessageQueueBase();
    virtual void write(QueueMsgType &msg);
    virtual void waitForItems();
    virtual bool read(QueueMsgType &msg);
    virtual bool pullAll(std::vector<QueueMsgType> &vec);
    virtual void deactivate();
};


template<typename T>
class BatchingConsumer {
public:
    enum class State {
        INIT = 0,
        RUNNING = 1,
        STOP_REQUESTED = 2,
        STOPPED = 3,
    };

public:
    BatchingConsumer() : mState(State::INIT) {}
    virtual ~BatchingConsumer(){}

    BatchingConsumer(const BatchingConsumer &) = delete;
    BatchingConsumer &operator=(const BatchingConsumer &) = delete;

    using OnBatchReceivedProcFunc = std::function<void(const std::vector<T>& vec)>;

#if USE_SELF_DEFINED_QUEUE_CLASS
    virtual void run(MessageQueueBase* queue,
#else
    virtual void run(ConcurrentQueue<T>* queue,
#endif
                    std::chrono::nanoseconds batchInterval,
                    const OnBatchReceivedProcFunc& callback) {
        mQueue = queue;
        mBatchInterval = batchInterval;
        mWorkerThread = std::thread(&BatchingConsumer<T>::runInternal, this, callback);
    }

    void requestStop() {
        std::cout << __func__ << std::endl;
        mState = State::STOP_REQUESTED;
    }

    void waitStopped() {
        std::cout << __func__ << std::endl;
        if (mWorkerThread.joinable()) {
            mWorkerThread.join();
        }
    }

private:
    void runInternal(const OnBatchReceivedProcFunc& onBatchReceivedCallback) {
        std::vector<T> items;
        if (mState.exchange(State::RUNNING) == State::INIT) {
            while (State::RUNNING == mState) {
                mQueue->waitForItems();
                if (State::STOP_REQUESTED == mState) break;

                std::this_thread::sleep_for(mBatchInterval);
                if (State::STOP_REQUESTED == mState) break;

                items.clear();
                mQueue->pullAll(items);

                if (items.size() > 0) {
                    onBatchReceivedCallback(items);
                }
            }
        }

        mState = State::STOPPED;
    }

public:
    std::thread mWorkerThread;
    std::atomic<State> mState;
    std::chrono::nanoseconds mBatchInterval;
#if USE_SELF_DEFINED_QUEUE_CLASS
    MessageQueueBase *mQueue;
#else
    ConcurrentQueue<T>* mQueue;
#endif
};


#endif


