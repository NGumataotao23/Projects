
// FinalDlg.h : header file
//

#pragma once


// CFinalDlg dialog
class CFinalDlg : public CDialogEx
{
// Construction

	

public:
	CFinalDlg(CWnd* pParent = nullptr);	// standard constructor
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FINAL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	HBITMAP m_BitmapHandles[8];
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEdit1Changed();
	afx_msg void OnEdit2Changed();
	afx_msg void OnTimer(UINT_PTR nIDEvent); // very interesting having to add these here
	
};
