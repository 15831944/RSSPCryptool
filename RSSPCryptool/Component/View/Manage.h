#pragma once
#include "afxwin.h"
#include "Component/DllApi/AlgDllApi.h"

// Manage �Ի���

class Manage : public CDialogEx
{
	DECLARE_DYNAMIC(Manage)

public:
	Manage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Manage();

// �Ի�������
	enum { IDD = IDD_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	AlgMng * mng;
	CComboBox cmb_AlgType;
	CComboBox cmb_AlgName;
	CComboBox cmb_AlgMode;
	CString curAlgType;
	CString curAlgName;
	CString curAlgMode;
	CStatic sts_CurAlg;


	void initCmbAlgType();
	void initCmbAlgMode();
	void initListControl();
	void showCmbAlgName(int mode);
	void showCurInfo();

	int modeStr2Int(CString strMode);
	int typeStr2Int(CString strType);

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSwitch();
	afx_msg void OnCbnSelchangeAlgType();
};
