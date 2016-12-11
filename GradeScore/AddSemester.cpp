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

	m_semester.SetCurSel(0);
}


BEGIN_MESSAGE_MAP(CAddSemester, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddSemester::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_SEMESTER, &CAddSemester::OnSelchangeSemester)
END_MESSAGE_MAP()


// CAddSemester-Meldungshandler


void CAddSemester::OnBnClickedOk()
{
	m_okClicked = TRUE;
	CDialogEx::OnOK();
}


void CAddSemester::OnSelchangeSemester()
{
	m_semesterNr = m_semester.GetCurSel();
}
