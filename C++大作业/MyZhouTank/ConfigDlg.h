#pragma once


// ConfigDlg dialog

class ConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConfigDlg)

public:
	ConfigDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ConfigDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
