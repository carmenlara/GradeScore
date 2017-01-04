// AddSemester.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "GradeScore.h"
#include "AddSemester.h"
#include "afxdialogex.h"

#include <time.h>


// CAddSemester-Dialogfeld

IMPLEMENT_DYNAMIC(CAddSemester, CDialogEx)

CAddSemester::CAddSemester(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEMESTER_ADD, pParent)
	, m_beschriftung(_T(""))
	, m_jahr(CTime(time(0)).GetYear())
	, m_semesterNr(0)
{
	m_okClicked = FALSE;
	m_bearbeiten = FALSE;
}

CAddSemester::~CAddSemester()
{
}

void CAddSemester::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BESCHRIFTUNG, m_beschriftung);
	DDX_Text(pDX, IDC_JAHR, m_jahr);
	DDV_MinMaxInt(pDX, m_jahr, 1900, 3000);
	DDX_Control(pDX, IDC_SEMESTER, m_semester);
}


BEGIN_MESSAGE_MAP(CAddSemester, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddSemester::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_SEMESTER, &CAddSemester::OnSelchangeSemester)
END_MESSAGE_MAP()


// CAddSemester-Meldungshandler

// Button "OK"
void CAddSemester::OnBnClickedOk()
{
	m_okClicked = TRUE;
	CDialogEx::OnOK();
}

// Itemwechsel der ComboBox
void CAddSemester::OnSelchangeSemester()
{
	// Index der ausgewählten Zeile in der ComboBox abfragen
	m_semesterNr = m_semester.GetCurSel();
}


BOOL CAddSemester::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_bearbeiten)
	{
		// Dialogtext ändern
		SetWindowText("Semester bearbeiten");
		if (m_semesterNr == 1)
		{
			m_semester.SetCurSel(0); // Erstes Semester in ComboBox auswählen
			m_semesterNr = 0;
		}
		if (m_semesterNr == 2)
		{
			m_semester.SetCurSel(1); // Zweites Semester in ComboBox auswählen
			m_semesterNr = 1;
		}
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}
