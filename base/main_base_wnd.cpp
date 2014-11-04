#ifdef WIN32

#include "Main_base_wnd.h"
#include "main_base_app.h"

MainBaseWnd::MainBaseWnd ()
:custom_msg_head_(0), wnd_handler_(0)
{
}
//�ͷ���Դ����Ҫ���Զ�����Ϣ�б�
MainBaseWnd::~MainBaseWnd()
{
	custom_message_t * msg;
	while(custom_msg_head_) {
		msg = custom_msg_head_;
		custom_msg_head_ = custom_msg_head_->next;
		free(msg);
	}
}
/*
 *	��Ҫͨ��RegisterClassExע�ᴰ����
 * �������и�����Դ������Ӧ�ĺ������
 * ������Դ������Ҫ��app�����ͨ������Main_Base_App::instance()ʵ��
 * ������CreateWindow��ɴ��ڵĴ���
 */
int
MainBaseWnd::create (UINT uclsname,
					   UINT utitle,
					   UINT icon,
					   UINT smallicon,
					   UINT menu,
					   DWORD style,
					   int cx, int cy)
{
	WNDCLASSEX wcx;
	
	LoadString (MainBaseApp::instance()->get_handle(), uclsname, cls_name, sizeof(cls_name) );
	LoadString (MainBaseApp::instance()->get_handle(), utitle, app_title, sizeof(app_title) );
	
	wcx.cbSize        = sizeof (WNDCLASSEX);
	wcx.style         = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc   = (WNDPROC)wnd_proc;
	wcx.cbClsExtra    = 0;
	wcx.cbWndExtra    = 0;
	wcx.hInstance     = MainBaseApp::instance()->get_handle();
	wcx.hIcon         = LoadIcon (MainBaseApp::instance()->get_handle(), (LPCTSTR)icon);
	wcx.hCursor       = LoadCursor( /*MainBaseApp::instance()->get_handle()*/0, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcx.lpszMenuName  = (LPCTSTR)menu;
	wcx.lpszClassName = cls_name;
	wcx.hIconSm       = LoadIcon (MainBaseApp::instance()->get_handle(), (LPCTSTR)smallicon);
	
	RegisterClassEx ( &wcx );

	
	/*����*/
	RECT rctop;
	RECT rc;
	HWND htop = GetDesktopWindow ();
	GetClientRect (htop, &rctop);
	rc.left   = (rctop.right-rctop.left-cx)/2;
	rc.top    = (rctop.bottom-rctop.top-cy)/2;
	rc.right  = rc.left + cx;
	rc.bottom = rc.top + cy;

	wnd_handler_ = CreateWindow( cls_name,
		app_title,
		style,
		rc.left,
		rc.top,
		cx,
		cy,
		NULL,
		NULL,
		MainBaseApp::instance()->get_handle(),
		NULL);

	ShowCursor(TRUE);

	return ( wnd_handler_ == NULL ? 0 : 1);
}
/*��ʾ*/
void
MainBaseWnd::show (int ncmd)
{
	ShowWindow ( wnd_handler_, ncmd );
	UpdateWindow( wnd_handler_ );
}
/*�����Զ�����Ϣ
*msg�������0���һص�����cb����ΪNULL�����򷵻أ�1���ɹ�ʱ����ֵΪ0
*/
int
MainBaseWnd::add_custom_msg(UINT msg, Msg_CB cb, void* context)
{
	custom_message_t * msg_p = 0;
	if (msg > 0 && cb) {
		if (msg_p = (custom_message_t*)malloc(sizeof(custom_message_t))) {
			msg_p->msgid  = msg;
			msg_p->msg_cb = cb;
			msg_p->_context = context;
			msg_p->next   = 0;
			if (custom_msg_head_) {
				msg_p->next = custom_msg_head_->next;
				custom_msg_head_->next = msg_p;
			}else
				custom_msg_head_ = msg_p;
			return 0;
		}
	}
	return -1;
}

LRESULT CALLBACK
MainBaseWnd::wnd_proc ( HWND hwnd, UINT nmsg, WPARAM wparam, LPARAM lparam)
{
	int nid, nevent;
	HDC dc;
	PAINTSTRUCT ps;
	
	MainBaseWnd* main_wnd = MainBaseApp::instance()->get_main_wnd();

	custom_message_t * msg_p = main_wnd->custom_msg_head_;
	bool has_custom = false;
	
	switch(nmsg)
	{
	case WM_COMMAND:
		nid = LOWORD(wparam);
		nevent = HIWORD(wparam);
		main_wnd->mainwnd_command (nevent, nid, (WORD)lparam);
		break;
	case WM_NCDESTROY:
		main_wnd->post_nc_destroy();
		break;
	case WM_DESTROY:
		PostQuitMessage (0);
		break;
	case WM_PAINT:
		dc = BeginPaint (hwnd, &ps);
		main_wnd->paint_event (dc);
		EndPaint (hwnd, &ps);
		break;
	case WM_CLOSE:
		main_wnd->close_window();
		break;
	default:
		//�������в����Ƿ�ƥ����Զ�����Ϣ���������ص�����
		//������ϵͳ�Զ�����ȱʡ��Ϣ��
		for(has_custom = false; msg_p; msg_p = msg_p->next){
			if (msg_p->msgid == nmsg) {
				msg_p->msg_cb(wparam, lparam, msg_p->_context);
				has_custom = true;
				break;
			}
		}
		if (!has_custom)
			return DefWindowProc ( hwnd, nmsg, wparam, lparam);
	}
	return 0;
}
/*****************************
 * �ػ�����
 *****************************/
void
MainBaseWnd::invalidate()
{
	HDC dc = GetDC (get_handle());
	redraw(dc);
	ReleaseDC (get_handle(), dc);
}
/*****************************************************************************
 * ����: invalidate_rect
 * ���: rc  �ػ�����
 * ����: ��
 * ����: ��
 * ����: �ػ�ָ������
 * ˵��: 
 *****************************************************************************/
void MainBaseWnd::invalidate_rect(const Rect& rc)
{
	HDC dc = GetDC (get_handle());
	redraw_rect(dc, rc);
	ReleaseDC (get_handle(), dc);
}
/*****************************************************************************
 * ����: destroy
 * ���: none
 * ����: ��
 * ����: ��
 * ����: ���ٴ���,����CLOSE��Ϣ��DESTROY��Ϣ
 * ˵��: 
 *****************************************************************************/
void MainBaseWnd::destroy()
{
	SendMessage(get_handle(), WM_CLOSE, 0, 0);
	SendMessage(get_handle(), WM_DESTROY, 0, 0);
}
#endif
