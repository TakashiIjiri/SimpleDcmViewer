
// SimpleDcmViewerDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CSimpleDcmViewerDlg dialog
class CSimpleDcmViewerDlg : public CDialogEx
{

	bool m_bPictContInit;
	int m_pcW, m_pcH, m_pcX, m_pcY;

	void NewVolumeLoaded();
	void drawPictCtrl();


// Construction
public:
	CSimpleDcmViewerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIMPLEDCMVIEWER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSpinButtonCtrl m_spin_clipXmin;
	CSpinButtonCtrl m_spin_clipXmax;
	CSpinButtonCtrl m_spin_clipYmin;
	CSpinButtonCtrl m_spin_clipYmax;
	CSpinButtonCtrl m_spin_clipZmin;
	CSpinButtonCtrl m_spin_clipZmax;
	afx_msg void OnEnChangeEditClipxmin();
	afx_msg void OnEnChangeEditClipxmax();
	afx_msg void OnEnChangeEditClipymin();
	afx_msg void OnEnChangeEditClipymax();
	afx_msg void OnEnChangeEditClipzmin();
	afx_msg void OnEnChangeEditClipzmax();
	CSliderCtrl m_slider_z;
	CSliderCtrl m_slider_winLvMin;
	CSliderCtrl m_slider_winLvMax;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButtonExporttraw3d();
	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedButtonExporttraw3dUshort();
};
