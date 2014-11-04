
#pragma once

#include "config_platform.h"

namespace EasyCoding {

	class ECExport IpcObjBase
	{
	public:

		enum eAcquireResult {
			IPC_FAILED=-1, // �ȴ��¼�ʧ��
			IPC_OK,        // �ȴ��¼��ɹ�
			IPC_TIMEOUT    // �ȴ��¼���ʱ
		};

		IpcObjBase() { _hdl = NULL; }
		IpcObjBase(IpcObjBase& ipcobj);
		virtual ~IpcObjBase();
		virtual eAcquireResult acquire(long tm = INFINITE); // ��ȡ
		virtual HANDLE handle() const { return _hdl; }
		virtual void set_handle(HANDLE hdl) { _hdl = hdl; }

	private:
		HANDLE _hdl;
	};

}
