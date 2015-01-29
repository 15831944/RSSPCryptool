#pragma once
#include "afxwin.h"


// AlgTestDlg �Ի���

class AlgTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AlgTestDlg)

public:
	AlgTestDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AlgTestDlg();

// �Ի�������
	enum { IDD = IDD_ALG_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CComboBox cmb_type;
	CComboBox cmb_name;
	CString cstr_input;
	CString cstr_key;
	CString cstr_enc;
	CString cstr_dec;
public:
	afx_msg void OnBnClickedEnc();
	afx_msg void OnBnClickedDec();
	afx_msg void OnCbnDropdownComboType();
	afx_msg void OnCbnDropdownComboName();
};
