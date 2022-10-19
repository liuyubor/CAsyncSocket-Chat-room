
// TalkCDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TalkC.h"
#include "TalkCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTalkCDlg 对话框



CTalkCDlg::CTalkCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TALKC_DIALOG, pParent)
	, m_strMsg(_T(""))
	, m_strName(_T("liuyubo"))
	, s_ip(_T("localhost"))
	, s_port(10000)
	, s_strName(_T("Server"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strFloder = _T(".\\data\\");
	m_strRecieveFile = _T("");
	m_strRecv = _T("");
}

void CTalkCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrRecv);
	DDX_Text(pDX, IDC_EDIT_MSG, m_strMsg);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_IP, s_ip);
	DDX_Text(pDX, IDC_EDIT_PORT, s_port);
	DDX_Text(pDX, IDC_EDIT_SNAME, s_strName);
}

BEGIN_MESSAGE_MAP(CTalkCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CTalkCDlg::OnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_CON, &CTalkCDlg::OnClickedButtonCon)
	ON_BN_CLICKED(IDC_BUTTON_FRECV, &CTalkCDlg::OnClickedButtonFrecv)
	ON_BN_CLICKED(IDC_BUTTON_FSENT, &CTalkCDlg::OnClickedButtonFsent)
	ON_BN_CLICKED(IDC_BUTTON_SEE, &CTalkCDlg::OnClickedButtonSee)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CTalkCDlg::OnClickedButtonSend)
END_MESSAGE_MAP()


// CTalkCDlg 消息处理程序

BOOL CTalkCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 额外的初始化代码
	m_sSocket.SetParent(this);
	GetDlgItem(IDC_BUTTON_CON)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FRECV)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FSENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTalkCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTalkCDlg::OnPaint()
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
HCURSOR CTalkCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTalkCDlg::OnClickedButtonClose()
{
	m_sSocket.Close();
	GetDlgItem(IDC_BUTTON_CON)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FRECV)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FSENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_IP)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_IP)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_SNAME)->EnableWindow(TRUE);
}

void CTalkCDlg::OnClickedButtonCon()
{
	UpdateData(TRUE);
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return;
	}
	if (!m_sSocket.Create())
	{
		AfxMessageBox(_T("创建套接字失败"));
		return;
	};
	
	int ret = m_sSocket.Connect(s_ip, s_port);
	CString s;
	s.Format(_T("%d"), ret);
	//AfxMessageBox(s);
	if (ret == SOCKET_ERROR)
	{
		AfxMessageBox(_T("连接套接字失败"));
		return;
	}
	m_ctrRecv.AddString(_T("Connect Success."));
	GetDlgItem(IDC_EDIT_IP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_IP)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_SNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CON)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FRECV)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FSENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(TRUE);
}

void CTalkCDlg::OnClickedButtonFrecv()
{
	AfxSocketInit(NULL);
	CSocket sockClient;
	sockClient.Create();

	CString	szIP;
	GetDlgItemText(IDC_EDIT_IP, szIP);

	if (!sockClient.Connect((LPCTSTR)szIP, 9999))
	{
		AfxMessageBox(_T("对方未发送"));
		return;
	}

	SOCKET_STREAM_FILE_INFO StreamFileInfo;
	sockClient.Receive(&StreamFileInfo, sizeof(SOCKET_STREAM_FILE_INFO));

	UpdateData(TRUE);
	//CString strFolderPath = _T("./data");
	CString strFolderPath = m_strFloder;
	if (!PathFileExists(strFolderPath))//文件夹是否存在
	{
		CreateDirectory(strFolderPath, NULL);//如果不存在就创建
	}
	CString strFileName;
	strFileName.Format(_T("%s"), StreamFileInfo.szFileTitle);
	strFileName = strFolderPath + strFileName;
	CFile destFile(strFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary);

	UINT dwRead = 0;
	while (dwRead < StreamFileInfo.nFileSizeLow)
	{
		byte* data = new byte[4096];
		memset(data, 0, 4096);

		UINT dw = sockClient.Receive(data, 4096);
		destFile.Write(data, dw);

		dwRead += dw;
		delete[] data;
	}
	SetFileTime((HANDLE)destFile.m_hFile, &StreamFileInfo.ftCreationTime,
		&StreamFileInfo.ftLastAccessTime, &StreamFileInfo.ftLastWriteTime);
	destFile.Close();
	SetFileAttributes(StreamFileInfo.szFileTitle, StreamFileInfo.dwFileAttributes);

	sockClient.Close();
	m_ctrRecv.AddString(_T("接收到了文件:") + strFileName);
	m_strRecieveFile = strFolderPath + strFileName;

	UpdateData(FALSE);
}

//收到A File消息或按下按钮后调用
void CTalkCDlg::OnClickedButtonFsent()
{

	CFileDialog	Dlg(TRUE);
	if (Dlg.DoModal() != IDOK)
		return;

	CFile myFile;
	if (!myFile.Open(Dlg.GetPathName(), CFile::modeRead | CFile::typeBinary))
	{
		AfxMessageBox(_T("文件不存在!"));
		return;
	}
	CString strFileName = myFile.GetFileTitle();
	CSocket sockSrvr;
	sockSrvr.Create(9999);
	sockSrvr.Listen();

	m_ctrRecv.AddString(_T("正在发送文件") + strFileName);
	UpdateData(FALSE);

	//提示对方在发送文件


	CString m_strMessage = _T("A File");
	m_sSocket.Send(LPCTSTR(m_strMessage), m_strMessage.GetLength() *sizeof(_TCHAR));

	CSocket sockRecv;
	sockSrvr.Accept(sockRecv);

	SOCKET_STREAM_FILE_INFO	StreamFileInfo;
	WIN32_FIND_DATA FindFileData;

	FindClose(FindFirstFile(Dlg.GetPathName(), &FindFileData));
	memset(&StreamFileInfo, 0, sizeof(SOCKET_STREAM_FILE_INFO));
	CString strFileTitle = myFile.GetFileTitle();
	_tcscpy_s(StreamFileInfo.szFileTitle, (LPCTSTR)strFileTitle);

	StreamFileInfo.dwFileAttributes = FindFileData.dwFileAttributes;
	StreamFileInfo.ftCreationTime = FindFileData.ftCreationTime;
	StreamFileInfo.ftLastAccessTime = FindFileData.ftLastAccessTime;
	StreamFileInfo.ftLastWriteTime = FindFileData.ftLastWriteTime;
	StreamFileInfo.nFileSizeHigh = FindFileData.nFileSizeHigh;
	StreamFileInfo.nFileSizeLow = FindFileData.nFileSizeLow;

	sockRecv.Send(&StreamFileInfo, sizeof(SOCKET_STREAM_FILE_INFO), 0);

	UINT dwRead = 0;
	while (dwRead < StreamFileInfo.nFileSizeLow)
	{
		byte* data = new byte[4096];
		UINT dw = myFile.Read(data, 4096);
		sockRecv.Send(data, dw);

		dwRead += dw;
		delete[] data;
	}
	myFile.Close();
	sockRecv.Close();

	m_ctrRecv.AddString(strFileName + "文件发送完成");
	UpdateData(FALSE);

}

void CTalkCDlg::OnClickedButtonSee()
{
	UpdateData(TRUE);
	ShellExecute(NULL, _T("open"), m_strFloder, NULL, NULL, SW_SHOWNORMAL);
}

void CTalkCDlg::OnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strMsg != "")
	{
		SendMsg(m_strMsg);
	}
	else {
		AfxMessageBox(_T("输入不得为空"));
	}
}

void CTalkCDlg::SendMsg(CString msg)
{
	CString m_sendBuffer = msg;
	int m_nBytesSent = 0;
	int m_nBytesBufferSize = m_sendBuffer.GetLength() * sizeof(_TCHAR);

	if (m_sendBuffer == "A File") //用于区分文件和普通消息
		return;

	// 拆包进行发送
	while (m_nBytesSent < m_nBytesBufferSize)
	{
		int dwBytes;

		if ((dwBytes = m_sSocket.Send((LPCTSTR)m_sendBuffer + m_nBytesSent,
			m_nBytesBufferSize - m_nBytesSent)) == SOCKET_ERROR)
		{
			if (GetLastError() == WSAEWOULDBLOCK)
			{
				break;
			}
			else
			{
				TCHAR szError[256];
				_stprintf_s(szError, _T("Server Socket failed to send: %d"),
					GetLastError());
				m_sSocket.Close();
				AfxMessageBox(szError);
			}
		}
		else
		{
			m_nBytesSent += dwBytes;
		}
	}
	if (m_nBytesSent == m_nBytesBufferSize)
	{
		m_sendBuffer = m_strName + _T("：") + m_sendBuffer;
		m_ctrRecv.AddString(m_sendBuffer);
		m_strMsg = "";
		UpdateData(FALSE);
		m_nBytesSent = m_nBytesBufferSize = 0;
		m_sendBuffer = _T("");
	}
}

void CTalkCDlg::OnReceive()
{
	TCHAR buff[4096];
	int nRead = m_sSocket.Receive(buff, 4096);

	switch (nRead)
	{
	case 0:
		AfxMessageBox(_T("Receive 失败"));
		m_sSocket.Close();
		break;
	case SOCKET_ERROR:
		if (GetLastError() != WSAEWOULDBLOCK)
		{
			AfxMessageBox(_T("Error occurred"));
			m_sSocket.Close();
		}
		break;
	default:
		buff[nRead / sizeof(_TCHAR)] = _T('\0'); //terminate the string
		CString szTemp(buff);
		// 接受标识符
		if (szTemp.Compare(_T("A File")) == 0) {
			OnClickedButtonFrecv();
			m_strRecv = _T("");
			break;
		}
		m_strRecv += szTemp;
		m_strRecv = s_strName + _T("：") + m_strRecv;
		m_ctrRecv.AddString(m_strRecv);
		m_strRecv = _T("");
		UpdateData(FALSE);
	}
}
