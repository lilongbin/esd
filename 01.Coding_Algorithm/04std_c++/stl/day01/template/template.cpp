#include "template.hpp"

MessageQueueBase::MessageQueueBase()
{
    //m_Queue = std::make_unique<ConcurrentQueue<QueueMsgType>>(3000);
    m_Queue = std::unique_ptr<ConcurrentQueue<QueueMsgType>>(new ConcurrentQueue<QueueMsgType>(3000));
}

MessageQueueBase::~MessageQueueBase()
{
}

void MessageQueueBase::write(QueueMsgType &msg)
{
    //logv("write msg.size=%zu", msg.size());
    /* msgs cannot be used any more after push */
    m_Queue->push(std::move(msg));
}

void MessageQueueBase::waitForItems()
{
    //logv("read waitForItems");
    m_Queue->waitForItems();
}

bool MessageQueueBase::read(QueueMsgType &msg)
{
    bool ret = false;
    ret = m_Queue->pull(msg);
    if (ret == true)
    {
        //logd("read msg.size=%zu", msg.size());
    }
    return ret;
}

bool MessageQueueBase::pullAll(std::vector<QueueMsgType> &msg)
{
    bool ret = false;
    ret = m_Queue->pullAll(msg);
    if (ret == true)
    {
        //logd("read msg.size=%zu", msg.size());
    }
    return ret;
}

void MessageQueueBase::deactivate()
{
    //logi("deactivate");
    m_Queue->deactivate();
}

