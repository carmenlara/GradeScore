// MenuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GradeScore.h"
#include "MenuDlg.h"
#include "afxdialogex.h"
#include "FachHinzufuegen.h"
#include "DetailAnsicht.h"

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
	ON_BN_CLICKED(IDC_FACH_AUSWAEHLEN, &CMenuDlg::OnBnClickedFachAuswaehlen)
END_MESSAGE_MAP()


// CMenuDlg message handlers


BOOL CMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString gesamtnoteStr;
	double gesamtnote = 0;
	int i = 0;

	m_fachList.InsertColumn(0, "Fach", LVCFMT_LEFT, 200);
	m_fachList.InsertColumn(1, "Note", LVCFMT_LEFT, 100);
	m_fachList.InsertColumn(2, "Note gerundet", LVCFMT_RIGHT, 100);
	m_fachList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE
		| LVS_EX_AUTOSIZECOLUMNS | LVS_EX_JUSTIFYCOLUMNS);

	FaecherHolen();
	NotenHolen();
	LoadListCtrl();

	// Gesamtnote berechnen und Info ausgeben
	for (i = 0; i < m_faecher.size(); i++)
	{
		gesamtnote += GesamtnoteBerechnen(_ttoi (m_faecher[i]["id"]));
	}
	if (i != 0)
	{
		gesamtnote = gesamtnote / m_faecher.size();
		gesamtnote = (double)((int)(gesamtnote * 100)) / 100;
		gesamtnoteStr.Format("%f", gesamtnote);
	}
	else
	{
		gesamtnoteStr = "Noch keine Noten vorhanden";
	}	

	if (m_beschriftung != "")
	{
		m_info = "Aktuelles Schuljahr " + m_jahr + ", Semester " + m_semester +
			"\r\n" + m_beschriftung + "\r\n Gesamtnote: " + gesamtnoteStr;
	}
	else
	{
		m_info = "Aktuelles Schuljahr " + m_jahr + ", Semester " + m_semester +
			"\r\n Gesamtnote: " + gesamtnoteStr;
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}


void CMenuDlg::FaecherHolen()
{
	CRecordset *rec = new CRecordset(m_db);
	CString query = "SELECT * FROM fach WHERE fach.\"fk_sem_id\" = " + m_idSemester, idFachStr, fach;
	int i = 0;
	m_faecher.clear();
	rec->Open(CRecordset::snapshot, query, NULL);
	while (!rec->IsEOF())
	{
		rec->GetFieldValue("fach_id", idFachStr);
		rec->GetFieldValue("fach", fach);
		m_faecher [i] ["id"] = idFachStr;
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
	m_noten.clear();
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
	m_fachList.DeleteAllItems();
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
	double dRet = 0.0;
	double dGesamtGewichtung = 0.0;
	int iOhneGewichtung = 0;
	struct SNote
	{
		double Note;
		double Gewichtung;
	};

	vector<SNote> vecNoten;
	for (int i = 0; i < m_faecher.size(); ++i)
	{
		SNote xNote;
		xNote.Note = atof(m_faecher[i]["note"]);
		xNote.Gewichtung = -1.0;
		if (!m_faecher[i]["Gewichtung"].IsEmpty())
		{
			xNote.Gewichtung = atof(m_faecher[i]["Gewichtung"]) / 100.0;
			dGesamtGewichtung += xNote.Gewichtung;
		}
		else
		{
			++iOhneGewichtung;
		}
		vecNoten.push_back(xNote);
	}

	double dGewichtungÜbriger = (1.0 - dGesamtGewichtung) / iOhneGewichtung;

	for (int i = 0; i < vecNoten.size(); ++i)
	{
		if (vecNoten[i].Gewichtung < 0)
		{
			vecNoten[i].Gewichtung = dGewichtungÜbriger;
			dGesamtGewichtung += dGewichtungÜbriger;
		}
	}

	for (int i = 0; i < vecNoten.size(); ++i)
	{
		dRet += vecNoten[i].Gewichtung * vecNoten[i].Note / dGesamtGewichtung;
	}

	return dRet / vecNoten.size();
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
	OnBnClickedFachAuswaehlen();
	*pResult = 0;
}


void CMenuDlg::OnBnClickedSemesterWechseln()
{
	OnCancel();
}


void CMenuDlg::OnBnClickedFachHinzufuegen()
{
	CFachHinzufuegen dlg;
	if (dlg.DoModal())
	{
		if (dlg.m_okClicked)
		{
			if (dlg.m_fachname != "")
			{
				try
				{
					m_db->ExecuteSQL("INSERT INTO fach (fach_id, fach, fk_sem_id) VALUES");
					FaecherHolen();
					NotenHolen();
					LoadListCtrl();
				}
				catch (CDBException *e)
				{
					MessageBox("Das Fach konnte nicht erfasst werden.", "Error", MB_ICONERROR);
				}
			}
			else
			{
				MessageBox("Bitte geben Sie einen Namen für das neue Fach an.", "Name eingeben", NULL);
				OnBnClickedFachHinzufuegen();
			}
		}
	}
}


void CMenuDlg::OnBnClickedFachAuswaehlen()
{
	CDetailAnsicht dlg;
	if (m_listLine != -1)
	{
		dlg.m_fachid = m_listLine;
		dlg.DoModal();
	}
	else
	{
		AfxMessageBox("Bitte wählen Sie ein Fach aus.");
	}
}


void CMenuDlg::OnBnClickedFachEntfernen()
{
	CString id;
	if (m_listLine != -1)
	{
		id.Format("%d", m_fachList.GetItemData(m_listLine));
		try
		{
			m_db->ExecuteSQL("DELETE FROM fach WHERE fach_id = " + id);
			FaecherHolen();
			NotenHolen();
			m_fachList.DeleteItem(m_listLine);
		}
		catch (CDBException *e)
		{
			AfxMessageBox("Das Fach konnte nicht gelöscht werden.");
		}
	}
}


void CMenuDlg::OnBnClickedGrafischeAnsicht()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}
