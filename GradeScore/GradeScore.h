
// GradeScore.h: Hauptheaderdatei f�r die GradeScore-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei f�r PCH einschlie�en"
#endif

#include "resource.h"       // Hauptsymbole


// CGradeScoreApp:
// Siehe GradeScore.cpp f�r die Implementierung dieser Klasse
//

class CGradeScoreApp : public CWinApp
{
public:
	CGradeScoreApp();


// �berschreibungen
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementierung
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGradeScoreApp theApp;
