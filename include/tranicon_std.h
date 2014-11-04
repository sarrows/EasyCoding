#ifndef __TRANICON_STD_INCLUDE
#define __TRANICON_STD_INCLUDE

/*
file:  tranicon_std.h
date:  2006-2-18
by:    liguoqiang
desc:
	��Ҫ�Ƕ�CTranIcon���޸ģ����಻��MFC�������ͼ��Ĺ��ܡ�
	��Ҫ������create_icon��modify_icon��delete_icon��
	create       //��ʼ����������ʾ����ͼ��
	modify_icon  //�޸�����ͼ��
	delete_icon  //ɾ������ͼ��
	�¼���Ӧ����:notify
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
