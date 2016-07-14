// DiagramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Othello.h"
#include "DiagramDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MARGIN_LEN	20
//#define get_offset(str, mem)	(int)(&(((str*)0)->mem))
/*
const int CDiagramDlg::m_Offset[8]={0, 0, 0, get_offset(SearchReport, nodes), get_offset(SearchReport, time),
									get_offset(SearchReport, value)
};
*/
/////////////////////////////////////////////////////////////////////////////
// CDiagramDlg dialog


CDiagramDlg::CDiagramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDiagramDlg::IDD, pParent)
{
	m_logFont.lfWidth = 4;  
	m_logFont.lfHeight = 8;
	m_logFont.lfCharSet = GB2312_CHARSET;  //字符集
	m_logFont.lfOutPrecision = 1;  
	m_logFont.lfClipPrecision = 1;  
	m_logFont.lfQuality = PROOF_QUALITY;  
	m_logFont.lfPitchAndFamily = 49;
	m_logFont.lfEscapement = 0;  
	m_logFont.lfOrientation = 0;  
	m_logFont.lfPitchAndFamily = DEFAULT_PITCH|FF_ROMAN;  
	m_logFont.lfUnderline = FALSE;  //下划线
	m_logFont.lfStrikeOut=FALSE;     //删除线  
	m_logFont.lfItalic= FALSE;      //斜体  
	m_logFont.lfWeight= FW_THIN;
	strcpy(m_logFont.lfFaceName, "宋体");

	m_Font.CreateFontIndirect(&m_logFont);

	//{{AFX_DATA_INIT(CDiagramDlg)
	m_ShowType = 0;
	//}}AFX_DATA_INIT
}


void CDiagramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiagramDlg)
	DDX_Radio(pDX, IDC_RADIO_TYPE, m_ShowType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiagramDlg, CDialog)
	//{{AFX_MSG_MAP(CDiagramDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_TYPE, OnRadioType)
	ON_BN_CLICKED(IDC_RADIO2, OnRadioType)
	ON_BN_CLICKED(IDC_RADIO3, OnRadioType)
	ON_BN_CLICKED(IDC_RADIO4, OnRadioType)
	ON_BN_CLICKED(IDC_RADIO5, OnRadioType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagramDlg message handlers

BOOL CDiagramDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ShowType = 0;
	UpdateData(FALSE);
	
	GetDlgItem(IDC_STATIC_DIAGRAM)->GetWindowRect(&m_dRect);
	ScreenToClient(&m_dRect);
	GetDC()->SelectObject(m_Font);

	m_apen.CreatePen(PS_SOLID, 1, 0x00ff00);
	m_wpen.CreatePen(PS_SOLID, 1, 0x00ffff);
	m_bpen.CreatePen(PS_SOLID, 1, 0xff007f);
	m_cpen.CreatePen(PS_SOLID, 1, 0x0000ff);
	InvalidateRect(&m_dRect, FALSE);
	UpdateWindow();

	return TRUE;
}


void CDiagramDlg::DrawDiagram(CDC *pdc)
{
	int nWidth = m_dRect.Width(), 
		nHeight= m_dRect.Height();
	int i, x = m_dRect.left+MARGIN_LEN,
		yMid = m_dRect.top+nHeight/2,
		y;
	long ymax;

	SearchReport* pSR = m_SRHead;

	pdc->FillSolidRect(m_dRect, 0);

	pdc->TextOut(m_dRect.left+5, m_dRect.top+5, "黑方");
	pdc->SelectObject(m_apen);		// draw axes
	pdc->MoveTo(x, m_dRect.top+MARGIN_LEN);
	pdc->LineTo(x, m_dRect.bottom-MARGIN_LEN);
	pdc->MoveTo(x, yMid);
	pdc->LineTo(m_dRect.right-MARGIN_LEN, yMid);
	pdc->TextOut(m_dRect.left+5, m_dRect.bottom-20, "白方");


	if(m_SRTop<=0) return;
	CPen dpen;
	dpen.CreatePen(PS_DOT,1,0xff00);
	pdc->SelectObject(dpen);
	nWidth-=2*MARGIN_LEN;
	int xStep= nWidth/(m_SRTop<10?10:m_SRTop);
	for(i=0; i<m_SRTop/10; i++){
		pdc->MoveTo(x+nWidth/(m_SRTop)*10*(i+1), m_dRect.top+MARGIN_LEN);
		pdc->LineTo(x+nWidth/(m_SRTop)*10*(i+1), m_dRect.bottom-MARGIN_LEN);		
	}
	dpen.DeleteObject();

	nHeight-=2*MARGIN_LEN;
	x = m_dRect.left+MARGIN_LEN;	

	if(m_ShowType<2){
		ymax = 128;
		if(m_ShowType==0){
			pdc->SelectObject(m_cpen);
			pdc->MoveTo(x, yMid);
			for(i=0; x+=xStep, i<m_SRTop; i++, pSR++){
				y=int((pSR->bw[1]-pSR->bw[0])*nHeight/ymax);
				pdc->LineTo(x, yMid+y);
			}
		}else{//discnum
			pdc->SelectObject(m_bpen);
			pdc->MoveTo(x, yMid-4);
			for(i=0; x+=xStep, i<m_SRTop; i++, pSR++){
				y=int(pSR->bw[0]*nHeight/ymax);
				pdc->LineTo(x, yMid-y);
			}
			x = m_dRect.left+MARGIN_LEN;
			pSR=m_SRHead;
			pdc->SelectObject(m_wpen);
			pdc->MoveTo(x, yMid+4);
			for(i=0; x+=xStep, i<m_SRTop; i++, pSR++){
				y=int(pSR->bw[1]*nHeight/ymax);
				pdc->LineTo(x, yMid+y);
			}		
		}
		return;
	}

	ymax = 1;
	for(i=0; i<m_SRTop; i++, pSR++)
		if(GetValueInSR(pSR)>ymax) ymax=GetValueInSR(pSR);
	pSR=m_SRHead;
	ymax += ymax;
	
//	pSR=m_SRHead;
	pdc->SelectObject(m_bpen);
	pdc->MoveTo(x, yMid);
	for(i=0; x+=xStep, i<m_SRTop; i++, pSR++){
		if(pSR->color==0){
			y=int(GetValueInSR(pSR)*nHeight/ymax);
			pdc->LineTo(x, yMid-y);
		}
	}
	x = m_dRect.left+MARGIN_LEN;
	pSR=m_SRHead;
	pdc->SelectObject(m_wpen);
	pdc->MoveTo(x, yMid);
	for(i=0; x+=xStep, i<m_SRTop; i++, pSR++){
		if(pSR->color==1){
			y=int(GetValueInSR(pSR)*nHeight/ymax);
			pdc->LineTo(x, yMid+y);
		}
	}
}

void CDiagramDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
//	dc.SetTextAlign(TA_CENTER);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(0xffffff);
	DrawDiagram(&dc);
	
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDiagramDlg::OnRadioType() 
{
	UpdateData(TRUE);
	InvalidateRect(&m_dRect, FALSE);
	UpdateWindow();	
}

long CDiagramDlg::GetValueInSR(SearchReport *psr)
{
	if(m_ShowType==0) return psr->bw[0]-psr->bw[1];
	if(m_ShowType==1) return psr->bw[0]-psr->bw[1];
	if(m_ShowType==2) return long(psr->time*1000);
	if(m_ShowType==3) return long(psr->nodes);
	if(m_ShowType==4) return long(psr->value);
//	if(m_ShowType==3) return psr->bw[0]-psr->bw[1];
	return 0;
}
