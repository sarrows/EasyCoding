#ifdef WIN32

#include "tranicon_std.h"

//构造函数
Tranicon_Std::Tranicon_Std()
: wnd_(0), icon_has_exists_(0),
 menu_id_(0), app_ins_(0), menu_cb_(0), cb_arg_(0)
{
	 memset(&notify_date_, 0, sizeof(notify_date_));
}
//析构函数
Tranicon_Std::~Tranicon_Std()
{
	if (icon_has_exists_)
		delete_icon();
}
//初始化托盘属性，调用Shell_NotifyIcon设置托盘属性。
BOOL
Tranicon_Std::create(HWND wnd,
					 UINT id,
					 HICON icon,
					 UINT menuid,
					 LPTSTR sztip,
					 UINT cbmsg,
					 HINSTANCE ins,
					 Menu_Cb_Func func,
					 void *p)
{
	wnd_     = wnd;
	menu_id_ = menuid;
	app_ins_ = ins;
	menu_cb_ = func;
	cb_arg_  = p;

	notify_date_.hWnd   = wnd;
	notify_date_.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	notify_date_.uID    = id;
	notify_date_.hIcon  = icon;
	notify_date_.uCallbackMessage = cbmsg;

	if (sztip)
		lstrcpyn(notify_date_.szTip, sztip, sizeof(notify_date_.szTip));
	else
		notify_date_.szTip[0] = 0;
	return (icon_has_exists_ = Shell_NotifyIcon(NIM_ADD, &notify_date_) ? TRUE : FALSE);
}
//修改托盘显示图标
void
Tranicon_Std::modify_icon(HICON icon)
{
	if (icon_has_exists_)
		notify_date_.hIcon = icon;
	Shell_NotifyIcon(NIM_MODIFY, &notify_date_);
}
//删除托盘显示的图标
void
Tranicon_Std::delete_icon()
{
	if (icon_has_exists_) {
		Shell_NotifyIcon(NIM_DELETE, &notify_date_);
		icon_has_exists_ = false;
	}
}
//接收托盘事件响应
LRESULT
Tranicon_Std::notify(WPARAM wparam, LPARAM lparam)
{
	if (wparam != notify_date_.uID)
		return 0;
	//装载右键菜单
	POINT pt;
	HMENU hmenu = LoadMenu(app_ins_, MAKEINTRESOURCE(menu_id_));
	if (hmenu) {
		//获取第一个子菜单
		HMENU hsubmenu = GetSubMenu(hmenu, 0);
		if (hsubmenu) {
			//判断是否为右键
			if (lparam == WM_RBUTTONUP) {
				//设置第一个菜单项为缺省，即：第一个菜单项显示为加粗
				SetMenuDefaultItem(hsubmenu, 0, TRUE);
				GetCursorPos(&pt);
				SetForegroundWindow(wnd_);
				//调用回调函数，由回调函数决定菜单如何显示（灰色？可见？不可见）
				if(menu_cb_)
					menu_cb_(hsubmenu, cb_arg_);
				TrackPopupMenu(hsubmenu,
					TPM_RIGHTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
					pt.x,
					pt.y,
					0,
					wnd_,
					NULL);
			}else if(lparam == WM_LBUTTONDBLCLK) {
				ShowWindow(wnd_, SW_SHOW);
				SetForegroundWindow(wnd_);
			}
		}
	}
	return 1L;
}
#endif
