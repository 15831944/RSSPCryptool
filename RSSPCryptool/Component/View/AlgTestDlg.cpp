// AlgTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RSSPCryptool.h"
#include "AlgTestDlg.h"
#include "afxdialogex.h"
#include "../DllApi/AlgDllApi.h"

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
	string text = "�������ϵͳSRTP�������ַ�����";

	AlgDllApi cipher,rng;
	rng.GetDllCipher(RNG,"BBS");
	
	/*�����������*/
	puts("��������ӽ��ܲ���---\n");
	for(int i = 0;i < 21;i++){
		cipher.GetDllCipher(BLOCK,B[i]);
		rng.RunRng(time(NULL),cipher.c->key_len);

		cipher.RunBlock(true,(byte *)text.data(),text.length(),rng.c->output,CBC,(byte *)text.data());

		cipher.c->input = NULL;
		byte * plain = cipher.RunBlock(false,cipher.c->output,text.length(),rng.c->output,CBC,(byte *)text.data());
		cout<<string((char *)plain,cipher.c->input_len)<<endl;
	}
	/*���������*/
	puts("������ӽ��ܲ���---\n");
	for(int i = 0;i <6;i++){
		cipher.GetDllCipher(STREAM,S[i]);
		rng.RunRng(time(NULL),cipher.c->key_len);

		cipher.RunStream(true,(byte *)text.data(),text.length(),rng.c->output,(byte *)text.data());

		cipher.c->input = NULL;
		byte * plain = cipher.RunStream(false,cipher.c->output,text.length(),rng.c->output,(byte *)text.data());
		cout<<string((char *)plain,cipher.c->input_len)<<endl;
	}
	/*Hash����*/
	puts("Hash �㷨����---\n");
	for (int i = 0;i < 18;i++){
		cipher.GetDllCipher(HASH,H[i]);
		AlgDllApi::ShowHex(cipher.RunHash(text),cipher.c->output_len);
	}
	/*��Ϣ��֤��*/
	puts("��Ϣ��֤�����ɲ���---\n");
	for(int i = 0;i < 6;i++){
		cipher.GetDllCipher(MAC,M[i]);
		byte *iv = new byte[cipher.c->iv_len];

		memcpy(iv,rng.RunRng(time(NULL),16),16);

		byte *mac = cipher.RunMac(text,rng.RunRng(time(NULL),cipher.c->key_len),iv);
		AlgDllApi::ShowHex(mac,cipher.c->output_len);

	}
	system("pause");
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
