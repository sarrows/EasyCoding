#ifdef WIN32

#include "main_base_app.h"

MainBaseApp* MainBaseApp::this_class_ = 0;

MainBaseApp::MainBaseApp()
:app_inst_(0),main_wnd_(0)
{
	this_class_ = this;
}
//����whileѭ��������ϵͳ��Ϣ���ɷ�
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
 *����,���ü򵥵�
 ******************************/
MainBaseApp *
MainBaseApp::instance()
{
	return this_class_;
}
/*****************************
* ʵ��������,��������
*******************************/
int
MainBaseApp::init(HINSTANCE hins)
{
	app_inst_ = hins;
	return 0;
}
/****************************
 * ��ʵ��������
 ****************************/
void
MainBaseApp::fini()
{
	app_inst_ = 0;
}
#endif
