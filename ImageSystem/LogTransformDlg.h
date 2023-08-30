#pragma once


// LogTransformDlg 对话框

class LogTransformDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LogTransformDlg)

public:
	LogTransformDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LogTransformDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LogTransformDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_c;
	afx_msg void OnBnClickedOk();
};
