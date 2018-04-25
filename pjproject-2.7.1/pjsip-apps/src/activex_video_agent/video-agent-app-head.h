// App.h : Declaration of the CApp

#ifndef __APP_HEAD_H_
#define __APP_HEAD_H_

#include "define.h"
#include "settings.h"
#include "pjsua_app_common.h"


//PJ_BEGIN_DECL

/**
 * This structure contains the configuration of application.
 */
typedef struct pjsua_app_cfg_t
{
    /**
     * The number of runtime arguments passed to the application.
     */
    int       argc;

    /**
     * The array of arguments string passed to the application. 
     */
    char    **argv;

    /** 
     * Tell app that CLI (and pjsua) is (re)started.
     * msg will contain start error message such as �Telnet to X:Y?
     * �failed to start pjsua lib? �port busy?.
     */
    void (*on_started)(pj_status_t status, const char* title);

    /**
     * Tell app that library request to stopped/restart.
     * GUI app needs to use a timer mechanism to wait before invoking the 
     * cleanup procedure.
     */
    void (*on_stopped)(pj_bool_t restart, int argc, char** argv);

    /**
     * This will enable application to supply customize configuration other than
     * the basic configuration provided by pjsua. 
     */
    void (*on_config_init)(pjsua_app_config *cfg);
} pjsua_app_cfg_t;

#endif //__APP_HEAD_H_
