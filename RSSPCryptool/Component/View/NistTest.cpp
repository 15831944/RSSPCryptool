// NistTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RSSPCryptool.h"
#include "NistTest.h"
#include "afxdialogex.h"
#include "Component\Evaluation\externs.h"
#include "Component\Evaluation\utilities.h"
#include "Component\Evaluation\Nist_access.h"
#include <string>

using namespace std;

// NistTest �Ի���

IMPLEMENT_DYNAMIC(NistTest, CDialog)

NistTest::NistTest(CWnd* pParent /*=NULL*/)
	: CDialog(NistTest::IDD, pParent)
	, m_NumOfRNG(0)
	, m_LenOfRNG(0)
	, m_blockFrequencyBlockLength(0)
	, m_overlappingTemplateBlockLength(0)
	, m_nonOverlappingTemplateBlockLength(0)
	, m_approximateEntropyBlockLength(0)
	, m_linearComplexitySequenceLength(0)
	, m_serialBlockLength(0)
{

}

NistTest::~NistTest()
{
}

void NistTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUM_OF_RNG, m_NumOfRNG);
	DDX_Text(pDX, IDC_LEN_OF_RNG, m_LenOfRNG);
	DDX_Control(pDX, IDC_RNG_GENERATE, m_RNGGenerate);
	DDX_Text(pDX, IDC_BLOCK_FREQUENCY_BLOCKLENGTH, m_blockFrequencyBlockLength);
	DDX_Text(pDX, IDC_OVERLAPPING_LENGTH, m_overlappingTemplateBlockLength);
	DDX_Text(pDX, IDC_NONOVERLAPPING_LENGTH, m_nonOverlappingTemplateBlockLength);
	DDX_Text(pDX, IDC_APPROXIMATE_LENGTH, m_approximateEntropyBlockLength);
	DDX_Text(pDX, IDC_LINEAR_LENGTH, m_linearComplexitySequenceLength);
	DDX_Text(pDX, IDC_SERIAL_LENGTH, m_serialBlockLength);
	DDX_Control(pDX, IDC_START, m_StartEvaluation);
	DDX_Control(pDX, IDC_SHOW_RESULT, m_ShowResult);
	DDX_Control(pDX, IDC_CHECK1, m_BlockFrequency);
	DDX_Control(pDX, IDC_CHECK2, m_Overlapping);
	DDX_Control(pDX, IDC_CHECK3, m_NonOverlapping);
	DDX_Control(pDX, IDC_CHECK4, m_Approximate);
	DDX_Control(pDX, IDC_CHECK5, m_Linear);
	DDX_Control(pDX, IDC_CHECK6, m_Serial);
	DDX_Control(pDX, IDC_CHECK8, m_Frequency);
	DDX_Control(pDX, IDC_CHECK9, m_LongestRun);
	DDX_Control(pDX, IDC_CHECK10, m_Cumulative);
	DDX_Control(pDX, IDC_CHECK11, m_DFT);
	DDX_Control(pDX, IDC_CHECK12, m_RandomExcursions);
	DDX_Control(pDX, IDC_CHECK13, m_Runs);
	DDX_Control(pDX, IDC_CHECK14, m_Rank);
	DDX_Control(pDX, IDC_CHECK15, m_RandomExcursionsVariant);
	DDX_Control(pDX, IDC_CHECK7, m_Universal);
}


BEGIN_MESSAGE_MAP(NistTest, CDialog)
	ON_BN_CLICKED(IDC_RNG_GENERATE, &NistTest::OnBnClickedRngGenerate)
	ON_BN_CLICKED(IDC_START, &NistTest::OnBnClickedStart)
END_MESSAGE_MAP()


// NistTest ��Ϣ�������


BOOL NistTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	//Ĭ�ϲ�����ʼ��
	m_blockFrequencyBlockLength=128;
	m_overlappingTemplateBlockLength=9;
	m_nonOverlappingTemplateBlockLength=9;
	m_approximateEntropyBlockLength=10;
	m_linearComplexitySequenceLength=500;
	m_serialBlockLength=16;
	UpdateData(false);

	tp.blockFrequencyBlockLength = 128;
	tp.nonOverlappingTemplateBlockLength = 9;
	tp.overlappingTemplateBlockLength = 9;
	tp.approximateEntropyBlockLength = 10;
	tp.serialBlockLength = 16;
	tp.linearComplexitySequenceLength = 500;
	tp.numOfBitStreams = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void NistTest::OnBnClickedRngGenerate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void NistTest::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	InitTestVector();
	ChooseTest();
	SetParameter();
}

//ѡ��������
void NistTest::ChooseTest()
{
	if(m_Frequency.GetCheck())
		testVector[1] = 1;
	if(m_BlockFrequency.GetCheck())
		testVector[2] = 1;
	if(m_Cumulative.GetCheck())
		testVector[3] = 1;
	if(m_Runs.GetCheck())
		testVector[4] = 1;
	if(m_LongestRun.GetCheck())
		testVector[5] = 1;
	if(m_Rank.GetCheck())
		testVector[6] = 1;
	if(m_DFT.GetCheck())
		testVector[7] = 1;
	if(m_NonOverlapping.GetCheck())
		testVector[8] = 1;
	if(m_Overlapping.GetCheck())
		testVector[9] = 1;
	if(m_Universal.GetCheck())
		testVector[10] = 1;
	if(m_Approximate.GetCheck())
		testVector[11] = 1;
	if(m_RandomExcursions.GetCheck())
		testVector[12] = 1;
	if(m_RandomExcursionsVariant.GetCheck())
		testVector[13] = 1;
	if(m_Serial.GetCheck())
		testVector[14] = 1;
	if(m_Linear.GetCheck())
		testVector[15] = 1;
}

//���ò���
void NistTest::SetParameter()
{
	UpdateData(true);
	tp.blockFrequencyBlockLength = m_blockFrequencyBlockLength;
	tp.approximateEntropyBlockLength = m_approximateEntropyBlockLength;
	tp.linearComplexitySequenceLength = m_linearComplexitySequenceLength;
	tp.nonOverlappingTemplateBlockLength = m_nonOverlappingTemplateBlockLength;
	tp.overlappingTemplateBlockLength = m_overlappingTemplateBlockLength;
	tp.serialBlockLength = m_serialBlockLength;
	tp.n = m_LenOfRNG;
	tp.numOfBitStreams = m_NumOfRNG;
}

//ִ������
void NistTest::StartProcess()
{
	option = 0;
	mode = 0;
}
