#ifndef _QFSM_H_
#define _QFSM_H_

#include "QFsmSuper.h"

// ��Ϣ���壬wparam:qq����
#define MSG_LOGIN   WM_USER+1    // ��½�����Ϣ,lparam:��½���,0�ɹ�
#define MSG_SENDMSG WM_USER+2    // ������Ϣ���,HIWORD(lparam):��ǰ���͵ڼ���,LOWORD(lparam):������
#define MSG_RESULT  WM_USER+3    // ��������Ϣ,lparam:����ʧ������,0����ȫ���ɹ�
    
#define SET_TIMER(x) do { CAnyType any;                                         \
                          if (0==qcb->GetVal(CQcb::QID, any) && _hwnd)      \
                              ::SetTimer(_hwnd, any, (x)*1000, CQFsm::OnTimer); \
                     } while (0)

class CQFsm : public CQFsmSuper
{
public:

    static CQFsm * Instance()
    {
        if (!_inst)
            _inst = new CQFsm;
        return _inst;
    }

    void Finalize()
    {
        if (_inst) {
            delete _inst;
            _inst = 0;
        }
    }

    static void CALLBACK OnTimer(HWND hwnd, UINT uMsg, UINT nIDEvent, DWORD dwTime);

    int DeleteInst(unsigned long number);

    int SetParam(unsigned short portstart, unsigned short portend, HWND hwnd, HWND hListCtrl);
    int Init();

	int SendData(const unsigned char *data, int len, unsigned char *decrypted);
    int SendEvent(unsigned long number, QEVENT ev, CQPacketSuper* p);

    int ChangeState(CQcb* qcb, QSTATE stat);
    
    QEVENT GetEventType(CQPacketSuper::PACKETTYPE pkttype);

private:
    CQFsm()
    {
        _hwnd       = 0;
        _hListCtrl  = 0;
        _iPortStart = 0;
        _iPortEnd   = 0;
        FUNCFILL
    }

    virtual ~CQFsm()
    {
        map_qobj::iterator it = _qbase.begin();
        map_qobj::iterator ittmp;
        while ((ittmp=it++) != _qbase.end()) {
            if (ittmp->second)
                delete ittmp->second;
        }
        _qbase.clear();
    }
    
    int CreateInst(unsigned long number);

    int SetListCtrlText(unsigned long qid, char* szText);

private:
    void fn_SLOGOUT_on_ESTART(CQcb* qcb, CQPacketSuper* p);
    void fn_SLOGOUT_on_ESTOP(CQcb* qcb, CQPacketSuper* p);
    void fn_SLOGOUT_on_EPAUSE(CQcb* qcb, CQPacketSuper* p);

private:
    static CQFsm * _inst;                         // Ψһʵ��
    map_qobj       _qbase;                        // �����
    HWND           _hwnd;                         // ���ھ��(��Ҫ���ڴ�����ʱ��)
    HWND           _hListCtrl;                    // �б����(��Ҫ������ʾ)
    unsigned short _iPortStart;                   // ��ʼ���ԵĶ˿�
    unsigned short _iPortEnd;                     // �������ԵĶ˿�
};

#endif
