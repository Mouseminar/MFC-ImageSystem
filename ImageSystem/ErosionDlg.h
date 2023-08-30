#pragma once


// ErosionDlg 对话框

class ErosionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ErosionDlg)

public:
	ErosionDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ErosionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ErosionDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_value;
	afx_msg void OnBnClickedOk();
};
