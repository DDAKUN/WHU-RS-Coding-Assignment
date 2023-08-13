
// ComputerGraphicDDA.h: ComputerGraphicDDA 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号
#include "math.h"

// CComputerGraphicDDAApp:
// 有关此类的实现，请参阅 ComputerGraphicDDA.cpp
//

class CComputerGraphicDDAApp : public CWinAppEx
{
public:
	CComputerGraphicDDAApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CComputerGraphicDDAApp theApp;
