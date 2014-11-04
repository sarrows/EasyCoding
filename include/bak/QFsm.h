#ifndef _QFSM_H_
#define _QFSM_H_

#include "QFsmSuper.h"

// 消息定义，wparam:qq号码
#define MSG_LOGIN   WM_USER+1    // 登陆结果消息,lparam:登陆结果,0成功
#define MSG_SENDMSG WM_USER+2    // 发送消息结果,HIWORD(lparam):当前发送第几个,LOWORD(lparam):共几个
#define MSG_RESULT  WM_USER+3    // 处理结果消息,lparam:处理失败数量,0代表全部成功
    
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
    static CQFsm * _inst;                         // 唯一实例
    map_qobj       _qbase;                        // 对象库
    HWND           _hwnd;                         // 窗口句柄(主要用于创建定时器)
    HWND           _hListCtrl;                    // 列表框句柄(主要用于显示)
    unsigned short _iPortStart;                   // 开始尝试的端口
    unsigned short _iPortEnd;                     // 结束尝试的端口
};

#endif
