
#pragma once

#include "ipcobjbase.h"

namespace EasyCoding {

	class ECExport Mutex : public IpcObjBase
	{
	public:

		Mutex(const char * pszName=NULL);
		Mutex(Mutex& mtx);
		void release();    // ÊÍ·ÅËø
		bool tryacquire(); // ³¢ÊÔËø
	};

	/* ËøÊØ»¤ */
	class ECExport Guard
	{
	public:
		Guard(Mutex * mutex) : locker_(mutex)
		{
			locker_->acquire();
		}
		~Guard(){ locker_->release();}
	private:
		Mutex * locker_;
	};

}