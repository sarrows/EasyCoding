#ifndef __DLG_BASE_INCLUDE
#define __DLG_BASE_INCLUDE

#include "config_platform.h"

#ifdef MY_WIN32

//对话框基类
class ECExport Dlgbase
{
public:
	Dlgbase(UINT uid);
	virtual ~Dlgbase(){};
	int do_modal (HINSTANCE hins, HWND hwnd );
	static Dlgbase* get_dlg()
	{
		return _dlg_base_ptr;
	}
	HWND get_hwnd() const { return _dlg_hwnd; }
protected:
	virtual void create(HWND hwnd);
	virtual bool initialize(HWND hwnd);
	virtual void ok();
	virtual void cancel();
	virtual void command(UINT umsg, WORD id);
	virtual void size(int cx, int cy);
	bool set_item_int(int item, long nval);
	bool set_item_uint(int item, unsigned int nval);
	bool set_item_text(int item, const TCHAR* psz);
	int  get_item_int(int item);
	unsigned int  get_item_uint(int item);
	int get_item_text(int item, TCHAR*, int max=1024);
protected:
	HWND     _dlg_hwnd;
private:
	static   LRESULT CALLBACK dlg_proc( HWND, UINT, WPARAM, LPARAM);
	static   Dlgbase * _dlg_base_ptr;
	UINT     _dlg_id;
};
#endif
#endif
