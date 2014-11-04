#ifndef __TRANICON_STD_INCLUDE
#define __TRANICON_STD_INCLUDE

/*
file:  tranicon_std.h
date:  2006-2-18
by:    liguoqiang
desc:
	主要是对CTranIcon的修改，此类不用MFC完成托盘图标的功能。
	主要函数：create_icon、modify_icon、delete_icon。
	create       //初始化函数和显示托盘图标
	modify_icon  //修改托盘图标
	delete_icon  //删除托盘图标
	事件响应函数:notify
*/

#include "config_platform.h"

#ifdef MY_WIN32

typedef void (*Menu_Cb_Func)(HMENU, void *);
class ECExport Tranicon_Std
{
public:
	Tranicon_Std();
	~Tranicon_Std();

	BOOL create(HWND wnd,
		UINT id,
		HICON icon,
		UINT menuid,
		LPTSTR sztip,
		UINT cbmsg,
		HINSTANCE ins,
		Menu_Cb_Func func,
		void * p);
	void modify_icon(HICON icon);
	void delete_icon();
	
	LRESULT notify(WPARAM wparam, LPARAM lparam);
private:
	NOTIFYICONDATA  notify_date_;
	bool         icon_has_exists_;
	HWND         wnd_;
	UINT         menu_id_;
	HINSTANCE    app_ins_;
	Menu_Cb_Func menu_cb_;
	void *       cb_arg_;
};
#endif
#endif
