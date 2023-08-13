// ConfigDlg.cpp : implementation file
//

#include "pch.h"
#include "MyZhouTank.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"


// ConfigDlg dialog

IMPLEMENT_DYNAMIC(ConfigDlg, CDialogEx)

ConfigDlg::ConfigDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONFIG, pParent)
{

}

ConfigDlg::~ConfigDlg()
{
}

void ConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ConfigDlg, CDialogEx)
END_MESSAGE_MAP()


// ConfigDlg message handlers
