
// RSSPCryptool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "../../resource.h"		// ������


// CRSSPCryptoolApp:
// �йش����ʵ�֣������ RSSPCryptool.cpp
//

class CRSSPCryptoolApp : public CWinApp
{
public:
	CRSSPCryptoolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRSSPCryptoolApp theApp;