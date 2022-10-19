
// TalkCDlg.h: 头文件
//

#pragma once
#include "CMySock.h"

typedef struct _SOCKET_STREAM_FILE_INFO {

	TCHAR       szFileTitle[128];                   //文件的标题名
	DWORD       dwFileAttributes;                   //文件的属性
	FILETIME    ftCreationTime;                     //文件的创建时间
	FILETIME    ftLastAccessTime;                   //文件的最后访问时间
	FILETIME    ftLastWriteTime;                    //文件的最后修改时间
	DWORD       nFileSizeHigh;                      //文件大小的高位双字
	DWORD       nFileSizeLow;                       //文件大小的低位双字
	DWORD       dwReserved0;                        //保留，为0
	DWORD       dwReserved1;                        //保留，为0

} SOCKET_STREAM_FILE_INFO, * PSOCKET_STREAM_FILE_INFO;


// CTalkCDlg 对话框
class CTalkCDlg : public CDialogEx
{
// 构造
public:
	CTalkCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TALKC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnClickedButtonClose();
	afx_msg void OnClickedButtonCon();
	afx_msg void OnClickedButtonFrecv();
	afx_msg void OnClickedButtonFsent();
	afx_msg void OnClickedButtonSee();
	afx_msg void OnClickedButtonSend();
	void SendMsg(CString msg);
	// 重写OnReceive()；
	afx_msg void OnReceive();

private:
	CMySock m_sSocket;
public:
	CString m_strRecieveFile;
	CListBox m_ctrRecv;
	CString m_strMsg;
	CString m_strName;
	CString m_strFloder;
	CString s_ip;
	UINT s_port;
private:
	CString m_strRecv;
public:
	CString s_strName;
};
