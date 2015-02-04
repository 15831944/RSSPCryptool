#pragma once
#include "afxwin.h"


// SensitivityTest �Ի���

class SensitivityTest : public CDialogEx
{
	DECLARE_DYNAMIC(SensitivityTest)

public:
	SensitivityTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SensitivityTest();

// �Ի�������
	enum { IDD = IDD_SENSITIVITY_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeAlgType();
	CString m_AlgType;
	CString m_AlgName;
	CString m_AlgMode;
	CString m_TestType;
	int m_TextLen;
	int m_TestTimes;
	CButton m_Test;
	CButton m_Report;
	CComboBox m_Name;
	CComboBox m_Type;
};
