
// TalkSDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TalkS.h"
#include "TalkSDlg.h"
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


// CTalkSDlg 对话框



CTalkSDlg::CTalkSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TALKS_DIALOG, pParent)
	, m_strName(_T("Server"))
	, m_strMsg(_T(""))
	, m_port(10000)
	, m_ip(_T("localhost"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	c_port = 0;
	c_ip = _T("");
	m_strFolder = _T(".\\data\\");
}

void CTalkSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctlRecv);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_MSG, m_strMsg);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_IP, m_ip);
}

BEGIN_MESSAGE_MAP(CTalkSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CTalkSDlg::OnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_FRECV, &CTalkSDlg::OnClickedButtonFrecv)
	ON_BN_CLICKED(IDC_BUTTON_FSENT, &CTalkSDlg::OnClickedButtonFsent)
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CTalkSDlg::OnClickedButtonListen)
	ON_BN_CLICKED(IDC_BUTTON_SEE, &CTalkSDlg::OnClickedButtonSee)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CTalkSDlg::OnClickedButtonSend)
END_MESSAGE_MAP()


// CTalkSDlg 消息处理程序

BOOL CTalkSDlg::OnInitDialog()
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

	m_sConnectSocket.SetParent(this);
	m_sListenSocket.SetParent(this);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FRECV)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FSENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTalkSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTalkSDlg::OnPaint()
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
HCURSOR CTalkSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CTalkSDlg::OnClickedButtonClose()
{
	m_sListenSocket.Close();
	m_sConnectSocket.Close();
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FRECV)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FSENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_IP)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_IP)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_NAME)->EnableWindow(TRUE);
}


void CTalkSDlg::OnClickedButtonFrecv()
{
	AfxSocketInit(NULL);
	CSocket sockClient;
	sockClient.Create();

	CString	szIP = c_ip;

	if (!sockClient.Connect((LPCTSTR)szIP, 9999))
	{
		AfxMessageBox(_T("对方未发送"));
		return;
	}

	SOCKET_STREAM_FILE_INFO StreamFileInfo;
	sockClient.Receive(&StreamFileInfo, sizeof(SOCKET_STREAM_FILE_INFO));

	UpdateData(TRUE);
	CString strFolderPath = m_strFolder;
	//CString strFolderPath = _T(".\\data\\");
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
	m_ctlRecv.AddString(_T("接收到了文件") + strFileName);
	//m_strRecieveFile = strFolderPath + strFileName;

	UpdateData(FALSE);
}


void CTalkSDlg::OnClickedButtonFsent()
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

	m_ctlRecv.AddString(_T("正在发送文件") + strFileName);
	UpdateData(FALSE);

	//提示对方在发送文件，
	//客户端收到此信息后，触发Connect(IP, 9999)

	CString m_strMessage = _T("A File");
	m_sConnectSocket.Send(LPCTSTR(m_strMessage), m_strMessage.GetLength() * sizeof(_TCHAR));


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

	m_ctlRecv.AddString(strFileName + "文件发送完成");
	UpdateData(FALSE);
}


void CTalkSDlg::OnClickedButtonListen()
{
	UpdateData(TRUE);
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return;
	}
	//创建套接字句柄，绑定特定的端口
	if (m_sListenSocket.Create(m_port) == 0)
	{
		AfxMessageBox(_T("监听套接字创建失败"));
		return;
	}
	//启动监听
	if (m_sListenSocket.Listen() == 0)
	{
		//错误信息输出
		AfxMessageBox(_T("监听套接字失败"));
		return;
	}

	m_ctlRecv.AddString(_T("Listening"));
	GetDlgItem(IDC_EDIT_IP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_IP)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_STATIC_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FRECV)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_FSENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_STATIC_MSG)->EnableWindow(TRUE);
}


void CTalkSDlg::OnClickedButtonSee()
{
	UpdateData(TRUE);
	ShellExecute(NULL, _T("open"), m_strFolder, NULL, NULL, SW_SHOWNORMAL);
}


void CTalkSDlg::OnClickedButtonSend()
{
	UpdateData(TRUE);
	if (m_strMsg != _T(""))
	{
		SendMsg(m_strMsg);
	}
	else {
		AfxMessageBox(_T("输入不得为空"));
	}
}

void CTalkSDlg::SendMsg(CString msg)
{
	CString m_sendBuffer = msg;
	int m_nBytesSent = 0;
	int m_nBytesBufferSize = m_sendBuffer.GetLength() * sizeof(TCHAR);

	if (m_sendBuffer == "A File") //用于区分文件和普通消息
		return;
	bool bBuff = TRUE;
	// 拆包进行发送
	while (m_nBytesSent < m_nBytesBufferSize)
	{
		int dwBytes;

		if ((dwBytes = m_sConnectSocket.Send((LPCTSTR)m_sendBuffer + m_nBytesSent,
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
				m_sConnectSocket.Close();
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
		m_ctlRecv.AddString(m_sendBuffer);
		m_strMsg = "";
		UpdateData(FALSE);
		m_nBytesSent = m_nBytesBufferSize = 0;
		m_sendBuffer = _T("");
	}
}

void CTalkSDlg::OnAccept()
{
	//使用m_sConnectSocket接受，再用它recv
	if (m_sListenSocket.Accept(m_sConnectSocket) == SOCKET_ERROR)
	{	
		AfxMessageBox(_T("Accept失败"));
		return;
	}
	else {
		m_sConnectSocket.GetPeerName(c_ip, c_port);
		CString c_sport;
		c_sport.Format(_T("%u"), c_port);
		m_ctlRecv.AddString(_T("client: ") + c_ip + _T(":") + c_sport + _T(" connected."));
		//AfxMessageBox(c_ip);
	}
}


void CTalkSDlg::OnReceive()
{
	TCHAR buff[4096]{0X00};
	int nRead = m_sConnectSocket.Receive(buff, 4096);

	switch (nRead)
	{
	case 0:
		AfxMessageBox(_T("Receive 失败"));
		m_sConnectSocket.Close();
		m_strRecv = _T("");
		break;
	case SOCKET_ERROR:
		if (GetLastError() != WSAEWOULDBLOCK)
		{
			AfxMessageBox(_T("Error occurred"));
			m_sConnectSocket.Close();
			m_strRecv = _T("");
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
		m_strRecv = _T("Client：") + m_strRecv;
		m_ctlRecv.AddString(m_strRecv);
		m_strRecv = _T("");
		UpdateData(FALSE);
	}
		/*if (szTemp.CompareNoCase(_T("bye")) == 0)
		{
			ShutDown();
			s_eventDone.SetEvent();
		}*/
}