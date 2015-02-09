// AlgTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RSSPCryptool.h"
#include "AlgTestDlg.h"
#include "afxdialogex.h"

//���ߺ���
byte * AlgTestDlg::getRandBytes(CString algName,int size){
	rngAlg->setAlg(RNG,algName);
	return rngAlg->RunCipher(time(0)*time(0),size);
}
void AlgTestDlg::initCmbAlgType(){
	cmb_type.InsertString(0,"���������㷨");
	cmb_type.InsertString(1,"�������㷨");
	cmb_type.InsertString(2,"HASH�㷨");
	cmb_type.InsertString(3,"MAC�㷨");
	cmb_type.InsertString(4,"�����������");
	cmb_type.SetCurSel(0);
}
void AlgTestDlg::initCmbAlgMode(){
	cmb_mode.InsertString(0,"ECB");
	cmb_mode.InsertString(1,"CBC");
	cmb_mode.InsertString(2,"CFB");
	cmb_mode.InsertString(3,"OFB");
	cmb_mode.InsertString(4,"CTR");
	cmb_mode.SetCurSel(0);
}
void AlgTestDlg::showCmbAlgName(int type){
	//�������֮ǰ���ַ���
	cmb_name.ResetContent();
	
	//��ʼ��ȡָ���㷨���͵��㷨����
	int index = 0;
	for(int i = 0;i < rngAlg->info->GetSize();i++){
		if(rngAlg->info->GetAt(i)->AlgType == type){
			cmb_name.InsertString(index,rngAlg->info->GetAt(i)->AlgName);
			index++;
		}
	}
	cmb_name.SetCurSel(0);
}

// AlgTestDlg �Ի���
IMPLEMENT_DYNAMIC(AlgTestDlg, CDialogEx)
AlgTestDlg::AlgTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AlgTestDlg::IDD, pParent)
	, cstr_input(_T("����"))
	, cstr_key(_T("��Կ"))
	, cstr_enc(_T("���ܺ������"))
	, cstr_dec(_T("���ܺ������"))
	, cstr_iv(_T("��ʼ����"))
{
	rngAlg = new AlgMng(&dllMng);
	cipherAlg = new AlgMng(&dllMng);
}
AlgTestDlg::~AlgTestDlg(){

}
void AlgTestDlg::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TYPE, cmb_type);
	DDX_Control(pDX, IDC_COMBO_NAME, cmb_name);
	DDX_Text(pDX, IDC_EDIT_INPUT, cstr_input);
	DDX_Text(pDX, IDC_EDIT_KEY, cstr_key);
	DDX_Text(pDX, IDC_EDIT_ENC, cstr_enc);
	DDX_Text(pDX, IDC_EDIT_DEC, cstr_dec);
	DDX_Text(pDX, IDC_EDIT_DEC2, cstr_iv);
	DDX_Control(pDX, IDC_COMBO_MODE, cmb_mode);
}


BEGIN_MESSAGE_MAP(AlgTestDlg, CDialogEx)
	ON_BN_CLICKED(ID_ENC, &AlgTestDlg::OnBnClickedEnc)
	ON_BN_CLICKED(ID_DEC, &AlgTestDlg::OnBnClickedDec)
	ON_BN_CLICKED(IDC_BTN_GENKEY, &AlgTestDlg::OnBnClickedBtnGenkey)
	ON_BN_CLICKED(ID_BTN_GENIV, &AlgTestDlg::OnBnClickedBtnGeniv)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &AlgTestDlg::OnCbnSelchangeComboType)
END_MESSAGE_MAP()


// AlgTestDlg ��Ϣ�������
void AlgTestDlg::OnBnClickedEnc(){
	UpdateData();
	byte * cipher;
	if(cur_alg_type.Compare("�������㷨") == 0){
		cipher = cipherAlg->RunCipher(true,CString2Byte(cstr_input),
			cstr_input.GetAllocLength(),CString2Byte(cstr_key),
			CString2Byte(cstr_iv));
		cstr_enc = Byte2CString(cipher,cstr_input.GetAllocLength());
	}
	UpdateData(false);
}
void AlgTestDlg::OnBnClickedDec(){
	UpdateData();
	byte * plain;
	if(cur_alg_type.Compare("�������㷨") == 0){
		plain = cipherAlg->RunCipher(false,CString2Byte(cstr_enc),
			cstr_enc.GetAllocLength(),CString2Byte(cstr_key),
			CString2Byte(cstr_iv));
		cstr_dec = Byte2CString(plain,cstr_enc.GetAllocLength());
	}
	UpdateData(false);
}
void AlgTestDlg::OnBnClickedBtnGenkey(){
	cmb_name.GetLBText(cmb_name.GetCurSel(),cur_alg_name);
	cmb_type.GetLBText(cmb_type.GetCurSel(),cur_alg_type);

	cipherAlg->setAlg(Manage::typeStr2Int(cur_alg_type),cur_alg_name);
	int len = cipherAlg->GetLength(KEY_LEN);
	CString randStr = Byte2CString(getRandBytes("BBS",len),len);
	cstr_key = randStr;
	UpdateData(false);
}
void AlgTestDlg::OnBnClickedBtnGeniv(){
	cmb_name.GetLBText(cmb_name.GetCurSel(),cur_alg_name);
	cmb_type.GetLBText(cmb_type.GetCurSel(),cur_alg_type);
	int type = Manage::typeStr2Int(cur_alg_type);
	int len;
	cipherAlg->setAlg(Manage::typeStr2Int(cur_alg_type),cur_alg_name);
	if(type == STREAM) len = cipherAlg->GetLength(IV_LEN);
	else if (type == BLOCK) len = cipherAlg->GetLength(BLOCK_SIZE);
	CString randStr = Byte2CString(getRandBytes("BBS",len),len);
	cstr_iv = randStr;
	UpdateData(false);
}
void AlgTestDlg::OnCbnSelchangeComboType(){
	UpdateData();
	int sel = cmb_type.GetCurSel();
	//�㷨���Ͳ��ǡ����������㷨ʱ ����ʾ������ģʽ��������
	if(sel != 0){
		GetDlgItem(IDC_STAT_MODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_MODE)->ShowWindow(SW_HIDE);
	}else{
		GetDlgItem(IDC_STAT_MODE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_MODE)->ShowWindow(SW_SHOW);
	}

	//���AlgName������
	CString selStr;
	cmb_type.GetLBText(cmb_type.GetCurSel(),selStr);
	showCmbAlgName(Manage::typeStr2Int(selStr));
}


BOOL AlgTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	initCmbAlgType();
	initCmbAlgMode();
	showCmbAlgName(BLOCK);
	return TRUE;
}