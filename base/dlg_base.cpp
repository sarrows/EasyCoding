#ifdef WIN32

#include "dlg_base.h"

Dlgbase * Dlgbase::_dlg_base_ptr = 0;

Dlgbase::Dlgbase(UINT uid)
{
	_dlg_id   = uid;
	_dlg_hwnd = NULL;
	Dlgbase::_dlg_base_ptr = this;
}
//初始化
bool Dlgbase::initialize(HWND hwnd)
{
	_dlg_hwnd = hwnd;
	HWND parent = GetParent(_dlg_hwnd);
	if ( parent )
	{
		RECT rc, rc_this;
		GetClientRect(parent, &rc);
		GetWindowRect(hwnd, &rc_this);
		int parent_w  = rc.right - rc.left;
		int parent_h  = rc.bottom - rc.top;
		int this_w    = rc_this.right - rc_this.left;
		int this_h    = rc_this.bottom - rc_this.top;
		
		int x = rc_this.left + (parent_w - this_w)/2;
		int y = rc_this.top + (parent_h - this_h) / 2;
		MoveWindow( hwnd, x, y, this_w, this_h, TRUE );
	}
	return true;
}
//启动对话框
int Dlgbase::do_modal (HINSTANCE hins, HWND hwnd)
{
	return DialogBox( hins, MAKEINTRESOURCE(_dlg_id), hwnd, (DLGPROC)dlg_proc);
}
//确定退出
void Dlgbase::ok()
{
	if ( _dlg_hwnd )
		EndDialog( _dlg_hwnd, IDOK );
}
//退出取消
void Dlgbase::cancel()
{
	if ( _dlg_hwnd )
		EndDialog( _dlg_hwnd, IDCANCEL );
}

void Dlgbase::create(HWND hwnd)
{
	_dlg_hwnd = hwnd;
}
//事件处理
LRESULT CALLBACK
Dlgbase::dlg_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg)
	{
	case WM_INITDIALOG:
		if ( !Dlgbase::get_dlg()->initialize(hwnd) )
			Dlgbase::get_dlg()->cancel();
		break;
	case WM_CREATE:
		Dlgbase::get_dlg()->create(hwnd);
		break;
	case WM_SIZE:
		Dlgbase::get_dlg()->size(LOWORD(lparam), HIWORD(lparam));
		break;
	case WM_COMMAND:
		Dlgbase::get_dlg()->command( umsg, LOWORD(wparam));
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void Dlgbase::size(int cx, int cy)
{
}

void Dlgbase::command(UINT umsg, WORD id)
{
	switch(id)
	{
	case IDOK:
		ok();
		break;
	case IDCANCEL:
		cancel();
		break;
	default:
		break;
	}
}
bool Dlgbase::set_item_int(int item, long nval)
{
	return SetDlgItemInt(_dlg_hwnd, item, nval, true) ? true : false;
}

bool Dlgbase::set_item_uint(int item, unsigned int nval)
{
	return SetDlgItemInt(_dlg_hwnd, item, nval, false) ? true : false;
}

bool Dlgbase::set_item_text(int item, const TCHAR* psz)
{
	return SetDlgItemText(_dlg_hwnd, item, psz) ? true : false;
}

int  Dlgbase::get_item_int(int item)
{
	return GetDlgItemInt(_dlg_hwnd, item, 0, true);
}

unsigned int Dlgbase::get_item_uint(int item)
{
	return GetDlgItemInt(_dlg_hwnd, item, 0, false);
}

int Dlgbase::get_item_text(int item, TCHAR* pszval, int max)
{
	return GetDlgItemText(_dlg_hwnd, item, pszval, max);
}
#endif
