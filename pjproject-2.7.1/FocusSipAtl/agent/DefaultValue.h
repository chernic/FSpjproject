/* $Id: focusua.hpp 5676 2018-04-18 15:19:22Z chernic $ */
/* 
 * Copyright (C) 2018 FOCUSTAR Inc. (http://www.focustar.net)
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

// ABChernic 
#include <pj/types.h>
#include <pjsua-lib/pjsua.h>
#include "focusua_typedef.h"
#include "focusua_common.h"
#include "focusua_structs.h"

//#########################################################
#include "pjsua2/focusua.hpp"
//#########################################################

using namespace std;

///////////////////////////////////////////
// String methods
///////////////////////////////////////////
#define Cp(d,s) Cp2(&d,s)
BSTR str2bstr(const char *str, unsigned len);
static pj_str_t Pj_str(pj_pool_t *pool, Fs__Str s){
    pj_str_t ret;
    unsigned len;

    len = wcslen(s);
    if (len) {
    ret.ptr = (char*)pj_pool_alloc(pool, len+1);
    ret.slen = len;
    pj_unicode_to_ansi(s, len, ret.ptr, len+1);
    ret.ptr[ret.slen] = '\0';
    } else {
    ret.ptr = NULL;
    ret.slen = 0;
    }

    return ret;
}
static void Cp2(BSTR *dst, const pj_str_t *src){
    *dst = str2bstr(src->ptr, src->slen);
}

///////////////////////////////////////////
// Chernic: Default values only for test
///////////////////////////////////////////
static int call_info2CallInfo                       (pjsua_call_info* c1, Focusip_Call_Info *c2){
    pj_memset(c2, 0, sizeof(Focusip_Call_Info));

    pjsua_call_id callIndex =  c1->id;
    
    c2->index               =  callIndex;
    c2->active              =  pjsua_call_is_active(callIndex);
    c2->is_uac              = (c1->role == PJSIP_ROLE_UAC);
    Cp(c2->local_info,        &c1->local_info);
    Cp(c2->remote_info,       &c1->remote_info);
    c2->state               = (Focusip_Call_State)c1->state;
    Cp(c2->state_text,        &c1->state_text);
    c2->connect_duration    =  c1->connect_duration.sec;
    c2->total_duration      =  c1->total_duration.sec;
    c2->last_status         =  c1->last_status;
    Cp(c2->last_status_text,  &c1->last_status_text);
    c2->has_media           =  pjsua_call_has_media(callIndex);
    c2->conf_slot           =  c1->conf_slot;
    return 0;
}
void    default_rx_data                             (pjsip_rx_data * rdata);
void    default_tx_data                             (pjsip_tx_data * rdata);
int     default_CallInfo                            (Focusip_Call_Info *c2);
void    default_stream_created_param                (pjsua_on_stream_created_param   *param);
void    default_stream_destroyed_param              (pjsua_on_stream_destroyed_param *param);
void    default_dtmf_digit_param                    (pjsua_on_dtmf_digit_param       *param);

///////////////////////////////////////////
// Chernic: Default JSON values only for test
///////////////////////////////////////////
Fs__Str default_json_sip_event                      (string sFilDir);
Fs__Str default_json_media_state                    (string sFilDir);
///////////////////////////////////////////
// 100 TestString
Fs__Str DefaultJsonTestStringParam                  (string sFilDir, int call_id);
// 101 on_call_state
Fs__Str DefaultJsonCallStateParam                   (string sFilDir);
// 102 on_incoming_call
Fs__Str DefaultJsonOnIncomingCallParam              (string sFilDir, int call_id);
// 103 on_call_tsx_state
Fs__Str DefaultJsonTsxStateParam                    (string sFilDir);
// 104 on_call_media_state
Fs__Str DefaultJsonMediaStateParam                  (string sFilDir);
// 107 on_stream_created2
Fs__Str DefaultJsonOnStreamCreatedParam             (string sFilDir, int call_id);
// 108 on_stream_destroyed
Fs__Str DefaultJsonOnStreamDestroyedParam           (string sFilDir, int call_id);
// 109 on_dtmf_digit
Fs__Str DefaultJsonOnDtmfDigitParam                 (string sFilDir, int call_id);

///////////////////////////////////////////
// Chernic: Json form callback function 's param 
///////////////////////////////////////////
// 101 on_call_state
// 103 on_call_tsx_state
Fs__Str JsonStrFrom_pjsip_event                     (int call_id, pjsip_event *e);
// 102 on_incoming_call
Fs__Str JsonStrFrom_pjsip_rx_data                   (int call_id, pjsip_rx_data *rdata);
// 107 on_stream_created2
Fs__Str JsonStrFrom_pjsua_on_stream_created_param   (int call_id, pjsua_on_stream_created_param   &param);
// 108 on_stream_destroyed
Fs__Str JsonStrFrom_pjsua_on_stream_destroyed_param (int call_id, pjsua_on_stream_destroyed_param &param);
// 109 on_dtmf_digit
Fs__Str JsonStrFrom_pjsua_on_dtmf_digit_param       (int call_id, pjsua_on_dtmf_digit_param       &param);
