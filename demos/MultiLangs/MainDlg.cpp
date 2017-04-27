// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
#include <helper/SMenuEx.h>

#ifdef DWMBLUR	//win7毛玻璃开关
#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")
#endif
	
CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_LangID = R.id.lang_cn;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	#ifdef DWMBLUR	//win7毛玻璃开关
	MARGINS mar = {5,5,30,5};
	DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	#endif

	SetMsgHandled(FALSE);
	return 0;
}

const wchar_t * strSrc = L"test input";
BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	SStringT strTr = S_CW2T(TR(strSrc, L"user"));
	SWindow *wnd = FindChildByID(R.id.txt_test);
	FindChildByID(R.id.txt_test)->SetWindowText(strTr);
	return 0;
}

void CMainDlg::onLanguageChanged()
{
	__super::onLanguageChanged();
	SStringT strTr = S_CW2T(TR(strSrc, L"user"));
	FindChildByID(R.id.txt_test)->SetWindowText(strTr);
}

void CMainDlg::OnLanguage(int nID)
{
	ITranslatorMgr *pTransMgr =  SApplication::getSingletonPtr()->GetTranslator();
	m_LangID = nID;
	bool bCnLang = nID == R.id.lang_cn;

	pugi::xml_document xmlLang;
	if (SApplication::getSingletonPtr()->LoadXmlDocment(xmlLang, bCnLang?_T("cn"):_T("en"), _T("lang")))
	{
		CAutoRefPtr<ITranslator> lang;
		pTransMgr->CreateTranslator(&lang);
		lang->Load(&xmlLang.child(L"language"), 1);//1=LD_XML
		pTransMgr->SetLanguage(lang->name());
		pTransMgr->InstallTranslator(lang);
	}

}


//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}

void CMainDlg::OnBtnMenu()
{
	SMenuEx menu;
	menu.LoadMenu(_T("smenu:menu_lang"));
	CPoint pt;
	GetCursorPos(&pt);

	SMenuEx *pLangMenu = menu.GetSubMenu(50);
	pLangMenu->GetMenuItem(m_LangID)->SetAttribute(L"check",L"1");

	menu.TrackPopupMenu(0,pt.x,pt.y,m_hWnd);
}

void CMainDlg::OnMenuCmd(UINT uNotifyCode, int nID, HWND wndCtl)
{
	if(nID == R.id.lang_cn || nID == R.id.lang_en)
	{
		OnLanguage(nID);
	}
}

void CMainDlg::OnBtnScale(int nID)
{
	int nScale = 100;
	switch(nID)
	{
	case R.id.btn_scale_100:
		nScale = 100;
		break;
	case R.id.btn_scale_125:
		nScale = 125;
		break;
	case R.id.btn_scale_150:
		nScale = 150;
		break;
	}

	SetScale(nScale);
}

