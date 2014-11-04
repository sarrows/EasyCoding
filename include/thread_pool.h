#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "config_platform.h"
#include "ipc/mutex.h"

class ECExport ThreadPool
{
public:
	typedef DWORD thread_id;      // 线程ID
	typedef HANDLE thread_handle; // 线程句柄

public:
	explicit ThreadPool() : handle_(0), critical_() {}
	virtual ~ThreadPool() {}

	int  activate(size_t nums, thread_id *id = 0, thread_handle * handle = 0 ); //激活线程池
	virtual int  svc() = 0;        // 线程实体,虚函数
	void wait();                   // 等待线程退出
	virtual void stop(bool wait_exit=false) = 0; // 通知所有线程退出
	thread_id thread_self() const; // 当前线程ID
	void enter_critical_section() { critical_.acquire(); } // 进入关键区，用于svc()
	void leave_critical_section() { critical_.release(); } // 离开关键区，用于svc()

private:
    /* 线程主函数, 设置为friend
     * 在此函数内调用svc方法
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
	EasyCoding::Mutex critical_; // 用于在svc()里面保护关健区（如果线程池数大于1的话）
};

#endif
