
// RSSPCryptool.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "RSSPCryptool.h"
#include "Manage.h"
#include "SensitivityTest.h"
#include "RSSPCryptoolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
BEGIN_MESSAGE_MAP(CRSSPCryptoolApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CRSSPCryptoolApp::CRSSPCryptoolApp(){
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

CRSSPCryptoolApp theApp;

BOOL CRSSPCryptoolApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	CShellManager *pShellManager = new CShellManager;
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//ָ��������
	CRSSPCryptoolDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	if(pShellManager != NULL) delete pShellManager;
	return FALSE;
}

