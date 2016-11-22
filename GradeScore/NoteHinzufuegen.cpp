// NoteHinzufuegen.cpp : implementation file
//

#include "stdafx.h"
#include "GradeScore.h"
#include "NoteHinzufuegen.h"
#include "afxdialogex.h"

#include <string>
#include <algorithm>

using namespace std;

// CNoteHinzufuegen dialog

IMPLEMENT_DYNAMIC(CNoteHinzufuegen, CDialogEx)

CNoteHinzufuegen::CNoteHinzufuegen(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NOTE_HINZUFUEGEN, pParent)
	, m_dateCTime(0)
	, m_beschriftung(_T(""))
	, m_note(0)
	, m_gewichtung(_T(""))
{
	m_okClicked = FALSE;
	m_gewichtungOK = FALSE;
	m_bearbeiten = FALSE;
}

CNoteHinzufuegen::~CNoteHinzufuegen()
{
}

void CNoteHinzufuegen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_dateCTime);
	DDX_Text(pDX, IDC_EDIT1, m_beschriftung);
	DDX_Text(pDX, IDC_EDIT2, m_note);
	DDV_MinMaxDouble(pDX, m_note, 0, 6);
	DDX_Text(pDX, IDC_EDIT3, m_gewichtung);
}


BEGIN_MESSAGE_MAP(CNoteHinzufuegen, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNoteHinzufuegen::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CNoteHinzufuegen::OnKillfocusEditGewichtung)
END_MESSAGE_MAP()


// CNoteHinzufuegen message handlers


void CNoteHinzufuegen::OnBnClickedOk()
{
	if (!m_gewichtungOK)
	{
		m_okClicked = TRUE;
		CDialogEx::OnOK();
	}
}


void CNoteHinzufuegen::OnKillfocusEditGewichtung()
{
	if (m_gewichtung != "")
	{
		string gwt = (string)m_gewichtung;
		int digit = 0;
		if ((std::find(gwt.begin(), gwt.end(), ".") == gwt.end()) && (std::find(gwt.begin(), gwt.end(), ",") == gwt.end()))
		{
			digit = _ttoi(m_gewichtung);
			if (digit < 0 || digit > 100)
			{
				AfxMessageBox("Bitte geben Sie eine Gewichtung zwischen 0 und 100% ein");
			}
			else
			{
				m_gewichtungOK = TRUE;
			}
		}
		else
		{
			AfxMessageBox("Bitte geben Sie eine ganze Zahl ohne Sonderzeichen ein.");
		}
	}
	else
	{
		m_gewichtungOK = TRUE;
	}
}


BOOL CNoteHinzufuegen::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_bearbeiten)
	{
		SetWindowTextA("Note bearbeiten");
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zur�ckgeben.
}
