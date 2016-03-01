
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
	// TODO: Add your message handler code here and/or call default

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
