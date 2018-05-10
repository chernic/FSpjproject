// DefaultValue.h : CFocusSip 的声明
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

// ABChernic 
#include <pj/types.h>
#include <pjsua-lib/pjsua.h>
#include "focusua_typedef.h"
#include "focusua_common.h"
#include "focusua_structs.h"

/*
$(SolutionDir)$(ConfigurationName)\$(ProjectName)
$(SolutionDir)Deploy\i386-$(PlatformName)-vc8-$(ConfigurationName)\$(ProjectName).ocx

/////////////////////////////////////////////////
命令:
// C:\Program Files\Internet Explorer\iexplore.exe
命令参数:
// $(SolutionDir)Deploy\FocusSipAtl.html
工作目录
// $(SolutionDir)Deploy\i386-Win32-vc8-Debug\

//////////////////////////////////////////////////
命令:
$(SolutionDir)Deploy\i386-Win32-vc8-Debug\FocusSipAtlmain.exe
工作目录:
$(SolutionDir)Deploy\i386-Win32-vc8-Debug\
*/

///////////////////////////////////////////
/** string methods **/
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
static int call_info2CallInfo           (pjsua_call_info* c1, Focusip_Call_Info *c2){
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
///////////////////////////////////////////
// Common values settings
void    default_rx_data ( pjsip_rx_data * rdata);
void    default_tx_data ( pjsip_tx_data * rdata);
int     default_CallInfo( Focusip_Call_Info *c2);

///////////////////////////////////////////
Fs__Str pjsip_event2JsonSipEvent       (pjsip_event *e);
// 000 Common
Fs__Str DefaultJsonSipEvent            (void);
Fs__Str DefaultJsonMediaStateParam     (void);
// 100 TestString
Fs__Str DefaultJsonTestString           (int call_id);
// 101 CallState
Fs__Str DefaultJsonCallState            (void);
// 102 IncomingCall
Fs__Str DefaultJsonOnIncomingCallParam  (int call_id);
// 103 TsxState
Fs__Str DefaultJsonTsxState             (void);
// 103 MediaState
Fs__Str DefaultJsonMediaState           (void);


