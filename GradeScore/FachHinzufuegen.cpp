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
{

}

CFachHinzufuegen::~CFachHinzufuegen()
{
}

void CFachHinzufuegen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFachHinzufuegen, CDialogEx)
END_MESSAGE_MAP()


// CFachHinzufuegen message handlers
