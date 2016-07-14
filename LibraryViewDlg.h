#if !defined(AFX_LIBRARYVIEWDLG_H__CE6212AF_8433_42BA_8A52_1CD126F33A07__INCLUDED_)
#define AFX_LIBRARYVIEWDLG_H__CE6212AF_8433_42BA_8A52_1CD126F33A07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LibraryViewDlg.h : header file
//

typedef struct{		//�ļ�ͷ�ṹ
	BYTE hyear;		//1�ֽ� �ļ�������ݵİ�λ���֣���20��ʾ20**��
	BYTE lyear;		//1�ֽ� �ļ�������ݵĵ�2λ
	BYTE month;		//1�ֽ� �ļ��������·�
	BYTE date;		//1�ֽ� �ļ�����������
	DWORD librec;	//4�ֽ� N1���ļ������ļ�¼��������ǶԾֿ��õģ�
	WORD player;	//2�ֽ� N2���ļ������ļ�¼������������ֿ�ͱ������õģ�
	WORD year;		//2�ֽ� �Ծ����
	BYTE size;		//1�ֽ� P1�����̴�С��0��8��ʾ8*8
	BYTE type;		//1�ֽ� P2����Ϸ���ͣ�1��ʾsolitaires��Ϸ��0��ʾ�����������ڰ��壩
	BYTE bestdepth;	//1�ֽ� P3������վּ����������ȣ�һ��Ϊ22
	BYTE breserve;	//1�ֽ� ����
}WTHOR_FILE_HEADER;	//16 bytes

typedef struct{		//�Ծֿ��¼�ṹ������8*8�ڰ��壬ÿ����¼68�ֽ�
	WORD match_no;	//2�ֽ� �������ƣ�����ֻ�Ǹ���ţ���������Ҫ��������е���Ӧ��¼
	WORD bla_no;	//2�ֽ� �ڷ��������֣�����ֻ�Ǹ���ţ���������Ҫ�����ֿ�
	WORD whi_no;	//2�ֽ� �׷���������
	BYTE black;		//1�ֽ� �Ծֽ���ʱ�ڷ���������������ո��ʤ����
	BYTE best_bla;	//1�ֽ� �ڷ�������ѵ��ӣ�����ʣ��P3���ո�ʱ����������վּ��㣬�ڷ��ĵ�����
	BYTE step[60];	//60�ֽ� �岽���У�ÿ����һ���ֽڣ���Ϊ�к�*10+�кţ���A1=11��A2=21��Ƿ�еĲ�������¼��ֻ�ǽ��������ֽ���0
}LIBRARY_RECORD;	//68 bytes

/////////////////////////////////////////////////////////////////////////////
// CLibraryViewDlg dialog

class CLibraryViewDlg : public CDialog
{
// Construction
public:
	CString lpszPathName;
	char m_Item[121];
	CLibraryViewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLibraryViewDlg)
	enum { IDD = IDD_LIBRARYVIEWDLG_DIALOG };
	CListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibraryViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFile m_File;
	void ReadData(CString lpszPathName);

	// Generated message map functions
	//{{AFX_MSG(CLibraryViewDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBRARYVIEWDLG_H__CE6212AF_8433_42BA_8A52_1CD126F33A07__INCLUDED_)
