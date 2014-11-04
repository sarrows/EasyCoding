#ifndef __QUEUE_ADAPTER_INCLUDE__
#define __QUEUE_ADAPTER_INCLUDE__

/*****************************************************
 * author: 李国强
 * date: 2006-6-20
 * desc: 实现list适配器,缺省为LoopList
 ****************************************************/
#include "loop_list.h"
#include "dilink_list.h"
#include "mutex.h"

template<class ITEM, class LIST = LoopList<ITEM> >
class QueueAdapter
{
    typedef LIST              Queue;
    typedef typename Queue::size_type  size_type;
public:
    QueueAdapter() : sem_(Mutex::THREAD_SEMA){}
    int    enqueue(const ITEM item);  //向队列添加元素
    int    dequeue(ITEM& item, timeval *val=0);        //从队列取元素
    size_type size() const;            //返回元素个数
    bool   full() const;               //队列是否满
    bool   empty() const;     
    void   clear();                    //清空队列
    void   close();   //关闭队别
private:
    Queue queue_;
    Mutex sem_;
    Mutex mutex_;
};

#include "queue_adapter.inl"

#endif
