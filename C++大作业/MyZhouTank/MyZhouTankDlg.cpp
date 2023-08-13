
// MyZhouTankDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MyZhouTank.h"
#include "MyZhouTankDlg.h"
#include "afxdialogex.h"
#include "sapi.h"
#include "ConfigDlg.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyZhouTankDlg dialog



CMyZhouTankDlg::CMyZhouTankDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYZHOUTANK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyZhouTankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyZhouTankDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyZhouTankDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyZhouTankDlg::OnBnClickedButton2)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDOK, &CMyZhouTankDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMyZhouTankDlg message handlers

BOOL CMyZhouTankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	
	SetTimer(1, 1, NULL);
	SetTimer(2, 0.01, NULL);
	SetTimer(3, 50, NULL);//设置计时器
	
	m_Tank.m_ptPos.x = 620;
	m_Tank.m_ptPos.y = 620;
	m_Tank.m_Armor = 10;//初始化我方坦克
	TCHAR cFilePathName[1024];
	GetModuleFileName(NULL, cFilePathName, 1024);
	CString str = cFilePathName;
	int npos = str.ReverseFind('\\');
	CString strPathName = str.Left(npos);
	strPathName += L"\\Data";
	CString strBGMPathName;
	strBGMPathName = strPathName + L"\\BGM.wav";//获取音乐路径
	
	PlaySound(strBGMPathName, NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);//播放背景音乐
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyZhouTankDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyZhouTankDlg::OnPaint()
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

	CDC* pdc = GetDC();
	CMemDC dc(*pdc, this);
	CDC* pDC = &dc.GetDC();

	CRect rct;
	GetWindowRect(&rct);
	ScreenToClient(&rct);
	pDC->Rectangle(rct);//双缓冲绘图防止闪烁

	srand(time(NULL));
	if (start) {//用start判断游戏是否开始
		for (auto& tl : m_vecTank) {

			if (tl.m_Armor > 0) {
				tl.Draw(pDC);
			}
		}//绘制敌方坦克
		if (m_Tank.m_Armor > 0) {
			m_Tank.Draw(pDC);
		}//绘制我方坦克

		for (auto& sl : m_vecShell) {
			sl.Draw(pDC);
		}//绘制炮弹


		for (auto& wl : m_vecWall) {
			CRect rct1;
			rct1.left = wl.m_ptPos.x - wl.m_nSize;
			rct1.right = wl.m_ptPos.x + wl.m_nSize;
			rct1.top = wl.m_ptPos.y - wl.m_nSize;
			rct1.bottom = wl.m_ptPos.y + wl.m_nSize;
			if (wl.m_Armor > 0) {
				walltest.Draw(pDC, rct1);
			}//每次只用一个wall绘制 防止报错

		}

		for (auto& wl : m_vecTree) {
			CRect rct2;
			rct2.left = wl.m_ptPos.x - wl.m_nSize;
			rct2.right = wl.m_ptPos.x + wl.m_nSize;
			rct2.top = wl.m_ptPos.y - wl.m_nSize;
			rct2.bottom = wl.m_ptPos.y + wl.m_nSize;
			if (wl.m_Armor > 0) {
				treetest.Draw(pDC, rct2);
			}//每次只用一个tree绘制 防止报错

		}

	}
	if (start) {
		CString str1;
		str1.Format(L"剩余生命值为：%d", m_Tank.m_Armor);//显示剩余生命值
		pDC->TextOut(720, 200, str1);
	}
	if (!start) {
		CString str2;
		str2.Format(L"点击开始游戏即可开始，坦克拥有10点生命值");
		pDC->TextOut(150, 300, str2);
		CString str3;
		str3.Format(L"自己的坦克被消灭则游戏失败，消灭地方所有坦克则游戏胜利");
		pDC->TextOut(150, 340, str3);
		CString str4;
		str4.Format(L"坦克大战");
		pDC->TextOut(350, 220, str4);
	}//说明文本
	if (win == 3) {
		CString str5;
		str5.Format(L"恭喜你！你胜利了！");
		pDC->TextOut(720, 340, str5);
	}//胜利
	if (win == 2) {
		CString str6;
		str6.Format(L"很遗憾，你失败了");
		pDC->TextOut(720, 340, str6);
	}//失败

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyZhouTankDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyZhouTankDlg::OnBnClickedButton1()
{
	ConfigDlg dlg;
	dlg.DoModal();
	// TODO: Add your control notification handler code here
}


void CMyZhouTankDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	srand(time(NULL));
	int num = 0;
	bool f[22][22];//建立bool数组，判断要生成的地方是否已生成物品
	for (int i = 0;i < 22;i++) {
		for (int j = 0;j < 22;j++) {
			f[i][j] = false;
		}
	}
	f[15][15] = true;//坦克要生成的位置
	while(num<90){
		
		int nx = rand() % 16;
		int ny = rand() % 16;//每条边最多容纳16个物品
		CPoint wp;
		if (f[nx][ny])continue;
		f[nx][ny] = true;
		wp.x = nx * 40 + 20;
		wp.y = ny * 40 + 20;//规划坐标
		Wall Bricktest;
		Bricktest.SetPosition(wp.x, wp.y);
		m_vecWall.push_back(Bricktest);
		num++;
	}//生成70面墙
	num = 0;
	while(num<50){
		int nx = rand() % 16;
		int ny = rand() % 16;
		CPoint wp;
		if (f[nx][ny])continue;
		f[nx][ny] = true;
		wp.x = nx * 40 + 20;
		wp.y = ny * 40 + 20;
	    Tree treetest;
		treetest.SetPosition(wp.x, wp.y);
		m_vecTree.push_back(treetest);
		num++;
	}//生成30片树林
	num = 0;
	while (num < 10) {
		int nx = rand() % 16;
		int ny = rand() % 16;
		CPoint wp;
		if (f[nx][ny])continue;
		f[nx][ny] = true;
		wp.x = nx * 40 + 20;
		wp.y = ny * 40 + 20;
		Tank tanks;
		tanks.SetPosition(wp.x, wp.y);
		m_vecTank.push_back(tanks);
		num++;
	}//生成10辆敌方坦克
	start = true;//开始游戏

}


BOOL CMyZhouTankDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL CMyZhouTankDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RIGHT) {
			m_Tank.Move(1);
		}
		if (pMsg->wParam == VK_LEFT) {
			m_Tank.Move(2);
		}
		if (pMsg->wParam == VK_UP) {
			m_Tank.Move(3);
		}
		if (pMsg->wParam == VK_DOWN) {
			m_Tank.Move(4);
		}
		
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyZhouTankDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	static __int64 tmLast1 = 0;
	__int64 tmCurrent1 = GetTickCount64();
	int total = 0;
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent) {
	case 1:
		Invalidate(FALSE);//刷新画面
		break;

	case 2:

		for (auto& ll : m_vecTank) {
			for (int i = 1;i < 5;i++) {
				ll.IsMoveEnable(m_vecWall, i);
				m_Tank.IsMoveEnable(m_vecWall, i);
			}
		}//坦克与墙碰撞

		for (auto& wl : m_vecWall) {
			for (auto& sl : m_vecShell) {
				if (wl.m_Armor < 1)continue;
				if (sl.IsOverLap(wl)) {
					wl.m_Armor -= sl.m_Armor;
					sl.m_Armor = 0;
					
				}
			}
		}//炮弹与墙碰撞


		m_Tank.Judge();
		for (auto& ql : m_vecTank) {
			ql.Judge();
		}//坦克越界判断

		if (tmCurrent1 - tmLast1 > 1000)//炮管冷却，开炮间隔时间要大于1秒
		{
			for (auto& tl : m_vecTank) {
				if (tl.m_Armor > 0) {
					Shell shell = tl.Fire();
					shell.f = false;
					m_vecShell.push_back(shell);
				}
			}
			tmLast1 = tmCurrent1;
		}

		for (auto& jl : m_vecShell) {
			if (jl.f == false) {//敌方炮弹
				if (jl.IsOverLap(m_Tank)) {
					if (m_Tank.m_Armor > 0) {
						m_Tank.m_Armor -= jl.m_Armor;
						jl.m_Armor = 0;
					}
					
				}

			}
			if (jl.f == true) {//我方炮弹
				for (auto& ml : m_vecTank) {
					if (jl.IsOverLap(ml)) {
						if (ml.m_Armor > 0) {
							ml.m_Armor -= jl.m_Armor;
							jl.m_Armor = 0;
							
						}
					}
				}
			}
		}//坦克与炮弹碰撞


		if (m_Tank.m_Armor < 1) {
			win = 2;
		}
		
		for (auto& ml : m_vecTank) {
			
			if (ml.m_Armor < 1) { total++; };
			if (total == 10) {
				win = 3;
			}
		}//输赢判断
		break;
	case 3:
		srand(time(NULL));
		if (start) {
			for (auto& tl : m_vecTank) {
				int n = rand() % 4 + 1;
				tl.Move(n);
			}
		}//敌方坦克的随机移动
		break;

	default:break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMyZhouTankDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	static __int64 tmLast = 0;
	__int64 tmCurrent = GetTickCount64();
	if (tmCurrent - tmLast > 1000)//炮管冷却，开炮间隔时间要大于1秒
	{
		if (m_Tank.m_Armor > 0) {
			TCHAR cFilePathName[1024];
			GetModuleFileName(NULL, cFilePathName, 1024);
			CString str = cFilePathName;
			int npos = str.ReverseFind('\\');
			CString strPathName = str.Left(npos);
			strPathName += L"\\Data";
			CString strfashePathName;
			strfashePathName = strPathName + L"\\fashe.wav";
			PlaySound(strfashePathName, NULL, SND_FILENAME | SND_ASYNC);
			Shell shell = m_Tank.Fire();
			m_vecShell.push_back(shell);
			tmLast = tmCurrent;
		}
	}//我方坦克开炮，并播放音效
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMyZhouTankDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
