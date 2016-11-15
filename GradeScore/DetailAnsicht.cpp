// DetailAnsicht.cpp : implementation file
//

#include "stdafx.h"
#include "GradeScore.h"
#include "DetailAnsicht.h"
#include "afxdialogex.h"


// CDetailAnsicht dialog

IMPLEMENT_DYNAMIC(CDetailAnsicht, CDialogEx)

CDetailAnsicht::CDetailAnsicht(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DETAIL_ANSICHT, pParent)
{

}

CDetailAnsicht::~CDetailAnsicht()
{
}

void CDetailAnsicht::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDetailAnsicht, CDialogEx)
	ON_BN_CLICKED(IDC_NOTE_HINZUFUEGEN, &CDetailAnsicht::OnBnClickedNoteHinzufuegen)
	ON_BN_CLICKED(IDC_NOTE_ENTFERNEN, &CDetailAnsicht::OnBnClickedNoteEntfernen)
	ON_BN_CLICKED(IDC_MENU, &CDetailAnsicht::OnBnClickedMenu)
	ON_BN_CLICKED(IDOK, &CDetailAnsicht::OnBnClickedOk)
END_MESSAGE_MAP()

void CDetailAnsicht::init()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CImageList il;
	m_db = new CDatabase();
	m_db->OpenEx("DSN=GradeScore;SERVER=localhost;UID=postgres;PWD={As2016sql_5};", FALSE);

	// Tabellenraster
	m_notenList.InsertColumn(0, _T("Beschriftung"), LVCFMT_LEFT, 250);
	m_notenList.InsertColumn(1, _T("Jahr"), LVCFMT_LEFT, 80);
	m_notenList.InsertColumn(2, _T("Semester"), LVCFMT_LEFT, 150);
	this->m_notenList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE
		| LVS_EX_AUTOSIZECOLUMNS | LVS_EX_JUSTIFYCOLUMNS);

	il.Create(1, 25, ILC_COLOR, 1, 1);
	m_notenList.SetImageList(&il, LVSIL_SMALL);

	LoadDBInList();
}

void CDetailAnsicht::LoadData()
{
	CRecordset *rec = new CRecordset(m_db);
	CString id, beschriftung, note, datum, gewichtung, query;
	int i = 0;
	query = CString.Format("SELECT * FROM fach WHERE fk_fach_id = %d;", m_fachid);
	m_notenList.DeleteAllItems();
	rec->Open(CRecordset::snapshot, query, NULL);
	while (!rec->IsEOF())
	{
		rec->GetFieldValue("note_id", id);
		rec->GetFieldValue("beschriftung", beschriftung);
		rec->GetFieldValue("note", note);
		rec->GetFieldValue("date", datum);
		rec->GetFieldValue("gewichtung", gewichtung);

		m_notenList.InsertItem(i, beschriftung);
		m_notenList.SetItemText(i, 1, datum);
		m_notenList.SetItemText(i, 2, semester);
		m_notenList.SetItemText(i, 3, gewichtung);
		m_notenList.SetItemData(i, (DWORD)_ttoi(id));
		i++;
		rec->MoveNext();
	}
	rec->Close();
}

// CDetailAnsicht message handlers


BOOL CDetailAnsicht::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	LoadData();
	init();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}


void CDetailAnsicht::OnBnClickedNoteHinzufuegen()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}


void CDetailAnsicht::OnBnClickedNoteEntfernen()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}


void CDetailAnsicht::OnBnClickedMenu()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}


void CDetailAnsicht::OnBnClickedOk()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	CDialogEx::OnOK();
}
