#ifndef __MAIN_BASE_WND_INCLUDE
#define __MAIN_BASE_WND_INCLUDE

/*
file:   main_wnd.h
date:   2005-5-11
by:     liguoqiang
modify: 2005-5-11
desc:
	����SDK��������ڵĴ�������ʾ����������ೣӦ��Ϊ���������ڵĻ��ࡣ
*/

#include "config_platform.h"
#include "rect.h"

#ifdef MY_WIN32

/*�Զ�����Ϣ*/
typedef LRESULT  (WINAPI *Msg_CB)(WPARAM wparam, LPARAM lparam, void*);
struct custom_message_t
{
	UINT   msgid;
	Msg_CB msg_cb;
	void* _context;
	custom_message_t * next;   //��һ���Զ�����Ϣ�ڵ㡣
};
//�����ڻ���
class ECExport MainBaseWnd
{
public:
	MainBaseWnd ();
	virtual ~MainBaseWnd ();
public:
	int  add_custom_msg(UINT msg, Msg_CB, void*);
	void show (int ncmd);    //��ʾ����
	HWND get_handle(){return wnd_handler_;}   //���������ھ��
	/*�ͷŴ���*/
	void destroy();
	/*��������ʵ�壬create����������Ӧ�õ��õ�
	�û����Լ̳и��࣬���������޸�create�����������������ܡ�
	*/
	virtual int  create (UINT uclsname,
		UINT utitle,
		UINT icon,
		UINT smallicon,
		UINT menu,
		DWORD style,
		int cx,
		int cy);
	virtual void invalidate(); //����redraw������ɴ����ػ�
	virtual void invalidate_rect(const Rect& rc); //�ػ��ɼ�����
protected:
	/*
	 *���ڻ滭�������麯����
	 *�麯�����治���κι�������ȫ���������
	 *���������ͨ�����麯����ɴ��ڵĻ滭
	 */
	virtual void paint_event (HDC dc){};
	/*
	 *�����¼�ִ�к������麯����
	 *��WM_COMMAND���͵���Ϣ����ʱ���ô˺���
	 *event���Ӵ����¼����ͣ����簴ť��
	 *id���Ӵ���ID��ͨ��ID�ж���Ϣ�ĸ��Ӵ���
	 */
	virtual void mainwnd_command (WORD event, WORD id, WORD param){}
	/*
	*	�ͷ���Դ���麯��
	*/
	virtual void post_nc_destroy(){};
	/*
	*	�����˳��麯��
	*/
	virtual void close_window(){};
	/*
	*	�麯����������̳�����ػ�����
	*/
	virtual void redraw(HDC dc){};
	virtual void redraw_rect(HDC dc, const Rect& rc){};

	HWND    wnd_handler_;    //���ھ��
private:
	TCHAR   cls_name[128];
	TCHAR   app_title[128];
private:
	static LRESULT CALLBACK wnd_proc ( HWND, UINT, WPARAM, LPARAM );
	custom_message_t     * custom_msg_head_;
};
#endif

#endif
