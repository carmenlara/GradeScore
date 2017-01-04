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
	// Hilfsmethoden
	afx_msg void LoadData();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	// Tabelle
	CListCtrl m_notenList;
	// Variablen
	int m_fachid;
	int m_listLine;

	// Methoden
	afx_msg void OnBnClickedNoteHinzufuegen();
	afx_msg void OnBnClickedNoteEntfernen();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickNotenUebersicht(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedNoteBearbeiten();
	afx_msg void OnNMDblclkNotenUebersicht(NMHDR *pNMHDR, LRESULT *pResult);
};
