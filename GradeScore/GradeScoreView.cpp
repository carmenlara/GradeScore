
// GradeScoreView.cpp: Implementierung der Klasse CGradeScoreView
//

#include "stdafx.h"
// SHARED_HANDLERS können in einem ATL-Projekt definiert werden, in dem Vorschau-, Miniaturansichts- 
// und Suchfilterhandler implementiert werden, und die Freigabe von Dokumentcode für das Projekt wird ermöglicht.
#ifndef SHARED_HANDLERS
#include "GradeScore.h"
#endif

#include "GradeScoreDoc.h"
#include "GradeScoreView.h"
#include "AddSemester.h"
#include "MenuDlg.h"

#include <string>
#include <vector>

using namespace std;

extern CDatabase *m_db;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGradeScoreView

IMPLEMENT_DYNCREATE(CGradeScoreView, CFormView)

BEGIN_MESSAGE_MAP(CGradeScoreView, CFormView)
	ON_NOTIFY(NM_CLICK, IDC_OVERVIEW, &CGradeScoreView::OnNMClickOverview)
	ON_NOTIFY(NM_DBLCLK, IDC_OVERVIEW, &CGradeScoreView::OnNMDblclkOverview)
	ON_BN_CLICKED(IDC_ADD_SEMESTER, &CGradeScoreView::OnBnClickedAddSemester)
	ON_BN_CLICKED(IDC_DELETE_SEMESTER, &CGradeScoreView::OnBnClickedDeleteSemester)
	ON_BN_CLICKED(IDC_SELECT_SEMESTER, &CGradeScoreView::OnBnClickedSelectSemester)
	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()

// CGradeScoreView-Erstellung/Zerstörung

CGradeScoreView::CGradeScoreView()
	: CFormView(IDD_GRADESCORE_FORM)
{
	m_selectedLine = -1;

}

CGradeScoreView::~CGradeScoreView()
{
}

void CGradeScoreView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OVERVIEW, m_overview);
}

BOOL CGradeScoreView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Ändern Sie hier die Fensterklasse oder die Darstellung, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CFormView::PreCreateWindow(cs);
}

void CGradeScoreView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CImageList il;
	m_db = new CDatabase();
	m_db->OpenEx("DSN=GradeScore;SERVER=localhost;UID=postgres;PWD={As2016sql_5};", FALSE);
	
	// Tabellenraster erstellen
	m_overview.InsertColumn(0, _T("Beschriftung"), LVCFMT_LEFT, 400);
	m_overview.InsertColumn(1, _T("Jahr"), LVCFMT_LEFT, 80);
	m_overview.InsertColumn(2, _T("Semester"), LVCFMT_LEFT, 150);
	this->m_overview.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE
		| LVS_EX_AUTOSIZECOLUMNS | LVS_EX_JUSTIFYCOLUMNS);

	// Zeilenhöhe definieren
	il.Create(1, 25, ILC_COLOR, 1, 1);
	m_overview.SetImageList(&il, LVSIL_SMALL);

	// Daten in Tabelle laden
	LoadDBInList();
}


// CGradeScoreView-Diagnose

#ifdef _DEBUG
void CGradeScoreView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGradeScoreView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CGradeScoreDoc* CGradeScoreView::GetDocument() const // Nichtdebugversion ist inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGradeScoreDoc)));
	return (CGradeScoreDoc*)m_pDocument;
}
#endif //_DEBUG


// CGradeScoreView-Meldungshandler

// Daten in Tabelle laden
void CGradeScoreView::LoadDBInList()
{
	CRecordset *rec = new CRecordset (m_db);
	CString id, beschriftung, jahr, semester, query;
	int i = 0;
	query = "SELECT * FROM semester ORDER BY sem_id;";
	// Tabelle löschen
	m_overview.DeleteAllItems();
	// Tabelle in DB öffnen
	rec->Open(CRecordset::snapshot, query, NULL);
	while (!rec->IsEOF ())
	{
		// Daten des aktuellen Datensatzes speichern
		rec->GetFieldValue("sem_id", id);
		rec->GetFieldValue("beschriftung", beschriftung);
		rec->GetFieldValue("jahr", jahr);
		rec->GetFieldValue("semester", semester);

		// Daten in Tabelle ausgeben
		m_overview.InsertItem(i, beschriftung);
		m_overview.SetItemText(i, 1, jahr);
		m_overview.SetItemText(i, 2, semester);
		m_overview.SetItemData(i, (DWORD)_ttoi(id));
		i++;
		// Zu nächsten Datensatz wechseln
		rec->MoveNext();
	}
	rec->Close(); // Tabelle schliessen
}


// Click on Overview List Control
void CGradeScoreView::OnNMClickOverview(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	m_selectedLine = m_overview.GetSelectionMark();
	m_overview.SetSelectionMark(-1);
	*pResult = 0;
}


// Doubleclick on Overview List Control
void CGradeScoreView::OnNMDblclkOverview(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	SemesterBearbeiten();
	*pResult = 0;
}


// Button Semester hinzufügen
void CGradeScoreView::OnBnClickedAddSemester()
{
	CAddSemester dlg;
	CString query, semester, jahr;
	if (dlg.DoModal())
	{
		if (dlg.m_okClicked)
		{
			jahr.Format("%d", dlg.m_jahr);
			if (dlg.m_semesterNr == 0)
			{
				semester = "1";
			}
			else
			{
				semester = "2";
			}
			try
			{
				m_db->ExecuteSQL("INSERT INTO semester (beschriftung, jahr, semester) VALUES ('" + dlg.m_beschriftung + "', " + jahr + ", " + semester + ");");
				LoadDBInList();
			}
			catch (CDBException *e)
			{
				MessageBox("Das Semester konnte nicht erfasst werden.", "Error", MB_ICONERROR);
			}
		}
	}
}


// Semester bearbeiten
void CGradeScoreView::SemesterBearbeiten()
{
	CAddSemester dlg;
	CString query, semester, jahr, id;
	dlg.m_bearbeiten = TRUE;
	if (m_selectedLine != -1)
	{
		// Daten in neuen Dialog laden
		id.Format("%d", m_overview.GetItemData(m_selectedLine));
		dlg.m_beschriftung = m_overview.GetItemText(m_selectedLine, 0);
		dlg.m_jahr = _ttoi (m_overview.GetItemText(m_selectedLine, 1));
		dlg.m_semesterNr = _ttoi (m_overview.GetItemText(m_selectedLine, 2));
		if (dlg.DoModal()) // Dialog öffnen
		{
			if (dlg.m_okClicked)
			{
				jahr.Format("%d", dlg.m_jahr);
				if (dlg.m_semesterNr == 0)
				{
					semester = "1";
				}
				else
				{
					semester = "2";
				}
				try
				{
					// Datensatz in DB updaten
					m_db->ExecuteSQL("UPDATE semester SET beschriftung = '" + dlg.m_beschriftung + "', jahr = " + jahr + ", semester = " + semester + " WHERE sem_id = " + id);
					// Datensatz in Tabelle updaten
					LoadDBInList();
				}
				catch (CDBException *e)
				{
					MessageBox("Das Semester konnte nicht bearbeitet werden.", "Error", MB_ICONERROR);
				}
			}
		}
	}
	else
	{
		AfxMessageBox("Bitte wählen Sie vorher ein Semester aus.");
	}
}


// Button Semester löschen
void CGradeScoreView::OnBnClickedDeleteSemester()
{
	CRecordset *rec = new CRecordset(m_db);
	int i = 0;
	int id = 0;
	int countLines = 0;
	CString idStr, fachid, beschriftung, jahr, semester;
	std::vector <CString> fachIDs;
	if (m_selectedLine != -1)
	{
		beschriftung = m_overview.GetItemText(m_selectedLine, 0);
		jahr = m_overview.GetItemText(m_selectedLine, 1);
		semester = m_overview.GetItemText(m_selectedLine, 2) + ". Semester";
		const int result = MessageBox("Möchten Sie \"" + beschriftung + ", " + jahr + ", " + semester + "\" wirklich löschen?", "Semester Löschen", MB_YESNO);
		if (result == IDYES)
		{
			id = m_overview.GetItemData(m_selectedLine);
			idStr.Format("%d", id);
			rec->Open(CRecordset::snapshot, "SELECT * FROM fach WHERE fk_sem_id = " + idStr, NULL);
			countLines = rec->GetRecordCount();
			for (i = 0; i < countLines; i++)
			{
				rec->GetFieldValue("fach_id", fachid);
				rec->MoveNext();
				fachIDs.push_back(fachid);
			}
			rec->Close();

			for (i = 0; i < fachIDs.size(); i++)
			{
				m_db->ExecuteSQL("DELETE FROM note WHERE fk_fach_id = " + fachIDs.at(i));
			}

			m_db->ExecuteSQL("DELETE FROM fach WHERE fk_sem_id = " + idStr);
			m_db->ExecuteSQL("DELETE FROM semester WHERE sem_id = " + idStr);
			m_overview.DeleteItem(m_selectedLine);
		}
	}
	else
	{
		MessageBox("Bitte wählen Sie einen Datensatz aus, den Sie löschen möchten.", "Error", MB_ICONERROR);
	}
}


// Button Semester auswählen
void CGradeScoreView::OnBnClickedSelectSemester()
{
	CMenuDlg dlg;
	if (m_selectedLine != -1)
	{
		dlg.m_idSemester.Format("%d", m_overview.GetItemData(m_selectedLine));
		dlg.m_beschriftung = m_overview.GetItemText(m_selectedLine, 0);
		dlg.m_jahr = m_overview.GetItemText(m_selectedLine, 1);
		dlg.m_semester = m_overview.GetItemText(m_selectedLine, 2);
		dlg.DoModal();
	}
}

// Fenster schliessen
BOOL CGradeScoreView::DestroyWindow()
{
	m_db->Close();
	return CFormView::DestroyWindow();
}
