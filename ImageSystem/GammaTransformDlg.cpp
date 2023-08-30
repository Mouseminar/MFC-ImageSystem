// GammaTransformDlg.cpp: 实现文件
//

#include "pch.h"
#include "ImageSystem.h"
#include "GammaTransformDlg.h"
#include "afxdialogex.h"


// GammaTransformDlg 对话框

IMPLEMENT_DYNAMIC(GammaTransformDlg, CDialogEx)

GammaTransformDlg::GammaTransformDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GammaTransformDlg, pParent)
	, m_gamma(0)
{

}

GammaTransformDlg::~GammaTransformDlg()
{
}

void GammaTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_gamma);
}


BEGIN_MESSAGE_MAP(GammaTransformDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &GammaTransformDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// GammaTransformDlg 消息处理程序


void GammaTransformDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
