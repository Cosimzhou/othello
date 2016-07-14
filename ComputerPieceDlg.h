#if !defined(AFX_COMPUTERPIECEDLG_H__7578E456_D21E_4E90_AAE7_BD87593726BA__INCLUDED_)
#define AFX_COMPUTERPIECEDLG_H__7578E456_D21E_4E90_AAE7_BD87593726BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CComputerPieceDlg dialog

class CComputerPieceDlg : public CDialog
{
// Construction
public:
	int m_BlackPlayer;
	int m_WhitePlayer;
//	void Receive(int*);
	CComputerPieceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CComputerPieceDlg)
	enum { IDD = IDD_COMPUTERPIECEDLG_DIALOG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComputerPieceDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
	//{{AFX_MSG(CComputerPieceDlg)
	virtual void OnOK();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonExchange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPUTERPIECEDLG_H__7578E456_D21E_4E90_AAE7_BD87593726BA__INCLUDED_)
