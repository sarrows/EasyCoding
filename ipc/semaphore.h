
#pragma once

#include "ipcobjbase.h"

namespace EasyCoding {

	class ECExport Semaphore : public IpcObjBase
	{
	public:
		Semaphore(int maxcnt=0, const char * pszName=NULL);
		Semaphore(Semaphore& sema);
		//eAcquireResult acquire(long tm = INFINITE); // ��ȡ��
		void release();    // �ͷ���
		bool tryacquire(); // ������
	};

}
