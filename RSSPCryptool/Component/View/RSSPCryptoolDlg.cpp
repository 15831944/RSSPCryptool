
// RSSPCryptoolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RSSPCryptool.h"
#include "RSSPCryptoolDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);//DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRSSPCryptoolDlg �Ի���




CRSSPCryptoolDlg::CRSSPCryptoolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRSSPCryptoolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRSSPCryptoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tab);
}

BEGIN_MESSAGE_MAP(CRSSPCryptoolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CRSSPCryptoolDlg::OnTcnSelchangeTab)
END_MESSAGE_MAP()


// CRSSPCryptoolDlg ��Ϣ�������

BOOL CRSSPCryptoolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	//��ʼ��Tab Control�ؼ�
	m_tab.InsertItem(0, _T("�㷨����"));
	m_tab.InsertItem(1, _T("ѩ��ЧӦ����"));
	m_tab.InsertItem(2, _T("NIST����Բ���"));

	m_manageDlg.Create(IDD_MANAGE,&m_tab);
	m_sensitivityTestDlg.Create(IDD_SENSITIVITY_TEST,&m_tab);
	m_nistTestDlg.Create(IDD_NIST_TEST,&m_tab);

	CRect tabRect;
	m_tab.GetClientRect(&tabRect);
	tabRect.top += 22;
	
	m_manageDlg.MoveWindow(tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height());
	m_sensitivityTestDlg.MoveWindow(tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height());
	m_nistTestDlg.MoveWindow(tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height());

	m_manageDlg.ShowWindow(SW_SHOW);
	m_sensitivityTestDlg.ShowWindow(SW_HIDE);
	m_nistTestDlg.ShowWindow(SW_HIDE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRSSPCryptoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRSSPCryptoolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRSSPCryptoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRSSPCryptoolDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	//Tab��ť�л�ʱ�Ĳ���
	*pResult = 0;
	switch(m_tab.GetCurSel()){
	case 0:
		m_manageDlg.ShowWindow(SW_SHOW);
		m_sensitivityTestDlg.ShowWindow(SW_HIDE);
		m_nistTestDlg.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_manageDlg.ShowWindow(SW_HIDE);
		m_sensitivityTestDlg.ShowWindow(SW_SHOW);
		m_nistTestDlg.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_manageDlg.ShowWindow(SW_HIDE);
		m_sensitivityTestDlg.ShowWindow(SW_HIDE);
		m_nistTestDlg.ShowWindow(SW_SHOW);
		break;
	}
}
