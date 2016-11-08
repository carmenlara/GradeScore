#pragma once


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
};
