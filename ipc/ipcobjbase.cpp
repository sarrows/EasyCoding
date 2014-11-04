
#include "IpcObjBase.h"

namespace EasyCoding {

	IpcObjBase::IpcObjBase(IpcObjBase& ipcobj)
	{
		_hdl = ipcobj.handle();

		DuplicateHandle(GetCurrentProcess(),
			ipcobj.handle(),
			GetCurrentProcess(),
			&_hdl,
			0,
			FALSE,
			DUPLICATE_SAME_ACCESS);
	}

	IpcObjBase::~IpcObjBase()
	{
		if (NULL != _hdl) {
			CloseHandle(_hdl);
			_hdl = NULL;
		}
	}

	/*******************************
	* 获取事件
	******************************/
	IpcObjBase::eAcquireResult IpcObjBase::acquire(long tm)
	{
		eAcquireResult er = IPC_FAILED;

		if (NULL != _hdl) {
			DWORD dwWaitResult = WaitForSingleObject(_hdl, tm);
			switch (dwWaitResult) { 
				// The event object was signaled.
			case WAIT_OBJECT_0:
				er = IPC_OK;
				break; 
				// The event was not signaled, so a time-out occurred.
			case WAIT_TIMEOUT: 
				er = IPC_TIMEOUT;
				break; 
			default:
				er = IPC_FAILED;
				break; 
			}
		}
		return er;
	}

}
