#ifndef _QFSMSUPER_H_
#define _QFSMSUPER_H_

#include <map>

#include "Qcb.h"
#include "QPacketSuper.h"

// 如果增加事件，必须修改
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

// 如果增加状态，必须修改
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

// 如果增加事件，必须修改
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

// 如果增加状态，必须修改
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

    // 如果增加事件，必须修改
    enum QEVENT {
        EDELETE=0,        // 删除事件
        ESTART,           // 开始事件
        EPAUSE,           // 暂停事件
        ESTOP,            // 停止事件
        ETIMER,           // 超时事件
        ETOKENRET,        // 令牌返回
        ELOGINRET,        // 登录返回
        EMSGREQRET,       // 消息请求返回
        EPUMPREQRET,      // 心跳请求返回
        ELOGOUTRET,       // 离线请求返回
        EFRIENDINFORET,   // 好友信息返回

        EVENTCNT
    };

    // 如果增加状态，必须修改
    enum QSTATE {
        SLOGOUT=0,          // 已离线状态
        STOKENREQSEND,      // 令牌请求已发送
        SLOGINREQSEND,      // 登陆请求已发送
        SFRIENDINFOREQSEND, // 读好友列表请求已发送
        SLOGIN,             // 已登入状态
        SPUMPREQSEND,       // 心跳请求已发送
        SLOGOUTREQSEND,     // 离线请求已发送
        SLEAVE,             // 离开状态
        SAUTOREPLY,         // 自动回复状态
        SDELETED,           // 已退出状态(此状态不可能稳定存在,呵呵)

        STATECNT
    };

    CQFsmSuper ()
    {
        memset(_arrExcuteFunc, 0, sizeof(_arrExcuteFunc));
    }

    virtual ~CQFsmSuper()
    {
    }

    // 跳转函数声明
    FUNCDECLARE

public:
    changestate    _arrExcuteFunc[STATECNT][EVENTCNT]; // 跳转函数数组
};

#endif
