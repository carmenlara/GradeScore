// Grafik.cpp : implementation file
//

#include "stdafx.h"
#include "GradeScore.h"
#include "Grafik.h"
#include "afxdialogex.h"


// CGrafik dialog

IMPLEMENT_DYNAMIC(CGrafik, CDialogEx)

CGrafik::CGrafik(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GRAFIK, pParent)
{

}

CGrafik::~CGrafik()
{
}

void CGrafik::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGrafik, CDialogEx)
END_MESSAGE_MAP()


// CGrafik message handlers
