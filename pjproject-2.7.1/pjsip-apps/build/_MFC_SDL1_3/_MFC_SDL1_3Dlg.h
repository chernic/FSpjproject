
// _MFC_SDL1_3Dlg.h : 头文件
//

#pragma once


// C_MFC_SDL1_3Dlg 对话框
class C_MFC_SDL1_3Dlg : public CDialog
{
// 构造
public:
	C_MFC_SDL1_3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD__MFC_SDL1_3_DIALOG };

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
	afx_msg void OnBnClickedButton1();
};
