#ifndef _QFSMSUPER_H_
#define _QFSMSUPER_H_

#include <map>

#include "Qcb.h"
#include "QPacketSuper.h"

// ��������¼��������޸�
#define FUNCDECLARE1(x) \
    virtual void fn_##x##_on_EDELETE(CQcb* qcb, CQPacketSuper* p){}        \
    virtual void fn_##x##_on_ESTART(CQcb* qcb, CQPacketSuper* p){}         \
    virtual void fn_##x##_on_EPAUSE(CQcb* qcb, CQPacketSuper* p){}         \
    virtual void fn_##x##_on_ESTOP(CQcb* qcb, CQPacketSuper* p){}          \
    virtual void fn_##x##_on_ETIMER(CQcb* qcb, CQPacketSuper* p){}         \
    virtual void fn_##x##_on_ETOKENRET(CQcb* qcb, CQPacketSuper* p){}      \
    virtual void fn_##x##_on_ELOGINRET(CQcb* qcb, CQPacketSuper* p){}      \
    virtual void fn_##x##_on_EMSGREQRET(CQcb* qcb, CQPacketSuper* p){}     \
    virtual void fn_##x##_on_EPUMPREQRET(CQcb* qcb, CQPacketSuper* p){}    \
    virtual void fn_##x##_on_ELOGOUTRET(CQcb* qcb, CQPacketSuper* p){}     \
    virtual void fn_##x##_on_EFRIENDINFORET(CQcb* qcb, CQPacketSuper* p){}

// �������״̬�������޸�
#define FUNCDECLARE \
    FUNCDECLARE1(SLOGOUT) \
    FUNCDECLARE1(STOKENREQSEND) \
    FUNCDECLARE1(SLOGINREQSEND) \
    FUNCDECLARE1(SFRIENDINFOREQSEND) \
    FUNCDECLARE1(SLOGIN) \
    FUNCDECLARE1(SPUMPREQSEND) \
    FUNCDECLARE1(SLOGOUTREQSEND) \
    FUNCDECLARE1(SLEAVE) \
    FUNCDECLARE1(SAUTOREPLY) \
    FUNCDECLARE1(SDELETED)

// ��������¼��������޸�
#define FUNCFILL1(y) \
    _arrExcuteFunc[y][EDELETE]        = (changestate)fn_##y##_on_EDELETE;       \
    _arrExcuteFunc[y][ESTART]         = (changestate)fn_##y##_on_ESTART;        \
    _arrExcuteFunc[y][EPAUSE]         = (changestate)fn_##y##_on_EPAUSE;        \
    _arrExcuteFunc[y][ESTOP]          = (changestate)fn_##y##_on_ESTOP;         \
    _arrExcuteFunc[y][ETIMER]         = (changestate)fn_##y##_on_ETIMER;        \
    _arrExcuteFunc[y][ETOKENRET]      = (changestate)fn_##y##_on_ETOKENRET;     \
    _arrExcuteFunc[y][ELOGINRET]      = (changestate)fn_##y##_on_ELOGINRET;     \
    _arrExcuteFunc[y][EMSGREQRET]     = (changestate)fn_##y##_on_EMSGREQRET;    \
    _arrExcuteFunc[y][EPUMPREQRET]    = (changestate)fn_##y##_on_EPUMPREQRET;   \
    _arrExcuteFunc[y][ELOGOUTRET]     = (changestate)fn_##y##_on_ELOGOUTRET;    \
    _arrExcuteFunc[y][EFRIENDINFORET] = (changestate)fn_##y##_on_EFRIENDINFORET;

// �������״̬�������޸�
#define FUNCFILL \
    FUNCFILL1(SLOGOUT)            \
    FUNCFILL1(STOKENREQSEND)      \
    FUNCFILL1(SLOGINREQSEND)      \
    FUNCFILL1(SFRIENDINFOREQSEND) \
    FUNCFILL1(SLOGIN)             \
    FUNCFILL1(SPUMPREQSEND)       \
    FUNCFILL1(SLOGOUTREQSEND)     \
    FUNCFILL1(SLEAVE)             \
    FUNCFILL1(SAUTOREPLY)         \
    FUNCFILL1(SDELETED)

// CQFsmSuper
class CQFsmSuper
{
public:

    typedef map<unsigned long, CQcb *> map_qobj;
    typedef void (CQFsmSuper::*changestate)(CQcb* qcb, CQPacketSuper* p);

    // ��������¼��������޸�
    enum QEVENT {
        EDELETE=0,        // ɾ���¼�
        ESTART,           // ��ʼ�¼�
        EPAUSE,           // ��ͣ�¼�
        ESTOP,            // ֹͣ�¼�
        ETIMER,           // ��ʱ�¼�
        ETOKENRET,        // ���Ʒ���
        ELOGINRET,        // ��¼����
        EMSGREQRET,       // ��Ϣ���󷵻�
        EPUMPREQRET,      // �������󷵻�
        ELOGOUTRET,       // �������󷵻�
        EFRIENDINFORET,   // ������Ϣ����

        EVENTCNT
    };

    // �������״̬�������޸�
    enum QSTATE {
        SLOGOUT=0,          // ������״̬
        STOKENREQSEND,      // ���������ѷ���
        SLOGINREQSEND,      // ��½�����ѷ���
        SFRIENDINFOREQSEND, // �������б������ѷ���
        SLOGIN,             // �ѵ���״̬
        SPUMPREQSEND,       // ���������ѷ���
        SLOGOUTREQSEND,     // ���������ѷ���
        SLEAVE,             // �뿪״̬
        SAUTOREPLY,         // �Զ��ظ�״̬
        SDELETED,           // ���˳�״̬(��״̬�������ȶ�����,�Ǻ�)

        STATECNT
    };

    CQFsmSuper ()
    {
        memset(_arrExcuteFunc, 0, sizeof(_arrExcuteFunc));
    }

    virtual ~CQFsmSuper()
    {
    }

    // ��ת��������
    FUNCDECLARE

public:
    changestate    _arrExcuteFunc[STATECNT][EVENTCNT]; // ��ת��������
};

#endif
