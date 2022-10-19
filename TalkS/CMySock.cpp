#include "pch.h"
#include "CMySock.h"
#include "TalkSDlg.h"

CMySock::CMySock()
{
}

CMySock::~CMySock()
{
}

void CMySock::OnAccept(int nErrorCode)
{
	((CTalkSDlg*)m_pDlg)->OnAccept();
	CAsyncSocket::OnAccept(nErrorCode);
}


void CMySock::OnReceive(int nErrorCode)
{
	((CTalkSDlg*)m_pDlg)->OnReceive();
	CAsyncSocket::OnReceive(nErrorCode);
}



void CMySock::OnClose(int nErrorCode)
{
	((CTalkSDlg*)m_pDlg)->OnClickedButtonClose();
	CAsyncSocket::OnClose(nErrorCode);
}


void CMySock::SetParent(CDialog* pDlg)
{
	m_pDlg = pDlg;
}