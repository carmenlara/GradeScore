
// GradeScore.h: Hauptheaderdatei für die GradeScore-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"       // Hauptsymbole


// CGradeScoreApp:
// Siehe GradeScore.cpp für die Implementierung dieser Klasse
//

class CGradeScoreApp : public CWinApp
{
public:
	CGradeScoreApp();


// Überschreibungen
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementierung
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGradeScoreApp theApp;
