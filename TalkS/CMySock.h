#pragma once
#include <afxsock.h>
class CMySock :
    public CAsyncSocket
{
public:
    CMySock();
    virtual ~CMySock();
    virtual void OnAccept(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
    virtual void OnClose(int nErrorCode);
    void SetParent(CDialog* pDlg);
private:
    CDialog* m_pDlg;
};

