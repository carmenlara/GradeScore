// DetailAnsicht.cpp : implementation file
//

#include "stdafx.h"
#include "GradeScore.h"
#include "DetailAnsicht.h"
#include "afxdialogex.h"
#include "NoteHinzufuegen.h"

#include <string>
#include <algorithm>

using namespace std;

extern CDatabase *m_db;

// CDetailAnsicht dialog

IMPLEMENT_DYNAMIC(CDetailAnsicht, CDialogEx)

CDetailAnsicht::CDetailAnsicht(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DETAIL_ANSICHT, pParent)
{
	m_listLine = -1;
}

CDetailAnsicht::~CDetailAnsicht()
{
}

void CDetailAnsicht::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NOTEN_UEBERSICHT, m_notenList);
}


BEGIN_MESSAGE_MAP(CDetailAnsicht, CDialogEx)
	ON_BN_CLICKED(IDC_NOTE_HINZUFUEGEN, &CDetailAnsicht::OnBnClickedNoteHinzufuegen)
	ON_BN_CLICKED(IDC_NOTE_ENTFERNEN, &CDetailAnsicht::OnBnClickedNoteEntfernen)
	ON_NOTIFY(NM_CLICK, IDC_NOTEN_UEBERSICHT, &CDetailAnsicht::OnNMClickNotenUebersicht)
	ON_BN_CLICKED(IDC_NOTE_BEARBEITEN, &CDetailAnsicht::OnBnClickedNoteBearbeiten)
	ON_NOTIFY(NM_DBLCLK, IDC_NOTEN_UEBERSICHT, &CDetailAnsicht::OnNMDblclkNotenUebersicht)
END_MESSAGE_MAP()

// CDetailAnsicht message handlers


BOOL CDetailAnsicht::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CImageList il;

	// Tabellenraster
	m_notenList.InsertColumn(0, "Note", LVCFMT_LEFT, 80);
	m_notenList.InsertColumn(1, "Gewichtung", LVCFMT_LEFT, 80);
	m_notenList.InsertColumn(2, "Datum", LVCFMT_LEFT, 80);
	m_notenList.InsertColumn(3, "Beschriftung", LVCFMT_LEFT, 150);
	this->m_notenList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE
		| LVS_EX_AUTOSIZECOLUMNS | LVS_EX_JUSTIFYCOLUMNS);

	il.Create(1, 25, ILC_COLOR, 1, 1);
	m_notenList.SetImageList(&il, LVSIL_SMALL);

	LoadData();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}


void CDetailAnsicht::LoadData()
{
	CRecordset *rec = new CRecordset(m_db);
	CString id, beschriftung, note, datum, gewichtung, query;
	int i = 0;
	std::string noteCut;
	id.Format("%d", m_fachid);
	query = "SELECT * FROM note WHERE fk_fach_id = " + id;
	m_notenList.DeleteAllItems();
	rec->Open(CRecordset::snapshot, query, NULL);
	while (!rec->IsEOF())
	{
		rec->GetFieldValue("note_id", id);
		rec->GetFieldValue("beschriftung", beschriftung);
		rec->GetFieldValue("note", note);
		rec->GetFieldValue("date", datum);
		rec->GetFieldValue("gewichtung", gewichtung);

		double noteD = atof(note);
		int noteGerundet = (int)(noteD * 10);
		note.Format("%d", noteGerundet);
		noteCut = (string)note;
		noteCut = noteCut.substr(0, 1) + "." + noteCut.substr(1, 1);
		note = noteCut.c_str();

		m_notenList.InsertItem(i, note);
		m_notenList.SetItemText(i, 1, gewichtung);
		m_notenList.SetItemText(i, 2, datum);
		m_notenList.SetItemText(i, 3, beschriftung);
		m_notenList.SetItemData(i, (DWORD)_ttoi(id));
		i++;
		rec->MoveNext();
	}
	rec->Close();
}


void CDetailAnsicht::OnBnClickedNoteHinzufuegen()
{
	CNoteHinzufuegen dlg;
	CString note, fachid;
	if (dlg.DoModal())
	{
		if (dlg.m_okClicked)
		{
			if (dlg.m_note != 0.0)
			{
				note.Format("%f", dlg.m_note);
				fachid.Format("%d", m_fachid);
				try
				{
					m_db->ExecuteSQL("INSERT INTO note (note, gewichtung, date, beschriftung, fk_fach_id) VALUES (" + note + ", " + dlg.m_gewichtung + ", '" + dlg.m_dateCTime.Format("%d.%m.%Y") + "', '" + dlg.m_beschriftung + "', " + fachid + ")");
					LoadData();
				}
				catch (CDBException *e)
				{
					AfxMessageBox("Die Note konnte nicht hinzugefügt werden.");
				}
			}
			else
			{
				AfxMessageBox("Bitte geben Sie eine Note ein.");
				OnBnClickedNoteHinzufuegen();
			}
		}
	}
}


void CDetailAnsicht::OnBnClickedNoteBearbeiten()
{
	CNoteHinzufuegen dlg;
	CString id, note, stringDate;
	if (m_listLine != -1)
	{
		id.Format("%d", m_notenList.GetItemData(m_listLine));
		dlg.m_bearbeiten = TRUE;
		dlg.m_note = atof(m_notenList.GetItemText(m_listLine, 0));
		dlg.m_gewichtung = m_notenList.GetItemText(m_listLine, 1);
		dlg.m_beschriftung = m_notenList.GetItemText(m_listLine, 3);

		// string to date conversion
		DATE date;
		stringDate = m_notenList.GetItemText(m_listLine, 2);
		COleDateTime myDtTime;
		myDtTime.ParseDateTime(stringDate);
		SYSTEMTIME sDate;
		myDtTime.GetAsSystemTime(sDate);
		dlg.m_dateCTime = sDate;

		if (dlg.DoModal())
		{
			if (dlg.m_okClicked)
			{
				if (dlg.m_note != NULL || dlg.m_note != 0.0)
				{
					try
					{
						note.Format("%f", dlg.m_note);
						m_db->ExecuteSQL("Update note SET note = " + note + ", gewichtung = " + dlg.m_gewichtung + ", date = '" + dlg.m_dateCTime.Format("%d.%m.%Y") + "', beschriftung = '" + dlg.m_beschriftung + "' WHERE note_id = " + id);
						LoadData();
					}
					catch (CDBException *e)
					{
						AfxMessageBox("Die Note konnte nicht bearbeitet werden. \n" + e->m_strError);
					}
				}
				else
				{
					AfxMessageBox("Bitte geben Sie eine Note ein.");
					OnBnClickedNoteBearbeiten();
				}
			}
		}
	}
	else
	{
		AfxMessageBox("Bitte wählen Sie zuerst eine Note aus, die Sie bearbeiten möchten.");
	}
}


void CDetailAnsicht::OnBnClickedNoteEntfernen()
{
	CString id;
	if (m_listLine != -1)
	{
		const int result = MessageBox("Möchten Sie die Note wirklich löschen?", "Note Löschen", MB_YESNO);
		if (result == IDYES)
		{
			id.Format("%d", m_notenList.GetItemData(m_listLine));
			m_db->ExecuteSQL("DELETE FROM note WHERE note_id = " + id);
			m_notenList.DeleteItem(m_listLine);
			m_listLine = -1;
		}
	}
	else
	{
		AfxMessageBox("Bitte wählen Sie zuerst eine Note aus, die Sie löschen möchten.");
	}
}


void CDetailAnsicht::OnNMClickNotenUebersicht(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	m_listLine = m_notenList.GetSelectionMark();
	m_notenList.SetSelectionMark(-1);
	*pResult = 0;
}


void CDetailAnsicht::OnNMDblclkNotenUebersicht(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnBnClickedNoteBearbeiten();
	*pResult = 0;
}
