
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
	SetTimer(3, 50, NULL);//���ü�ʱ��
	
	m_Tank.m_ptPos.x = 620;
	m_Tank.m_ptPos.y = 620;
	m_Tank.m_Armor = 10;//��ʼ���ҷ�̹��
	TCHAR cFilePathName[1024];
	GetModuleFileName(NULL, cFilePathName, 1024);
	CString str = cFilePathName;
	int npos = str.ReverseFind('\\');
	CString strPathName = str.Left(npos);
	strPathName += L"\\Data";
	CString strBGMPathName;
	strBGMPathName = strPathName + L"\\BGM.wav";//��ȡ����·��
	
	PlaySound(strBGMPathName, NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);//���ű�������
	
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
	pDC->Rectangle(rct);//˫�����ͼ��ֹ��˸

	srand(time(NULL));
	if (start) {//��start�ж���Ϸ�Ƿ�ʼ
		for (auto& tl : m_vecTank) {

			if (tl.m_Armor > 0) {
				tl.Draw(pDC);
			}
		}//���Ƶз�̹��
		if (m_Tank.m_Armor > 0) {
			m_Tank.Draw(pDC);
		}//�����ҷ�̹��

		for (auto& sl : m_vecShell) {
			sl.Draw(pDC);
		}//�����ڵ�


		for (auto& wl : m_vecWall) {
			CRect rct1;
			rct1.left = wl.m_ptPos.x - wl.m_nSize;
			rct1.right = wl.m_ptPos.x + wl.m_nSize;
			rct1.top = wl.m_ptPos.y - wl.m_nSize;
			rct1.bottom = wl.m_ptPos.y + wl.m_nSize;
			if (wl.m_Armor > 0) {
				walltest.Draw(pDC, rct1);
			}//ÿ��ֻ��һ��wall���� ��ֹ����

		}

		for (auto& wl : m_vecTree) {
			CRect rct2;
			rct2.left = wl.m_ptPos.x - wl.m_nSize;
			rct2.right = wl.m_ptPos.x + wl.m_nSize;
			rct2.top = wl.m_ptPos.y - wl.m_nSize;
			rct2.bottom = wl.m_ptPos.y + wl.m_nSize;
			if (wl.m_Armor > 0) {
				treetest.Draw(pDC, rct2);
			}//ÿ��ֻ��һ��tree���� ��ֹ����

		}

	}
	if (start) {
		CString str1;
		str1.Format(L"ʣ������ֵΪ��%d", m_Tank.m_Armor);//��ʾʣ������ֵ
		pDC->TextOut(720, 200, str1);
	}
	if (!start) {
		CString str2;
		str2.Format(L"�����ʼ��Ϸ���ɿ�ʼ��̹��ӵ��10������ֵ");
		pDC->TextOut(150, 300, str2);
		CString str3;
		str3.Format(L"�Լ���̹�˱���������Ϸʧ�ܣ�����ط�����̹������Ϸʤ��");
		pDC->TextOut(150, 340, str3);
		CString str4;
		str4.Format(L"̹�˴�ս");
		pDC->TextOut(350, 220, str4);
	}//˵���ı�
	if (win == 3) {
		CString str5;
		str5.Format(L"��ϲ�㣡��ʤ���ˣ�");
		pDC->TextOut(720, 340, str5);
	}//ʤ��
	if (win == 2) {
		CString str6;
		str6.Format(L"���ź�����ʧ����");
		pDC->TextOut(720, 340, str6);
	}//ʧ��

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
	bool f[22][22];//����bool���飬�ж�Ҫ���ɵĵط��Ƿ���������Ʒ
	for (int i = 0;i < 22;i++) {
		for (int j = 0;j < 22;j++) {
			f[i][j] = false;
		}
	}
	f[15][15] = true;//̹��Ҫ���ɵ�λ��
	while(num<90){
		
		int nx = rand() % 16;
		int ny = rand() % 16;//ÿ�����������16����Ʒ
		CPoint wp;
		if (f[nx][ny])continue;
		f[nx][ny] = true;
		wp.x = nx * 40 + 20;
		wp.y = ny * 40 + 20;//�滮����
		Wall Bricktest;
		Bricktest.SetPosition(wp.x, wp.y);
		m_vecWall.push_back(Bricktest);
		num++;
	}//����70��ǽ
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
	}//����30Ƭ����
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
	}//����10���з�̹��
	start = true;//��ʼ��Ϸ

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
		Invalidate(FALSE);//ˢ�»���
		break;

	case 2:

		for (auto& ll : m_vecTank) {
			for (int i = 1;i < 5;i++) {
				ll.IsMoveEnable(m_vecWall, i);
				m_Tank.IsMoveEnable(m_vecWall, i);
			}
		}//̹����ǽ��ײ

		for (auto& wl : m_vecWall) {
			for (auto& sl : m_vecShell) {
				if (wl.m_Armor < 1)continue;
				if (sl.IsOverLap(wl)) {
					wl.m_Armor -= sl.m_Armor;
					sl.m_Armor = 0;
					
				}
			}
		}//�ڵ���ǽ��ײ


		m_Tank.Judge();
		for (auto& ql : m_vecTank) {
			ql.Judge();
		}//̹��Խ���ж�

		if (tmCurrent1 - tmLast1 > 1000)//�ڹ���ȴ�����ڼ��ʱ��Ҫ����1��
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
			if (jl.f == false) {//�з��ڵ�
				if (jl.IsOverLap(m_Tank)) {
					if (m_Tank.m_Armor > 0) {
						m_Tank.m_Armor -= jl.m_Armor;
						jl.m_Armor = 0;
					}
					
				}

			}
			if (jl.f == true) {//�ҷ��ڵ�
				for (auto& ml : m_vecTank) {
					if (jl.IsOverLap(ml)) {
						if (ml.m_Armor > 0) {
							ml.m_Armor -= jl.m_Armor;
							jl.m_Armor = 0;
							
						}
					}
				}
			}
		}//̹�����ڵ���ײ


		if (m_Tank.m_Armor < 1) {
			win = 2;
		}
		
		for (auto& ml : m_vecTank) {
			
			if (ml.m_Armor < 1) { total++; };
			if (total == 10) {
				win = 3;
			}
		}//��Ӯ�ж�
		break;
	case 3:
		srand(time(NULL));
		if (start) {
			for (auto& tl : m_vecTank) {
				int n = rand() % 4 + 1;
				tl.Move(n);
			}
		}//�з�̹�˵�����ƶ�
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
	if (tmCurrent - tmLast > 1000)//�ڹ���ȴ�����ڼ��ʱ��Ҫ����1��
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
	}//�ҷ�̹�˿��ڣ���������Ч
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMyZhouTankDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
