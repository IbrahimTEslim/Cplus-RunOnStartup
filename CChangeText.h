#pragma once


// CChangeText dialog

class CChangeText : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeText)

public:
	CChangeText(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CChangeText();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
