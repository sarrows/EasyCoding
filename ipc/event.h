
#pragma once

#include "ipcobjbase.h"

namespace EasyCoding {

	// ��ʼ״̬Ϊ�����¼���
	class ECExport Event : public IpcObjBase
	{
	public:
		enum eEventType {
			AUTO,
			MANUAL
		};

		Event(eEventType type=AUTO, const char * pszName=NULL);
		Event(Event& evt);
		void set();   // �����¼�
		void reset(); // �����¼�

	private:
		eEventType _type;
	};

}
