
// ImageSystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ImageSystem.h"
#include "ImageSystemDlg.h"
#include "afxdialogex.h"

#include "LinearTransformDlg.h"
#include "LogTransformDlg.h"
#include "GammaTransformDlg.h"
#include "ErosionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageSystemDlg 对话框



CImageSystemDlg::CImageSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGESYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture1, m_p1);
	DDX_Control(pDX, IDC_Picture2, m_p2);
}

BEGIN_MESSAGE_MAP(CImageSystemDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CImageSystemDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CImageSystemDlg::OnBnClickedButton3)
	ON_COMMAND(ID_32771, &CImageSystemDlg::OnRGB_2_Gray)
	ON_BN_CLICKED(IDC_BUTTON4, &CImageSystemDlg::OnBnClickedButton4)
	ON_COMMAND(ID_32773, &CImageSystemDlg::OnEqualizeHist)
	ON_BN_CLICKED(IDC_BUTTON5, &CImageSystemDlg::OnBnClickedButton5)
	ON_COMMAND(ID_32775, &CImageSystemDlg::OnGrayscaleLinearTransform)
	ON_COMMAND(ID_32777, &CImageSystemDlg::OnLogTransform)
	ON_COMMAND(ID_32778, &CImageSystemDlg::OnGammaTransform)
	ON_COMMAND(ID_32779, &CImageSystemDlg::OnErosion)
	ON_COMMAND(ID_32780, &CImageSystemDlg::OnDilation)
	ON_COMMAND(ID_32784, &CImageSystemDlg::OnThresholdSegmentation)
	ON_COMMAND(ID_32785, &CImageSystemDlg::OnAdaptiveThreshold)
	ON_COMMAND(ID_32782, &CImageSystemDlg::OnRegionGrowing)
	ON_COMMAND(ID_32786, &CImageSystemDlg::OnSobel)
	ON_COMMAND(ID_32787, &CImageSystemDlg::OnCanny)
	ON_COMMAND(ID_32788, &CImageSystemDlg::OnMeanFilter)
	ON_COMMAND(ID_32789, &CImageSystemDlg::OnMedianFilter)
	ON_COMMAND(ID_32790, &CImageSystemDlg::OnGaussianFilter)
	ON_COMMAND(ID_32791, &CImageSystemDlg::OnFace)
	ON_BN_CLICKED(IDC_BUTTON2, &CImageSystemDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CImageSystemDlg 消息处理程序

BOOL CImageSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	isopen = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImageSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CImageSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageSystemDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	TCHAR szFilter[] = _T("JPEG文件(*.jpg)|*.jpg|PNG文件(*.png)|*.png|bmp文件(*.bmp)|*.bmp||");
	CFileDialog fileDlg(TRUE, _T("jpg"), NULL, 0, szFilter, this);

	if (fileDlg.DoModal() != IDOK)     //没有点确定按钮，返回
		return;

	fileName = fileDlg.GetPathName();

	CImage image;	//创建图片对象，保存图片信息
	image.Load(fileName);	//加载
	CRect rectControl;	//用于存储图片控件的位置和尺寸信息
	m_p1.GetClientRect(rectControl);	//获取图片控件位置和尺寸信息，并将这些信息保存在rectControl对象中
	CDC* pDc = m_p1.GetDC();	//获取与图片控件控件关联的DC
	image.Draw(pDc->m_hDC, rectControl);	//将图像绘制在从 pDc 获得的设备上下文中，rectControl 用作绘制图像的目标矩形
	image.Destroy();	//销毁图片
	m_p1.ReleaseDC(pDc);	//释放指针

	src = imread(fileName.GetBuffer(), 1);
	isopen = true;
}


void CImageSystemDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UINT i;
	i = MessageBox(_T("确定要退出吗？"), _T("提示"), MB_YESNO | MB_ICONQUESTION);
	if (i == IDYES)
	{
		//你自己的代码
		exit(0);
	}

}


void CImageSystemDlg::ShowDst()
{
	CImage image;	//创建图片对象，保存图片信息
	image.Load(TEXT("result.png"));	//加载
	CRect rectControl;	//用于存储图片控件的位置和尺寸信息
	m_p2.GetClientRect(rectControl);	//获取图片控件位置和尺寸信息，并将这些信息保存在rectControl对象中
	CDC* pDc = m_p2.GetDC();	//获取与图片控件控件关联的DC
	image.Draw(pDc->m_hDC, rectControl);	//将图像绘制在从 pDc 获得的设备上下文中，rectControl 用作绘制图像的目标矩形
	image.Destroy();	//销毁图片
	m_p2.ReleaseDC(pDc);	//释放指针
}

void CImageSystemDlg::OnRGB_2_Gray()
{
	// TODO: 在此添加命令处理程序代码

	if (isopen)
	{
		dst = ImageProcessing.RGB_2_Gray(src);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}



void CImageSystemDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isopen)
	{
		ImageProcessing.Show_Histogram(src);
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}



void CImageSystemDlg::OnEqualizeHist()
{
	// TODO: 在此添加命令处理程序代码
	if (isopen)
	{
		dst = ImageProcessing.EqualizeHist(src);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}


void CImageSystemDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isopen)
	{
		dst = imread("result.png", 1);
		ImageProcessing.Show_Histogram(dst);
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}



void CImageSystemDlg::OnGrayscaleLinearTransform()
{
	// TODO: 在此添加命令处理程序代码
	if (isopen)
	{
		// 定义线性变换参数
		double alpha = 1;  // 增益
		double beta = -30;    // 偏移

		LinearTransformDlg dlg;
		dlg.m_k = alpha;
		dlg.m_b = beta;
		if (dlg.DoModal() == IDOK)
		{
			alpha = dlg.m_k;
			beta = dlg.m_b;
		}

		dst = ImageProcessing.GrayscaleLinearTransform(src, alpha, beta);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}


void CImageSystemDlg::OnLogTransform()
{
	// TODO: 在此添加命令处理程序代码
	if (isopen)
	{
		// 定义对数变换参数
		double c = 40;  // 对数变换参数

		LogTransformDlg dlg;
		dlg.m_c = c;
		if (dlg.DoModal() == IDOK)
		{
			c = dlg.m_c;
		}
		dst = ImageProcessing.grayscaleLogTransform(src, c);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
	
}


void CImageSystemDlg::OnGammaTransform()
{
	// TODO: 在此添加命令处理程序代码

	if (isopen)
	{
		// 定义伽马变换参数
		double gamma = 0.5;  // 伽马值

		GammaTransformDlg dlg;
		dlg.m_gamma = gamma;
		if (dlg.DoModal() == IDOK)
		{
			gamma = dlg.m_gamma;
		}

		dst = ImageProcessing.grayscaleGammaTransform(src, gamma);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}


void CImageSystemDlg::OnErosion()
{
	// TODO: 在此添加命令处理程序代码

	if (isopen)
	{
		// 定义腐蚀核尺寸
		int erosionSize = 3;

		ErosionDlg dlg;
		dlg.m_value = erosionSize;
		if (dlg.DoModal() == IDOK)
		{
			erosionSize = dlg.m_value;
		}

		dst = ImageProcessing.ImageErosion(src, erosionSize);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
	
}


void CImageSystemDlg::OnDilation()
{
	// TODO: 在此添加命令处理程序代码

	if (isopen)
	{
		// 定义膨胀核尺寸
		int dilationSize = 3;

		ErosionDlg dlg;
		dlg.m_value = dilationSize;
		if (dlg.DoModal() == IDOK)
		{
			dilationSize = dlg.m_value;
		}

		dst = ImageProcessing.ImageDilation(src, dilationSize);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}


void CImageSystemDlg::OnThresholdSegmentation()
{
	// TODO: 在此添加命令处理程序代码

	if (isopen)
	{
		// 定义阈值
		int thresholdValue = 128;

		ErosionDlg dlg;
		dlg.m_value = thresholdValue;
		if (dlg.DoModal() == IDOK)
		{
			thresholdValue = dlg.m_value;
		}

		dst = ImageProcessing.imageThresholdSegmentation(src, thresholdValue);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}


void CImageSystemDlg::OnAdaptiveThreshold()
{
	// TODO: 在此添加命令处理程序代码

	if (isopen)
	{
		// 定义自适应阈值分割参数
		int blockSize = 11;      // 邻域大小，奇数
		int subtractValue = 10;  // 阈值修正值

		dst = ImageProcessing.adaptiveThresholdSegmentation(src, blockSize, subtractValue);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}

}


void CImageSystemDlg::OnRegionGrowing()
{
	// TODO: 在此添加命令处理程序代码
	if (isopen)
	{
		// 定义种子点和阈值
		int seedX = 100;         // 种子点的X坐标
		int seedY = 100;         // 种子点的Y坐标
		int threshold = 50;      // 阈值

		ErosionDlg dlg;
		dlg.m_value = threshold;
		if (dlg.DoModal() == IDOK)
		{
			threshold = dlg.m_value;
		}

		dst = ImageProcessing.regionGrowingSegmentation(src, seedX, seedY, threshold);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}


void CImageSystemDlg::OnSobel()
{
	// TODO: 在此添加命令处理程序代码
	if (isopen)
	{	// 定义Sobel核大小
		int kernelSize = 3;

		dst = ImageProcessing.sobelEdgeDetection(src, kernelSize);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}


void CImageSystemDlg::OnCanny()
{
	// TODO: 在此添加命令处理程序代码
	if (isopen)
	{
		// 定义Canny边缘检测的两个阈值
		double threshold1 = 50;   // 低阈值
		double threshold2 = 150;   // 高阈值

		dst = ImageProcessing.cannyEdgeDetection(src, threshold1, threshold2);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}


void CImageSystemDlg::OnMeanFilter()
{
	// TODO: 在此添加命令处理程序代码
	if (isopen)
	{
		// 定义均值滤波的核大小
		int kernelSize = 5;

		dst = ImageProcessing.meanFilter(src, kernelSize);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}


void CImageSystemDlg::OnMedianFilter()
{
	// TODO: 在此添加命令处理程序代码
	if (isopen)
	{
		// 定义均值滤波的核大小
		int kernelSize = 7;

		dst = ImageProcessing.medianFilter(src, kernelSize);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}


void CImageSystemDlg::OnGaussianFilter()
{
	// TODO: 在此添加命令处理程序代码
	if (isopen)
	{
		// 定义高斯滤波的核大小和标准差
		int kernelSize = 5;
		double sigma = 2.0;

		dst = ImageProcessing.gaussianFilter(src, kernelSize, sigma);
		imwrite("result.png", dst);
		ShowDst();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}


void CImageSystemDlg::OnFace()
{
	// TODO: 在此添加命令处理程序代码
	if (isopen)
	{
		dst = ImageProcessing.detectFaces(src);
		imwrite("result.png", dst);
		ShowDst();
		src = imread(fileName.GetBuffer(), 1);
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}


void CImageSystemDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isopen)
	{
		CWnd* bmpShow = GetDlgItem(IDC_Picture2);
		CDC* pdc = bmpShow->GetDC();
		CImage  imag;
		CRect rect;

		GetClientRect(&rect);        //获取画布大小
		bmpShow->GetWindowRect(&rect);
		imag.Create(rect.Width(), rect.Height(), 32);
		::BitBlt(imag.GetDC(), 0, 0, rect.Width(), rect.Height(), pdc->m_hDC, 0, 0, SRCCOPY);

		TCHAR szFilter[] = _T("jpg file(*.jpg)|*.jpg|bmp file(*.bmp)|*.bmp|所有文件(*.*)|*.*||");  //文件格式过滤
		// 构造保存文件对话框    
		CFileDialog fileDlg(FALSE, _T("jpg"), _T("*.jpg"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
		fileDlg.m_ofn.lpstrTitle = _T("保存图像");  //保存对话窗口标题名
		CString picturePath;
		if (IDOK == fileDlg.DoModal())  //按下确认键
		{
			picturePath = fileDlg.GetPathName();  //文件路径
		}

		HRESULT hResult = imag.Save(picturePath); //保存图片
		ReleaseDC(pdc);
		imag.ReleaseDC();
	}
	else
	{
		MessageBox(TEXT("请先打开图片！"), TEXT("提示"));
	}
}
