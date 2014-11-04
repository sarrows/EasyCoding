
#include "log/Logger.h"
#include "event.h"

namespace EasyCoding {

	Event::Event(eEventType type, const char * pszName)
	{
		HANDLE hEvt = CreateEvent(
			NULL,  // default security attributes
			(MANUAL==type) ? TRUE : FALSE,  // event type
			FALSE, // initial state
			pszName); // named or unnamed event

		if (NULL == hEvt) {
			// TODO: handle this
			EC_ERROR("CreateEvent failed! (name = %s)", pszName ? pszName : "");
		} else {
			set_handle(hEvt);
		}
	}

	Event::Event(Event& evt)
		: IpcObjBase(evt)
	{
	}

	/*设置事件*/
	void Event::set()
	{
		HANDLE hEvt = handle();
		if (hEvt) SetEvent(hEvt);
	}

	/*重置事件*/
	void Event::reset()
	{
		HANDLE hEvt = handle();
		if (hEvt) ResetEvent(hEvt);
	}

}
