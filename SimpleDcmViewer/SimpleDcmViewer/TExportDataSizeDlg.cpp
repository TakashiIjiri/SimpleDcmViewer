// TExportDataSizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleDcmViewer.h"
#include "TExportDataSizeDlg.h"
#include "afxdialogex.h"


// TExportDataSizeDlg dialog

IMPLEMENT_DYNAMIC(TExportDataSizeDlg, CDialogEx)

TExportDataSizeDlg::TExportDataSizeDlg(const int w, const int h, const int d, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_EXPORT, pParent), m_W(w), m_H(h), m_D(d)
{
}

TExportDataSizeDlg::~TExportDataSizeDlg()
{
}

void TExportDataSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Control(pDX, IDC_CHECK_FLIP, m_check_flipz);
}


BEGIN_MESSAGE_MAP(TExportDataSizeDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_FLIP, &TExportDataSizeDlg::OnBnClickedCheckFlip)
END_MESSAGE_MAP()


// TExportDataSizeDlg message handlers



void TExportDataSizeDlg::updateEditBoxInfo()
{
	double rate = m_slider.GetPos() / (double)m_W;
	m_expW = m_slider.GetPos();
	m_expH = (int)(m_H * rate);
	m_expD = (int)(m_D * rate);

	double g = 2.0 * m_expW * m_expH * m_expD / 1024.0 / 1024.0;

	CString str;
	str.Format("Resolution(%d, %d %d), file Size %.1f Mbyte", m_expW, m_expH, m_expD, g);
	SetDlgItemText(IDC_TEXT_EXPORT_SIZE, str);
}


void TExportDataSizeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	if ( *pScrollBar == m_slider)
	{
		double rate = m_slider.GetPos() / (double)m_W;
		m_expW = m_slider.GetPos();
		m_expH = (int)(m_H * rate);
		m_expD = (int)(m_D * rate);

		double g = 2.0 * m_expW * m_expH * m_expD / 1024.0 / 1024.0;

		CString str;
		str.Format("Resolution(%d, %d %d), file Size %.1f Mbyte", m_expW, m_expH, m_expD, g ); 
		SetDlgItemText(IDC_TEXT_EXPORT_SIZE, str );
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}





void TExportDataSizeDlg::OnBnClickedCheckFlip()
{
	m_bFlipZ = m_check_flipz.GetCheck() ? true : false;
}


BOOL TExportDataSizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	fprintf(stderr, "%d %d %d\n", m_W, m_H, m_D);
	m_slider.SetRange(m_W / 5, m_W);
	m_slider.SetPos(m_W);
	updateEditBoxInfo();

	m_bFlipZ = true;
	m_check_flipz.SetCheck(1);



	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
