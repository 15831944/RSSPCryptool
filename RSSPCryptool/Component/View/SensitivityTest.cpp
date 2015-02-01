// SensitivityTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RSSPCryptool.h"
#include "SensitivityTest.h"
#include "afxdialogex.h"
#include "Component\DllApi\AlgDllApi.h"


// SensitivityTest �Ի���

IMPLEMENT_DYNAMIC(SensitivityTest, CDialogEx)

SensitivityTest::SensitivityTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(SensitivityTest::IDD, pParent)
	, m_AlgType(_T(""))
	, m_AlgName(_T(""))
	, m_AlgMode(_T(""))
	, m_TestType(_T(""))
	, m_TextLen(0)
	, m_TestTimes(0)
{

}

SensitivityTest::~SensitivityTest()
{
}

void SensitivityTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_ALG_TYPE, m_AlgType);
	DDX_CBString(pDX, IDC_ALG_NAME, m_AlgName);
	DDX_CBString(pDX, IDC_ALG_MODE, m_AlgMode);
	DDX_CBString(pDX, IDC_TEST_TYPE, m_TestType);
	DDX_Text(pDX, IDC_TEXT_LEN, m_TextLen);
	DDX_Text(pDX, IDC_TEST_TIMES, m_TestTimes);
	DDX_Control(pDX, IDC_TEST, m_Test);
	DDX_Control(pDX, IDC_REPORT, m_Report);
	DDX_Control(pDX, IDC_ALG_NAME, m_Name);
	DDX_Control(pDX, IDC_ALG_TYPE, m_Type);
}


BEGIN_MESSAGE_MAP(SensitivityTest, CDialogEx)
	ON_CBN_SELCHANGE(IDC_ALG_TYPE, &SensitivityTest::OnCbnSelchangeAlgType)
END_MESSAGE_MAP()


// SensitivityTest ��Ϣ�������




void SensitivityTest::OnCbnSelchangeAlgType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_AlgType.Compare("��������"))  //��ȵ���0 ���ȵ���1
	{
		GetDlgItem(IDC_ALG_MODE)->EnableWindow(FALSE);//���
		GetDlgItem(IDC_STATIC_MODE)->EnableWindow(FALSE);//���	
	}
	else 
	{
		GetDlgItem(IDC_ALG_MODE)->EnableWindow(TRUE);//����
		GetDlgItem(IDC_STATIC_MODE)->EnableWindow(TRUE);//����
	}
	m_Name.ResetContent();
	AlgMng mng(&dllMng);
	for(int i = 0;i < mng.info->GetSize();i++)
	{
		if(mng.info->GetAt(i)->AlgType==(m_Type.GetCurSel()+1))
		m_Name.AddString(mng.info->GetAt(i)->AlgName);
	}
}

