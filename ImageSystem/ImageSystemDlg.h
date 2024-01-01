
// ImageSystemDlg.h: 头文件
//

#include "CImageProcessing.h"

#pragma once


// CImageSystemDlg 对话框
class CImageSystemDlg : public CDialogEx
{
// 构造
public:
	CImageSystemDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGESYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_p1;
	CStatic m_p2;
	CString fileName;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();

	Mat src;	//原始图像
	Mat dst;	//处理后的图像
	void ShowDst();

	CImageProcessing ImageProcessing;
	afx_msg void OnRGB_2_Gray();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEqualizeHist();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnGrayscaleLinearTransform();
	afx_msg void OnLogTransform();
	afx_msg void OnGammaTransform();
	afx_msg void OnErosion();
	afx_msg void OnDilation();
	afx_msg void OnThresholdSegmentation();
	afx_msg void OnAdaptiveThreshold();
	afx_msg void OnRegionGrowing();
	afx_msg void OnSobel();
	afx_msg void OnCanny();
	afx_msg void OnMeanFilter();
	afx_msg void OnMedianFilter();
	afx_msg void OnGaussianFilter();
	afx_msg void OnFace();
	afx_msg void OnBnClickedButton2();

	bool isopen;
	CSliderCtrl m_slider1;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int slider_value;
};
