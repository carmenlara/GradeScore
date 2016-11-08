// NoteHinzufuegen.cpp : implementation file
//

#include "stdafx.h"
#include "GradeScore.h"
#include "NoteHinzufuegen.h"
#include "afxdialogex.h"


// CNoteHinzufuegen dialog

IMPLEMENT_DYNAMIC(CNoteHinzufuegen, CDialogEx)

CNoteHinzufuegen::CNoteHinzufuegen(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NOTE_HINZUFUEGEN, pParent)
{

}

CNoteHinzufuegen::~CNoteHinzufuegen()
{
}

void CNoteHinzufuegen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNoteHinzufuegen, CDialogEx)
END_MESSAGE_MAP()


// CNoteHinzufuegen message handlers
