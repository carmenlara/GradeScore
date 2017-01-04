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

#include <iostream>

using namespace std;

extern CDatabase *m_db;
// CMenuDlg dialog

IMPLEMENT_DYNAMIC(CMenuDlg, CDialogEx)

CMenuDlg::CMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MENU, pParent)
	, m_info(_T(""))
{
	m_listLine = -1;
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
	ON_BN_CLICKED(IDC_FACH_AUSWAEHLEN, &CMenuDlg::OnBnClickedFachAuswaehlen)
	ON_BN_CLICKED(IDC_FACH_BEARBEITEN, &CMenuDlg::OnBnClickedFachBearbeiten)
END_MESSAGE_MAP()


// CMenuDlg message handlers


BOOL CMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CImageList il;

	// Tabellenspalten erstellen
	m_fachList.InsertColumn(0, "Fach", LVCFMT_LEFT, 300);
	m_fachList.InsertColumn(1, "Note", LVCFMT_LEFT, 100);
	m_fachList.InsertColumn(2, "Note gerundet", LVCFMT_RIGHT, 100);
	m_fachList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE
		| LVS_EX_AUTOSIZECOLUMNS | LVS_EX_JUSTIFYCOLUMNS);

	// Höhe der Tabellenzeilen ändern
	il.Create(1, 25, ILC_COLOR, 1, 1);
	m_fachList.SetImageList(&il, LVSIL_SMALL);

	// Vektoren füllen
	FaecherHolen();
	NotenHolen();
	// Tabelle mit Daten laden
	LoadListCtrl();
	// Information anpassen
	ShowInfo();

	// Daten werden im GUI updated, sodass der User diese sehen kann
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

// Information bearbeiten
void CMenuDlg::ShowInfo()
{
	CString gesamtnoteStr;
	double gesamtnote = 0;
	int i = 0;
	// Alle Gesamtnoten der Fächer zusammen zählen
	for (i = 0; i < m_fachList.GetItemCount (); i++)
	{
		gesamtnote += atof (m_fachList.GetItemText(i, 1));
	}
	if (gesamtnote != 0)
	{
		// Das Resultata durch die Anzahl Gesamtnoten rechnen
		gesamtnote = gesamtnote / i;
		gesamtnote = (double)((int)(gesamtnote * 100)) / 100;
		gesamtnoteStr.Format("%.1f", gesamtnote);
	}
	else
	{
		// Sind keine Noten vorhanden, wird dies bemerkt
		gesamtnoteStr = "Noch keine Noten vorhanden";
	}

	if (m_beschriftung != "") // Wenn das Semester einen Beschriftungstext hat wird dieser ebenfalls ausgegeben
	{
		// Die Information wird zusammengefasst
		m_info = "Aktuelles Schuljahr " + m_jahr + ", Semester " + m_semester +
			"\r\n" + m_beschriftung + "\r\n Gesamtnote: " + gesamtnoteStr;
	}
	else
	{
		// Die Information wird zusammengefasst
		m_info = "Aktuelles Schuljahr " + m_jahr + ", Semester " + m_semester +
			"\r\n Gesamtnote: " + gesamtnoteStr;
	}
}

// Vektor mit Fächer füllen
void CMenuDlg::FaecherHolen()
{
	CRecordset *rec = new CRecordset(m_db);
	CString query = "SELECT * FROM fach WHERE fach.\"fk_sem_id\" = " + m_idSemester, idFachStr, fach;
	int i = 0;
	m_faecher.clear(); // Vektor löschen
	rec->Open(CRecordset::snapshot, query, NULL); // Tabelle öffnen
	while (!rec->IsEOF()) // Solagen man nicht am Ende der Tabelle angelangt ist
	{
		// Die Daten des aktuellen Datensatzes  werden in die Variablen gespeichert
		rec->GetFieldValue("fach_id", idFachStr);
		rec->GetFieldValue("fach", fach);
		// Vektor füllen
		m_faecher [i] ["id"] = idFachStr;
		m_faecher [i] ["fach"] = fach;
		// Zum nächsten Element der Tabelle gehen
		rec->MoveNext();
		i++;
	}
	rec->Close(); // Tabelle schliessen
}

// Vektor mit Noten füllen
void CMenuDlg::NotenHolen()
{
	CRecordset *rec = new CRecordset(m_db);
	CString noteStr, gewichtungStr;
	int fachIdx = 0;
	int notenIdx = 0;
	m_noten.clear();
	for (fachIdx = 0; fachIdx < m_faecher.size(); ++fachIdx)
	{
		// Alle Noten des ausgewählten Faches werden geholt und in den Vektor geseichert
		rec->Open(CRecordset::snapshot, "SELECT * FROM note WHERE note.\"fk_fach_id\" = " + m_faecher [fachIdx] ["id"], NULL);
		while (!rec->IsEOF())
		{
			rec->GetFieldValue("note", noteStr);
			rec->GetFieldValue("gewichtung", gewichtungStr);
			m_noten[notenIdx]["fachid"] = m_faecher[fachIdx]["id"];
			m_noten[notenIdx]["note"] = noteStr;
			m_noten[notenIdx]["gewichtung"] = gewichtungStr;
			rec->MoveNext();
			++notenIdx;
		}
		rec->Close();
	}
}

// Tabelle laden
void CMenuDlg::LoadListCtrl()
{
	int i = 0;
	double note = 0.0;
	CString noteStr, notegerundetStr;
	m_fachList.DeleteAllItems(); // Der ganze Tabelleninhalt wird gelöscht
	for (i = 0; i < m_faecher.size(); i++)
	{
		note = GesamtnoteBerechnen(_ttoi(m_faecher[i]["id"])); // Gesamtnote des aktuellen Fachs wird berechnet
		noteStr.Format("%.2f", note); // Konvertierung der Gesamtnote in einen String
		notegerundetStr.Format("%.2f", round(note * 2.0)/2.0);
		// Daten in Tabelle einfügen
		m_fachList.InsertItem(i, m_faecher[i]["fach"]);
		m_fachList.SetItemText(i, 1, noteStr);
		m_fachList.SetItemText(i, 2, notegerundetStr);
		m_fachList.SetItemData(i, (DWORD)_ttoi(m_faecher[i]["id"])); // Zusatzinformation mitgeben, die der User nicht sehen kann
	}
	UpdateData(FALSE);
}

// Gesamtnote berechnen
double CMenuDlg::GesamtnoteBerechnen(int fachid)
{
	double dRet = 0.0;
	double dGesamtGewichtung = 0.0;
	int iOhneGewichtung = 0;
	CString fachidStr;
	// Struct definieren
	struct SNote
	{
		double Note;
		double Gewichtung;
	};

	// Noten werden neu geladen um Inkonsistenzen aus dem Weg zu gehen
	NotenHolen();

	// Vektor erstellen mit Typ des erstellten Structs
	vector<SNote> vecNoten;
	fachidStr.Format("%d", fachid);
	for (int i = 0; i < m_noten.size(); ++i)
	{
		if (m_noten[i]["fachid"] == fachidStr) // Gehört die Note zum aktuellen Fach?
		{
			SNote xNote; // Objekt des Struct erstellen
			xNote.Note = atof(m_noten[i]["note"]);
			xNote.Gewichtung = -1.0;
			if (!m_noten[i]["gewichtung"].IsEmpty()) // Ist eine Gewichtung vorhanden?
			{
				xNote.Gewichtung = atof(m_noten[i]["gewichtung"]) / 100.0;
				dGesamtGewichtung += xNote.Gewichtung;
			}
			else
			{
				++iOhneGewichtung;
			}
			vecNoten.push_back(xNote); // Objekt in Vektor speichern
		}
	}

	// Gewichtung der Noten berechnen, bei denen keine Gewichtung angegeben wurde
	double dGewichtungÜbriger = (1.0 - dGesamtGewichtung) / iOhneGewichtung; 

	for (int i = 0; i < vecNoten.size(); ++i)
	{
		if (vecNoten.at (i).Gewichtung < 0)
		{
			vecNoten.at (i).Gewichtung = dGewichtungÜbriger;
			// Gesamtgewichtung der Noten, bei denen keine angegeben wurde
			dGesamtGewichtung += dGewichtungÜbriger; 
		}
	}

	// Gesamtnote berechnen
	for (int i = 0; i < vecNoten.size(); ++i)
	{
		dRet += vecNoten.at(i).Gewichtung * vecNoten.at(i).Note / dGesamtGewichtung;
	}

	return dRet;
}


// Ein Klick auf die Tabelle
void CMenuDlg::OnNMClickModule(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	m_listLine = m_fachList.GetSelectionMark(); // Index der ausgewählt Zeile in Variable speichern
	m_fachList.SetSelectionMark(-1); // In Tabelle wieder abwählen um Fehler zu vermeiden
	*pResult = 0;
}

// Doppelklick auf die Tabelle
void CMenuDlg::OnNMDblclkModule(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnBnClickedFachAuswaehlen(); // Detailansicht anzeigen
	*pResult = 0;
}

// Semester wechseln
void CMenuDlg::OnBnClickedSemesterWechseln()
{
	// Fenster schliessen
	OnCancel();
}

// Fach hinzufügen
void CMenuDlg::OnBnClickedFachHinzufuegen()
{
	CFachHinzufuegen dlg; // Objekt der Klasse CFachHinzufuegen erstellen
	if (dlg.DoModal()) // Dialog der Klasse CFachHinzufuegen öffnen
	{
		if (dlg.m_okClicked) // Wurde der Button "OK" betätigt?
		{
			if (dlg.m_fachname != "") // Wurde ein Fachname eingegeben?
			{
				try
				{
					// Fach in DB hinzufügen
					m_db->ExecuteSQL("INSERT INTO fach (fach, fk_sem_id) VALUES ('" + dlg.m_fachname + "', " + m_idSemester + ")");
					// Daten updaten
					FaecherHolen();
					NotenHolen();
					// Tabelle aktualisieren
					LoadListCtrl();
					// Information aktualisieren
					ShowInfo();
				}
				catch (CDBException *e)
				{
					// Konto das Fach nicht in die DB hinzugefügt werden, Fehlermeldung ausgeben
					MessageBox("Das Fach konnte nicht erfasst werden.", "Error", MB_ICONERROR);
				}
			}
			else
			{
				// Wurde kein Fachname eingegeben, Fehlermeldung ausgeben
				MessageBox("Bitte geben Sie einen Namen für das neue Fach an.", "Name eingeben", NULL);
				OnBnClickedFachHinzufuegen();
			}
		}
	}
}

// Fach bearbeiten
void CMenuDlg::OnBnClickedFachBearbeiten()
{
	CFachHinzufuegen dlg;
	CString id;
	if (m_listLine != -1)
	{
		id.Format("%d", m_fachList.GetItemData(m_listLine));
		dlg.m_fachname = m_fachList.GetItemText(m_listLine, 0);
		if (dlg.DoModal())
		{
			if (dlg.m_okClicked)
			{
				if (dlg.m_fachname != "")
				{
					try
					{
						// Die Daten in der DB updaten
						m_db->ExecuteSQL("UPDATE fach SET fach = '" + dlg.m_fachname + "' WHERE fach_id = " + id);
						// Daten in Tabelle updaten
						m_fachList.SetItemText(m_listLine, 0, dlg.m_fachname);
						// Vektor updaten
						FaecherHolen();
					}
					catch (CDBException *e)
					{
						AfxMessageBox("Das Fach konnte nicht bearbeitet werden.");
					}
				}
				else
				{
					AfxMessageBox("Bitte geben Sie einen Fachnamen ein.");
					OnBnClickedFachBearbeiten();
				}
			}
		}
	}
	else
	{
		AfxMessageBox("Bitte wählen Sie ein Fach aus, das Sie bearbeiten möchten.");
	}
}

// Fach auswählen
void CMenuDlg::OnBnClickedFachAuswaehlen()
{
	CDetailAnsicht dlg;
	if (m_listLine != -1)
	{
		dlg.m_fachid = m_fachList.GetItemData(m_listLine);
		// Aus Detailansicht wechseln
		dlg.DoModal();
		// Daten updaten
		FaecherHolen();
		NotenHolen();
		// Tabelle updaten
		LoadListCtrl();
		// Information  updaten
		ShowInfo();
		UpdateData(FALSE);
	}
	else
	{
		// Wurde kein Fach ausgewählt, Fehlermeldung ausgeben
		AfxMessageBox("Bitte wählen Sie ein Fach aus.");
	}
}

// Fach löschen
void CMenuDlg::OnBnClickedFachEntfernen()
{
	CString id, fach;
	if (m_listLine != -1)
	{
		fach = m_fachList.GetItemText(m_listLine, 0);
		// User abfragen, ob er Fach wirklich löschen möchte
		const int result = MessageBox("Möchten Sie das Fach \"" + fach + "\" wirklich löschen?", "Fach Löschen", MB_YESNO);
		if (result == IDYES)
		{
			id.Format("%d", m_fachList.GetItemData(m_listLine));
			try
			{
				// Alle Noten die zum beliebigen Fach gehören löschen
				m_db->ExecuteSQL("DELETE FROM note WHERE fk_fach_id = " + id);
				// Das Fach löschen
				m_db->ExecuteSQL("DELETE FROM fach WHERE fach_id = " + id);
				// Vektoren aktualisieren
				FaecherHolen();
				NotenHolen();
				// Datensatz in Tabelle löschen
				m_fachList.DeleteItem(m_listLine);
			}
			catch (CDBException *e) // Funktionierte das löschen nicht, wird eine Fehlermeldung ausgegeben
			{
				AfxMessageBox("Das Fach konnte nicht gelöscht werden.");
			}
		}
	}
	else // Hat der User keinen Datensatz ausgewählt, wird er darauf hingewiesen
	{
		AfxMessageBox("Bitte wählen Sie ein Fach aus, das Sie löschen möchten.");
	}
}
