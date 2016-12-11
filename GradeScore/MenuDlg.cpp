// MenuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GradeScore.h"
#include "MenuDlg.h"
#include "afxdialogex.h"
#include "FachHinzufuegen.h"
#include "DetailAnsicht.h"

#include <string>
#include <vector>
#include <map>
#include <stdlib.h>

using namespace std;

extern CDatabase *m_db;
// CMenuDlg dialog

IMPLEMENT_DYNAMIC(CMenuDlg, CDialogEx)

CMenuDlg::CMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MENU, pParent)
	, m_info(_T(""))
{
	m_listLine = -1;
}

CMenuDlg::~CMenuDlg()
{
}

void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODULE, m_fachList);
	DDX_Text(pDX, IDC_INFO_SEMESTER_JAHR_TEXT_GESAMMTNOTE, m_info);
}


BEGIN_MESSAGE_MAP(CMenuDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_MODULE, &CMenuDlg::OnNMClickModule)
	ON_NOTIFY(NM_DBLCLK, IDC_MODULE, &CMenuDlg::OnNMDblclkModule)
	ON_BN_CLICKED(IDC_SEMESTER_WECHSELN, &CMenuDlg::OnBnClickedSemesterWechseln)
	ON_BN_CLICKED(IDC_FACH_HINZUFUEGEN, &CMenuDlg::OnBnClickedFachHinzufuegen)
	ON_BN_CLICKED(IDC_FACH_ENTFERNEN, &CMenuDlg::OnBnClickedFachEntfernen)
	ON_BN_CLICKED(IDC_GRAFISCHE_ANSICHT, &CMenuDlg::OnBnClickedGrafischeAnsicht)
	ON_BN_CLICKED(IDC_FACH_AUSWAEHLEN, &CMenuDlg::OnBnClickedFachAuswaehlen)
	ON_BN_CLICKED(IDC_FACH_BEARBEITEN, &CMenuDlg::OnBnClickedFachBearbeiten)
END_MESSAGE_MAP()


// CMenuDlg message handlers


BOOL CMenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CImageList il;

	m_fachList.InsertColumn(0, "Fach", LVCFMT_LEFT, 300);
	m_fachList.InsertColumn(1, "Note", LVCFMT_LEFT, 100);
	m_fachList.InsertColumn(2, "Note gerundet", LVCFMT_RIGHT, 100);
	m_fachList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE
		| LVS_EX_AUTOSIZECOLUMNS | LVS_EX_JUSTIFYCOLUMNS);

	il.Create(1, 25, ILC_COLOR, 1, 1);
	m_fachList.SetImageList(&il, LVSIL_SMALL);

	FaecherHolen();
	NotenHolen();
	LoadListCtrl();
	ShowInfo();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}


void CMenuDlg::ShowInfo()
{
	CString gesamtnoteStr;
	double gesamtnote = 0;
	int i = 0;
	// Gesamtnote berechnen und Info ausgeben
	for (i = 0; i < m_fachList.GetItemCount (); i++)
	{
		gesamtnote += atof (m_fachList.GetItemText(i, 1));
	}
	if (gesamtnote != 0)
	{
		gesamtnote = gesamtnote / i;
		gesamtnote = (double)((int)(gesamtnote * 100)) / 100;
		gesamtnoteStr.Format("%f", gesamtnote);
	}
	else
	{
		gesamtnoteStr = "Noch keine Noten vorhanden";
	}

	if (m_beschriftung != "")
	{
		m_info = "Aktuelles Schuljahr " + m_jahr + ", Semester " + m_semester +
			"\r\n" + m_beschriftung + "\r\n Gesamtnote: " + gesamtnoteStr;
	}
	else
	{
		m_info = "Aktuelles Schuljahr " + m_jahr + ", Semester " + m_semester +
			"\r\n Gesamtnote: " + gesamtnoteStr;
	}
}


void CMenuDlg::FaecherHolen()
{
	CRecordset *rec = new CRecordset(m_db);
	CString query = "SELECT * FROM fach WHERE fach.\"fk_sem_id\" = " + m_idSemester, idFachStr, fach;
	int i = 0;
	m_faecher.clear();
	rec->Open(CRecordset::snapshot, query, NULL);
	while (!rec->IsEOF())
	{
		rec->GetFieldValue("fach_id", idFachStr);
		rec->GetFieldValue("fach", fach);
		m_faecher [i] ["id"] = idFachStr;
		m_faecher [i] ["fach"] = fach;
		rec->MoveNext();
		i++;
	}
	rec->Close();
}


void CMenuDlg::NotenHolen()
{
	CRecordset *rec = new CRecordset(m_db);
	CString noteStr, gewichtungStr;
	int i = 0;
	int fachid = 0;
	m_noten.clear();
	for (i = 0; i < m_faecher.size(); i++)
	{
		m_noten.clear();
		rec->Open(CRecordset::snapshot, "SELECT * FROM note WHERE note.\"fk_fach_id\" = " + m_faecher [i] ["id"], NULL);
		while (!rec->IsEOF())
		{
			rec->GetFieldValue("note", noteStr);
			rec->GetFieldValue("gewichtung", gewichtungStr);
			m_noten[i]["fachid"] = m_faecher[i]["id"];
			m_noten[i]["note"] = noteStr;
			m_noten[i]["gewichtung"] = gewichtungStr;
			rec->MoveNext();
		}
		rec->Close();
	}
}


void CMenuDlg::LoadListCtrl()
{
	int i = 0;
	double note = 0.0;
	CString noteStr, notegerundetStr;
	m_fachList.DeleteAllItems();
	for (i = 0; i < m_faecher.size(); i++)
	{
		note = GesamtnoteBerechnen(_ttoi(m_faecher[i]["id"]));
		noteStr.Format("%d", note);
		notegerundetStr.Format("%d", (int)note);
		m_fachList.InsertItem(i, m_faecher[i]["fach"]);
		m_fachList.SetItemText(i, 1, noteStr);
		m_fachList.SetItemText(i, 1, notegerundetStr);
		m_fachList.SetItemData(i, (DWORD)_ttoi(m_faecher[i]["id"]));
	}
	UpdateData(FALSE);
}


double CMenuDlg::GesamtnoteBerechnen(int fachid)
{
	double dRet = 0.0;
	double dGesamtGewichtung = 0.0;
	int iOhneGewichtung = 0;
	CString fachidStr;
	struct SNote
	{
		double Note;
		double Gewichtung;
	};

	vector<SNote> vecNoten;
	fachidStr.Format("%d", fachid);
	for (int i = 0; i < m_noten.size(); ++i)
	{
		if (m_noten[i]["fachid"] == fachidStr)
		{
			SNote xNote;
			xNote.Note = atof(m_noten[i]["note"]);
			xNote.Gewichtung = -1.0;
			if (!m_noten[i]["Gewichtung"].IsEmpty())
			{
				xNote.Gewichtung = atof(m_noten[i]["Gewichtung"]) / 100.0;
				dGesamtGewichtung += xNote.Gewichtung;
			}
			else
			{
				++iOhneGewichtung;
			}
			vecNoten.push_back(xNote);
		}
	}

	double dGewichtungÜbriger = (1.0 - dGesamtGewichtung) / iOhneGewichtung;

	for (int i = 0; i < vecNoten.size(); ++i)
	{
		if (vecNoten[i].Gewichtung < 0)
		{
			vecNoten[i].Gewichtung = dGewichtungÜbriger;
			dGesamtGewichtung += dGewichtungÜbriger;
		}
	}

	for (int i = 0; i < vecNoten.size(); ++i)
	{
		dRet += vecNoten[i].Gewichtung * vecNoten[i].Note / dGesamtGewichtung;
	}

	if (dRet == 0)
	{
		return 0;
	}
	else
	{
		return dRet / vecNoten.size();
	}	
}


void CMenuDlg::OnNMClickModule(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	m_listLine = m_fachList.GetSelectionMark();
	m_fachList.SetSelectionMark(-1);
	*pResult = 0;
}


void CMenuDlg::OnNMDblclkModule(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnBnClickedFachAuswaehlen();
	*pResult = 0;
}


void CMenuDlg::OnBnClickedSemesterWechseln()
{
	OnCancel();
}


void CMenuDlg::OnBnClickedFachHinzufuegen()
{
	CFachHinzufuegen dlg;
	if (dlg.DoModal())
	{
		if (dlg.m_okClicked)
		{
			if (dlg.m_fachname != "")
			{
				try
				{
					m_db->ExecuteSQL("INSERT INTO fach (fach, fk_sem_id) VALUES ('" + dlg.m_fachname + "', " + m_idSemester + ")");
					FaecherHolen();
					NotenHolen();
					LoadListCtrl();
				}
				catch (CDBException *e)
				{
					MessageBox("Das Fach konnte nicht erfasst werden.", "Error", MB_ICONERROR);
				}
			}
			else
			{
				MessageBox("Bitte geben Sie einen Namen für das neue Fach an.", "Name eingeben", NULL);
				OnBnClickedFachHinzufuegen();
			}
		}
	}
}


void CMenuDlg::OnBnClickedFachBearbeiten()
{
	CFachHinzufuegen dlg;
	CString id;
	if (m_listLine != -1)
	{
		id.Format("%d", m_fachList.GetItemData(m_listLine));
		dlg.m_fachname = m_fachList.GetItemText(m_listLine, 0);
		if (dlg.DoModal())
		{
			if (dlg.m_okClicked)
			{
				if (dlg.m_fachname != "")
				{
					try
					{
						m_db->ExecuteSQL("UPDATE fach SET fach = '" + dlg.m_fachname + "' WHERE fach_id = " + id);
						m_fachList.SetItemText(m_listLine, 0, dlg.m_fachname);
					}
					catch (CDBException *e)
					{
						AfxMessageBox("Das Fach konnte nicht bearbeitet werden.");
					}
				}
				else
				{
					AfxMessageBox("Bitte geben Sie einen Fachnamen ein.");
					OnBnClickedFachBearbeiten();
				}
			}
		}
	}
	else
	{
		AfxMessageBox("Bitte wählen Sie ein Fach aus, das Sie bearbeiten möchten.");
	}
}


void CMenuDlg::OnBnClickedFachAuswaehlen()
{
	CDetailAnsicht dlg;
	if (m_listLine != -1)
	{
		dlg.m_fachid = m_fachList.GetItemData(m_listLine);
		if (dlg.DoModal())
		{
			FaecherHolen();
			NotenHolen();
			LoadListCtrl();
			ShowInfo();
		}
	}
	else
	{
		AfxMessageBox("Bitte wählen Sie ein Fach aus.");
	}
}


void CMenuDlg::OnBnClickedFachEntfernen()
{
	CString id, fach;
	if (m_listLine != -1)
	{
		fach = m_fachList.GetItemText(m_listLine, 0);
		const int result = MessageBox("Möchten Sie das Fach \"" + fach + "\" wirklich löschen?", "Fach Löschen", MB_YESNO);
		if (result == IDYES)
		{
			id.Format("%d", m_fachList.GetItemData(m_listLine));
			try
			{
				m_db->ExecuteSQL("DELETE FROM fach WHERE fach_id = " + id);
				FaecherHolen();
				NotenHolen();
				m_fachList.DeleteItem(m_listLine);
			}
			catch (CDBException *e)
			{
				AfxMessageBox("Das Fach konnte nicht gelöscht werden.");
			}
		}
	}
	else
	{
		AfxMessageBox("Bitte wählen Sie ein Fach aus, das Sie löschen möchten.");
	}
}


void CMenuDlg::OnBnClickedGrafischeAnsicht()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}
