#pragma once
#include "atltime.h"


// CNoteHinzufuegen dialog

class CNoteHinzufuegen : public CDialogEx
{
	DECLARE_DYNAMIC(CNoteHinzufuegen)

public:
	CNoteHinzufuegen(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNoteHinzufuegen();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTE_HINZUFUEGEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// Variablen
	double m_note;
	CTime m_dateCTime;
	CString m_beschriftung;
	CString m_gewichtung;
	BOOL m_okClicked;
	BOOL m_gewichtungOK;
	BOOL m_bearbeiten;
	
	// Methoden
	afx_msg void OnBnClickedOk();
	afx_msg void OnKillfocusEditGewichtung();
	virtual BOOL OnInitDialog();
};
