#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "config_platform.h"
#include "ipc/mutex.h"

class ECExport ThreadPool
{
public:
	typedef DWORD thread_id;      // �߳�ID
	typedef HANDLE thread_handle; // �߳̾��

public:
	explicit ThreadPool() : handle_(0), critical_() {}
	virtual ~ThreadPool() {}

	int  activate(size_t nums, thread_id *id = 0, thread_handle * handle = 0 ); //�����̳߳�
	virtual int  svc() = 0;        // �߳�ʵ��,�麯��
	void wait();                   // �ȴ��߳��˳�
	virtual void stop(bool wait_exit=false) = 0; // ֪ͨ�����߳��˳�
	thread_id thread_self() const; // ��ǰ�߳�ID
	void enter_critical_section() { critical_.acquire(); } // ����ؼ���������svc()
	void leave_critical_section() { critical_.release(); } // �뿪�ؼ���������svc()

private:
    /* �߳�������, ����Ϊfriend
     * �ڴ˺����ڵ���svc����
     */
	friend DWORD WINAPI thread_func(void * arg)
	{
		ThreadPool * pool = (ThreadPool*)arg;
		pool->svc();
		return 0;
	}

private:
	thread_handle * handle_;
	size_t thread_nums_;
	EasyCoding::Mutex critical_; // ������svc()���汣���ؽ���������̳߳�������1�Ļ���
};

#endif
