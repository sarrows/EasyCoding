
// EasyCoding_Dlg_UT.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEasyCoding_Dlg_UTApp:
// �йش����ʵ�֣������ EasyCoding_Dlg_UT.cpp
//

class CEasyCoding_Dlg_UTApp : public CWinApp
{
public:
	CEasyCoding_Dlg_UTApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEasyCoding_Dlg_UTApp theApp;