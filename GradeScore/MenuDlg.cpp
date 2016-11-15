// MenuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GradeScore.h"
#include "MenuDlg.h"
#include "afxdialogex.h"

#include <string>
#include <vector>
#include <map>
#include <stdlib.h>

using namespace std;

extern CDatabase *m_db;
// CMenuDlg dialog

IMPLEMENT_DYNAMIC(CMenuDlg, CDialogEx)

CMenuDlg::CMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MENU, pParent)
	, m_info(_T(""))
{

}

CMenuDlg::~CMenuDlg()
{
}

void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODULE, m_fachList);
	DDX_Text(pDX, IDC_INFO_SEMESTER_JAHR_TEXT_GESAMMTNOTE, m_info);
}


BEGIN_MESSAGE_MAP(CMenuDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_MODULE, &CMenuDlg::OnNMClickModule)
	ON_NOTIFY(NM_DBLCLK, IDC_MODULE, &CMenuDlg::OnNMDblclkModule)
	ON_BN_CLICKED(IDC_SEMESTER_WECHSELN, &CMenuDlg::OnBnClickedSemesterWechseln)
	ON_BN_CLICKED(IDC_FACH_HINZUFUEGEN, &CMenuDlg::OnBnClickedFachHinzufuegen)
	ON_BN_CLICKED(IDC_FACH_ENTFERNEN, &CMenuDlg::OnBnClickedFachEntfernen)
	ON_BN_CLICKED(IDC_GRAFISCHE_ANSICHT, &CMenuDlg::OnBnClickedGrafischeAnsicht)
END_MESSAGE_MAP()


// CMenuDlg message handlers


BOOL CMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_fachList.InsertColumn(0, "Fach", LVCFMT_LEFT, 200);
	m_fachList.InsertColumn(0, "Note", LVCFMT_RIGHT, 100);
	m_fachList.InsertColumn(0, "Note gerundet", LVCFMT_RIGHT, 100);
	m_fachList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE
		| LVS_EX_AUTOSIZECOLUMNS | LVS_EX_JUSTIFYCOLUMNS);

	FaecherHolen();
	NotenHolen();
	LoadListCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}


void CMenuDlg::FaecherHolen()
{
	CRecordset *rec = new CRecordset(m_db);
	CString query = "SELECT * FROM fach WHERE fach.\"fk_sem_id\" = " + m_idSemester, idFachStr, fach;
	int idFach = 0;
	int i = 0;
	rec->Open(CRecordset::snapshot, query, NULL);
	while (!rec->IsEOF())
	{
		rec->GetFieldValue("fach_id", idFachStr);
		rec->GetFieldValue("fach", fach);
		idFach = _ttoi(idFachStr);
		m_faecher [i] ["id"] = fach;
		m_faecher [i] ["fach"] = fach;
		rec->MoveNext();
		i++;
	}
	rec->Close();
}


void CMenuDlg::NotenHolen()
{
	CRecordset *rec = new CRecordset(m_db);
	CString idFachStr, noteStr, gewichtungStr;
	int i = 0;
	int fachid = 0;
	for (i = 0; i < m_faecher.size(); i++)
	{
		m_noten.clear();
		rec->Open(CRecordset::snapshot, "SELECT * FROM noten WHERE noten.\"fk_fach_id\" = " + m_faecher [i] ["id"], NULL);
		while (!rec->IsEOF())
		{
			rec->GetFieldValue("fach_id", idFachStr);
			rec->GetFieldValue("note", noteStr);
			rec->GetFieldValue("gewichtung", gewichtungStr);
			fachid = _ttoi(idFachStr);
			m_noten[fachid]["note"] = noteStr;
			m_noten[fachid]["gewichtung"] = gewichtungStr;
			rec->MoveNext();
		}
		rec->Close();
	}
}


void CMenuDlg::LoadListCtrl()
{
	int i = 0;
	double note = 0.0;
	CString noteStr, notegerundetStr;
	for (i = 0; i < m_faecher.size(); i++)
	{
		note = GesamtnoteBerechnen(_ttoi(m_faecher[i]["id"]));
		noteStr.Format("%d", note);
		notegerundetStr.Format("%d", (int)note);
		m_fachList.InsertItem(i, m_faecher[i]["fach"]);
		m_fachList.SetItemText(i, 1, noteStr);
		m_fachList.SetItemText(i, 1, notegerundetStr);
		m_fachList.SetItemData(i, (DWORD)_ttoi(m_faecher[i]["id"]));
	}
	UpdateData(FALSE);
}


double CMenuDlg::GesamtnoteBerechnen(int fachid)
{
	return 0;
}


void CMenuDlg::OnNMClickModule(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	m_listLine = m_fachList.GetSelectionMark();
	m_fachList.SetSelectionMark(-1);
	*pResult = 0;
}


void CMenuDlg::OnNMDblclkModule(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	*pResult = 0;
}


void CMenuDlg::OnBnClickedSemesterWechseln()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}


void CMenuDlg::OpenFachAnsicht()
{
	
}


void CMenuDlg::OnBnClickedFachHinzufuegen()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}


void CMenuDlg::OnBnClickedFachEntfernen()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}


void CMenuDlg::OnBnClickedGrafischeAnsicht()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}
