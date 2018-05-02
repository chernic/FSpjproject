/* $Id: focusua.hpp 5676 2018-04-18 15:19:22Z chernic $ */

#ifndef __PJSUA2_FOCUSUA_HPP__
#define __PJSUA2_FOCUSUA_HPP__

/**
 * @file pjsua2/focusua.hpp
 * @brief PJSUA2 focusua operations
 */
#include <pjsua-lib/pjsua.h>
#include <pjsua2/persistent.hpp>
#include <pjsua2/presence.hpp>
#include <pjsua2/siptypes.hpp>
#include <pjsua2/call.hpp>

/** PJSUA2 API is inside pj namespace */
namespace pj{

/**
 * @defgroup PJSUA2_ACC Focusua
 * @ingroup PJSUA2_Ref
 * @{
 */
using std::string;
struct JsonAccountInfo : public AccountInfo, public PersistentObject{
public:
    /** Import from pjsip data */
    void fromPj(const pjsua_acc_info &pai);
    
    virtual void readObject(const ContainerNode &node) throw(Error);
    virtual void writeObject(ContainerNode &node) const throw(Error);
};
struct JsonOnIncomingCallParam: 
    public PersistentObject
{
    int         callId;
    string      info;
    string      wholeMsg;
    string      srcAddress;
    // void     *pjRxData;
public:
    /*  不添加以下虚函数则会有以下报错
    1>focussip.cpp(1687) : error C2039: “fromPj”: 不是“pj::JsonOnIncomingCallParam”的成员
    1>        account.hpp(1365) : 参见“pj::JsonOnIncomingCallParam”的声明
     */
    void fromPj(int call_id, pjsip_rx_data &rdata);

    /*  不添加以下虚函数则会有以下报错
    1>focussip.cpp(1686) : error C2259: “pj::JsonOnIncomingCallParam”: 不能实例化抽象类
    1>        由于下列成员:
    1>        “void pj::PersistentObject::readObject(const pj::ContainerNode &) throw(pj::Error)”: 是抽象的
    1>        persistent.hpp(65) : 参见“pj::PersistentObject::readObject”的声明
    1>        “void pj::PersistentObject::writeObject(pj::ContainerNode &) throw(pj::Error) const”: 是抽象的
    1>        persistent.hpp(72) : 参见“pj::PersistentObject::writeObject”的声明
    */
    virtual void readObject(const ContainerNode &node) throw(Error);
    virtual void writeObject(ContainerNode &node) const throw(Error);
};

// 00000000000000000000000000000000000000000000000000000
struct Json_SipTxData:          public PersistentObject{
    string          info;
    string          wholeMsg;
    SocketAddress   dstAddress;
    void*           pjTxData;
    string          void_pjTxData;
public:
    Json_SipTxData();
    void fromPj                     (pjsip_tx_data &tdata);
    virtual void readObject         (const ContainerNode &node) throw(Error);
    virtual void writeObject        (ContainerNode &node) const throw(Error);
};
struct Json_SipTransaction:          public PersistentObject{
    pjsip_role_e        role;           /**< Role (UAS or UAC)      */
    string              method;         /**< The method.            */
    int                 statusCode;     /**< Last status code seen. */
    string              statusText;     /**< Last reason phrase.    */
    pjsip_tsx_state_e   state;          /**< State.                 */
    Json_SipTxData      lastTx;         // SipTxData           lastTx;         /**< Msg kept for retrans.  */
    void               *pjTransaction;  /**< pjsip_transaction.     */
public:
    Json_SipTransaction();
    void fromPj                     (pjsip_transaction &tsx);
    virtual void readObject         (const ContainerNode &node) throw(Error);
    virtual void writeObject        (ContainerNode &node) const throw(Error);
};

// 22222222222222222222222222222222222222222222222222222
struct Json_TxMsgEvent:         public PersistentObject{
    Json_SipTxData  tdata;
public:
    Json_TxMsgEvent();
    virtual void readObject         (const ContainerNode &node) throw(Error);
    virtual void writeObject        (ContainerNode &node) const throw(Error);
};
// 33333333333333333333333333333333333333333333333333333
struct Json_SipRxData:          public PersistentObject{
    string          info;
    string          wholeMsg;
    SocketAddress   srcAddress;
    void*           pjRxData;
    string          void_pjRxData;
public:
    Json_SipRxData();
    void fromPj                     (pjsip_rx_data &rdata);
    virtual void readObject         (const ContainerNode &node) throw(Error);
    virtual void writeObject        (ContainerNode &node) const throw(Error);
};
struct Json_RxMsgEvent:         public PersistentObject{
    Json_SipRxData  rdata;
public:
    Json_RxMsgEvent();
    virtual void readObject         (const ContainerNode &node) throw(Error);
    virtual void writeObject        (ContainerNode &node) const throw(Error);
};
// 44444444444444444444444444444444444444444444444444444
struct Json_TxErrorEvent:         public PersistentObject{
    Json_SipTxData          tdata;  // SipTxData            tdata;
    Json_SipTransaction     tsx;    // SipTransaction       tsx;
public:
    Json_TxErrorEvent();
    virtual void readObject         (const ContainerNode &node) throw(Error);
    virtual void writeObject        (ContainerNode &node) const throw(Error);
};
// 66666666666666666666666666666666666666666666666666666
struct Json_UserEvent:          public PersistentObject{
    GenericData  user1;
    GenericData  user2;
    GenericData  user3;
    GenericData  user4;
    
    string  void_user1;
    string  void_user2;
    string  void_user3;
    string  void_user4;

public:
    Json_UserEvent();
    void fromPj(const UserEvent &ev);
    virtual void readObject(const ContainerNode &node) throw(Error);
    virtual void writeObject(ContainerNode &node) const throw(Error);
};
// 00000000000000000000000000000000000000000000000000000
struct Json_SipEventBody:       public PersistentObject{
    TimerEvent          timer;
    TsxStateEvent       tsxState;
    Json_TxMsgEvent     txMsg;      // 2 TxMsgEvent        txMsg;
    Json_RxMsgEvent     rxMsg;      // 3 RxMsgEvent        rxMsg;
    Json_TxErrorEvent   txError;    // 4 TxErrorEvent      txError;
    Json_UserEvent      user;       // 6 UserEvent         user;
public:
    Json_SipEventBody();
    void fromPj(const pjsip_event &ev);
    virtual void readObject(const ContainerNode &node) throw(Error);
    virtual void writeObject(ContainerNode &node) const throw(Error);
};
struct Json_SipEvent:           public PersistentObject{
    pjsip_event_id_e    type;
    Json_SipEventBody   body;
    void                *pjEvent;
public:
    Json_SipEvent();
    void fromPj(const pjsip_event &ev);
    virtual void readObject(const ContainerNode &node) throw(Error);
    virtual void writeObject(ContainerNode &node) const throw(Error);
};
struct JsonOnCallStateParam:    public PersistentObject{
public:
    void fromPj(int call_id, pjsip_event &rdata);
public:
    virtual void readObject(const ContainerNode &node) throw(Error);
    virtual void writeObject(ContainerNode &node) const throw(Error);
};

/**
 * @}  PJSUA2
 */

} // namespace pj

#endif  /* __PJSUA2_FOCUSUA_HPP__ */
