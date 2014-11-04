
#pragma once

#include "ipcobjbase.h"

namespace EasyCoding {

	// 初始状态为“无事件”
	class ECExport Event : public IpcObjBase
	{
	public:
		enum eEventType {
			AUTO,
			MANUAL
		};

		Event(eEventType type=AUTO, const char * pszName=NULL);
		Event(Event& evt);
		void set();   // 设置事件
		void reset(); // 重置事件

	private:
		eEventType _type;
	};

}
