#ifdef WIN32

#include "main_base_app.h"

MainBaseApp* MainBaseApp::this_class_ = 0;

MainBaseApp::MainBaseApp()
:app_inst_(0),main_wnd_(0)
{
	this_class_ = this;
}
//采用while循环，接收系统消息并派发
int
MainBaseApp::run()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
/*******************************
 *单体,采用简单的
 ******************************/
MainBaseApp *
MainBaseApp::instance()
{
	return this_class_;
}
/*****************************
* 实例化方法,创建窗口
*******************************/
int
MainBaseApp::init(HINSTANCE hins)
{
	app_inst_ = hins;
	return 0;
}
/****************************
 * 反实例化方法
 ****************************/
void
MainBaseApp::fini()
{
	app_inst_ = 0;
}
#endif
