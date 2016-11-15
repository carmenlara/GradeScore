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

	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}


void CMenuDlg::NotenHolen()
{

}


int CMenuDlg::GesamtnoteBerechnen()
{
	CRecordset *rec = new CRecordset(m_db);
	CString query = "SELECT * FROM fach WHERE fach.\"fk_sem_id\" = " + m_idSemester, idFach, noteStr, gewichtungStr;
	int i = 0;
	int x = 0;
	double summeNoten = 0;
	double gewichtung = 0;
	int noteGerundet = 0;
	int summeGewichtung = 0;
	BOOL hatFachGewichtung = TRUE;
	std::map <int, std::map <CString, CString>> noten;
	rec->Open(CRecordset::snapshot, query, NULL);
	while (!rec->IsEOF())
	{
		rec->GetFieldValue("fach_id", idFach);
		rec->MoveNext();
		m_fachIDs.push_back(idFach);
	}
	rec->Close();
	for (i = 0; i < m_fachIDs.size(); i++)
	{
		noten.clear();
		x = 0;
		hatFachGewichtung = TRUE;
		summeNoten = 0;
		noteGerundet = 0;
		summeGewichtung = 0;
		rec->Open(CRecordset::snapshot, "SELECT * FROM noten WHERE noten.\"fk_fach_id\" = " + m_fachIDs.at(i), NULL);
		while (!rec->IsEOF())
		{
			rec->GetFieldValue("note", noteStr);
			rec->GetFieldValue("gewichtung", gewichtungStr);
			noten[x]["note"] = noteStr;
			noten[x]["gewichtung"] = gewichtungStr;
			if (gewichtungStr == "")
			{
				hatFachGewichtung = FALSE;
				noten[x]["gewichtung"] = "0";
			}
			rec->MoveNext();
		}
		rec->Close();
		if (hatFachGewichtung)
		{
			for (x = 0; x < noten.size(); x++)
			{
				summeGewichtung += _ttoi(noten[x]["gewichtung"]);
			}
			if (summeGewichtung == 100)
			{
				for (x = 0; x < noten.size(); x++)
				{
					gewichtung = ((double)_ttoi(noten[x]["gewichtung"])) / 100;
					summeNoten += gewichtung * atof(noten[x]["note"]);
				}
			}
			else
			{

			}
		}
		else
		{
			for (x = 0; x < noten.size(); x++)
			{
				summeNoten += _ttoi(noten[x]["note"]);
			}
			summeNoten = summeNoten / noten.size();
		}
		noteGerundet = int(summeNoten);
	}
}


void CMenuDlg::OnNMClickModule(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
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
