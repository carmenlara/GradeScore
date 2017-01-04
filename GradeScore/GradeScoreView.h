
// GradeScoreView.h: Schnittstelle der Klasse CGradeScoreView
//

#pragma once
#include "afxcmn.h"


class CGradeScoreView : public CFormView
{
protected: // Nur aus Serialisierung erstellen
	CGradeScoreView();
	DECLARE_DYNCREATE(CGradeScoreView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_GRADESCORE_FORM };
#endif

// Attribute
public:
	CGradeScoreDoc* GetDocument() const;

// Vorgänge
public:

// Überschreibungen
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnInitialUpdate(); // Erster Aufruf nach Erstellung

// Implementierung
public:
	virtual ~CGradeScoreView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Funktionen für die Meldungstabellen
protected:
	DECLARE_MESSAGE_MAP()
public:
	// Selbsterstellte Variablen
	int m_selectedLine;

	// Control Variablen
	CListCtrl m_overview;

	// Hilfsmethoden
	afx_msg void LoadDBInList();

	// Methoden
	afx_msg void SemesterBearbeiten();
	afx_msg void OnNMClickOverview(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkOverview(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAddSemester();
	afx_msg void OnBnClickedDeleteSemester();
	afx_msg void OnBnClickedSelectSemester();
	virtual BOOL DestroyWindow();
};

#ifndef _DEBUG  // Debugversion in GradeScoreView.cpp
inline CGradeScoreDoc* CGradeScoreView::GetDocument() const
   { return reinterpret_cast<CGradeScoreDoc*>(m_pDocument); }
#endif

