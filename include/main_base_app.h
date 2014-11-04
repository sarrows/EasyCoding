#ifndef __MAIN_BASE_APP_INCLUDE
#define __MAIN_BASE_APP_INCLUDE

/*
 *file: main_base_app.h
 *date: 2005-5-10
 *by:   liguoqiang
 *desc:
 *	����APP�Ļ��࣬������ֻʹ��SDK��������ϵͳ
 */
#include "config_platform.h"

#ifdef MY_WIN32
 
class MainBaseWnd;
class ECExport MainBaseApp
{
public:
/*�����,�˺���������WINDOW*/
#define DECL_MAINWND(MainWndType) \
	typedef MainWndType __MyMainWnd;
#define REGISTER_MAINWND(ClsName, WinTitle, MainIcon, SmallIcon, Menu, Cx, Cy) \
	main_wnd_ = new __MyMainWnd; \
	main_wnd_->create(ClsName, \
		WinTitle, \
		MainIcon, \
		SmallIcon, \
		Menu, \
		WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX, \
		Cx, \
		Cy);
#define UNREGISTER_MAINWND \
    main_wnd_->destroy(); \
	delete main_wnd_;
	
	MainBaseApp();        //ȱʡ���캯��
	int run();             //�¼�ѭ��ֱ��ϵͳ�˳�
	static MainBaseApp * instance();
	virtual int init(HINSTANCE hins);
	virtual void fini();
	HINSTANCE get_handle(){return app_inst_;}
	MainBaseWnd* get_main_wnd(){return main_wnd_;}
protected:
	HINSTANCE    app_inst_;   //ʵ�����
	MainBaseWnd* main_wnd_;
	static MainBaseApp* this_class_;  //��̬����
};
#endif
#endif
