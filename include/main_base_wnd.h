#ifndef __MAIN_BASE_WND_INCLUDE
#define __MAIN_BASE_WND_INCLUDE

/*
file:   main_wnd.h
date:   2005-5-11
by:     liguoqiang
modify: 2005-5-11
desc:
	基于SDK完成主窗口的创建、显示工作，这个类常应作为各种主窗口的基类。
*/

#include "config_platform.h"
#include "rect.h"

#ifdef MY_WIN32

/*自定义消息*/
typedef LRESULT  (WINAPI *Msg_CB)(WPARAM wparam, LPARAM lparam, void*);
struct custom_message_t
{
	UINT   msgid;
	Msg_CB msg_cb;
	void* _context;
	custom_message_t * next;   //下一个自定义消息节点。
};
//主窗口基类
class ECExport MainBaseWnd
{
public:
	MainBaseWnd ();
	virtual ~MainBaseWnd ();
public:
	int  add_custom_msg(UINT msg, Msg_CB, void*);
	void show (int ncmd);    //显示窗体
	HWND get_handle(){return wnd_handler_;}   //返回主窗口句柄
	/*释放窗口*/
	void destroy();
	/*创建窗口实体，create函数是首先应该调用的
	用户可以继承该类，并在类中修改create函数，增加其他功能。
	*/
	virtual int  create (UINT uclsname,
		UINT utitle,
		UINT icon,
		UINT smallicon,
		UINT menu,
		DWORD style,
		int cx,
		int cy);
	virtual void invalidate(); //调用redraw方法完成窗口重画
	virtual void invalidate_rect(const Rect& rc); //重画可见区域
protected:
	/*
	 *窗口绘画函数（虚函数）
	 *虚函数里面不做任何工作，完全由子类完成
	 *派生类可以通过此虚函数完成窗口的绘画
	 */
	virtual void paint_event (HDC dc){};
	/*
	 *窗口事件执行函数（虚函数）
	 *当WM_COMMAND类型的消息触发时调用此函数
	 *event：子窗口事件类型（比如按钮）
	 *id：子窗口ID，通过ID判断消息哪个子窗口
	 */
	virtual void mainwnd_command (WORD event, WORD id, WORD param){}
	/*
	*	释放资源的虚函数
	*/
	virtual void post_nc_destroy(){};
	/*
	*	窗口退出虚函数
	*/
	virtual void close_window(){};
	/*
	*	虚函数，被子类继承完成重画操作
	*/
	virtual void redraw(HDC dc){};
	virtual void redraw_rect(HDC dc, const Rect& rc){};

	HWND    wnd_handler_;    //窗口句柄
private:
	TCHAR   cls_name[128];
	TCHAR   app_title[128];
private:
	static LRESULT CALLBACK wnd_proc ( HWND, UINT, WPARAM, LPARAM );
	custom_message_t     * custom_msg_head_;
};
#endif

#endif
