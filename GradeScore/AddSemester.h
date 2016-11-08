#pragma once
#include "afxwin.h"


// CAddSemester-Dialogfeld

class CAddSemester : public CDialogEx
{
	DECLARE_DYNAMIC(CAddSemester)

public:
	CAddSemester(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CAddSemester();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEMESTER_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CString m_beschriftung;
	int m_jahr;
	CComboBox m_semester;
	afx_msg void OnBnClickedOk();
	BOOL m_okClicked;
	afx_msg void OnSelchangeSemester();
	int m_semesterNr;
};
