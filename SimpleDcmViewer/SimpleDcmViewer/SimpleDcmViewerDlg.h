
// SimpleDcmViewerDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CSimpleDcmViewerDlg dialog
class CSimpleDcmViewerDlg : public CDialogEx
{

	bool m_bPictContInit;

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
};
