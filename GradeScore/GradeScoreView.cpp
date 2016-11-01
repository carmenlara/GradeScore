
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

	/*m_db = new CDatabase();
	m_db->OpenEx("DSN=GradeScore;SERVER=localhost;UID=postgres;PWD={As2016sql_5};", FALSE);
	CRecordset *rec = new CRecordset(m_db);
	CString query = "Select * FROM test;";
	rec->Open(CRecordset::snapshot, query);
	if (rec->IsOpen())
	{
		CString xy;
		rec->GetFieldValue("spalte", xy);
	}*/
	
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
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	*pResult = 0;
}


// Button Semester hinzufügen
void CGradeScoreView::OnBnClickedAddSemester()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}


// Button Semester löschen
void CGradeScoreView::OnBnClickedDeleteSemester()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}


// Button Semester auswählen
void CGradeScoreView::OnBnClickedSelectSemester()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}
