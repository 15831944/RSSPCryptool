#pragma once
#include "afxeditbrowsectrl.h"
#include "Component\DllApi\AlgDllApi.h"
#include "Manage.h"

// DllDirSetDlg �Ի���

class DllDirSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DllDirSetDlg)

public:
	DllDirSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DllDirSetDlg();

// �Ի�������
	enum { IDD = IDD_DIR_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CString strDirPath;
	CMFCEditBrowseCtrl eb_DllDirSel;
	Manage *mngDlg;
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDirset();
	afx_msg void OnBnClickedCancelDirset();
};
