
// RSSPCryptoolDlg.h : ͷ�ļ�
//


#pragma once
#include "afxcmn.h"
#include "Manage.h"
#include "AlgTestDlg.h"
#include "SensitivityTest.h"
#include "NistTest.h"

// CRSSPCryptoolDlg �Ի���
class CRSSPCryptoolDlg : public CDialogEx
{
// ����
public:
	CRSSPCryptoolDlg(CWnd* pParent = NULL);	// ��׼���캯��
	Manage m_manageDlg;
	AlgTestDlg m_algTestDlg;
	SensitivityTest m_sensitivityTestDlg;
	NistTest m_nistTestDlg;

// �Ի�������
	enum { IDD = IDD_RSSPCRYPTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAboutMenu();
	afx_msg void OnDirSet();
};
