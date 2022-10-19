#pragma once
#include <afxsock.h>
class CMySock : public CAsyncSocket
{
public:
    CMySock();
    virtual ~CMySock();
    virtual void OnReceive(int nErrorCode);
    void SetParent(CDialog* pDlg);
private:
    CDialog* m_pDlg;
public:
    virtual void OnClose(int nErrorCode);
};

