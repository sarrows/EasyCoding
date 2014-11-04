
#pragma once

#include "config_platform.h"

namespace EasyCoding {

	class ECExport IpcObjBase
	{
	public:

		enum eAcquireResult {
			IPC_FAILED=-1, // 等待事件失败
			IPC_OK,        // 等待事件成功
			IPC_TIMEOUT    // 等待事件超时
		};

		IpcObjBase() { _hdl = NULL; }
		IpcObjBase(IpcObjBase& ipcobj);
		virtual ~IpcObjBase();
		virtual eAcquireResult acquire(long tm = INFINITE); // 获取
		virtual HANDLE handle() const { return _hdl; }
		virtual void set_handle(HANDLE hdl) { _hdl = hdl; }

	private:
		HANDLE _hdl;
	};

}
