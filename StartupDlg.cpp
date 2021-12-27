
// StartupDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Startup.h"
#include "StartupDlg.h"
#include "afxdialogex.h"
#include "CChangeText.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>
using namespace std;


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg UINT OnQueryUIState();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_QUERYUISTATE()
//ON_WM_TIMER()
END_MESSAGE_MAP()


// CStartupDlg dialog



CStartupDlg::CStartupDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STARTUP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStartupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStartupDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CStartupDlg::OnBnClickedOk)
//	ON_WM_CREATE()
ON_WM_CREATE()
//ON_WM_TIMER()
ON_COMMAND(ID_ABOUTUS_SHOWABOUTUS, &CStartupDlg::OnAboutusShowaboutus)
ON_COMMAND(ID_CHANGETEXT_CHANGETEXT, &CStartupDlg::OnChangetextChangetext)
ON_COMMAND(ID_REFRESH_REFRESH, &CStartupDlg::OnRefreshRefresh)
ON_WM_ERASEBKGND()
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CStartupDlg message handlers
CString GetRegString(HKEY hKeyArg, LPCTSTR keyNameArg, LPCTSTR valNameArg,DWORD length)
{
	CString s;
	CRegKey k;
	k.Open(HKEY_LOCAL_MACHINE, keyNameArg);
	ULONG len = length*2+1;
	k.QueryStringValue(valNameArg, s.GetBufferSetLength(len), &len);
	s.ReleaseBuffer();
	return s;
}
BOOL CStartupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	DWORD dType = REG_SZ, length = 1, size = sizeof(DWORD);
	RegGetValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Startup", L"Length", RRF_RT_DWORD, NULL, &length, &size);

	CString text = GetRegString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Startup", L"Text",length);
	

	this->SetWindowPos(&this->wndTopMost, 100, 60, 1000, 500, NULL);
	CRect rect;
	GetWindowRect(&rect);
	GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, rect.right-rect.left-30, rect.bottom-rect.top-80, NULL);
	

	CFont* font = new CFont();
	font->CreatePointFont(300, L"Arial");

	GetDlgItem(IDC_EDIT1)->SetWindowText(text);
	GetDlgItem(IDC_EDIT1)->SetFont(font);
 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStartupDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStartupDlg::OnPaint()
{
	
	
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);

		
		//exit(1);
	}
	else
	{
		CDialogEx::OnPaint();
	}


}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStartupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStartupDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
}




int CStartupDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	return 0;
}


//void CStartupDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: Add your message handler code here and/or call default
//	/*
//	CDialogEx::OnTimer(nIDEvent);
//	switch (nIDEvent)
//	{
//	case 8:
//		exit(1);
//	}
//	*/
//}


void CStartupDlg::OnAboutusShowaboutus()
{
	// TODO: Add your command handler code here
	CAboutDlg about;
	about.DoModal();
}


void CStartupDlg::OnChangetextChangetext()
{
	// TODO: Add your command handler code here
	CChangeText changeText;
	changeText.DoModal();
	
}


void CStartupDlg::OnRefreshRefresh()
{
	// TODO: Add your command handler code here
	this->OnInitDialog();
}


BOOL CStartupDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(&rect);

	CBrush myBrush(RGB(0, 25, 51)); 	// dialog background color
	pDC->SelectObject(myBrush);  // restore old brush

	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	return bRes;
}


HBRUSH CStartupDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	//// TODO:  Change any attributes of the DC here

	//if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
	//{
	//	pDC->SetTextColor(RGB(255,255, 255));
	//	pDC->SetBkColor(RGB(0, 25, 51));
	//}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
