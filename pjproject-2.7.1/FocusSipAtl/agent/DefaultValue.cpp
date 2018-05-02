/* $Id: DefaultValue.cpp 5676 2018-04-18 15:19:22Z chernic $ */
#include "stdafx.h"

#include "pjsua2/util.hpp"
#include "pjsua2/json.hpp"
#include "pjsua2/endpoint.hpp"
#include "pjsua2/account.hpp"
#include "pjsua2/focusua.hpp"

using namespace std;

#include "DefaultValue.h"

#define THIS_FILE "DefaultValue.cpp"

///////////////////////////////////////////
/** string methods */
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
    UINT uSize;
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


/* Transaction layer module definition. */
static struct mod_tsx_layer
{
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
Fs__Str DefaultTestJsonString(int call_id){
    pj::EpConfig prm;
    prm.uaConfig.maxCalls = 61;
    prm.uaConfig.userAgent = "DefaultTestJsonString";

    pj::JsonDocument jDoc;
    jDoc.writeObject(prm);

    string  sCb  = jDoc.saveString();
    Fs__Str bsCb = str2bstr( sCb.data(), sCb.size());

#ifndef DO_NOT_SAVE_JDOC
    string sFilDir = string( "DefaultTestJsonString.json" );
    sFilDir = GetCurrentDir( "DefaultTestJsonString.json" );
    jDoc.saveFile( sFilDir );
#endif

    return bsCb;
}

void Default_rx_data( pjsip_rx_data * rdata ){
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
void Default_tx_data( pjsip_tx_data * rdata ){
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
Fs__Str DefaultIncomingCall(int call_id){
    pjsip_rx_data *rdata = new pjsip_rx_data();
    Default_rx_data(rdata);

    pj::JsonOnIncomingCallParam prm;
    prm.fromPj(call_id, *rdata);
    rdata = NULL;
    
    pj::JsonDocument jDoc;
    jDoc.writeObject(prm);
    string  sCb  = jDoc.saveString();
    Fs__Str bsCb = str2bstr( sCb.data(), sCb.size());

#ifndef DO_NOT_SAVE_JDOC
    string sFilDir = string( "DefaultIncomingCall.json" );
    sFilDir = GetCurrentDir( "DefaultIncomingCall.json" );
    jDoc.saveFile( sFilDir );
#endif

    return bsCb;
}
Fs__Str DefaultCallState(void){
    pj::Json_SipEvent prm;
    pj::JsonDocument jDoc;

    // prm.type = PJSIP_EVENT_TIMER;               // 1
    // prm.type = PJSIP_EVENT_TX_MSG;              // 2
    // prm.type = PJSIP_EVENT_RX_MSG;              // 3
    prm.type = PJSIP_EVENT_TRANSPORT_ERROR;     // 4
    // prm.type = PJSIP_EVENT_TSX_STATE;           // 5
    // prm.type = PJSIP_EVENT_USER;                // 6
    
    string  sCb   = string("");
    Fs__Str bsCb  = str2bstr( sCb.data(), sCb.size());

    switch(prm.type){
        //{
        // #define PJSIP_EVENT_INIT_TIMER(event,pentry)                     
        // #define PJSIP_EVENT_INIT_TSX_STATE(event,ptsx,ptype,pdata,prev)  
        // #define PJSIP_EVENT_INIT_TX_MSG(event,ptdata)                    
        // #define PJSIP_EVENT_INIT_RX_MSG(event,prdata)                    
        // #define PJSIP_EVENT_INIT_TRANSPORT_ERROR(event,ptsx,ptdata)      
        // #define PJSIP_EVENT_INIT_USER(event,u1,u2,u3,u4)                 

        // Line 281:  struct pjsip_rx_data
        // Line 508:  struct pjsip_tx_data
        // Line 776:  struct pjsip_transport
        // Line 1001: struct pjsip_tpfactory
        
        //$(SolutionDir)\Deploy\i386-$(PlatformName)-vc8-$(ConfigurationName)\$(ProjectName).ocx
        
        // PJSIP_EVENT_UNKNOWN          0
        // PJSIP_EVENT_TIMER            1
        // PJSIP_EVENT_TX_MSG           2#
        // PJSIP_EVENT_RX_MSG           3#
        // PJSIP_EVENT_TRANSPORT_ERROR  4#
        // PJSIP_EVENT_TSX_STATE        5
        // PJSIP_EVENT_USER             6#

        // TimerEvent      timer;           1               ( TimerEntry
        // TxMsgEvent      txMsg;           2               ( SipTxData       SipTransaction
        // RxMsgEvent      rxMsg;           3               ( SipRxData
        // TxErrorEvent    txError;          4              ( SipTxData       SipTransaction
        // TsxStateEvent   tsxState;         5              ( TsxStateEventSrc
        // UserEvent       user;            6               ( GenericData
        //}
        case PJSIP_EVENT_TIMER:{            //1
        }break;
        case PJSIP_EVENT_TX_MSG:{           //2
            pjsip_event         event;
            pjsip_tx_data       *tdata = new pjsip_tx_data();
            
            Default_tx_data(tdata);
            PJSIP_EVENT_INIT_TX_MSG(event, tdata);
            tdata = NULL;

            prm.fromPj(event);
            jDoc.writeObject(prm);

            sCb  = jDoc.saveString();
            bsCb = str2bstr( sCb.data(), sCb.size());
        }break;
        case PJSIP_EVENT_RX_MSG:{           //3
            pjsip_event         event;
            pjsip_rx_data       *prdata = new pjsip_rx_data();
            
            Default_rx_data(prdata);
            PJSIP_EVENT_INIT_RX_MSG(event, prdata);

            prm.fromPj(event);
            jDoc.writeObject(prm);

            sCb  = jDoc.saveString();
            bsCb = str2bstr( sCb.data(), sCb.size());
        }break;
        case PJSIP_EVENT_TRANSPORT_ERROR:{  //4 This One may not test while is not runtime.
            // via : pjsip\sip_transaction.c tsx_create()
            pjsip_transaction   *ptsx;
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

            ptsx = NULL;

            pjsip_event         event;
            pjsip_tx_data      *ptdata = new pjsip_tx_data();

            Default_tx_data(ptdata);
            PJSIP_EVENT_INIT_TRANSPORT_ERROR(event, ptsx, ptdata);
            ptdata = NULL;

            prm.fromPj(event);
            jDoc.writeObject(prm);

            sCb  = jDoc.saveString();
            bsCb = str2bstr( sCb.data(), sCb.size());
        }break;
        case PJSIP_EVENT_TSX_STATE:{        //5
            //pjsip_transport *tdata = new pjsip_transport();

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
    string sFilDir = string( "DefaultCallState.json" );
    sFilDir = GetCurrentDir( "DefaultCallState.json" );
    jDoc.saveFile( sFilDir );
#endif

    return bsCb;
}
