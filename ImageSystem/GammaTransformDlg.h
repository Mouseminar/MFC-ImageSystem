#pragma once


// GammaTransformDlg 对话框

class GammaTransformDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GammaTransformDlg)

public:
	GammaTransformDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GammaTransformDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GammaTransformDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_gamma;
	afx_msg void OnBnClickedOk();
};
