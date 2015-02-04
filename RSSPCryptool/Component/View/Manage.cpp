// Manage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RSSPCryptool.h"
#include "Manage.h"
#include "afxdialogex.h"

//���ƿؼ�������ʾ����
void Manage::initCmbAlgType(){
	cmb_AlgType.InsertString(0,"���������㷨");
	cmb_AlgType.InsertString(1,"�������㷨");
	cmb_AlgType.InsertString(2,"HASH�㷨");
	cmb_AlgType.InsertString(3,"MAC�㷨");
	cmb_AlgType.InsertString(4,"�����������");
	cmb_AlgType.SetCurSel(0);
}
void Manage::initCmbAlgMode(){
	cmb_AlgMode.InsertString(0,"ECB");
	cmb_AlgMode.InsertString(1,"CBC");
	cmb_AlgMode.InsertString(2,"CFB");
	cmb_AlgMode.InsertString(3,"OFB");
	cmb_AlgMode.InsertString(4,"CTR");
	cmb_AlgMode.SetCurSel(0);
}
void Manage::initListControl(){
	
}
void Manage::showCmbAlgName(int mode){
	//�������֮ǰ���ַ���
	cmb_AlgName.ResetContent();
	
	//��ʼ��ȡָ���㷨���͵��㷨����
	int index = 0;
	for(int i = 0;i < mng->info->GetSize();i++){
		if(mng->info->GetAt(i)->AlgType == mode){
			cmb_AlgName.InsertString(index,mng->info->GetAt(i)->AlgName);
			index++;
		}
	}
	cmb_AlgName.SetCurSel(0);
}
void Manage::showCurInfo(){
	CString strCfg = "���������㷨:";
	strCfg.Append(mng->GetCurrCfg(CURR_BLOCK));
	strCfg.AppendChar(',');
	strCfg.Append("����ģʽ:");
	strCfg.Append(mng->GetCurrCfg(CURR_MODE));
	strCfg.AppendChar(',');
	strCfg.Append("�������㷨:");
	strCfg.Append(mng->GetCurrCfg(CURR_STREAM));
	strCfg.AppendChar(',');
	strCfg.Append("HASH�㷨:");
	strCfg.Append(mng->GetCurrCfg(CURR_HASH));
	strCfg.AppendChar(',');
	strCfg.Append("MAC�㷨:");
	strCfg.Append(mng->GetCurrCfg(CURR_MAC));
	strCfg.AppendChar(',');
	strCfg.Append("�����������:");
	strCfg.Append(mng->GetCurrCfg(CURR_RNG));
	strCfg.AppendChar('.');
	sts_CurAlg.SetWindowTextA(strCfg);
}

//��������
int Manage::modeStr2Int(CString strMode){
	if(strMode.Compare("ECB") == 0) return ECB;
	else if(strMode.Compare("CBC") == 0) return CBC;
	else if(strMode.Compare("CFB") == 0) return CFB;
	else if(strMode.Compare("OFB") == 0) return OFB;
	else if(strMode.Compare("CTR") == 0) return CTR;
	else return -1;
}
int Manage::typeStr2Int(CString strType){
	if(strType.Compare("���������㷨") == 0) return BLOCK;
	else if(strType.Compare("�������㷨") == 0) return STREAM;
	else if(strType.Compare("HASH�㷨") == 0) return HASH;
	else if(strType.Compare("MAC�㷨") == 0) return MAC;
	else if(strType.Compare("�����������") == 0) return RNG;
	else return -1;
}


// Manage �Ի���
IMPLEMENT_DYNAMIC(Manage, CDialogEx)
Manage::Manage(CWnd* pParent /*=NULL*/)
	: CDialogEx(Manage::IDD, pParent)
	, curAlgType(_T(""))
	, curAlgName(_T(""))
	, curAlgMode(_T(""))
{
	mng = new AlgMng(&dllMng);
}
Manage::~Manage()
{
}
void Manage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALG_TYPE, cmb_AlgType);
	DDX_Control(pDX, IDC_ALG_NAME, cmb_AlgName);
	DDX_Control(pDX, IDC_ALG_MODE, cmb_AlgMode);
	DDX_Control(pDX, IDC_CURR_ALG, sts_CurAlg);
}


BEGIN_MESSAGE_MAP(Manage, CDialogEx)
	ON_CBN_SELCHANGE(IDC_ALG_TYPE, &Manage::OnCbnSelchangeAlgType)
	ON_BN_CLICKED(IDC_BTN_SWITCH, &Manage::OnBnClickedBtnSwitch)
END_MESSAGE_MAP()

//��ʼ�������ؼ���״̬
BOOL Manage::OnInitDialog(){
	CDialogEx::OnInitDialog();

	//�㷨�������Ƴ����ֽ���
	initCmbAlgType();
	initCmbAlgMode();
	showCmbAlgName(BLOCK);
	showCurInfo();
	return TRUE;
}
void Manage::OnCbnSelchangeAlgType(){
	UpdateData();
	int sel = cmb_AlgType.GetCurSel();
	//�㷨���Ͳ��ǡ����������㷨ʱ ����ʾ������ģʽ��������
	if(sel != 0){
		GetDlgItem(IDC_STATIC_MODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ALG_MODE)->ShowWindow(SW_HIDE);
	}else{
		GetDlgItem(IDC_STATIC_MODE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ALG_MODE)->ShowWindow(SW_SHOW);
	}

	//���AlgName������
	CString selStr;
	cmb_AlgType.GetLBText(cmb_AlgType.GetCurSel(),selStr);
	showCmbAlgName(typeStr2Int(selStr));
}
void Manage::OnBnClickedBtnSwitch(){
	//��ȡ��ǰѡ����Ϣ
	cmb_AlgType.GetLBText(cmb_AlgType.GetCurSel(),curAlgType);
	cmb_AlgName.GetLBText(cmb_AlgName.GetCurSel(),curAlgName);
	cmb_AlgMode.GetLBText(cmb_AlgMode.GetCurSel(),curAlgMode);
	int curr_type = typeStr2Int(curAlgType);
	//ȷ���Ƿ�Ҫ�л�
	CString tip = "ȷ��Ҫ�л����㷨";
	tip.Append(curAlgName);
	if(curr_type == BLOCK){
		tip.Append("����ʹ��");
		tip.Append(curAlgMode);
		tip.Append("ģʽ");
	}
	tip.Append("��");
	int responce = MessageBox(tip,"�㷨�л�ȷ��",MB_OKCANCEL);
	if(responce != IDOK) return;

	//�޸ĵ�ǰ�㷨��Ϣ
	mng->SetCurrCfg(curr_type,curAlgName);
	if(curr_type == BLOCK) mng->SetCurrCfg(CURR_MODE,curAlgMode);
	
	//���¡���ǰʹ���㷨��������������
	showCurInfo();
	//��ʾ�л��ɹ�
	MessageBox("�㷨�л��ɹ�","�л��ɹ���ʾ",MB_OK);
}
