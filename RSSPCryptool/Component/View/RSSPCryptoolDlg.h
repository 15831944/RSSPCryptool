
// RSSPCryptoolDlg.h : ͷ�ļ�
//


#pragma once
#include "afxcmn.h"
#include "Manage.h"
#include "SensitivityTest.h"

// CRSSPCryptoolDlg �Ի���
class CRSSPCryptoolDlg : public CDialogEx
{
// ����
public:
	CRSSPCryptoolDlg(CWnd* pParent = NULL);	// ��׼���캯��
	Manage m_manageDlg;
	SensitivityTest m_sensitivityTestDlg;

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
};
