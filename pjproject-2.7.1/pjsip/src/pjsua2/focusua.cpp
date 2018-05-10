/* $Id: focusua.hpp 5676 2018-04-18 15:19:22Z chernic $ */
/* 
 * Copyright (C) 2018 FOCUSTAR Inc. (http://www.focustar.net)
 */
#include <pjsua2/account.hpp>
#include <pjsua2/endpoint.hpp>
#include <pjsua2/presence.hpp>
#include <pjsua2/focusua.hpp>
#include <pj/ctype.h>
#include "util.hpp"

using namespace pj;
using namespace std;

#define THIS_FILE   "focusua.cpp"
// 
void JsonAccountInfo            ::fromPj(const pjsua_acc_info &pai){
    id                  = pai.id;
    isDefault           = pai.is_default != 0;
    uri                 = pj2Str(pai.acc_uri);
    regIsConfigured     = pai.has_registration != 0;
    regIsActive         = pai.has_registration && pai.expires > 0 &&(pai.status / 100 == 2);
    regExpiresSec       = pai.expires;
    regStatus           = pai.status;
    regStatusText       = pj2Str(pai.status_text);
    regLastErr          = pai.reg_last_err;
    onlineStatus        = pai.online_status != 0;
    onlineStatusText    = pj2Str(pai.online_status_text);
}
void JsonAccountInfo            ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("JsonAccountInfo");

    NODE_WRITE_INT      ( this_node, id);
    NODE_WRITE_BOOL     ( this_node, isDefault);
    NODE_WRITE_STRING   ( this_node, uri);
    NODE_WRITE_BOOL     ( this_node, regIsConfigured);
    NODE_WRITE_BOOL     ( this_node, regIsActive);
    NODE_WRITE_INT      ( this_node, regExpiresSec);
    /*NODE_WRITE_INT    ( this_node, regStatus);*/
    NODE_WRITE_NUM_T    ( this_node, pjsip_status_code, regStatus);
    NODE_WRITE_STRING   ( this_node, regStatusText);
    NODE_WRITE_INT      ( this_node, regLastErr);
    NODE_WRITE_BOOL     ( this_node, onlineStatus);
    NODE_WRITE_STRING   ( this_node, onlineStatusText);
}
//
void JsonOnIncomingCallParam    ::fromPj(int call_id, pjsip_rx_data &rdata){
    char straddr[PJ_INET6_ADDRSTRLEN+10];
    
    callId          = call_id;
    
    // Chernic : if test, do not use pjsip_rx_data_get_info in case error!!!
    if( string("no_info") != rdata.msg_info.info ){
        info        = pjsip_rx_data_get_info(&rdata);
    }else{
        info = string("no_info");
    }

    wholeMsg        = string(rdata.msg_info.msg_buf, rdata.msg_info.len);
    pj_sockaddr_print(&rdata.pkt_info.src_addr, straddr, sizeof(straddr), 3);
    srcAddress      = straddr;

    //pjRxData      = (void *)&rdata;
    
}
void JsonOnIncomingCallParam    ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("JsonOnIncomingCallParam");

    NODE_WRITE_INT      ( this_node, callId);
    NODE_WRITE_STRING   ( this_node, info);
    NODE_WRITE_STRING   ( this_node, wholeMsg);
    NODE_WRITE_STRING   ( this_node, srcAddress);
}
///////////////////////////////// 000000
// basic struct
void Json_SipTxData             ::fromPj(pjsip_tx_data      &tdata){
    char straddr[PJ_INET6_ADDRSTRLEN+10];
    
    if( string("no_info") != tdata.info ){
        //info        = pjsip_rx_data_get_info(&tdata);
        info        = pjsip_tx_data_get_info(&tdata);
    }else{
        info = string("no_info");
    }
    
    pjsip_tx_data_encode(&tdata);
    wholeMsg        = string(tdata.buf.start, tdata.buf.end - tdata.buf.start);
    if (pj_sockaddr_has_addr(&tdata.tp_info.dst_addr)) {
        pj_sockaddr_print(&tdata.tp_info.dst_addr, straddr, sizeof(straddr), 3);
        dstAddress      = straddr;
    } else {
        dstAddress      = "";
    }
    pjTxData        = (void *)&tdata;
}
void Json_SipTxData             ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_SipTxData");

    NODE_WRITE_STRING   ( this_node, info);                         // string          info;
    NODE_WRITE_STRING   ( this_node, wholeMsg);                     // string          wholeMsg;
    NODE_WRITE_STRING   ( this_node, dstAddress);                   // SocketAddress   dstAddress;
    //NODE_WRITE_OBJ    ( this_node, pjTxData);
    NODE_WRITE_STRING   ( this_node, void_pjTxData);                // void*           pjTxData;
}
//
void Json_SipRxData             ::fromPj(pjsip_rx_data      &rdata){
    char straddr[PJ_INET6_ADDRSTRLEN+10];

    // Chernic : if test, do not use pjsip_rx_data_get_info in case error!!!
    if( string("no_info") != rdata.msg_info.info ){
        info        = pjsip_rx_data_get_info(&rdata);
    }else{
        info = string("no_info");
    }
    wholeMsg        = string(rdata.msg_info.msg_buf, rdata.msg_info.len);
    pj_sockaddr_print(&rdata.pkt_info.src_addr, straddr, sizeof(straddr), 3);
    srcAddress      = straddr;
    pjRxData        = (void *)&rdata;
}
void Json_SipRxData             ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_SipRxData");

    NODE_WRITE_STRING   ( this_node, info);                         // string          info;
    NODE_WRITE_STRING   ( this_node, wholeMsg);                     // string          wholeMsg;
    NODE_WRITE_STRING   ( this_node, srcAddress);                   // SocketAddress   srcAddress;
    //NODE_WRITE_OBJ    ( this_node, pjRxData);
    NODE_WRITE_STRING   ( this_node, void_pjRxData);                // void*           pjRxData;
}
//
void Json_SipTransaction        ::fromPj(pjsip_transaction  & data){
    PJ_UNUSED_ARG( data );
}
void Json_SipTransaction        ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_SipTransaction");

    NODE_WRITE_NUM_T    ( this_node, pjsip_role_e,       role);     // pjsip_role_e      role;
    NODE_WRITE_STRING   ( this_node, method);                       // string            method;
    NODE_WRITE_INT      ( this_node, statusCode);                   // int               statusCode;
    NODE_WRITE_STRING   ( this_node, statusText);                   // string            statusText;
    NODE_WRITE_NUM_T    ( this_node, pjsip_tsx_state_e, state);     // pjsip_tsx_state_e state;
    NODE_WRITE_OBJ      ( this_node, lastTx);                       // SipTxData         lastTx;
}
//
void Json_TimerEntry            ::fromPj(pj_timer_entry     &entry){// Start with "pj_" is away from application
    //via : body.tsxState.src.timer.fromPj(*ev.body.tsx_state.src.timer);
    PJ_UNUSED_ARG( entry );

    // void *user_data;                                             // (×) Application should not touch this
    // int id;                                                      // (×) Application should not touch this
    // pj_timer_heap_callback *cb;                                  // (×) Application should not touch this
    // pj_timer_id_t _timer_id;                                     // (×) Application should not touch this
    // pj_time_val _timer_value;                                    // (×) Application should not touch this
    // pj_grp_lock_t *_grp_lock;                                    // (×) Application should not touch this
}
void Json_TimerEntry            ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_TimerEntry");
}
// complex struct
///////////////////////////////// 111111
void Json_TimerEvent            ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_TimerEvent");

    NODE_WRITE_OBJ      ( this_node, entry);                        //  Json_TimerEntry  entry;
}
///////////////////////////////// 222222
void Json_TxMsgEvent            ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_TxMsgEvent");

    NODE_WRITE_OBJ      ( this_node, tdata);                        //  SipTxData    tdata;
}
///////////////////////////////// 333333
void Json_RxMsgEvent            ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_RxMsgEvent");

    NODE_WRITE_OBJ      ( this_node, rdata);                        //  SipRxData    rdata;
}
///////////////////////////////// 444444
void Json_TxErrorEvent          ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_TxErrorEvent");

    NODE_WRITE_OBJ      ( this_node, tdata);                        //  Json_SipTxData
    NODE_WRITE_OBJ      ( this_node, tsx);                          //  Json_SipTransaction
}
///////////////////////////////// 555555
void Json_TsxStateEventSrc      ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_TsxStateEventSrc");

    NODE_WRITE_OBJ      ( this_node, rdata);                        // Json_SipRxData  rdata; 
    NODE_WRITE_OBJ      ( this_node, tdata);                        // Json_SipTxData  tdata;
    NODE_WRITE_OBJ      ( this_node, timer);                        // Json_TimerEntry timer;
    NODE_WRITE_INT      ( this_node, tran_erro_rstatus);            // pj_status_t     status;
    // GenericData      data;
    NODE_WRITE_STRING   ( this_node, void_data);                    // string          void_data;
}
void Json_TsxStateEvent         ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_TsxStateEvent");

    NODE_WRITE_OBJ      ( this_node, src);                          // Json_TsxStateEventSrc   src;
    NODE_WRITE_OBJ      ( this_node, tsx);                          // Json_SipTransaction     tsx;
    NODE_WRITE_NUM_T    ( this_node, pjsip_tsx_state_e, prevState); // pjsip_tsx_state_e   prevState;
    NODE_WRITE_NUM_T    ( this_node, pjsip_event_id_e, type);       // pjsip_event_id_e        type;
}
///////////////////////////////// 666666
void Json_UserEvent             ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_UserEvent");

    NODE_WRITE_STRING   ( this_node, void_user1);                   // NODE_WRITE_OBJ        ( this_node, user1);
    NODE_WRITE_STRING   ( this_node, void_user2);                   // NODE_WRITE_OBJ        ( this_node, user2);
    NODE_WRITE_STRING   ( this_node, void_user3);                   // NODE_WRITE_OBJ        ( this_node, user3);
    NODE_WRITE_STRING   ( this_node, void_user4);                   // NODE_WRITE_OBJ        ( this_node, user4);
}
///////////////////////////////// xxxxxx
void Json_SipEventBody          ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_SipEventBody");

    NODE_WRITE_OBJ      ( this_node, timer);                        // 1 Json_TimerEvent      timer;
    NODE_WRITE_OBJ      ( this_node, txMsg);                        // 2 Json_TxMsgEvent      txMsg;
    NODE_WRITE_OBJ      ( this_node, rxMsg);                        // 3 Json_RxMsgEvent      rxMsg;
    NODE_WRITE_OBJ      ( this_node, txError);                      // 4 Json_TxErrorEvent    txError;
    NODE_WRITE_OBJ      ( this_node, tsxState);                     // 5 Json_TsxStateEvent   tsxState;
    NODE_WRITE_OBJ      ( this_node, user);                         // 6 Json_UserEvent       user;
}
void Json_SipEvent              ::fromPj(const pjsip_event  &ev){
    type = ev.type;
    if (type == PJSIP_EVENT_TIMER) {
        /// body.timer.entry = ev.body.timer.entry;
        body.timer.entry.fromPj(*ev.body.timer.entry);
    } else if (type == PJSIP_EVENT_TSX_STATE) {
        body.tsxState.prevState = (pjsip_tsx_state_e)
        ev.body.tsx_state.prev_state;
        body.tsxState.tsx.fromPj(*ev.body.tsx_state.tsx);
        body.tsxState.type = ev.body.tsx_state.type;
        if (body.tsxState.type == PJSIP_EVENT_TX_MSG) {
            if (ev.body.tsx_state.src.tdata)
            body.tsxState.src.tdata.fromPj(*ev.body.tsx_state.src.tdata);
        } else if (body.tsxState.type == PJSIP_EVENT_RX_MSG) {
            if (ev.body.tsx_state.src.rdata)
            body.tsxState.src.rdata.fromPj(*ev.body.tsx_state.src.rdata);
        } else if (body.tsxState.type == PJSIP_EVENT_TRANSPORT_ERROR) {
            body.tsxState.src.tran_erro_rstatus = ev.body.tsx_state.src.status;
        } else if (body.tsxState.type == PJSIP_EVENT_TIMER) {
            /// body.tsxState.src.timer = ev.body.tsx_state.src.timer;
            body.tsxState.src.timer.fromPj(*ev.body.tsx_state.src.timer);
        } else if (body.tsxState.type == PJSIP_EVENT_USER) {
            body.tsxState.src.data = ev.body.tsx_state.src.data;
        }
    } else if (type == PJSIP_EVENT_TX_MSG) {
    if (ev.body.tx_msg.tdata)
        body.txMsg.tdata.fromPj(*ev.body.tx_msg.tdata);
    } else if (type == PJSIP_EVENT_RX_MSG) {
    if (ev.body.rx_msg.rdata)
        body.rxMsg.rdata.fromPj(*ev.body.rx_msg.rdata);
    } else if (type == PJSIP_EVENT_TRANSPORT_ERROR) {
    if (ev.body.tx_error.tdata)
        body.txError.tdata.fromPj(*ev.body.tx_error.tdata);
    if (ev.body.tx_error.tsx)
        body.txError.tsx.fromPj(*ev.body.tx_error.tsx);
    } else if (type == PJSIP_EVENT_USER) {
        body.user.user1 = ev.body.user.user1;
        body.user.user2 = ev.body.user.user2;
        body.user.user3 = ev.body.user.user3;
        body.user.user4 = ev.body.user.user4;
    }
    pjEvent = (void *)&ev;
}
void Json_SipEvent              ::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_SipEvent");

    NODE_WRITE_NUM_T    ( this_node, pjsip_event_id_e, type);       // pjsip_event_id_e    type;
    NODE_WRITE_OBJ      ( this_node, body);                         // SipEventBody ody;
    //NODE_WRITE_OBJ    ( this_node, pjEvent);                      // void *pjEvent;
    PJ_UNUSED_ARG       ( node );
}
///////////////////////////////// zzzzzz
