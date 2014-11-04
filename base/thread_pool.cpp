#include "thread_pool.h"
#include "windows.h"

/************************************
 * �����߳�,��ʱ�������߳�����
 * ���ݺ�WIN32�жϿ�ƽ̨
 ************************************/
int
ThreadPool::activate(size_t nums, thread_id * id, thread_handle * handle)
{
	thread_nums_ = nums;
	handle_ = new thread_handle[nums];
	for (size_t n = 0; n < nums; n++) {
		handle_[n] = CreateThread(0, 0, thread_func, this, 0, id ? &id[n] : 0);
		if (handle) handle[n] = handle_[n];
	}
	return 0;
}

/************************************
 * �ȴ��߳��˳�
 ************************************/
void
ThreadPool::wait()
{
	if (handle_) {
		for (size_t n = 0; n < thread_nums_; n++)
			WaitForSingleObject (handle_[n], INFINITE);
		delete[] handle_;
		handle_ = 0;
	}
}

/************************************
 * ���ص�ǰ�߳�ID
 ************************************/
ThreadPool::thread_id
ThreadPool::thread_self() const
{
	return GetCurrentThreadId();
}
