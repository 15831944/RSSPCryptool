#pragma once


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
};
