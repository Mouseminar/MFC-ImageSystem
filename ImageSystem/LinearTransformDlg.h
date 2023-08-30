#pragma once


// LinearTransformDlg 对话框

class LinearTransformDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LinearTransformDlg)

public:
	LinearTransformDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LinearTransformDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LinearTransformDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_k;
	double m_b;
	afx_msg void OnBnClickedOk();
};
