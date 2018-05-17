/* $Id: focusua.hpp 5676 2018-04-18 15:19:22Z chernic $ */
/* 
 * Copyright (C) 2018 FOCUSTAR Inc. (http://www.focustar.net)
 */

#include "stdafx.h"
#include "DefaultValue.h"

#include "pjsua2/util.hpp"
#include "pjsua2/json.hpp"
#include "pjsua2/endpoint.hpp"
#include "pjsua2/account.hpp"

using namespace std;
#define THIS_FILE "DefaultValue.cpp"

///////////////////////////////////////////
// String methods
BSTR str2bstr(const char *str, unsigned len){
    if (len == 0) {
        return SysAllocString(L"");
    } else {
        OLECHAR *tmp;
        BSTR result;
        tmp = (OLECHAR*) malloc((len+1) * sizeof(OLECHAR));
        pj_ansi_to_unicode(str, len, tmp, len+1);
        result = SysAllocString(tmp);
        free(tmp);
        return result;
    }
}
static string GetCurrentDir(const string &path){
    // 由程序->属性->调试->工作目录 决定
    // 如果该值为空, 则默认为 $(InputDir) 或 $(ProjectDir)
    // 本工程为$(SolutionDir)Deploy\i386-Win32-vc8-Debug
    // 完整为E:\github\focusSipX\FSpjproject\pjproject-2.7.1\Deploy\i386-Win32-vc8-Debug
    string sFileName;
    CString ls_FileName;

    LPTSTR lpBuffer;
    UINT   uSize;
    HANDLE hHeap;
    uSize=(GetCurrentDirectory(0,NULL))*sizeof(TCHAR);
    hHeap=GetProcessHeap();
    lpBuffer=(LPTSTR)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,uSize);
    GetCurrentDirectory(uSize,lpBuffer);

    ls_FileName=CString(lpBuffer);

    USES_CONVERSION;
    sFileName = string(T2A(ls_FileName));

    //sFileName = (string) lpBuffer;

    sFileName.append("\\");
    sFileName.append(path);
    return sFileName;
}
// Transaction layer module definition.
static struct mod_tsx_layer{
    struct pjsip_module  mod;
    pj_pool_t       *pool;
    pjsip_endpoint  *endpt;
    pj_mutex_t      *mutex;
    pj_hash_table_t *htable;
} mod_tsx_layer = 
{   {
    NULL, NULL,         /* List's prev and next.    */
    { "mod-tsx-layer", 13 },    /* Module name.         */
    -1,             /* Module ID            */
    PJSIP_MOD_PRIORITY_TSX_LAYER,   /* Priority.            */
    NULL, //    mod_tsx_layer_load,     /* load().          */
    NULL, //    mod_tsx_layer_start,        /* start()          */
    NULL, //    mod_tsx_layer_stop,     /* stop()           */
    NULL, //    mod_tsx_layer_unload,       /* unload()         */
    NULL, //    mod_tsx_layer_on_rx_request,    /* on_rx_request()      */
    NULL, //    mod_tsx_layer_on_rx_response,   /* on_rx_response()     */
    NULL
    }
};

///////////////////////////////////////////
// Chernic: Default values only for test
///////////////////////////////////////////
int     default_CallInfo                            (Focusip_Call_Info *c2){
    pjsua_call_info *pc1;
    pjsua_call_info c1;
    pj_bzero(&c1,  sizeof(c1));
    pc1 = &c1;

    pjsua_call_id callIndex =  pc1->id;
    c2->index               =  callIndex;
    c2->active              =  0;
    c2->is_uac              = (pc1->role == PJSIP_ROLE_UAC);
    Cp(c2->local_info,        &pc1->local_info);
    Cp(c2->remote_info,       &pc1->remote_info);
    c2->state               = (Focusip_Call_State)pc1->state;
    Cp(c2->state_text,        &pc1->state_text);
    c2->connect_duration    =  pc1->connect_duration.sec;
    c2->total_duration      =  pc1->total_duration.sec;
    c2->last_status         =  pc1->last_status;
    Cp(c2->last_status_text,  &pc1->last_status_text);
    c2->has_media           =  0;
    c2->conf_slot           =  pc1->conf_slot;

    pj_bzero(&c1,  sizeof(c1));
    pc1 = NULL;
    return 0;
}
void    default_rx_data                             (pjsip_rx_data * rdata ){
    // srcAddress
    pj_sockaddr_in  addr;
    pj_str_t        s;
    pj_sockaddr_in_init(&addr, pj_cstr(&s, "127.0.0.1"), 50123);

    // info
    rdata->msg_info.info        = "no_info";

    // wholeMsg msg_buf
    rdata->msg_info.msg_buf     = "msg_buf";
    rdata->msg_info.len         = 7;

    // dstAddress <= pkt_info
    pj_memcpy(&rdata->pkt_info.src_addr,  &addr,  sizeof(addr) );
    rdata->pkt_info.len         = 9;
}
void    default_tx_data                             (pjsip_tx_data * rdata ){
    // srcAddress
    pj_sockaddr_in  addr;
    pj_str_t        s;
    pj_sockaddr_in_init(&addr, pj_cstr(&s, "127.0.0.1"), 50123);

    // info
    rdata->info                 = "no_info";

    // wholeMsg msg_buf
    rdata->buf.start            = "msg_buf";
    rdata->buf.end              = rdata->buf.start +7;

    // dstAddress <= tp_info
    pj_memcpy(&rdata->tp_info.dst_addr,  &addr,  sizeof(addr) );
    rdata->tp_info.dst_addr_len = 9;
}
// 107a on_stream_created2      Bad values
void    default_stream_created_param                (pjsua_on_stream_created_param * param){
    // param->stream;       = stream;
    param->stream_idx       = 2;
    param->destroy_port     = 1;
    // param->pjmedia_port  = pjmedia_port;
}
// 108a on_stream_destroyed     Bad values
void    default_stream_destroyed_param              (pjsua_on_stream_destroyed_param * param){
    // param->stream;       = stream;
    param->stream_idx       = 2;
    // param->destroy_port  = 1;
    // param->pjmedia_port  = pjmedia_port;
}
// 109a on_dtmf_digit           Bad values
void    default_dtmf_digit_param                    (pjsua_on_dtmf_digit_param * param){
    char buf[10];
    pj_ansi_sprintf(buf, "%c", 99);
    param->digit = (string)buf;
}
// 111a on_dtmf_digit           Bad values
void    default_transfer_request2_param             (pjsua_on_call_transfer_request2_param * param){
}

///////////////////////////////////////////
// Chernic: Default JSON values only for test
///////////////////////////////////////////
Fs__Str default_json_sip_event                      (string sFilDir){
    pj::Json_SipEvent prm;
    pj::JsonDocument jDoc;

    // prm.type = PJSIP_EVENT_TIMER;                // 1
    // prm.type = PJSIP_EVENT_TX_MSG;               // 2
    // prm.type = PJSIP_EVENT_RX_MSG;               // 3
    // prm.type = PJSIP_EVENT_TRANSPORT_ERROR;      // 4
    prm.type = PJSIP_EVENT_TSX_STATE;               // 5
    // prm.type = PJSIP_EVENT_USER;                 // 6

    string  sCb   = string("");
    Fs__Str bsCb  = str2bstr( sCb.data(), sCb.size());
    
    // Chernic : See more in X\pjsip\include\pjsua2\focusua.hpp
    switch(prm.type){
        case PJSIP_EVENT_TIMER:{            //1
            // pjsip_event event;
            // pjsip_tx_data event_timer_tdata;
            // default_tx_data(tdata);
            // PJSIP_EVENT_INIT_TX_MSG(event, tdata);
            // tdata = NULL;

            // prm.fromPj(event);
            // jDoc.writeObject(prm);

            // sCb  = jDoc.saveString();
            // bsCb = str2bstr( sCb.data(), sCb.size());
        }break;
        case PJSIP_EVENT_TX_MSG:{           //2
            pjsip_event event;
            pjsip_tx_data tx_msg_tdata;
            default_tx_data(&tx_msg_tdata);
            
            PJSIP_EVENT_INIT_TX_MSG(event, &tx_msg_tdata);

            prm.fromPj(event);
            jDoc.writeObject(prm);

            sCb  = jDoc.saveString();
            bsCb = str2bstr( sCb.data(), sCb.size());
        }break;
        case PJSIP_EVENT_RX_MSG:{           //3
            pjsip_event event;
            pjsip_rx_data rx_msg_rx_data;
            default_rx_data(&rx_msg_rx_data);
            PJSIP_EVENT_INIT_RX_MSG(event, &rx_msg_rx_data);

            prm.fromPj(event);
            jDoc.writeObject(prm);

            sCb  = jDoc.saveString();
            bsCb = str2bstr( sCb.data(), sCb.size());
        }break;
        case PJSIP_EVENT_TRANSPORT_ERROR:{  //4 This One may not test while is not runtime.
            // via : pjsip\sip_transaction.c tsx_create()
            pjsip_event event;
            pjsip_transaction *ptsx= NULL;
            /*
            pj_pool_t           *pool;
            pjsip_transaction   *tsx;
            pj_status_t         status;

            // ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR
            status = pjsip_tsx_layer_init_module(mod_tsx_layer.endpt);
            PJ_ASSERT_RETURN(status == PJ_SUCCESS, NULL);
            
            pool = pjsip_endpt_create_pool( mod_tsx_layer.endpt, "tsx", PJSIP_POOL_TSX_LEN, PJSIP_POOL_TSX_INC );
            if (!pool)
                return NULL;

            tsx = PJ_POOL_ZALLOC_T(pool, pjsip_transaction);
            tsx->pool = pool;
//          tsx->tsx_user = tsx_user;
            tsx->endpt = mod_tsx_layer.endpt;

            pj_memcpy(pool->obj_name, tsx->obj_name, sizeof(pool->obj_name));

            tsx->handle_200resp = 1;
//          tsx->retransmit_timer.id = TIMER_INACTIVE;
            tsx->retransmit_timer.user_data = tsx;
//          tsx->retransmit_timer.cb = &tsx_timer_callback;

            status = pj_mutex_create_simple(pool, tsx->obj_name, &tsx->mutex_b);
            if (status != PJ_SUCCESS) {
////            tsx_shutdown(tsx);
//              return status;
                return NULL;
            }

            ptsx = tsx;
            */
            pjsip_tx_data transport_tx_data;
            default_tx_data(&transport_tx_data);
            
            PJSIP_EVENT_INIT_TRANSPORT_ERROR(event, ptsx, &transport_tx_data);
            ptsx  = NULL;

            prm.fromPj(event);
            jDoc.writeObject(prm);

            sCb  = jDoc.saveString();
            bsCb = str2bstr( sCb.data(), sCb.size());
        }break;
        case PJSIP_EVENT_TSX_STATE:{        //5
            pjsip_event         e;                              // p1
            pjsip_transaction   *ptsx = NULL;                   // p2
            pjsip_event_id_e    event_src_type;                 // p3
            pjsip_rx_data       *event_src = NULL;              // p4
            pjsip_tsx_state_e   prev_state;                     // p5

            // must : ptsx->state < PJSIP_TSX_STATE_TERMINATED  //
            // ptsx->state  = PJSIP_TSX_STATE_CONFIRMED;        // 5
            prev_state      = PJSIP_TSX_STATE_CONFIRMED;        // 5

            // event_src_type = PJSIP_EVENT_TIMER;              // 1
            //event_src_type  = PJSIP_EVENT_TX_MSG;             // 2
            event_src_type    = PJSIP_EVENT_RX_MSG;             // 3
            // event_src_type = PJSIP_EVENT_TRANSPORT_ERROR;    // 4
            // event_src_type = PJSIP_EVENT_USER;               // 6

             // "Json_TsxStateEvent":   { 
                // "prevState":            5,
                // "type":                 3
             // },

            if (event_src_type==PJSIP_EVENT_TIMER){
                //PJSIP_EVENT_INIT_TSX_STATE(e, ptsx, event_src_type, NULL, prev_state);
            }
            // Chernic : Callback Fuction is happened here.
            // X\pjsip\src\pjsip\sip_transaction.c line:1168
            // PJSIP_EVENT_INIT_TSX_STATE(e, tsx, event_src_type, event_src, prev_state);
            // (*tsx->tsx_user->on_tsx_state)(tsx, &e);
            if (event_src_type==PJSIP_EVENT_RX_MSG){
                pjsip_rx_data tsx_state_rx_msg_rx_data;
                default_rx_data(&tsx_state_rx_msg_rx_data);

                PJSIP_EVENT_INIT_TSX_STATE(e, ptsx, event_src_type, event_src, prev_state);
            }
            // Chernic : Callback Fuction is happened here.
            // X\pjsip\src\pjsip\sip_transaction.c line:1168
            // PJSIP_EVENT_INIT_TSX_STATE(e, tsx, PJSIP_EVENT_TRANSPORT_ERROR, NULL, prev_state);
            // (*tsx->tsx_user->on_tsx_state)(tsx, &e);
            if (event_src_type==PJSIP_EVENT_TRANSPORT_ERROR){
                PJSIP_EVENT_INIT_TSX_STATE(e, ptsx, event_src_type, NULL, prev_state);
            }

            prm.fromPj(e);
            jDoc.writeObject(prm);

            sCb  = jDoc.saveString();
            bsCb = str2bstr( sCb.data(), sCb.size());
        }break;
        case PJSIP_EVENT_USER:{             //6#
            pjsip_event event;
            PJSIP_EVENT_INIT_USER(event, 0, 1, 2, 3);
            
            prm.fromPj(event);
            prm.body.user.void_user1.append("str_user1");
            prm.body.user.void_user2.append("str_user2");
            prm.body.user.void_user3.append("str_user3");
            prm.body.user.void_user4.append("str_user4");

            jDoc.writeObject(prm);

            sCb  = jDoc.saveString();
            bsCb = str2bstr( sCb.data(), sCb.size());
        }break;
        default:{
        }break;
    }

#ifndef DO_NOT_SAVE_JDOC
    if( 0 < sFilDir.size())
        jDoc.saveFile(sFilDir);
#else
    PJ_UNUSED_ARG(sFilDir);
#endif
    return bsCb;
}
Fs__Str default_json_media_state                    (string sFilDir){
    pj::JsonOnMediaStateParam prm;
    prm.Info = string("none");
    
    pj::JsonDocument jDoc;
    jDoc.writeObject(prm);
    // prm.fromPj();
    
    string  sCb   = jDoc.saveString();
    Fs__Str bsCb  = str2bstr( sCb.data(), sCb.size());
    
#ifndef DO_NOT_SAVE_JDOC
    if( 0 < sFilDir.size())
        jDoc.saveFile(sFilDir);
#else
    PJ_UNUSED_ARG(sFilDir);
#endif

    return bsCb;
}
///////////////////////////////////////////
// 100 TestString
Fs__Str DefaultJsonTestStringParam                  (string sFilDir, int call_id){
    pj::EpConfig prm;
    prm.uaConfig.maxCalls = 61;
    prm.uaConfig.userAgent = "DefaultTestJsonString";

    pj::JsonDocument jDoc;
    jDoc.writeObject(prm);

    string  sCb  = jDoc.saveString();
    Fs__Str bsCb = str2bstr( sCb.data(), sCb.size());

#ifndef DO_NOT_SAVE_JDOC
    if( 0 < sFilDir.size())
        jDoc.saveFile(sFilDir);
#else
    PJ_UNUSED_ARG(sFilDir);
#endif

    return bsCb;
}
// 101 on_call_state
Fs__Str DefaultJsonCallStateParam                   (string sFilDir){
    Fs__Str bsCb  = default_json_sip_event(sFilDir);;
    return bsCb;
}
// 102 on_incoming_call
Fs__Str DefaultJsonOnIncomingCallParam              (string sFilDir, int call_id){
    pjsip_rx_data rdata;
    default_rx_data(&rdata);

    pj::JsonOnIncomingCallParam prm;
    prm.fromPj(call_id, rdata);

    pj::JsonDocument jDoc;
    jDoc.writeObject(prm);
    string  sCb  = jDoc.saveString();
    Fs__Str bsCb = str2bstr( sCb.data(), sCb.size());

#ifndef DO_NOT_SAVE_JDOC
    if( 0 < sFilDir.size())
        jDoc.saveFile(sFilDir);
#else
    PJ_UNUSED_ARG(sFilDir);
#endif

    return bsCb;
}
// 103 on_call_tsx_state
Fs__Str DefaultJsonTsxStateParam                    (string sFilDir){
    Fs__Str bsCb = default_json_sip_event(sFilDir);
    return bsCb;
}
// 104 on_call_media_state
Fs__Str DefaultJsonMediaStateParam                  (string sFilDir){
    Fs__Str bsCb = default_json_media_state(sFilDir);;
    return bsCb;
}
// 107b on_stream_created2          Bad values - Json Form struct
Fs__Str DefaultJsonOnStreamCreatedParam             (string sFilDir, int call_id){
    pjsua_on_stream_created_param param;
    default_stream_created_param(&param);

    pj::JsonOnStreamCreatedParam jParam;
    jParam.fromPj(call_id, param);

    pj::JsonDocument jDoc;
    jDoc.writeObject(jParam);
    string  sCb  = jDoc.saveString();
    Fs__Str bsCb = str2bstr( sCb.data(), sCb.size());

#ifndef DO_NOT_SAVE_JDOC
    if( 0 < sFilDir.size())
        jDoc.saveFile(sFilDir);
#else
    PJ_UNUSED_ARG(sFilDir);
#endif

    return bsCb;
}
// 108b on_stream_destroyed         Bad values - Json Form struct
Fs__Str DefaultJsonOnStreamDestroyedParam           (string sFilDir, int call_id){
    pjsua_on_stream_destroyed_param param;
    default_stream_destroyed_param(&param);

    pj::JsonOnStreamDestroyedParam jParam;
    jParam.fromPj(call_id, param);

    pj::JsonDocument jDoc;
    jDoc.writeObject(jParam); 

    string  sCb  = jDoc.saveString();
    Fs__Str bsCb = str2bstr( sCb.data(), sCb.size());

#ifndef DO_NOT_SAVE_JDOC
    if( 0 < sFilDir.size())
        jDoc.saveFile(sFilDir);
#else
    PJ_UNUSED_ARG(sFilDir);
#endif

    return bsCb;
}
// 109b on_dtmf_digit               Bad values - Json Form struct
Fs__Str DefaultJsonOnDtmfDigitParam                 (string sFilDir, int call_id){
    pjsua_on_dtmf_digit_param param;
    default_dtmf_digit_param(&param);

    pj::JsonOnDtmfDigitParam jParam;
    jParam.fromPj(call_id, param);

    pj::JsonDocument jDoc;
    jDoc.writeObject(jParam); 

    string  sCb  = jDoc.saveString();
    Fs__Str bsCb = str2bstr( sCb.data(), sCb.size());

#ifndef DO_NOT_SAVE_JDOC
    if( 0 < sFilDir.size())
        jDoc.saveFile(sFilDir);
#else
    PJ_UNUSED_ARG(sFilDir);
#endif

    return bsCb;
}
// 111b on_call_transfer_request2   Bad values - Json Form struct
Fs__Str DefaultJsonOnTransferRequest2tParam         (string sFilDir, int call_id){
    pjsua_on_call_transfer_request2_param param;
    default_transfer_request2_param(&param);

    pj::JsonOnTransferRequest2Param jParam;
    jParam.fromPj(call_id, param);

    pj::JsonDocument jDoc;
    jDoc.writeObject(jParam); 

    string  sCb  = jDoc.saveString();
    Fs__Str bsCb = str2bstr( sCb.data(), sCb.size());

#ifndef DO_NOT_SAVE_JDOC
    if( 0 < sFilDir.size())
        jDoc.saveFile(sFilDir);
#else
    PJ_UNUSED_ARG(sFilDir);
#endif

    return bsCb;
}

///////////////////////////////////////////
// Chernic: Json form callback function 's param 
///////////////////////////////////////////
// 101 on_call_state
// 103 on_call_tsx_state
Fs__Str JsonStrFrom_pjsip_event                     (int call_id, pjsip_event *e){
    PJ_UNUSED_ARG( e );
    
    string  sCb   = string("");
    Fs__Str bsCb  = str2bstr( sCb.data(), sCb.size());
    return bsCb;
}
// 102 on_incoming_call
Fs__Str JsonStrFrom_pjsip_rx_data                   (int call_id, pjsip_rx_data *rdata){
    pj::JsonOnIncomingCallParam prm;
    pj::JsonDocument jDoc;
    
    prm.fromPj(call_id, *rdata);
    jDoc.writeObject(prm);
    
    string  sCb  = jDoc.saveString();
    Fs__Str bsCb = str2bstr( sCb.data(), sCb.size());

// #ifndef DO_NOT_SAVE_JDOC
    // if( 0 < sFilDir.size())
        // jDoc.saveFile(sFilDir);
// #else
    // PJ_UNUSED_ARG(sFilDir);
// #endif

    return bsCb;
}
// 107o on_stream_created2
Fs__Str JsonStrFrom_pjsua_on_stream_created_param   (int call_id, pjsua_on_stream_created_param &param){
    pj::JsonOnStreamCreatedParam jParam;
    pj::JsonDocument jDoc;

    jParam.fromPj(call_id, param);
    jDoc.writeObject(jParam);

    string  sCb  = jDoc.saveString();
    Fs__Str bsCb = str2bstr( sCb.data(), sCb.size());

    return bsCb;
}
// 108o on_stream_destroyed
Fs__Str JsonStrFrom_pjsua_on_stream_destroyed_param (int call_id, pjsua_on_stream_destroyed_param &param){
    pj::JsonOnStreamDestroyedParam jParam;
    pj::JsonDocument jDoc;

    jParam.fromPj(call_id, param);
    jDoc.writeObject(jParam);

    string  sCb  = jDoc.saveString();
    Fs__Str bsCb = str2bstr( sCb.data(), sCb.size());

    return bsCb;
}
// 109  on_dtmf_digit
Fs__Str JsonStrFrom_pjsua_on_dtmf_digit_param       (int call_id, pjsua_on_dtmf_digit_param &param){
    pj::JsonOnDtmfDigitParam jParam;
    pj::JsonDocument jDoc;

    jParam.fromPj(call_id, param);
    jDoc.writeObject(jParam);

    string  sCb  = jDoc.saveString();
    Fs__Str bsCb = str2bstr( sCb.data(), sCb.size());

    return bsCb;
}
