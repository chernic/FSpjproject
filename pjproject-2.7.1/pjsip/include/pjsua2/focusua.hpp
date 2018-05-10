/* $Id: focusua.hpp 5676 2018-04-18 15:19:22Z chernic $ */
/* 
 * Copyright (C) 2018 FOCUSTAR Inc. (http://www.focustar.net)
 */

// PJSIP_EVENT_UNKNOWN,             // 0
// PJSIP_EVENT_TIMER,               // 1
// PJSIP_EVENT_TX_MSG,              // 2
// PJSIP_EVENT_RX_MSG,              // 3
// PJSIP_EVENT_TRANSPORT_ERROR,     // 4
// PJSIP_EVENT_TSX_STATE,           // 5
// PJSIP_EVENT_USER                 // 6

// PJSIP_TSX_STATE_NULL,            // 0 /**< For UAC, before any message is sent.       */
// PJSIP_TSX_STATE_CALLING,         // 1 /**< For UAC, just after request is sent.       */
// PJSIP_TSX_STATE_TRYING,          // 2 /**< For UAS, just after request is received.   */
// PJSIP_TSX_STATE_PROCEEDING,      // 3 /**< For UAS/UAC, after provisional response.  */
// PJSIP_TSX_STATE_COMPLETED,       // 4 /**< For UAS/UAC, after final response.         */
// PJSIP_TSX_STATE_CONFIRMED,       // 5 /**< For UAS, after ACK is received.            */
// PJSIP_TSX_STATE_TERMINATED,      // 6 /**< For UAS/UAC, before it's destroyed.        */
// PJSIP_TSX_STATE_DESTROYED,       // 7 /**< For UAS/UAC, will be destroyed now.        */
// PJSIP_TSX_STATE_MAX              // 9 /**< Number of states.                          */

//{
// #define PJSIP_EVENT_INIT_TIMER(event,pentry)                     
// #define PJSIP_EVENT_INIT_TSX_STATE(event,ptsx,ptype,pdata,prev)  
// #define PJSIP_EVENT_INIT_TX_MSG(event,ptdata)                    
// #define PJSIP_EVENT_INIT_RX_MSG(event,prdata)                    
// #define PJSIP_EVENT_INIT_TRANSPORT_ERROR(event,ptsx,ptdata)      
// #define PJSIP_EVENT_INIT_USER(event,u1,u2,u3,u4)                 
//}

// Line 281:  struct pjsip_rx_data
// Line 508:  struct pjsip_tx_data
// Line 776:  struct pjsip_transport
// Line 1001: struct pjsip_tpfactory

// TimerEvent      timer;           1               ( TimerEntry
// TxMsgEvent      txMsg;           2               ( SipTxData       SipTransaction
// RxMsgEvent      rxMsg;           3               ( SipRxData
// TxErrorEvent    txError;         4               ( SipTxData       SipTransaction
// TsxStateEvent   tsxState;        5               ( TsxStateEventSrc
// UserEvent       user;            6               ( GenericData

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
struct JsonOnExample:               public PersistentObject{
    int nExample;
public:
    /*  不添加以下虚函数则会有以下报错
        1>focussip.cpp(1686) : error C2259: “pj::JsonOnExample”: 不能实例化抽象类
        1>        由于下列成员:
        1>        “void pj::PersistentObject::writeObject(pj::ContainerNode &) throw(pj::Error) const”: 是抽象的
        1>        persistent.hpp(72) : 参见“pj::PersistentObject::writeObject”的声明
    */
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    /*  不添加以下虚函数则会有以下报错
        1>focussip.cpp(1686) : error C2259: “pj::JsonOnExample”: 不能实例化抽象类
        1>        由于下列成员:
        1>        “void pj::PersistentObject::readObject(const pj::ContainerNode &) throw(pj::Error)”: 是抽象的
        1>        persistent.hpp(65) : 参见“pj::PersistentObject::readObject”的声明
    */
    virtual void readObject         (const ContainerNode &node) throw(Error);
    /*  不添加以下函数则会有以下报错
        1>focussip.cpp(1687) : error C2039: “fromPj”: 不是“pj::JsonOnExample”的成员
        1>        account.hpp(1365) : 参见“pj::JsonOnExample”的声明
     */
    void fromPj                     (int call_id, pjsip_rx_data &rdata);
};
struct JsonAccountInfo :            public AccountInfo, 
                                    public PersistentObject{
public:
    virtual void writeObject(ContainerNode &node) const throw(Error);
    void readObject(const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("JsonAccountInfo");

        NODE_READ_INT           ( this_node, id);
        NODE_READ_BOOL          ( this_node, isDefault);
        NODE_READ_STRING        ( this_node, uri);
        NODE_READ_BOOL          ( this_node, regIsConfigured);
        NODE_READ_BOOL          ( this_node, regIsActive);
        NODE_READ_INT           ( this_node, regExpiresSec);
        //NODE_READ_INT           ( this_node, regStatus);
        NODE_READ_NUM_T         ( this_node, pjsip_status_code, regStatus);
        NODE_READ_STRING        ( this_node, regStatusText);
        NODE_READ_INT           ( this_node, regLastErr);
        NODE_READ_BOOL          ( this_node, onlineStatus);
        NODE_READ_STRING        ( this_node, onlineStatusText);
    }
    void fromPj(const pjsua_acc_info &pai);
};
struct JsonOnIncomingCallParam:     public PersistentObject{
    int         callId;
    string      info;
    string      wholeMsg;
    string      srcAddress;
    // void     *pjRxData;
public:
    virtual void writeObject(ContainerNode &node) const throw(Error);
    void readObject(const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("JsonOnIncomingCallParam");

        NODE_READ_INT       ( this_node, callId);
        NODE_READ_STRING    ( this_node, info);
        NODE_READ_STRING    ( this_node, wholeMsg);
        NODE_READ_STRING    ( this_node, srcAddress);
    }
    void fromPj(int call_id, pjsip_rx_data &rdata);
};
// 000000000000000000000000000000000000000000000000000000000
struct Json_TimerEntry:             public PersistentObject{
    // void *user_data;
    // int id;
    // pj_timer_heap_callback *cb;
    // pj_timer_id_t _timer_id;
    // pj_time_val _timer_value;
    // pj_grp_lock_t *_grp_lock;
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_SipTxData");
        PJ_UNUSED_ARG( this_node );
    }
    void fromPj                     (pj_timer_entry  &entry);
    Json_TimerEntry(){
    }
};
struct Json_SipTxData:              public PersistentObject{
    string          info;
    string          wholeMsg;
    SocketAddress   dstAddress;
    void*           pjTxData;
    string          void_pjTxData;
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_SipTxData");
        PJ_UNUSED_ARG( this_node );
    }
    void fromPj                     (pjsip_tx_data &tdata);
    Json_SipTxData(){
    }
};
struct Json_SipRxData:              public PersistentObject{
    string          info;
    string          wholeMsg;
    SocketAddress   srcAddress;
    void*           pjRxData;
    string          void_pjRxData;
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_SipRxData");
        PJ_UNUSED_ARG( this_node );
    }
    void fromPj                     (pjsip_rx_data &rdata);
    Json_SipRxData(){
    }
};
struct Json_SipTransaction:         public PersistentObject{
    pjsip_role_e        role;           /**< Role (UAS or UAC)      */
    string              method;         /**< The method.            */
    int                 statusCode;     /**< Last status code seen. */
    string              statusText;     /**< Last reason phrase.    */
    pjsip_tsx_state_e   state;          /**< State.                 */
    Json_SipTxData      lastTx;         /**< Msg kept for retrans.  */
    void               *pjTransaction;  /**< pjsip_transaction.     */
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_SipTransaction");
        PJ_UNUSED_ARG( this_node );
    }
    void fromPj                     (pjsip_transaction &tsx);
    Json_SipTransaction(){
    }
};
// 111111111111111111111111111111111111111111111111111111111
struct Json_TimerEvent:             public PersistentObject{//struct{}
    // (Void*) Timer entry, corresponds to pj_timer_entry
    Json_TimerEntry                 entry;  
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_TimerEvent");
        PJ_UNUSED_ARG( this_node );
    }
    Json_TimerEvent(){
    }
};
// 222222222222222222222222222222222222222222222222222222222
struct Json_TxMsgEvent:             public PersistentObject{//struct{}
    Json_SipTxData  tdata;
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_TxMsgEvent");
        PJ_UNUSED_ARG( this_node );
    }
    Json_TxMsgEvent(){
    }
};
// 333333333333333333333333333333333333333333333333333333333
struct Json_RxMsgEvent:             public PersistentObject{//struct{}
    Json_SipRxData  rdata;
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_RxMsgEvent");
        PJ_UNUSED_ARG( this_node );
    }
    Json_RxMsgEvent(){
    }
};
// 444444444444444444444444444444444444444444444444444444444
struct Json_TxErrorEvent:           public PersistentObject{
    Json_SipTxData          tdata;  // SipTxData            tdata;
    Json_SipTransaction     tsx;    // SipTransaction       tsx;
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_TxErrorEvent");
        PJ_UNUSED_ARG( this_node );
    }
    Json_TxErrorEvent(){
    }
};
// 555555555555555555555555555555555555555555555555555555555
struct Json_TsxStateEventSrc:       public PersistentObject{
    Json_SipRxData  rdata;              /**< The incoming message.      */
    Json_SipTxData  tdata;              /**< The outgoing message.      */
    Json_TimerEntry timer;              /**< The timer.                 */
    pj_status_t     tran_erro_rstatus;  /**< Transport error status.    */
    GenericData     data;               /**< Generic data.              */
    
    string          void_data;          /**< */
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_TsxStateEventSrc");
        PJ_UNUSED_ARG( this_node );
    }
    Json_TsxStateEventSrc(){
    }
};
struct Json_TsxStateEvent:          public PersistentObject{
    Json_TsxStateEventSrc     src;  /**< Event source.              */
    Json_SipTransaction       tsx;  /**< The transaction.           */
    pjsip_tsx_state_e   prevState;  /**< Previous state.            */
    pjsip_event_id_e         type;  /**< Type of event source:      */
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_TsxStateEvent");
        PJ_UNUSED_ARG( this_node );
    }
    Json_TsxStateEvent(){
    }
};
// 666666666666666666666666666666666666666666666666666666666
struct Json_UserEvent:              public PersistentObject{
    GenericData  user1;
    GenericData  user2;
    GenericData  user3;
    GenericData  user4;

    string  void_user1;
    string  void_user2;
    string  void_user3;
    string  void_user4;
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_UserEvent");
        PJ_UNUSED_ARG( this_node );
    }
    void fromPj                     (const UserEvent &ev){
        PJ_UNUSED_ARG( ev );
    }
    Json_UserEvent(){
    }
};

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
struct Json_SipEventBody:           public PersistentObject{
    Json_TimerEvent     timer;      // 1 TimerEvent        timer;
    Json_TxMsgEvent     txMsg;      // 2 TxMsgEvent        txMsg;
    Json_RxMsgEvent     rxMsg;      // 3 RxMsgEvent        rxMsg;
    Json_TxErrorEvent   txError;    // 4 TxErrorEvent      txError;
    Json_TsxStateEvent  tsxState;   // 5 TsxStateEvent     tsxState;
    Json_UserEvent      user;       // 6 UserEvent         user;
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_SipEventBody");
        PJ_UNUSED_ARG( this_node );
    }
    Json_SipEventBody(){
    }
};
struct Json_SipEvent:               public PersistentObject{
    pjsip_event_id_e    type;
    Json_SipEventBody   body;
    void                *pjEvent;
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        ContainerNode this_node = node.readContainer("Json_SipEvent");
        PJ_UNUSED_ARG( this_node );
    }
    void fromPj                     (const pjsip_event &ev);
    Json_SipEvent() : type          (PJSIP_EVENT_UNKNOWN), pjEvent(NULL){
    }
};

/**
 * @}  PJSUA2
 */
} // namespace pj

#endif  /* __PJSUA2_FOCUSUA_HPP__ */
