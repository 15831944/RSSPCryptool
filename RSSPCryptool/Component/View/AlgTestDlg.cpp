// AlgTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RSSPCryptool.h"
#include "AlgTestDlg.h"
#include "afxdialogex.h"

// AlgTestDlg �Ի���

IMPLEMENT_DYNAMIC(AlgTestDlg, CDialogEx)

AlgTestDlg::AlgTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AlgTestDlg::IDD, pParent)
	, cstr_input(_T("����"))
	, cstr_key(_T("��Կ"))
	, cstr_enc(_T("���ܺ������"))
	, cstr_dec(_T("���ܺ������"))
{

}

AlgTestDlg::~AlgTestDlg()
{
}

void AlgTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, cmb_type);
	DDX_Control(pDX, IDC_COMBO_NAME, cmb_name);
	DDX_Text(pDX, IDC_EDIT_INPUT, cstr_input);
	DDX_Text(pDX, IDC_EDIT_KEY, cstr_key);
	DDX_Text(pDX, IDC_EDIT_ENC, cstr_enc);
	DDX_Text(pDX, IDC_EDIT_DEC, cstr_dec);
}


BEGIN_MESSAGE_MAP(AlgTestDlg, CDialogEx)
	ON_BN_CLICKED(ID_ENC, &AlgTestDlg::OnBnClickedEnc)
	ON_BN_CLICKED(ID_DEC, &AlgTestDlg::OnBnClickedDec)
	ON_CBN_DROPDOWN(IDC_COMBO_TYPE, &AlgTestDlg::OnCbnDropdownComboType)
	ON_CBN_DROPDOWN(IDC_COMBO_NAME, &AlgTestDlg::OnCbnDropdownComboName)
END_MESSAGE_MAP()


// AlgTestDlg ��Ϣ�������


void AlgTestDlg::OnBnClickedEnc()
{
	
}


void AlgTestDlg::OnBnClickedDec()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void AlgTestDlg::OnCbnDropdownComboType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void AlgTestDlg::OnCbnDropdownComboName()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
