#ifndef __QUEUE_ADAPTER_INCLUDE__
#define __QUEUE_ADAPTER_INCLUDE__

/*****************************************************
 * author: ���ǿ
 * date: 2006-6-20
 * desc: ʵ��list������,ȱʡΪLoopList
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
    int    enqueue(const ITEM item);  //��������Ԫ��
    int    dequeue(ITEM& item, timeval *val=0);        //�Ӷ���ȡԪ��
    size_type size() const;            //����Ԫ�ظ���
    bool   full() const;               //�����Ƿ���
    bool   empty() const;     
    void   clear();                    //��ն���
    void   close();   //�رնӱ�
private:
    Queue queue_;
    Mutex sem_;
    Mutex mutex_;
};

#include "queue_adapter.inl"

#endif
