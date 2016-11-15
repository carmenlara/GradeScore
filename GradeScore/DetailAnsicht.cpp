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
	ON_BN_CLICKED(IDC_NOTE_HINZUFUEGEN, &CDetailAnsicht::OnBnClickedNoteHinzufuegen)
	ON_BN_CLICKED(IDC_NOTE_ENTFERNEN, &CDetailAnsicht::OnBnClickedNoteEntfernen)
	ON_BN_CLICKED(IDC_MENU, &CDetailAnsicht::OnBnClickedMenu)
	ON_BN_CLICKED(IDOK, &CDetailAnsicht::OnBnClickedOk)
END_MESSAGE_MAP()


// CDetailAnsicht message handlers


BOOL CDetailAnsicht::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  hier zus�tzliche Initialisierung hinzuf�gen.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zur�ckgeben.
}


void CDetailAnsicht::OnBnClickedNoteHinzufuegen()
{
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
}


void CDetailAnsicht::OnBnClickedNoteEntfernen()
{
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
}


void CDetailAnsicht::OnBnClickedMenu()
{
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
}


void CDetailAnsicht::OnBnClickedOk()
{
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	CDialogEx::OnOK();
}
