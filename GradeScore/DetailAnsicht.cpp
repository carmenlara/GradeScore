// DetailAnsicht.cpp : implementation file
//

#include "stdafx.h"
#include "GradeScore.h"
#include "DetailAnsicht.h"
#include "afxdialogex.h"


// CDetailAnsicht dialog

IMPLEMENT_DYNAMIC(CDetailAnsicht, CDialogEx)

CDetailAnsicht::CDetailAnsicht(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DETAIL_ANSICHT, pParent)
{

}

CDetailAnsicht::~CDetailAnsicht()
{
}

void CDetailAnsicht::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDetailAnsicht, CDialogEx)
END_MESSAGE_MAP()


// CDetailAnsicht message handlers
