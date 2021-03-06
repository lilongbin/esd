/*****************************************
* Copyright (C) 2020 * Ltd. All rights reserved.
* File name   : template.test.cpp
* Created date: 2020-03-25 10:36:24
*******************************************/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "template.hpp"
using namespace std;

constexpr std::chrono::milliseconds TimeInterVal(5);

class MessageParser:public Singleton<MessageParser>
{
    friend class Singleton<MessageParser>;
    public:
        MessageParser();
        ~MessageParser();
        void onRecvMessage(const std::vector<MsgQueueT> &vec);
        void putMsgTest(MsgQueueT &val);
    private:
        void init();
        void deinit();
#if USE_SELF_DEFINED_QUEUE_CLASS
        MessageQueueBase *mqueue;
#else
        std::shared_ptr<ConcurrentQueue<MsgQueueT>> mqueue;
#endif
        BatchingConsumer<MsgQueueT> mBatchingConsumer;
};

MessageParser::MessageParser()
{
    init();
}

MessageParser::~MessageParser()
{
    std::cout << __func__ << std::endl;
    deinit();
}

void MessageParser::init()
{
#if USE_SELF_DEFINED_QUEUE_CLASS
    mqueue = MessageQueueBase::getInstance();
    mBatchingConsumer.run(mqueue, TimeInterVal,
                            std::bind(&MessageParser::onRecvMessage, this, std::placeholders::_1));
#else
    mqueue = std::make_shared<ConcurrentQueue<MsgQueueT>>(3000);
    mBatchingConsumer.run(mqueue.get(), TimeInterVal,
                            std::bind(&MessageParser::onRecvMessage, this, std::placeholders::_1));
#endif
}

void MessageParser::deinit()
{
    mBatchingConsumer.requestStop();
    if (mqueue != NULL) {
        mqueue->deactivate();
    }
    mBatchingConsumer.waitStopped();
}

void MessageParser::putMsgTest(MsgQueueT &val)
{
    MsgQueueT value;
    value = val;
    cout << __func__ << " write: " << value << endl;
#if USE_SELF_DEFINED_QUEUE_CLASS
    mqueue->write(value);
#else
    mqueue->push(std::move(value));
#endif
}

void MessageParser::onRecvMessage(const std::vector<MsgQueueT> &vec)
{
    std::cout << "onRecvMessage begin" << std::endl;
    for (auto value:vec) {
        std::cout << __func__ << " value: " << value << std::endl;
    }
    std::cout << "onRecvMessage end" << std::endl;
    std::cout << std::endl << std::endl;
}

int test() {
    std::string str = "hello template";
    std::string test;
    MessageParser *parser = MessageParser::getInstance();
    /*
     * MessageQueueBase *mqueue =  MessageQueueBase::getInstance();
     * mqueue->write(str);
     * mqueue->read(str);
     * std::cout << "read: " << str << std::endl;
     * mqueue->deactivate();
     */
    for (auto i = 0; i < 5; i++) {
        str = "hello template " + toString(i);
        parser->putMsgTest(str);
        // mqueue->write(str);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
	return 0;
}

int main() {
    test();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 0;
}
