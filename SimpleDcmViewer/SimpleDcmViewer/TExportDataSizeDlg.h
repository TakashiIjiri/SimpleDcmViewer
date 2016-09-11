#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// TExportDataSizeDlg dialog

class TExportDataSizeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TExportDataSizeDlg)


private:
	const int m_W, m_H, m_D;

public:
	int  m_expW, m_expH, m_expD;
	bool m_bFlipInZ;
	void updateEditBoxInfo();

public:
	TExportDataSizeDlg(const int w, const int h, const int d, CWnd* pParent = NULL);   // standard constructor
	virtual ~TExportDataSizeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EXPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_slider;
	CButton m_check_flipz;
	afx_msg void OnBnClickedCheckFlip();
	virtual BOOL OnInitDialog();
};



