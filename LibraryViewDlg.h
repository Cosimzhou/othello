#if !defined(AFX_LIBRARYVIEWDLG_H__CE6212AF_8433_42BA_8A52_1CD126F33A07__INCLUDED_)
#define AFX_LIBRARYVIEWDLG_H__CE6212AF_8433_42BA_8A52_1CD126F33A07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LibraryViewDlg.h : header file
//

typedef struct{		//文件头结构
	BYTE hyear;		//1字节 文件建立年份的百位部分，如20表示20**年
	BYTE lyear;		//1字节 文件建立年份的低2位
	BYTE month;		//1字节 文件建立的月份
	BYTE date;		//1字节 文件建立的日期
	DWORD librec;	//4字节 N1，文件包含的记录数（这个是对局库用的）
	WORD player;	//2字节 N2，文件包含的记录数（这个是棋手库和比赛库用的）
	WORD year;		//2字节 对局年份
	BYTE size;		//1字节 P1，棋盘大小，0或8表示8*8
	BYTE type;		//1字节 P2，游戏类型，1表示solitaires游戏，0表示其他（包括黑白棋）
	BYTE bestdepth;	//1字节 P3，最佳终局计算的搜索深度，一般为22
	BYTE breserve;	//1字节 保留
}WTHOR_FILE_HEADER;	//16 bytes

typedef struct{		//对局库记录结构，对于8*8黑白棋，每条记录68字节
	WORD match_no;	//2字节 比赛名称，这里只是个序号，具体名称要查比赛库中的相应记录
	WORD bla_no;	//2字节 黑方棋手名字，这里只是个序号，具体名字要查棋手库
	WORD whi_no;	//2字节 白方棋手名字
	BYTE black;		//1字节 对局结束时黑方的棋子数（多余空格归胜方）
	BYTE best_bla;	//1字节 黑方理论最佳得子，即在剩余P3个空格时，进行最佳终局计算，黑方的得子数
	BYTE step[60];	//60字节 棋步序列，每步棋一个字节，记为行号*10+列号，如A1=11，A2=21。欠行的步不作记录，只是将最后多余字节填0
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
