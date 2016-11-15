#pragma once
#include "afxcmn.h"

#include "afxcmn.h"

// CDetailAnsicht dialog

class CDetailAnsicht : public CDialogEx
{
	DECLARE_DYNAMIC(CDetailAnsicht)

public:
	CDetailAnsicht(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDetailAnsicht();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DETAIL_ANSICHT };
#endif
private:

	// Control Variablen
	CListCtrl m_overview;

	// Hilfsmethoden
	afx_msg void LoadData();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void init(); // Erster Aufruf nach Erstellung

	DECLARE_MESSAGE_MAP()

public:
	int m_fachid;
	CListCtrl m_notenList;
	afx_msg void OnBnClickedNoteHinzufuegen();
	afx_msg void OnBnClickedNoteEntfernen();
	afx_msg void OnBnClickedMenu();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
