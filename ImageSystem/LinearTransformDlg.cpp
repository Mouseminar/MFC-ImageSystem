// LinearTransformDlg.cpp: 实现文件
//

#include "pch.h"
#include "ImageSystem.h"
#include "LinearTransformDlg.h"
#include "afxdialogex.h"


// LinearTransformDlg 对话框

IMPLEMENT_DYNAMIC(LinearTransformDlg, CDialogEx)

LinearTransformDlg::LinearTransformDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LinearTransformDlg, pParent)
	, m_k(0)
	, m_b(0)
{

}

LinearTransformDlg::~LinearTransformDlg()
{
}

void LinearTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_k);
	DDX_Text(pDX, IDC_EDIT2, m_b);
}


BEGIN_MESSAGE_MAP(LinearTransformDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &LinearTransformDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// LinearTransformDlg 消息处理程序


void LinearTransformDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	CDialogEx::OnOK();
}
