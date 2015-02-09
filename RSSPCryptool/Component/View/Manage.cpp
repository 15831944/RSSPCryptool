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
	CRect rect;
	lst_AlgInfo.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����
	lst_AlgInfo.SetExtendedStyle(lst_AlgInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//������
	lst_AlgInfo.InsertColumn(0, _T("�㷨����"), LVCFMT_CENTER, rect.Width()*5.5/36,0);
	lst_AlgInfo.InsertColumn(1, _T("�㷨����"), LVCFMT_CENTER, rect.Width()*5.5/36,0);
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
void Manage::showAlgInfoLst(int type){
	//ɾ����ѡ��
	int columns = lst_AlgInfo.GetHeaderCtrl()->GetItemCount();
	//ע����ұߵ��������ɾ
	for(int i = columns-1;i >= 2;i--){
		lst_AlgInfo.DeleteColumn(i);
	}
	//ɾ������������Ŀ
	lst_AlgInfo.DeleteAllItems();
	CRect rect;
	lst_AlgInfo.GetClientRect(&rect);
	//����������������Ŀ
	int row = 0;
	Cipher * alg;
	switch(type){
	case BLOCK:
		lst_AlgInfo.InsertColumn(2,_T("��Կ����/bit"),LVCFMT_CENTER,rect.Width()*5/36,0);
		lst_AlgInfo.InsertColumn(3,_T("���鳤��/bit"),LVCFMT_CENTER,rect.Width()*5/36,0);
		for(int i = 0;i < mng->info->GetSize();i++){
			alg = mng->info->GetAt(i);
			if(alg->AlgType == BLOCK){
				lst_AlgInfo.InsertItem(row,NULL);
				lst_AlgInfo.SetItemText(row,0,"���������㷨");
				lst_AlgInfo.SetItemText(row,1,alg->AlgName);
				lst_AlgInfo.SetItemText(row,2,int2CString(8*alg->key_len));
				lst_AlgInfo.SetItemText(row,3,int2CString(8*alg->block_size));
				row++;
			}
		}
		break;
	case STREAM:
		lst_AlgInfo.InsertColumn(2,_T("��Կ����/bit"),LVCFMT_CENTER,rect.Width()*5/36,0);
		lst_AlgInfo.InsertColumn(3,_T("��ʼ��������/bit"),LVCFMT_CENTER,rect.Width()*7/36,0);
		for(int i = 0;i < mng->info->GetSize();i++){
			alg = mng->info->GetAt(i);
			if(alg->AlgType == STREAM){
				lst_AlgInfo.InsertItem(row,NULL);
				lst_AlgInfo.SetItemText(row,0,"�������㷨");
				lst_AlgInfo.SetItemText(row,1,alg->AlgName);
				lst_AlgInfo.SetItemText(row,2,int2CString(8*alg->key_len));
				lst_AlgInfo.SetItemText(row,3,int2CString(8*alg->iv_len));
				row++;
			}
		}
		break;
	case HASH:
		lst_AlgInfo.InsertColumn(2,_T("ժҪ����/bit"),LVCFMT_CENTER,rect.Width()*5/36, 0);
		for(int i = 0;i < mng->info->GetSize();i++){
			alg = mng->info->GetAt(i);
			if(alg->AlgType == HASH){
				lst_AlgInfo.InsertItem(row,NULL);
				lst_AlgInfo.SetItemText(row,0,"HASH�㷨");
				lst_AlgInfo.SetItemText(row,1,alg->AlgName);
				lst_AlgInfo.SetItemText(row,2,int2CString(8*alg->output_len));
				row++;
			}
		}
		break;
	case MAC:
		lst_AlgInfo.InsertColumn(2,_T("��Կ����/bit"),LVCFMT_CENTER,rect.Width()*5/36,0);
		lst_AlgInfo.InsertColumn(3,_T("��Ϣ��֤�볤��/bit"),LVCFMT_CENTER,rect.Width()*8/36,0);
		for(int i = 0;i < mng->info->GetSize();i++){
			alg = mng->info->GetAt(i);
			if(alg->AlgType == MAC){
				lst_AlgInfo.InsertItem(row,NULL);
				lst_AlgInfo.SetItemText(row,0,"MAC�㷨");
				lst_AlgInfo.SetItemText(row,1,alg->AlgName);
				lst_AlgInfo.SetItemText(row,2,int2CString(8*alg->key_len));
				lst_AlgInfo.SetItemText(row,3,int2CString(8*alg->output_len));
				row++;
			}
		}
		break;
	case RNG:
		lst_AlgInfo.InsertColumn(2,_T("���ӳ���/bit"),LVCFMT_CENTER,rect.Width()*5/36, 0);
		for(int i = 0;i < mng->info->GetSize();i++){
			alg = mng->info->GetAt(i);
			if(alg->AlgType == RNG){
				lst_AlgInfo.InsertItem(row,NULL);
				lst_AlgInfo.SetItemText(row,0,"�����������");
				lst_AlgInfo.SetItemText(row,1,alg->AlgName);
				lst_AlgInfo.SetItemText(row,2,int2CString(8*alg->seed_len));
				row++;
			}
		}
		break;
	default:;
	}
}

//���ߺ���
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
CString Manage::int2CString(int num){
	CString str;
	str.Format("%d",num);
	return str;
}

// Manage �Ի���
IMPLEMENT_DYNAMIC(Manage, CDialogEx)
Manage::Manage(CWnd* pParent /*=NULL*/)
	: CDialogEx(Manage::IDD, pParent)
	, curAlgType(_T(""))
	, curAlgName(_T(""))
	, curAlgMode(_T(""))
	, strDllName(_T(""))
{
	mng = new AlgMng(&dllMng);
}
Manage::~Manage()
{
}
void Manage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALG_TYPE_MNG, cmb_AlgType);
	DDX_Control(pDX, IDC_ALG_NAME_MNG, cmb_AlgName);
	DDX_Control(pDX, IDC_ALG_MODE_MNG, cmb_AlgMode);
	DDX_Control(pDX, IDC_CURR_ALG, sts_CurAlg);
	DDX_Control(pDX, IDC_LST_INFO, lst_AlgInfo);
	DDX_Text(pDX, IDC_FILE_BROSWER, strDllName);
}


BEGIN_MESSAGE_MAP(Manage, CDialogEx)
	ON_CBN_SELCHANGE(IDC_ALG_TYPE_MNG, &Manage::OnCbnSelchangeAlgType)
	ON_BN_CLICKED(IDC_BTN_SWITCH, &Manage::OnBnClickedBtnSwitch)
	ON_BN_CLICKED(IDC_ADD_DLL, &Manage::OnBnClickedAddDll)
END_MESSAGE_MAP()

//��ʼ�������ؼ���״̬
BOOL Manage::OnInitDialog(){
	CDialogEx::OnInitDialog();

	//�㷨�������Ƴ����ֽ���
	initCmbAlgType();
	initCmbAlgMode();
	showCmbAlgName(BLOCK);
	showCurInfo();
	initListControl();
	showAlgInfoLst(BLOCK);
	return TRUE;
}
void Manage::OnCbnSelchangeAlgType(){
	UpdateData();
	int sel = cmb_AlgType.GetCurSel();
	//�㷨���Ͳ��ǡ����������㷨ʱ ����ʾ������ģʽ��������
	if(sel != 0){
		GetDlgItem(IDC_STATIC_MODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ALG_MODE_MNG)->ShowWindow(SW_HIDE);
	}else{
		GetDlgItem(IDC_STATIC_MODE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ALG_MODE_MNG)->ShowWindow(SW_SHOW);
	}

	//���AlgName������
	CString selStr;
	cmb_AlgType.GetLBText(cmb_AlgType.GetCurSel(),selStr);
	showCmbAlgName(typeStr2Int(selStr));
	//��ʾ�����������㷨����Ϣ
	showAlgInfoLst(typeStr2Int(selStr));
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
void Manage::OnBnClickedAddDll(){
	UpdateData();
	if(dllMng.checkDll(strDllName)){
		if(dllMng.addDll(strDllName)){
			dllMng.FreeDlls();
			dllMng.LoadDlls();
			dllMng.getAllCipher();
			OnCbnSelchangeAlgType();
			MessageBox("�㷨Dll�ļ���ӳɹ�","��ӳɹ���ʾ",MB_OK);
		}else{
			MessageBox("�㷨Dll�ļ������Ѿ����ڻ��߳����޷����ʸ��ļ�","DLL�ļ�����ʧ��",MB_OK);
		}
	}else{
		MessageBox("�㷨Dll�ļ������ϸ�ʽ","DLL�ļ���ʽ����",MB_OK);
	}

}
