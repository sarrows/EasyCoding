
#include "log/Logger.h"
#include "mutex.h"

namespace EasyCoding {

	Mutex::Mutex(const char * pszName)
	{
		HANDLE hMtx = CreateMutex(
			NULL,  // default security attributes
			FALSE, // initial owner
			pszName); // named or unnamed mutex

		if (NULL == hMtx) {
			// TODO: handle this
			EC_ERROR("CreateMutex failed! (name = %s)", pszName ? pszName : "");
		} else {
			set_handle(hMtx);
		}
	}

	Mutex::Mutex(Mutex& mtx)
		: IpcObjBase(mtx)
	{
	}

	/* Õ∑≈À¯*/
	void Mutex::release()
	{
		HANDLE hMtx = handle();
		if (hMtx) ReleaseMutex(hMtx);
	}

	/*≥¢ ‘À¯*/
	bool Mutex::tryacquire()
	{
		return (IPC_OK == acquire(0));
	}

}
