#pragma once


// CFachHinzufuegen dialog

class CFachHinzufuegen : public CDialogEx
{
	DECLARE_DYNAMIC(CFachHinzufuegen)

public:
	CFachHinzufuegen(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFachHinzufuegen();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FACH_HINZUFUEGEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_fachname;
	BOOL m_okClicked;
	BOOL m_bearbeiten;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
