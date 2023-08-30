// ErosionDlg.cpp: 实现文件
//

#include "pch.h"
#include "ImageSystem.h"
#include "ErosionDlg.h"
#include "afxdialogex.h"


// ErosionDlg 对话框

IMPLEMENT_DYNAMIC(ErosionDlg, CDialogEx)

ErosionDlg::ErosionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ErosionDlg, pParent)
	, m_value(0)
{

}

ErosionDlg::~ErosionDlg()
{
}

void ErosionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_value);
}


BEGIN_MESSAGE_MAP(ErosionDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ErosionDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ErosionDlg 消息处理程序


void ErosionDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
