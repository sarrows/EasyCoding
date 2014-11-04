#include "StdAfx.h"
#include "QPacketTokenRsp.h"
#include "QFsm.h"

// 转换矩阵: 数据包类型->事件类型
// 如果增加数据包类型，必须修改
static const int m_arrConversions[] = {
    -1,                       // PKTTOKENREQ
    CQFsmSuper::ETOKENRET,    // PKTTOKENRSP
};

CQFsmSuper::QEVENT CQFsm::GetEventType(CQPacketSuper::PACKETTYPE pkttype)
{
    return (QEVENT)m_arrConversions[pkttype];
}

CQFsm * CQFsm::_inst = 0;

void CALLBACK CQFsm::OnTimer(HWND hwnd, UINT uMsg, UINT nIDEvent, DWORD dwTime)
{
    CQFsm::Instance()->SendEvent(nIDEvent, ETIMER, 0);
    ::KillTimer(hwnd, nIDEvent);
    return;
}

int CQFsm::Init()
{
    return 0;
}

int CQFsm::CreateInst(unsigned long number)
{
    if (!number)
        return -1;
    CQcb * p = new CQcb;
    p->SetVal(CQcb::QID, number);
    p->SetVal(CQcb::QCBSTATE, CQFsmSuper::SLOGOUT);
    _qbase.insert(make_pair(number, p));
    return 0;
}

int CQFsm::DeleteInst(unsigned long number)
{
    if (_qbase.find(number)==_qbase.end())
        return 0;
    SendEvent(number, EDELETE, 0);
    return 0;
}

int CQFsm::SetParam(unsigned short portstart, unsigned short portend, HWND hwnd, HWND hListCtrl)
{
    if (!portstart || !portend || !hwnd || !hListCtrl)
        return -1;
    _iPortStart = portstart;
    _iPortEnd   = portend;
    _hwnd       = hwnd;
    _hListCtrl  = hListCtrl;
    return 0;
}

// SendData to local QCB when net data come
int CQFsm::SendData(const unsigned char *data, int len, unsigned char *decrypted)
{
    if (!data)
        return -1;

    CPacketTokenRsp pkgHeader(0);
    CQPacketSuper * p = pkgHeader.Parse(data, len);
    if (p) {
        // 包已经解析成功
        CAnyType any;
        if (0 == p->GetVal(CPacketRsp::QID, any)) {
            unsigned long qid = any;
            CQPacketSuper::PACKETTYPE pt = p->GetPacketType();
            int ev = GetEventType(pt);
            if (-1!=ev)
                SendEvent(qid, (QEVENT)ev, p);
            p->GetDecryptedData(decrypted);
        }
        delete p;
        p = 0;
    }

	return 0;
}

int CQFsm::SendEvent(unsigned long number, QEVENT ev, CQPacketSuper* p)
{
	map_qobj::iterator it = _qbase.find(number);
    if (_qbase.end() == it) {
        CreateInst(number);
        it = _qbase.find(number);
    }

	if (_qbase.end() != it) {
		CAnyType any;
		it->second->GetVal(CQcb::QCBSTATE, any);

		long curstate = any;
		if (_arrExcuteFunc[curstate][ev]) {
		    (this->*_arrExcuteFunc[curstate][ev])(it->second, p);
		}
	}
    return 0;
}

int CQFsm::SetListCtrlText(unsigned long qid, char* szText)
{
    CListCtrl* ctl = (CListCtrl*)CWnd::FromHandle(_hListCtrl);
    CString str, str1;
    str1.Format("%d", qid);
    for (int i=0; i<ctl->GetItemCount(); i++)
    {
        str = ctl->GetItemText(i, 0);
        if (str==str1) {
            ctl->SetItemText(i, 1, szText);
            break;
        }
    }
    if (i>=ctl->GetItemCount())
        return -1;
    return 0;
}

int CQFsm::ChangeState(CQcb* qcb, QSTATE stat)
{
    CAnyType any;
    qcb->SetVal(CQcb::QCBSTATE, any);
    return 0;
}

/*****************************  定义状态改变函数 *****************************/

void CQFsm::fn_SLOGOUT_on_ESTART(CQcb* qcb, CQPacketSuper* p)
{
    CAnyType any;
    qcb->GetVal(CQcb::QID, any);
    SetListCtrlText(any, "started");
    //SET_TIMER(3);
}

void CQFsm::fn_SLOGOUT_on_ESTOP(CQcb* qcb, CQPacketSuper* p)
{
    CAnyType any;
    qcb->GetVal(CQcb::QID, any);
    SetListCtrlText(any, "");
    //SET_TIMER(3);
}

void CQFsm::fn_SLOGOUT_on_EPAUSE(CQcb* qcb, CQPacketSuper* p)
{
    CAnyType any;
    qcb->GetVal(CQcb::QID, any);
    SetListCtrlText(any, "paused");
    //SET_TIMER(3);
}