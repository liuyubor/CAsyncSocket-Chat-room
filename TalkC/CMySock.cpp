#include "pch.h"
#include "CMySock.h"
#include "TalkCDlg.h"

CMySock::CMySock()
{
}

CMySock::~CMySock()
{
}


void CMySock::OnReceive(int nErrorCode)
{
	((CTalkCDlg*)m_pDlg)->OnReceive();
	CAsyncSocket::OnReceive(nErrorCode);
}


void CMySock::SetParent(CDialog* pDlg)
{
	// TODO: 在此处添加实现代码.
	m_pDlg = pDlg;
}


void CMySock::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	((CTalkCDlg*)m_pDlg)->OnClickedButtonClose();
	CAsyncSocket::OnClose(nErrorCode);
}
