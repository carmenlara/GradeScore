// FachHinzufuegen.cpp : implementation file
//

#include "stdafx.h"
#include "GradeScore.h"
#include "FachHinzufuegen.h"
#include "afxdialogex.h"


// CFachHinzufuegen dialog

IMPLEMENT_DYNAMIC(CFachHinzufuegen, CDialogEx)

CFachHinzufuegen::CFachHinzufuegen(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FACH_HINZUFUEGEN, pParent)
	, m_fachname(_T(""))
{
	m_okClicked = FALSE;
}

CFachHinzufuegen::~CFachHinzufuegen()
{
}

void CFachHinzufuegen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FACH_BEZEICHNUNG, m_fachname);
}


BEGIN_MESSAGE_MAP(CFachHinzufuegen, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFachHinzufuegen::OnBnClickedOk)
END_MESSAGE_MAP()


// CFachHinzufuegen message handlers


void CFachHinzufuegen::OnBnClickedOk()
{
	m_okClicked = TRUE;
	CDialogEx::OnOK();
}
