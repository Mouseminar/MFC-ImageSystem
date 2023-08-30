// LogTransformDlg.cpp: 实现文件
//

#include "pch.h"
#include "ImageSystem.h"
#include "LogTransformDlg.h"
#include "afxdialogex.h"


// LogTransformDlg 对话框

IMPLEMENT_DYNAMIC(LogTransformDlg, CDialogEx)

LogTransformDlg::LogTransformDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LogTransformDlg, pParent)
	, m_c(0)
{

}

LogTransformDlg::~LogTransformDlg()
{
}

void LogTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_c);
}


BEGIN_MESSAGE_MAP(LogTransformDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &LogTransformDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// LogTransformDlg 消息处理程序


void LogTransformDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CDialogEx::OnOK();
}
