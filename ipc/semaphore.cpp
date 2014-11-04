
#include "log/Logger.h"
#include "semaphore.h"

namespace EasyCoding {

	Semaphore::Semaphore(int maxcnt, const char * pszName)
	{
		HANDLE hSema = CreateSemaphore(
			NULL,  // default security attributes
			maxcnt,   // initial count
			maxcnt,   // maximum count
			pszName); // named or unnamed semaphore

		if (NULL == hSema) {
			// TODO: handle this
			EC_ERROR("CreateSemiphore failed! (name = %s)", pszName ? pszName : "");
		} else {
			set_handle(hSema);
		}
	}

	Semaphore::Semaphore(Semaphore& sema)
		: IpcObjBase(sema)
	{
	}

	/* Õ∑≈À¯*/
	void Semaphore::release()
	{
		HANDLE hSema = handle();
		if (hSema) ReleaseSemaphore(hSema, 1, NULL);
	}

	/*≥¢ ‘À¯*/
	bool Semaphore::tryacquire()
	{
		return (IPC_OK == acquire(0));
	}

}
