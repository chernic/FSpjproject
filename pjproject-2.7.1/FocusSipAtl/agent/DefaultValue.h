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

/////////////////////////////////////////////////////////////////////////////
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

Fs__Str DefaultTestJsonString(int call_id);
Fs__Str DefaultIncomingCall(int call_id);
Fs__Str DefaultCallState(void);
