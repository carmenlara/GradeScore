#pragma once
#include "afxcmn.h"

#include <vector>
#include <map>
#include <string>

using namespace std;

// CMenuDlg dialog

class CMenuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMenuDlg)

public:
	CMenuDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMenuDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_fachList;
	CString m_info;
	CString m_idSemester;
	CString m_beschriftung;
	CString m_jahr;
	CString m_semester;
	int m_listLine;

	std::map <int, std::map <CString, CString>> m_faecher;
	std::map <int, std::map <CString, CString>> m_noten;
	std::map <CString, double> m_fachNoten;

	afx_msg double GesamtnoteBerechnen(int fachid);
	afx_msg void FaecherHolen();
	afx_msg void NotenHolen();
	afx_msg void LoadListCtrl();

	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickModule(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkModule(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSemesterWechseln();
	afx_msg void OnBnClickedFachHinzufuegen();
	afx_msg void OnBnClickedFachEntfernen();
	afx_msg void OnBnClickedGrafischeAnsicht();
	afx_msg void OnBnClickedFachAuswaehlen();
};
