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
	bool m_bFlipZ      ;

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





/*

class TDlgVolExportParam : public CDialogEx
{
DECLARE_DYNAMIC(TDlgVolExportParam)



public:
TDlgVolExportParam(int W, int H, int D, CWnd* pParent = NULL);   // 標準コンストラクター
virtual ~TDlgVolExportParam();

// ダイアログ データ
enum { IDD = IDD_DIALOG1 };

protected:
virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

DECLARE_MESSAGE_MAP()
public:
CSliderCtrl m_slider_exportVolWidth;
CButton m_check_nearest;
CButton m_check_linear;
virtual BOOL OnInitDialog();
afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
afx_msg void OnBnClickedCheckExpNearest();
afx_msg void OnBnClickedCheckExpLinear ();
CButton m_check_flipz;
afx_msg void OnBnClickedCheckExpFlipz();
};

*/