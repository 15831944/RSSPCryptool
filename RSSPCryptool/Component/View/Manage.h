#pragma once


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
};
