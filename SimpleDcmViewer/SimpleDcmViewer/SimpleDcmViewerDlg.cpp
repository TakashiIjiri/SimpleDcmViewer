
// SimpleDcmViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleDcmViewer.h"
#include "SimpleDcmViewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimpleDcmViewerDlg dialog



CSimpleDcmViewerDlg::CSimpleDcmViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SIMPLEDCMVIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bPictContInit = false;
}

void CSimpleDcmViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN_CLIPXMIN, m_spin_clipXmin);
	DDX_Control(pDX, IDC_SPIN_CLIPXMAX, m_spin_clipXmax);
	DDX_Control(pDX, IDC_SPIN_CLIPYMIN, m_spin_clipYmin);
	DDX_Control(pDX, IDC_SPIN_CLIPYMAX, m_spin_clipYmax);
	DDX_Control(pDX, IDC_SPIN_CLIPZMIN, m_spin_clipZmin);
	DDX_Control(pDX, IDC_SPIN_CLIPZMAX, m_spin_clipZmax);
	DDX_Control(pDX, IDC_SLIDER_Z     , m_slider_z);
	DDX_Control(pDX, IDC_SLIDER_WINLV_MIN, m_slider_winLvMin);
	DDX_Control(pDX, IDC_SLIDER_WINLV_MAX, m_slider_winLvMax);
}

BEGIN_MESSAGE_MAP(CSimpleDcmViewerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_CLIPXMIN, &CSimpleDcmViewerDlg::OnEnChangeEditClipxmin)
	ON_EN_CHANGE(IDC_EDIT_CLIPXMAX, &CSimpleDcmViewerDlg::OnEnChangeEditClipxmax)
	ON_EN_CHANGE(IDC_EDIT_CLIPYMIN, &CSimpleDcmViewerDlg::OnEnChangeEditClipymin)
	ON_EN_CHANGE(IDC_EDIT_CLIPYMAX, &CSimpleDcmViewerDlg::OnEnChangeEditClipymax)
	ON_EN_CHANGE(IDC_EDIT_CLIPZMIN, &CSimpleDcmViewerDlg::OnEnChangeEditClipzmin)
	ON_EN_CHANGE(IDC_EDIT_CLIPZMAX, &CSimpleDcmViewerDlg::OnEnChangeEditClipzmax)
	ON_WM_DROPFILES()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CSimpleDcmViewerDlg message handlers

BOOL CSimpleDcmViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_spin_clipXmin.SetRange32(0, 0);
	m_spin_clipYmin.SetRange32(0, 0);
	m_spin_clipZmin.SetRange32(0, 0);
	m_spin_clipXmax.SetRange32(0, 0);
	m_spin_clipYmax.SetRange32(0, 0);
	m_spin_clipZmax.SetRange32(0, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSimpleDcmViewerDlg::OnPaint()
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
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSimpleDcmViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CSimpleDcmViewerDlg::OnEnChangeEditClipxmin()
{
	if (!m_bPictContInit) return; 
	if (m_spin_clipXmin.GetPos32() >= m_spin_clipXmax.GetPos32())
	{
		m_spin_clipXmin.SetPos(m_spin_clipXmax.GetPos32() - 1);
	}
	Invalidate(FALSE); 
	UpdateWindow();
}

void CSimpleDcmViewerDlg::OnEnChangeEditClipymin()
{
	if (!m_bPictContInit) return;
	if (m_spin_clipYmin.GetPos32() >= m_spin_clipYmax.GetPos32())
	{
		m_spin_clipYmin.SetPos(m_spin_clipYmax.GetPos32() - 1);
	}
	Invalidate(FALSE);
	UpdateWindow();
}

void CSimpleDcmViewerDlg::OnEnChangeEditClipzmin()
{
	if (!m_bPictContInit) return;
	if (m_spin_clipZmin.GetPos32() >= m_spin_clipZmax.GetPos32())
	{
		m_spin_clipZmin.SetPos(m_spin_clipZmax.GetPos32() - 1);
	}
	Invalidate(FALSE);
	UpdateWindow();
}


void CSimpleDcmViewerDlg::OnEnChangeEditClipxmax()
{
	if (!m_bPictContInit) return;
	if (m_spin_clipXmin.GetPos32() >= m_spin_clipXmax.GetPos32())
	{
		m_spin_clipXmax.SetPos(m_spin_clipXmin.GetPos32() + 1);
	}
	Invalidate(FALSE);
	UpdateWindow();
}

void CSimpleDcmViewerDlg::OnEnChangeEditClipymax()
{
	if (!m_bPictContInit) return;
	if (m_spin_clipYmin.GetPos32() >= m_spin_clipYmax.GetPos32())
	{
		m_spin_clipYmax.SetPos(m_spin_clipYmin.GetPos32() + 1);
	}
	Invalidate(FALSE);
	UpdateWindow();
}

void CSimpleDcmViewerDlg::OnEnChangeEditClipzmax()
{
	if (!m_bPictContInit) return;
	if (m_spin_clipZmin.GetPos32() >= m_spin_clipZmax.GetPos32())
	{
		m_spin_clipZmax.SetPos(m_spin_clipZmin.GetPos32() + 1);
	}
	Invalidate(FALSE);
	UpdateWindow();
}




void CSimpleDcmViewerDlg::OnDropFiles(HDROP hDropInfo)
{

	CDialogEx::OnDropFiles(hDropInfo);
}


void CSimpleDcmViewerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CSimpleDcmViewerDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}




/*

static CBrush m_backBrush;

void CSimpleVolumeViewerDlg::paintPictureControl()
{
if( VolumeFileManager::getInst()->m_D == 0 ) return;

static bool first = true;
if( first )
{
CWnd *cwndPC = GetDlgItem(IDC_MAIN_PICTCONTROL);
first = false;
CRect r;                   cwndPC->GetClientRect(&r);
WINDOWPLACEMENT winplace;  cwndPC->GetWindowPlacement( &winplace );
m_pcW = m_pcH = PC_SIZE;//-2
m_pcX = winplace.rcNormalPosition.left;
m_pcY = winplace.rcNormalPosition.top ;
m_backBrush.CreateSolidBrush( RGB(50,50,50) );
}


//A. picture ControlのCWndを取得
CWnd *pcWnd = GetDlgItem( IDC_MAIN_PICTCONTROL );
CDC  *pcDC  = pcWnd->GetDC();  //pcDC->SetPixel( 3, 4, RGB(10, 10, 10)); これが速ければ何の問題もないのに・・・

//C. デバイスに依存しないカラービットマップを作成
BITMAPINFO binfo;
ZeroMemory( &binfo, sizeof(binfo));
binfo.bmiHeader.biSize     = sizeof(BITMAPINFOHEADER);
binfo.bmiHeader.biBitCount = 32;//1pixel 32-bit (4-byte)
binfo.bmiHeader.biPlanes   =  1      ;
binfo.bmiHeader.biWidth    =  PC_SIZE;
binfo.bmiHeader.biHeight   = -PC_SIZE; //ここが負だと、左上が原点になる(正なら左下が原点)

byte    *bmpbits; //この byte *bmpbits に HBITMAP の中身へのポインタが入る
HBITMAP  hbmp = CreateDIBSection( NULL, &binfo, DIB_RGB_COLORS, (void **)(&bmpbits), NULL, 0);

//D. hbmpに関連付けた CBitmapと、CDCを作成
CBitmap *cbmp = CBitmap::FromHandle( hbmp );//hbmpをCBitmap cbmpに変換
CDC cbmpDC;
cbmpDC.CreateCompatibleDC( pcDC );          //cbmpに関連づけたCDCを準備
CBitmap *oldBmp = cbmpDC.SelectObject( cbmp );

//E. hbmp(cbmp)に ポインタから (bmpbits) から高速にアクセスできる
const int    imgW = VolumeFileManager::getInst()->m_W;
const int    imgH = VolumeFileManager::getInst()->m_H;
const int    imgD = VolumeFileManager::getInst()->m_D;
const int    imgZ = m_slider_depth .GetPos();
const short  vMax = m_slider_winMax.GetPos();
const short  vMin = m_slider_winMin.GetPos();
int x0 = m_spin_xmin.GetPos32(), x1 = m_spin_xmax.GetPos32();  t_cropI(x0,0,imgW-1);  t_cropI(x0,0,imgW-1);
int y0 = m_spin_ymin.GetPos32(), y1 = m_spin_ymax.GetPos32();  t_cropI(y0,0,imgH-1);  t_cropI(y0,0,imgH-1);
int z0 = m_spin_zmin.GetPos32(), z1 = m_spin_zmax.GetPos32();  t_cropI(z0,0,imgD-1);  t_cropI(z0,0,imgD-1);


if( imgZ < 0 || imgZ > imgD - 1 ) return;


const int WH = imgW * imgH;
float *sliceImg = &VolumeFileManager::getInst()->m_volume[ imgZ * WH];


double xCoef = imgW / (double) PC_SIZE;
double yCoef = imgH / (double) PC_SIZE;



for( int y = 0; y < PC_SIZE; ++y)
for( int x = 0; x < PC_SIZE; ++x)
{
int imgX = (int)( (x+0.5) * xCoef );
int imgY = (int)( (y+0.5) * yCoef );
int imgI = imgX + imgY * imgW      ;
const short imgV = (short) sliceImg[ imgI ];

int bmpI = (x + y * PC_SIZE ) * 4;
if( x0 <= imgX && imgX <= x1 && y0 <= imgY && imgY <= y1 && z0 <= imgZ && imgZ <= z1 )
{
byte c  = (byte)( 255.0 * min(1, max(0, ( imgV - vMin) / (double)(vMax-vMin) ) ));
bmpbits[ bmpI + 0 ] = bmpbits[ bmpI + 1 ] = bmpbits[ bmpI + 2 ] = c;
}else{
bmpbits[ bmpI + 0 ] = 192; bmpbits[ bmpI + 1 ] =  bmpbits[ bmpI + 2 ] = 0;
}
}

//F. CDC cbmpDCからもアクセスできて結構便利
//cbmpDC.MoveTo( 10, 10);
//cbmpDC.LineTo( 10, 60);
//cbmpDC.LineTo( 60, 60);
//cbmpDC.LineTo( 60, 10);
//cbmpDC.LineTo( 10, 10);

//G. pcDCにhbmpをコピーする
pcDC->BitBlt( 1,1, PC_SIZE-2, PC_SIZE-2, &cbmpDC, 0,0,SRCCOPY);

//H. 解放を忘れない
cbmpDC.SelectObject( oldBmp );
DeleteDC( cbmpDC );
DeleteObject( hbmp );//HBITMAPを解放
pcWnd->ReleaseDC(pcDC);
}





void CSimpleVolumeViewerDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
if( *pScrollBar == m_slider_depth )
{
CString CStrZ;
CStrZ.Format("%d", m_slider_depth.GetPos() );
((CEdit*)GetDlgItem( IDC_EDIT_IMAGE_Z))->SetWindowTextA( CStrZ);
Invalidate( FALSE );
UpdateWindow();
}

CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CSimpleVolumeViewerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
if( *pScrollBar == m_slider_winMax)
{
CString CStrMax; CStrMax.Format("%d", m_slider_winMax.GetPos());
((CEdit*)GetDlgItem( IDC_EDIT_WINDOW_MAX))->SetWindowTextA(CStrMax);
Invalidate( FALSE );
UpdateWindow();
}
if( *pScrollBar == m_slider_winMin)
{
CString CStrMin; CStrMin.Format("%d", m_slider_winMin.GetPos());
((CEdit*)GetDlgItem( IDC_EDIT_WINDOW_MIN))->SetWindowTextA(CStrMin);
Invalidate( FALSE );
UpdateWindow();
}
CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}





*/