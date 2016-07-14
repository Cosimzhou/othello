#if !defined(AFX_OPENINGDLG_H__3D663EEE_181C_4EEC_995E_41BF957E02F8__INCLUDED_)
#define AFX_OPENINGDLG_H__3D663EEE_181C_4EEC_995E_41BF957E02F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpeningDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpeningDlg dialog

class COpeningDlg : public CDialog
{
// Construction
public:
	char m_StepList[128];
	COpeningDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpeningDlg)
	enum { IDD = IDD_OPENINGDLG_DIALOG };
	CTreeCtrl	m_Tree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpeningDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_FirstLoc;
	void Rotate();
	BYTE* m_lpBy;
	void InitData();
	CImageList m_Images;

	// Generated message map functions
	//{{AFX_MSG(COpeningDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClickTreeview(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioC4();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENINGDLG_H__3D663EEE_181C_4EEC_995E_41BF957E02F8__INCLUDED_)
