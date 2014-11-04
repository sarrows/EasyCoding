
// EasyCoding_Dlg_UT.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "EasyCoding_Dlg_UT.h"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/mfc/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "any_type.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#ifdef DEBUG
#pragma comment(lib, "cppunitd_dll.lib")
#pragma comment(lib, "testrunnerud.lib")
#else
#pragma comment(lib, "cppunit_dll.lib")
#pragma comment(lib, "testrunneru.lib")
#endif


// CEasyCoding_Dlg_UTApp

BEGIN_MESSAGE_MAP(CEasyCoding_Dlg_UTApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CEasyCoding_Dlg_UTApp ����

CEasyCoding_Dlg_UTApp::CEasyCoding_Dlg_UTApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CEasyCoding_Dlg_UTApp ����

CEasyCoding_Dlg_UTApp theApp;


// CEasyCoding_Dlg_UTApp ��ʼ��

BOOL CEasyCoding_Dlg_UTApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//CEasyCoding_Dlg_UTDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	//}
	//else if (nResponse == IDCANCEL)
	//{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	//}

	// ɾ�����洴���� shell ��������
	//if (pShellManager != NULL)
	//{
	//	delete pShellManager;
	//}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�

	CPPUNIT_NS::MfcUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());
	runner.run();

	return FALSE;
}

