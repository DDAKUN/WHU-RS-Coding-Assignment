
// MyZhouTankDlg.h : header file
//

#pragma once
#include "Tank.h"
#include <vector>
#include "Wall.h"
#include "Shell.h"
#include "sapi.h"
#include "Tree.h"
// CMyZhouTankDlg dialog
class CMyZhouTankDlg : public CDialogEx
{
// Construction
public:
	CMyZhouTankDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYZHOUTANK_DIALOG };
#endif



	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:
	Tank m_Tank;
	
	std::vector<Shell> m_vecShell;
	std::vector<Wall> m_vecWall;
	std::vector<Tank> m_vecTank;
	std::vector<Tree> m_vecTree;
	bool start = false;
	Wall walltest;
	Tree treetest;
	int win = 1;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOk();
};
