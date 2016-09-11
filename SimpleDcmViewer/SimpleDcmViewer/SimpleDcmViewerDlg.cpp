// SimpleDcmViewerDlg.cpp : implementation file
//





#include "stdafx.h"
#include "SimpleDcmViewer.h"
#include "SimpleDcmViewerDlg.h"
#include "afxdialogex.h"
#include "TFileManager.h"

#include "TExportDataSizeDlg.h"

#include <vector>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning( disable: 4996 )


#define PC_SIZE 700



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
	ON_WM_DROPFILES()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_EN_CHANGE (IDC_EDIT_CLIPXMIN		 , &CSimpleDcmViewerDlg::OnEnChangeEditClipxmin)
	ON_EN_CHANGE (IDC_EDIT_CLIPXMAX		 , &CSimpleDcmViewerDlg::OnEnChangeEditClipxmax)
	ON_EN_CHANGE (IDC_EDIT_CLIPYMIN		 , &CSimpleDcmViewerDlg::OnEnChangeEditClipymin)
	ON_EN_CHANGE (IDC_EDIT_CLIPYMAX		 , &CSimpleDcmViewerDlg::OnEnChangeEditClipymax)
	ON_EN_CHANGE (IDC_EDIT_CLIPZMIN		 , &CSimpleDcmViewerDlg::OnEnChangeEditClipzmin)
	ON_EN_CHANGE (IDC_EDIT_CLIPZMAX		 , &CSimpleDcmViewerDlg::OnEnChangeEditClipzmax)
	ON_BN_CLICKED(IDC_BUTTON_EXPORTTRAW3D, &CSimpleDcmViewerDlg::OnBnClickedButtonExporttraw3d)
	ON_BN_CLICKED(IDC_BUTTON_QUIT		 , &CSimpleDcmViewerDlg::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_EXPORTTRAW3D_USHORT, &CSimpleDcmViewerDlg::OnBnClickedButtonExporttraw3dUshort)
END_MESSAGE_MAP()





BOOL CSimpleDcmViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DragAcceptFiles();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE );			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_spin_clipXmin.SetRange32(0, 0);
	m_spin_clipYmin.SetRange32(0, 0);
	m_spin_clipZmin.SetRange32(0, 0);
	m_spin_clipXmax.SetRange32(0, 0);
	m_spin_clipYmax.SetRange32(0, 0);
	m_spin_clipZmax.SetRange32(0, 0);

	m_slider_z.SetRange( 0, 0 );
	m_slider_z.SetPos  ( 0    );


	//resize DIALOG and PICTURE CONTROL = 『PC_SIZE』
	CWnd *h_PC = GetDlgItem(IDC_PC);

	WINDOWPLACEMENT wplm_dlg, wplm_pc;
	this->GetWindowPlacement( &wplm_dlg );
	h_PC->GetWindowPlacement( &wplm_pc  );


	//resize dlg
	int dlgW = wplm_dlg.rcNormalPosition.right  - wplm_dlg.rcNormalPosition.left;
	int dlgH = wplm_dlg.rcNormalPosition.bottom - wplm_dlg.rcNormalPosition.top ;
	dlgW = max( dlgW, PC_SIZE + wplm_pc.rcNormalPosition.left + 30 );
	dlgH = max( dlgH, PC_SIZE + wplm_pc.rcNormalPosition.top  + 30 );

	this->SetWindowPos( &CWnd::wndNoTopMost, wplm_dlg.rcNormalPosition.left, wplm_dlg.rcNormalPosition.top, dlgW, dlgH, SWP_NOACTIVATE | SWP_SHOWWINDOW  );
	h_PC->MoveWindow( wplm_pc .rcNormalPosition.left, wplm_pc.rcNormalPosition .top, PC_SIZE, PC_SIZE);

	m_bPictContInit = true;

	return TRUE;  // return TRUE  unless you set the focus to a control
}





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
		drawPictCtrl();
		CDialogEx::OnPaint();
	}
}




// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSimpleDcmViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




static void t_cropI(int &x, const int &minV, const int &maxV)
{
	if (x < minV) x = minV;
	if (x > maxV) x = maxV;
}

static void t_cropD(double &x, const double &minV, const double &maxV)
{
	if (x < minV) x = minV;
	if (x > maxV) x = maxV;
}




void CSimpleDcmViewerDlg::drawPictCtrl()
{
	if (TFileManager::getInst()->m_D == 0) return;

	static bool first = true;

	if (first)
	{
		CWnd *cwndPC = GetDlgItem(IDC_PC);
		first = false;
		CRect r;
		WINDOWPLACEMENT winplace;
		cwndPC->GetClientRect(&r);
		cwndPC->GetWindowPlacement(&winplace);

		m_pcW = m_pcH = PC_SIZE;//-2
		m_pcX = winplace.rcNormalPosition.left;
		m_pcY = winplace.rcNormalPosition.top;
	}


	// picture ControlのCWndを取得
	CWnd *pcWnd = GetDlgItem(IDC_PC);
	CDC  *pcDC = pcWnd->GetDC(); 


	BITMAPINFO binfo;
	ZeroMemory(&binfo, sizeof(binfo));
	binfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	binfo.bmiHeader.biBitCount = 32;//1pixel 32-bit (4-byte)
	binfo.bmiHeader.biPlanes   = 1;
	binfo.bmiHeader.biWidth    =  PC_SIZE;
	binfo.bmiHeader.biHeight   = -PC_SIZE; //if negative : origin --> left top 

	byte    *bmpbits; 
	HBITMAP  hbmp = CreateDIBSection(NULL, &binfo, DIB_RGB_COLORS, (void **)(&bmpbits), NULL, 0);

	CBitmap *cbmp = CBitmap::FromHandle(hbmp);
	CDC cbmpDC;
	cbmpDC.CreateCompatibleDC(pcDC);          
	CBitmap *oldBmp = cbmpDC.SelectObject(cbmp);

	const int    imgW = TFileManager::getInst()->m_W;
	const int    imgH = TFileManager::getInst()->m_H;
	const int    imgD = TFileManager::getInst()->m_D;
	const int    imgZ = - m_slider_z       .GetPos();
	const float  vMax = (float)m_slider_winLvMax.GetPos();
	const float  vMin = (float)m_slider_winLvMin.GetPos();
	int x0 = m_spin_clipXmin.GetPos32(), x1 = m_spin_clipXmax.GetPos32();  t_cropI(x0, 0, imgW - 1);  t_cropI(x0, 0, imgW - 1);
	int y0 = m_spin_clipYmin.GetPos32(), y1 = m_spin_clipYmax.GetPos32();  t_cropI(y0, 0, imgH - 1);  t_cropI(y0, 0, imgH - 1);
	int z0 = m_spin_clipZmin.GetPos32(), z1 = m_spin_clipZmax.GetPos32();  t_cropI(z0, 0, imgD - 1);  t_cropI(z0, 0, imgD - 1);

	if (imgZ < 0 || imgZ > imgD - 1) return;


	const int WH = imgW * imgH;
	float *sliceImg = TFileManager::getInst()->m_volume[imgZ];

	double xCoef = imgW / (double)PC_SIZE;
	double yCoef = imgH / (double)PC_SIZE;

	for (int y = 0; y < PC_SIZE; ++y)
	{
		for (int x = 0; x < PC_SIZE; ++x)
		{
			int imgX = (int)((x + 0.5) * xCoef);
			int imgY = (int)((y + 0.5) * yCoef);
			int imgI = imgX + imgY * imgW;
			const float imgV = sliceImg[imgI];

			int bmpI = (x + y * PC_SIZE) * 4;
			if (x0 <= imgX && imgX <= x1 && y0 <= imgY && imgY <= y1 && z0 <= imgZ && imgZ <= z1)
			{
				byte c = (byte)(255.0 * min(1, max(0, (imgV - vMin) / (vMax - vMin))));
				bmpbits[bmpI + 0] = bmpbits[bmpI + 1] = bmpbits[bmpI + 2] = c;
			}
			else {
				bmpbits[bmpI + 0] = 192; bmpbits[bmpI + 1] = bmpbits[bmpI + 2] = 0;
			}
		}
	}

	pcDC->BitBlt(1, 1, PC_SIZE - 2, PC_SIZE - 2, &cbmpDC, 0, 0, SRCCOPY);


	//解放
	cbmpDC.SelectObject(oldBmp);
	DeleteDC(cbmpDC);
	DeleteObject(hbmp);
	pcWnd->ReleaseDC(pcDC);
}
//m_backBrush.CreateSolidBrush(RGB(50, 50, 50));

















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
	UINT numFile = DragQueryFile(hDropInfo, ~0lu, NULL, 0);

	if (numFile >= 2)
	{
		AfxMessageBox("drop only one folder\n");
		return;
	}

	UINT pathLen = DragQueryFile(hDropInfo, 0, NULL, 0);

	CString path;
	DragQueryFile(hDropInfo, 0, path.GetBuffer(pathLen + 1), pathLen + 1);
	path.ReleaseBuffer();

	if (!PathIsDirectoryA(path))
	{
		AfxMessageBox("please drop a folder (not a file)\n");
		return;
	}
	
	TFileManager::getInst()->loadDirectry( string(path) );
	NewVolumeLoaded();


	CDialog::OnDropFiles(hDropInfo);
}







void CSimpleDcmViewerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (*pScrollBar == m_slider_winLvMax)
	{
		CString CStrMax; 
		CStrMax.Format("%d", m_slider_winLvMax.GetPos());
		((CEdit*)GetDlgItem(IDC_EDIT_WINLV_MAX))->SetWindowTextA(CStrMax);
		Invalidate(FALSE);
		UpdateWindow();
	}
	if (*pScrollBar == m_slider_winLvMin)
	{
		CString CStrMin; 
		CStrMin.Format("%d", m_slider_winLvMin.GetPos());
		((CEdit*)GetDlgItem(IDC_EDIT_WINLV_MIN))->SetWindowTextA(CStrMin);
		Invalidate(FALSE);
		UpdateWindow();
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}



void CSimpleDcmViewerDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (*pScrollBar == m_slider_z)
	{
		CString CStrZ;
		CStrZ.Format("%d", -m_slider_z.GetPos());
		((CEdit*)GetDlgItem(IDC_EDIT_ZVALUE))->SetWindowTextA(CStrZ);

		Invalidate(FALSE);
		UpdateWindow();
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}






//directry loading 直後に呼ばれる
void CSimpleDcmViewerDlg::NewVolumeLoaded()
{
	TFileManager *FM = TFileManager::getInst();

	//Loaded Image information
	CString strPitch, strRes;
	strPitch.Format("pitch:%.4f %.4f %.4f (mm)\n", FM->m_pW, FM->m_pH, FM->m_pD);
	strRes  .Format("reso :%d %d %d"             , FM->m_W , FM->m_H , FM->m_D );
	SetDlgItemText(IDC_STATICTEXT_DCMINFO, strPitch + strRes);


	//clipping info (double値のCubeSizeで制御)
	const int W = FM->m_W, H = FM->m_H, D = FM->m_D;
	m_spin_clipXmin.SetRange32(0, W - 1); 
	m_spin_clipXmax.SetRange32(0, W - 1);
	m_spin_clipYmin.SetRange32(0, H - 1); 
	m_spin_clipYmax.SetRange32(0, H - 1);
	m_spin_clipZmin.SetRange32(0, D - 1); 
	m_spin_clipZmax.SetRange32(0, D - 1);

	m_spin_clipXmin.SetPos32( 0     ); 
	m_spin_clipXmax.SetPos32( W - 1 );
	m_spin_clipYmin.SetPos32( 0     );
	m_spin_clipYmax.SetPos32( H - 1 );
	m_spin_clipZmin.SetPos32( 0     );
	m_spin_clipZmax.SetPos32( D - 1 );

	//window level 
	m_slider_winLvMin.SetRange( (int)FM->m_valMin, (int)FM->m_valMax);  m_slider_winLvMin.SetPos((int)FM->m_valMin);
	m_slider_winLvMax.SetRange( (int)FM->m_valMin, (int)FM->m_valMax);  m_slider_winLvMax.SetPos((int)FM->m_valMax);

	CString CStrMin, CStrMax;
	CStrMin.Format("%d", m_slider_winLvMin.GetPos());
	CStrMax.Format("%d", m_slider_winLvMax.GetPos());
	((CEdit*)GetDlgItem(IDC_EDIT_WINLV_MAX))->SetWindowTextA(CStrMax);
	((CEdit*)GetDlgItem(IDC_EDIT_WINLV_MIN))->SetWindowTextA(CStrMin);

	//z slider
	m_slider_z.SetRange( -(D - 1), 0);
	m_slider_z.SetPos  ( - (D / 2) );
	CString CStrZ; CStrZ.Format("%d", - m_slider_z.GetPos());
	((CEdit*)GetDlgItem(IDC_EDIT_ZVALUE))->SetWindowTextA(CStrZ);

	RedrawWindow();
}





void CSimpleDcmViewerDlg::OnBnClickedButtonQuit()
{
	exit(0);
}




void CSimpleDcmViewerDlg::OnBnClickedButtonExporttraw3d()
{
	//file名取得	
	CString filter("traw signed short 3D (*traw3D_ss)|*.traw3D_ss||");
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_CREATEPROMPT, filter);
	if (dlg.DoModal() != IDOK) return;
	string fname(dlg.GetPathName());
	if (strcmp(dlg.GetFileExt(), "traw3D_ss") != 0) fname = fname + ".traw3D_ss";

	//等方voxelを出力する
	TFileManager* FM = TFileManager::getInst();

	//入力 volume に関する値は  in*
	//出力 volume に関する値は out*
	int in_x0 = max(0, min(FM->m_W - 1, m_spin_clipXmin.GetPos32())), in_x1 = max(0, min(FM->m_W - 1, m_spin_clipXmax.GetPos32()));
	int in_y0 = max(0, min(FM->m_H - 1, m_spin_clipYmin.GetPos32())), in_y1 = max(0, min(FM->m_H - 1, m_spin_clipYmax.GetPos32()));
	int in_z0 = max(0, min(FM->m_D - 1, m_spin_clipZmin.GetPos32())), in_z1 = max(0, min(FM->m_D - 1, m_spin_clipZmax.GetPos32()));

	double pitchMin = min(FM->m_pW, min(FM->m_pH, FM->m_pD));


	TExportDataSizeDlg paramDlg((int)((in_x1 - in_x0 + 1) * FM->m_pW / pitchMin),
								(int)((in_y1 - in_y0 + 1) * FM->m_pH / pitchMin),
								(int)((in_z1 - in_z0 + 1) * FM->m_pD / pitchMin));
	
	if (paramDlg.DoModal() != IDOK) return;
	int  outW   = paramDlg.m_expW;
	int  outH   = paramDlg.m_expH;
	int  outD   = paramDlg.m_expD;
	bool bFlipZ = paramDlg.m_bFlipInZ;
	double rateW = (in_x1 - in_x0 + 1) / (double)outW;
	double rateH = (in_y1 - in_y0 + 1) / (double)outH;
	double rateD = (in_z1 - in_z0 + 1) / (double)outD;
	double pW = FM->m_pW * rateW;
	double pH = FM->m_pH * rateH;
	double pD = FM->m_pD * rateD;
	fprintf(stderr, "resolution (%d %d %d)\n", outW, outH, outD);
	fprintf(stderr, "rate       (%f %f %f)\n", rateW, rateH, rateD);
	fprintf(stderr, "pitch      (%f %f %f)\n", pW, pH, pD);


	//file open ------------------------------------
	FILE *fp = fopen(fname.c_str(), "wb");
	if (fp == 0) return;

	//header info   W, H, D,  pitchX, pitchY, pitchZ 
	fwrite(&outW, sizeof( int  ), 1, fp);
	fwrite(&outH, sizeof( int  ), 1, fp);
	fwrite(&outD, sizeof( int  ), 1, fp);
	fwrite(&pW  , sizeof(double), 1, fp);
	fwrite(&pH  , sizeof(double), 1, fp);
	fwrite(&pD  , sizeof(double), 1, fp);

	//画像書き込み
	float *inImg2D1 = new float[FM->m_W * FM->m_H]; //補間のため2個用意
	float *inImg2D2 = new float[FM->m_W * FM->m_H];

	const int inImgW = FM->m_W;
	const int inImgH = FM->m_H;
	const int inImgD = FM->m_D;

	for (int z = 0; z < outD; ++z)
	{
		double zPos = (!bFlipZ) ? (z + 0.5) * rateD + in_z0 :
			(outD - 1 - z + 0.5) * rateD + in_z0;
		int inZpre = (int)(zPos - 0.5); t_cropI(inZpre, in_z0, in_z1);
		int inZnex = (int)(zPos + 0.5); t_cropI(inZnex, in_z0, in_z1);
		double tZ = zPos - (inZpre + 0.5);
		FM->getSliceImg_Zth_slice(inZpre, inImg2D1);
		FM->getSliceImg_Zth_slice(inZnex, inImg2D2);


		for (int y = 0; y < outH; ++y)
		{
			double yPos = (y + 0.5) * rateH + in_y0;
			int    inYpre = (int)(yPos - 0.5); t_cropI(inYpre, in_y0, in_y1);
			int    inYnex = (int)(yPos - 0.5); t_cropI(inYnex, in_y0, in_y1);

			for (int x = 0; x < outW; ++x)
			{
				double xPos = (x + 0.5) * rateW + in_x0;
				int    inXpre = (int)(xPos - 0.5); t_cropI(inXpre, in_x0, in_x1);
				int    inXnex = (int)(xPos - 0.5); t_cropI(inXnex, in_x0, in_x1);

				double tY = yPos - (inYpre + 0.5);
				double tX = xPos - (inXpre + 0.5);

				//  c1   c2  x→
				//           y↓
				//  c3   c4   
				double c1    = (1 - tZ) * inImg2D1[inXpre + inYpre * inImgW] + tZ * inImg2D2[inXpre + inYpre * inImgW];
				double c2    = (1 - tZ) * inImg2D1[inXnex + inYpre * inImgW] + tZ * inImg2D2[inXnex + inYpre * inImgW];
				double c3    = (1 - tZ) * inImg2D1[inXpre + inYnex * inImgW] + tZ * inImg2D2[inXpre + inYnex * inImgW];
				double c4    = (1 - tZ) * inImg2D1[inXnex + inYnex * inImgW] + tZ * inImg2D2[inXnex + inYnex * inImgW];
				double c13   = (1 - tY) * c1 + tY * c3;
				double c24   = (1 - tY) * c2 + tY * c4;
				double c1324 = (1 - tX) * c13+ tX * c24;
				t_cropD(c1324, SHRT_MIN, SHRT_MAX);
				short  s1324 = (short)c1324;
				fwrite(&s1324, sizeof(short), 1, fp);
			}
		}
		fprintf(stderr, "(%d/%d)done ", z, outD);
	}

	delete[] inImg2D1;
	delete[] inImg2D2;
	fclose(fp);
}



void CSimpleDcmViewerDlg::OnBnClickedButtonExporttraw3dUshort()
{
	//todo 
	//	make this sined short and u short!!


}
