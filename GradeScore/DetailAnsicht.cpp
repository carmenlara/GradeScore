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

	// Tabellenraster erstellen
	m_notenList.InsertColumn(0, "Note", LVCFMT_LEFT, 80);
	m_notenList.InsertColumn(1, "Gewichtung", LVCFMT_LEFT, 80);
	m_notenList.InsertColumn(2, "Datum", LVCFMT_LEFT, 80);
	m_notenList.InsertColumn(3, "Beschriftung", LVCFMT_LEFT, 150);
	this->m_notenList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE
		| LVS_EX_AUTOSIZECOLUMNS | LVS_EX_JUSTIFYCOLUMNS);

	// Zeilenhöhe anpassen
	il.Create(1, 25, ILC_COLOR, 1, 1);
	m_notenList.SetImageList(&il, LVSIL_SMALL);

	// Daten in Tabelle laden
	LoadData();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

// Daten in Tabelle laden
void CDetailAnsicht::LoadData()
{
	CRecordset *rec = new CRecordset(m_db);
	CString id, beschriftung, note, datum, gewichtung, query;
	int i = 0;
	std::string noteCut;
	id.Format("%d", m_fachid);
	query = "SELECT * FROM note WHERE fk_fach_id = " + id;
	// Tabelleninhalt löschen
	m_notenList.DeleteAllItems();
	// Tabelle öffnen
	rec->Open(CRecordset::snapshot, query, NULL);
	while (!rec->IsEOF())
	{
		// Daten des aktuellen Datensatzes in Variablen speichern
		rec->GetFieldValue("note_id", id);
		rec->GetFieldValue("beschriftung", beschriftung);
		rec->GetFieldValue("note", note);
		rec->GetFieldValue("date", datum);
		rec->GetFieldValue("gewichtung", gewichtung);

		// Note runden
		double noteD = atof(note);
		int noteGerundet = (int)(noteD * 10);
		note.Format("%d", noteGerundet);
		noteCut = (string)note;
		noteCut = noteCut.substr(0, 1) + "." + noteCut.substr(1, 1);
		note = noteCut.c_str();

		// Gespeicherte Daten in Tabelle ausgegeben
		m_notenList.InsertItem(i, note);
		m_notenList.SetItemText(i, 1, gewichtung);
		m_notenList.SetItemText(i, 2, datum);
		m_notenList.SetItemText(i, 3, beschriftung);
		m_notenList.SetItemData(i, (DWORD)_ttoi(id));
		i++;
		// Zu nächsten Datensatz wechseln
		rec->MoveNext();
	}
	rec->Close(); // Tabelle schliessen
}

// Note hinzufügen
void CDetailAnsicht::OnBnClickedNoteHinzufuegen()
{
	CNoteHinzufuegen dlg;
	CString note, fachid;
	// Dialog von CNoteHinzufuegen öffnen
	if (dlg.DoModal())
	{
		if (dlg.m_okClicked) // Wurde auf "OK" geklickt?
		{
			if (dlg.m_note != 0.0) // Wurde eine Note eingegeben?
			{
				// Note und Fach ID konvertieren
				note.Format("%f", dlg.m_note);
				fachid.Format("%d", m_fachid);
				try
				{
					// SQL Query erstellen um Note in DB hinzu zufügen
					string sql;
					sql = "INSERT INTO note (note";
					sql += dlg.m_gewichtung == "" ? "" : ", gewichtung";
					sql += ", date";
					sql += dlg.m_beschriftung == "" ? "" : ", beschriftung";
					sql += ", fk_fach_id) VALUES(" + note;
					sql += dlg.m_gewichtung == "" ? "" : ", " + dlg.m_gewichtung;
					sql += ", '" + dlg.m_dateCTime.Format("%d.%m.%Y") + "'";
					sql += dlg.m_beschriftung == "" ? "" : ", '" + dlg.m_beschriftung + "'";
					sql += ", " + fachid + ")";

					// Note in DB speichern
					m_db->ExecuteSQL(sql.c_str());
					LoadData(); // Tabelle updaten
				}
				catch (CDBException *e)
				{
					// Konte die Note nicht hinzugefügt werden, Fehlermeldung ausgeben
					AfxMessageBox("Die Note konnte nicht hinzugefügt werden. \n" + e->m_strError);
				}
			}
			else
			{
				// Wurde keine Note eingegeben, Fehlermeldung ausgeben
				AfxMessageBox("Bitte geben Sie eine Note ein.");
				OnBnClickedNoteHinzufuegen();
			}
		}
	}
}

// Note bearbeiten
void CDetailAnsicht::OnBnClickedNoteBearbeiten()
{
	CNoteHinzufuegen dlg;
	CString id, note, stringDate;
	if (m_listLine != -1)
	{
		// Dialog mit Daten füllen
		id.Format("%d", m_notenList.GetItemData(m_listLine));
		dlg.m_bearbeiten = TRUE;
		dlg.m_note = atof(m_notenList.GetItemText(m_listLine, 0));
		dlg.m_gewichtung = m_notenList.GetItemText(m_listLine, 1);
		dlg.m_beschriftung = m_notenList.GetItemText(m_listLine, 3);

		// String zu Datum Konvertierung
		DATE date;
		stringDate = m_notenList.GetItemText(m_listLine, 2);
		COleDateTime myDtTime;
		myDtTime.ParseDateTime(stringDate);
		SYSTEMTIME sDate;
		myDtTime.GetAsSystemTime(sDate);
		dlg.m_dateCTime = sDate;

		// Dialog öffnen
		if (dlg.DoModal())
		{
			if (dlg.m_okClicked)
			{
				if (dlg.m_note != NULL || dlg.m_note != 0.0)
				{
					try
					{
						// Note in DB updaten
						note.Format("%f", dlg.m_note);
						string sql = "Update note SET note = " + note;
						sql += dlg.m_gewichtung == "" ? "" : ", gewichtung = " + dlg.m_gewichtung;
						sql += ", date = '" + dlg.m_dateCTime.Format("%d.%m.%Y") + "'";
						sql += dlg.m_beschriftung == "" ? "" : ", beschriftung = '" + dlg.m_beschriftung + "'";
						sql += " WHERE note_id = " + id;
						m_db->ExecuteSQL(sql.c_str());
						// Tabelle updaten
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

// Note löschen
void CDetailAnsicht::OnBnClickedNoteEntfernen()
{
	CString id;
	if (m_listLine != -1)
	{
		// Den User Fragen, ob er die Note wirklick löschen möchte
		const int result = MessageBox("Möchten Sie die Note wirklich löschen?", "Note Löschen", MB_YESNO);
		if (result == IDYES)
		{
			id.Format("%d", m_notenList.GetItemData(m_listLine));
			// Note in DB löschen
			m_db->ExecuteSQL("DELETE FROM note WHERE note_id = " + id);
			// Note in Tabelle löschen
			m_notenList.DeleteItem(m_listLine);
			m_listLine = -1;
		}
	}
	else
	{
		AfxMessageBox("Bitte wählen Sie zuerst eine Note aus, die Sie löschen möchten.");
	}
}

// Ein Klick auf die Tabelle
void CDetailAnsicht::OnNMClickNotenUebersicht(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	m_listLine = m_notenList.GetSelectionMark(); // Index der ausgewählten Zeilen speichern
	m_notenList.SetSelectionMark(-1); // Tabellen Mark Index wieder auf -1 stellen
	*pResult = 0;
}

// Doppelklick auf die Tabelle
void CDetailAnsicht::OnNMDblclkNotenUebersicht(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnBnClickedNoteBearbeiten(); // Note bearbeiten
	*pResult = 0;
}
