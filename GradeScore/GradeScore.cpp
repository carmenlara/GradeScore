
// GradeScore.cpp: Definiert das Klassenverhalten f�r die Anwendung.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GradeScore.h"
#include "MainFrm.h"

#include "GradeScoreDoc.h"
#include "GradeScoreView.h"

// Deklaration der globalen CDatabase Variable, die �berall genutzt werden kann
CDatabase *m_db;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGradeScoreApp

BEGIN_MESSAGE_MAP(CGradeScoreApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CGradeScoreApp::OnAppAbout)
	// Dateibasierte Standarddokumentbefehle
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CGradeScoreApp-Erstellung

CGradeScoreApp::CGradeScoreApp()
{
	// Neustart-Manager unterst�tzen
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Wenn die Anwendung mit Common Language Runtime-Unterst�tzung (/clr) erstellt wurde:
	//     1) Diese zus�tzliche Eigenschaft ist erforderlich, damit der Neustart-Manager ordnungsgem�� unterst�tzt wird.
	//     2) F�r die Projekterstellung m�ssen Sie im Projekt einen Verweis auf System.Windows.Forms hinzuf�gen.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: Ersetzen Sie die Anwendungs-ID-Zeichenfolge unten durch eine eindeutige ID-Zeichenfolge; empfohlen
	// Das Format f�r die Zeichenfolge ist: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("GradeScore.AppID.NoVersion"));

	// TODO: Hier Code zur Konstruktion einf�gen
	// Alle wichtigen Initialisierungen in InitInstance positionieren
}

// Das einzige CGradeScoreApp-Objekt

CGradeScoreApp theApp;


// CGradeScoreApp-Initialisierung

BOOL CGradeScoreApp::InitInstance()
{
	// InitCommonControlsEx() ist f�r Windows XP erforderlich, wenn ein Anwendungsmanifest
	// die Verwendung von ComCtl32.dll Version 6 oder h�her zum Aktivieren
	// von visuellen Stilen angibt.  Ansonsten treten beim Erstellen von Fenstern Fehler auf.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Legen Sie dies fest, um alle allgemeinen Steuerelementklassen einzubeziehen,
	// die Sie in Ihrer Anwendung verwenden m�chten.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// OLE-Bibliotheken initialisieren
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() ist f�r die Verwendung des RichEdit-Steuerelements erforderlich.	
	// AfxInitRichEdit2();

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht verwenden und die Gr��e
	// der ausf�hrbaren Datei verringern m�chten, entfernen Sie
	// die nicht erforderlichen Initialisierungsroutinen.
	// �ndern Sie den Registrierungsschl�ssel, unter dem Ihre Einstellungen gespeichert sind.
	// TODO: �ndern Sie diese Zeichenfolge entsprechend,
	// z.B. zum Namen Ihrer Firma oder Organisation.
	SetRegistryKey(_T("Vom lokalen Anwendungs-Assistenten generierte Anwendungen"));
	LoadStdProfileSettings(4);  // Standard INI-Dateioptionen laden (einschlie�lich MRU)


	// Dokumentvorlagen der Anwendung registrieren.  Dokumentvorlagen
	//  dienen als Verbindung zwischen Dokumenten, Rahmenfenstern und Ansichten.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGradeScoreDoc),
		RUNTIME_CLASS(CMainFrame),       // Haupt-SDI-Rahmenfenster
		RUNTIME_CLASS(CGradeScoreView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Befehlszeile auf Standardumgebungsbefehle �berpr�fen, DDE, Datei �ffnen
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Verteilung der in der Befehlszeile angegebenen Befehle.  Gibt FALSE zur�ck, wenn
	// die Anwendung mit /RegServer, /Register, /Unregserver oder /Unregister gestartet wurde.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Das einzige Fenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CGradeScoreApp::ExitInstance()
{
	//TODO: Zus�tzliche Ressourcen behandeln, die Sie m�glicherweise hinzugef�gt haben
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CGradeScoreApp-Meldungshandler


// CAboutDlg-Dialogfeld f�r Anwendungsbefehl "Info"

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung

// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Anwendungsbefehl zum Ausf�hren des Dialogfelds
void CGradeScoreApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CGradeScoreApp-Meldungshandler



