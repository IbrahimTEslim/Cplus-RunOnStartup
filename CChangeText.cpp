// CChangeText.cpp : implementation file
//

#include "pch.h"
#include "Startup.h"
#include "CChangeText.h"
#include "afxdialogex.h"


// CChangeText dialog

IMPLEMENT_DYNAMIC(CChangeText, CDialogEx)

CChangeText::CChangeText(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CChangeText::~CChangeText()
{
}

void CChangeText::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChangeText, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChangeText::OnBnClickedOk)
END_MESSAGE_MAP()


// CChangeText message handlers

HKEY openRegKey(HKEY hKeyRoot, wchar_t* subKey) {
	HKEY hKey;
	LONG lError = RegOpenKeyEx(hKeyRoot, subKey, NULL, KEY_ALL_ACCESS, &hKey);
	if (lError == ERROR_FILE_NOT_FOUND) {
		lError = RegCreateKeyEx(hKeyRoot, subKey, NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	}
	if (lError != ERROR_SUCCESS) {
	}
	return hKey;
}

bool setRegValue(HKEY hKey, LPCWSTR valueName, CString data) {
	const BYTE* pb = reinterpret_cast<const BYTE*>(data.GetString());
	LONG lError = RegSetValueEx(hKey, valueName, 0, REG_SZ, pb, data.GetLength() * 2 + 1);
	if (lError == ERROR_SUCCESS) return 1;
	else return 0;
}
bool setRegValue(HKEY hKey, LPCWSTR valueName, DWORD data) {
	
	LONG lError = RegSetValueEx(hKey, valueName, 0, REG_DWORD, (LPBYTE)&data, sizeof(DWORD));
	if (lError == ERROR_SUCCESS) return 1;
	else return 0;
}

void CChangeText::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString text;
	HKEY hKey = openRegKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Startup");
	GetDlgItemText(IDC_EDIT1, text);
	setRegValue(hKey, L"Text", text + '\0');
	setRegValue(hKey, L"Length", text.GetLength());
	CDialogEx::OnOK();
}
#ifndef GetRegString
CString GetRegString2(HKEY hKeyArg, LPCTSTR keyNameArg, LPCTSTR valNameArg, DWORD length)
{
	CString s;
	CRegKey k;
	k.Open(HKEY_LOCAL_MACHINE, keyNameArg);
	ULONG len = length * 2 + 1;
	k.QueryStringValue(valNameArg, s.GetBufferSetLength(len), &len);
	s.ReleaseBuffer();
	return s;
}

#endif // !GetRegString


BOOL CChangeText::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	DWORD dType = REG_SZ, length = 1, size = sizeof(DWORD);
	RegGetValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Startup", L"Length", RRF_RT_DWORD, NULL, &length, &size);

	CString text = GetRegString2(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Startup", L"Text", length);

	GetDlgItem(IDC_EDIT1)->SetWindowText(text);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
