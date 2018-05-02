/* $Id: focusua.hpp 5676 2018-04-18 15:19:22Z chernic $ */
/* 
 * Copyright (C) 2013 Teluu Inc. (http://www.teluu.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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
void JsonAccountInfo::fromPj(const pjsua_acc_info &pai){
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
void JsonAccountInfo::readObject(const ContainerNode &node) throw(Error){
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
void JsonAccountInfo::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("JsonAccountInfo");

    NODE_WRITE_INT           ( this_node, id);
    NODE_WRITE_BOOL          ( this_node, isDefault);
    NODE_WRITE_STRING        ( this_node, uri);
    NODE_WRITE_BOOL          ( this_node, regIsConfigured);
    NODE_WRITE_BOOL          ( this_node, regIsActive);
    NODE_WRITE_INT           ( this_node, regExpiresSec);
    /*NODE_WRITE_INT         ( this_node, regStatus);*/
    NODE_WRITE_NUM_T         ( this_node, pjsip_status_code, regStatus);
    NODE_WRITE_STRING        ( this_node, regStatusText);
    NODE_WRITE_INT           ( this_node, regLastErr);
    NODE_WRITE_BOOL          ( this_node, onlineStatus);
    NODE_WRITE_STRING        ( this_node, onlineStatusText);
}
//
void JsonOnIncomingCallParam::fromPj(int call_id, pjsip_rx_data &rdata){
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
void JsonOnIncomingCallParam::readObject(const ContainerNode &node) throw(Error){
    ContainerNode this_node = node.readContainer("JsonOnIncomingCallParam");

    NODE_READ_INT       ( this_node, callId);
    NODE_READ_STRING    ( this_node, info);
    NODE_READ_STRING    ( this_node, wholeMsg);
    NODE_READ_STRING    ( this_node, srcAddress);
}
void JsonOnIncomingCallParam::writeObject(ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("JsonOnIncomingCallParam");

    NODE_WRITE_INT      ( this_node, callId);
    NODE_WRITE_STRING   ( this_node, info);
    NODE_WRITE_STRING   ( this_node, wholeMsg);
    NODE_WRITE_STRING   ( this_node, srcAddress);
}

///////////////////////////////// 000000
Json_SipTxData::Json_SipTxData(){
}
void Json_SipTxData::fromPj             (pjsip_tx_data &tdata){
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
void Json_SipTxData::readObject         (const ContainerNode &node) throw(Error){
    ContainerNode this_node = node.readContainer("Json_SipTxData");
    PJ_UNUSED_ARG( this_node );
}
void Json_SipTxData::writeObject        (ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_SipTxData");

    // string          info;
    // string          wholeMsg;
    // SocketAddress   dstAddress;
    // void*           pjTxData;

    NODE_WRITE_STRING     ( this_node, info);
    NODE_WRITE_STRING     ( this_node, wholeMsg);
    NODE_WRITE_STRING     ( this_node, dstAddress);
    //NODE_WRITE_OBJ        ( this_node, pjTxData);
    NODE_WRITE_STRING     ( this_node, void_pjTxData);

}
Json_SipRxData::Json_SipRxData(){
}
void Json_SipRxData::fromPj             (pjsip_rx_data &rdata){
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
void Json_SipRxData::readObject         (const ContainerNode &node) throw(Error){
    ContainerNode this_node = node.readContainer("Json_SipRxData");
    PJ_UNUSED_ARG( this_node );
}
void Json_SipRxData::writeObject        (ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_SipRxData");
    /*
    // string          info;
    // string          wholeMsg;
    // SocketAddress   srcAddress;
    // void*           pjRxData;
    */
    NODE_WRITE_STRING     ( this_node, info);
    NODE_WRITE_STRING     ( this_node, wholeMsg);
    NODE_WRITE_STRING     ( this_node, srcAddress);
    //NODE_WRITE_OBJ        ( this_node, pjRxData);
    NODE_WRITE_STRING     ( this_node, void_pjRxData);
}

Json_SipTransaction::Json_SipTransaction(){
}
void Json_SipTransaction::fromPj             (pjsip_transaction &rdata){
}
void Json_SipTransaction::readObject         (const ContainerNode &node) throw(Error){
    ContainerNode this_node = node.readContainer("Json_SipTransaction");
    PJ_UNUSED_ARG( this_node );
}
void Json_SipTransaction::writeObject        (ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_SipTransaction");
}

///////////////////////////////// 222222
Json_TxMsgEvent::Json_TxMsgEvent(){
}
void Json_TxMsgEvent::readObject        (const ContainerNode &node) throw(Error){
    ContainerNode this_node = node.readContainer("Json_TxMsgEvent");
    PJ_UNUSED_ARG( this_node );
}
void Json_TxMsgEvent::writeObject       (ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_TxMsgEvent");
    //    SipTxData    tdata;
    NODE_WRITE_OBJ          ( this_node, tdata);
}
///////////////////////////////// 333333
Json_RxMsgEvent::Json_RxMsgEvent(){
}
void Json_RxMsgEvent::readObject        (const ContainerNode &node) throw(Error){
    ContainerNode this_node = node.readContainer("Json_RxMsgEvent");
    PJ_UNUSED_ARG( this_node );
}
void Json_RxMsgEvent::writeObject       (ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_RxMsgEvent");
    //    SipRxData    rdata;
    NODE_WRITE_OBJ          ( this_node, rdata);
}
///////////////////////////////// 444444
Json_TxErrorEvent::Json_TxErrorEvent(){
}
void Json_TxErrorEvent::readObject        (const ContainerNode &node) throw(Error){
    ContainerNode this_node = node.readContainer("Json_TxErrorEvent");
    PJ_UNUSED_ARG( this_node );
}
void Json_TxErrorEvent::writeObject       (ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_TxErrorEvent");
    NODE_WRITE_OBJ          ( this_node, tdata);    // Json_SipTxData
    NODE_WRITE_OBJ          ( this_node, tsx);      // Json_SipTransaction
}
///////////////////////////////// 666666
Json_UserEvent::Json_UserEvent(){
}
void Json_UserEvent::fromPj             (const UserEvent &ev){
    PJ_UNUSED_ARG( ev );
}
void Json_UserEvent::readObject         (const ContainerNode &node) throw(Error){
    ContainerNode this_node = node.readContainer("Json_UserEvent");

    //NODE_READ_OBJ         ( this_node, user1);
    //NODE_READ_OBJ         ( this_node, user2);
    //NODE_READ_OBJ         ( this_node, user3);
    //NODE_READ_OBJ         ( this_node, user4);
    NODE_READ_STRING      ( this_node, void_user1);
    NODE_READ_STRING      ( this_node, void_user2);
    NODE_READ_STRING      ( this_node, void_user3);
    NODE_READ_STRING      ( this_node, void_user4);
}
void Json_UserEvent::writeObject        (ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_UserEvent");

    //NODE_WRITE_OBJ        ( this_node, user1);
    //NODE_WRITE_OBJ        ( this_node, user2);
    //NODE_WRITE_OBJ        ( this_node, user3);
    //NODE_WRITE_OBJ        ( this_node, user4);
    NODE_WRITE_STRING     ( this_node, void_user1);
    NODE_WRITE_STRING     ( this_node, void_user2);
    NODE_WRITE_STRING     ( this_node, void_user3);
    NODE_WRITE_STRING     ( this_node, void_user4);
}
/////////////////////////////////
Json_SipEventBody::Json_SipEventBody(){
}
void Json_SipEventBody::fromPj          (const pjsip_event &ev){
    PJ_UNUSED_ARG( ev );
}
void Json_SipEventBody::readObject      (const ContainerNode &node) throw(Error){
    ContainerNode this_node = node.readContainer("Json_SipEventBody");

    PJ_UNUSED_ARG( this_node );
}
void Json_SipEventBody::writeObject     (ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_SipEventBody");
    /*
    TimerEvent          timer;
    TsxStateEvent       tsxState;
    */
    NODE_WRITE_OBJ      ( this_node, txMsg);    // 2 Json_TxMsgEvent      txMsg;
    NODE_WRITE_OBJ      ( this_node, rxMsg);    // 3 Json_RxMsgEvent      rxMsg;
    NODE_WRITE_OBJ      ( this_node, txError);  // 4 Json_TxErrorEvent    txError;
    NODE_WRITE_OBJ      ( this_node, user);     // 6 Json_UserEvent       user;
}
//
Json_SipEvent::Json_SipEvent() : type(PJSIP_EVENT_UNKNOWN), pjEvent(NULL){
}
void Json_SipEvent::fromPj              (const pjsip_event &ev){
    type = ev.type;
    if (type == PJSIP_EVENT_TIMER) {
        body.timer.entry = ev.body.timer.entry;
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
            body.tsxState.src.status = ev.body.tsx_state.src.status;
        } else if (body.tsxState.type == PJSIP_EVENT_TIMER) {
            body.tsxState.src.timer = ev.body.tsx_state.src.timer;
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
void Json_SipEvent::readObject          (const ContainerNode &node) throw(Error){
    ContainerNode this_node = node.readContainer("Json_SipEvent");

    //pjsip_event_id_e    type;
    NODE_READ_NUM_T      ( this_node, pjsip_event_id_e, type);

    //SipEventBody        body;
    NODE_READ_OBJ         ( this_node, body);

    //void               *pjEvent;
    //NODE_READ_OBJ       ( this_node, pjEvent);
}
void Json_SipEvent::writeObject         (ContainerNode &node) const throw(Error){
    ContainerNode this_node = node.writeNewContainer("Json_SipEvent");

    //pjsip_event_id_e    type;
    NODE_WRITE_NUM_T    ( this_node, pjsip_event_id_e, type);

    //SipEventBody        body;
    NODE_WRITE_OBJ      ( this_node, body);

    //void               *pjEvent;
    //NODE_WRITE_OBJ    ( this_node, pjEvent);
    
    PJ_UNUSED_ARG       ( node );
}
//
void JsonOnCallStateParam::fromPj       (int call_id, pjsip_event &rdata){
    PJ_UNUSED_ARG( call_id );
    PJ_UNUSED_ARG( rdata   );
}
void JsonOnCallStateParam::readObject   (const ContainerNode &node) throw(Error){
    PJ_UNUSED_ARG( node );
}
void JsonOnCallStateParam::writeObject  (ContainerNode &node) const throw(Error){
    PJ_UNUSED_ARG( node );
}
