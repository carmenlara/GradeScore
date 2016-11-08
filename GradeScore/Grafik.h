#pragma once


// CGrafik dialog

class CGrafik : public CDialogEx
{
	DECLARE_DYNAMIC(CGrafik)

public:
	CGrafik(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGrafik();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAFIK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
