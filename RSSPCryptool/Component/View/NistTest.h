#pragma once


// NistTest �Ի���

class NistTest : public CDialog
{
	DECLARE_DYNAMIC(NistTest)

public:
	NistTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~NistTest();

// �Ի�������
	enum { IDD = IDD_NIST_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
