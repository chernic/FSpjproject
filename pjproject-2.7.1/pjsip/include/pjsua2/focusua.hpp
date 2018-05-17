/* $Id: focusua.hpp 5676 2018-04-18 15:19:22Z chernic $ */
/* 
 * Copyright (C) 2018 FOCUSTAR Inc. (http://www.focustar.net)
 */

#ifndef __PJSUA2_FOCUSUA_HPP__
#define __PJSUA2_FOCUSUA_HPP__

#include <pjsua2/persistent.hpp>
#include <pjsua2/media.hpp>
#include <pjsua2/siptypes.hpp>
#include <list>
#include <map>
using std::string;

typedef struct pjsua_on_stream_destroyed_param{
    // int                  CallId;

    pjmedia_stream      *stream;
    unsigned            stream_idx;
    // pj_bool_t        destroy_port;
    // pjmedia_port    *port;
} pjsua_on_stream_destroyed_param;

typedef struct pjsua_on_dtmf_digit_param{
    string digit;
} pjsua_on_dtmf_digit_param;

typedef struct pjsua_on_call_transfer_request2_param{
    string digit;
} pjsua_on_call_transfer_request2_param;


/** PJSUA2 API is inside pj namespace */
namespace pj{
/**
 * @defgroup PJSUA2_ACC Focusua
 * @ingroup PJSUA2_Ref
 * @{
 */
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
struct JsonAccountInfo :            public PersistentObject{
    pjsua_acc_id    id;
    bool                isDefault;
    string              uri;
    bool                regIsConfigured;
    bool                regIsActive;
    int                 regExpiresSec;
    pjsip_status_code   regStatus;
    string              regStatusText;
    pj_status_t             regLastErr;
    bool                onlineStatus;
    string              onlineStatusText;
public:
    virtual void writeObject(ContainerNode &node) const throw(Error);
    void readObject(const ContainerNode &node) throw(Error){
        PJ_UNUSED_ARG( node );
    }
    void fromPj(const pjsua_acc_info &pai);
};


// base 1
struct JsonMediaStream:             public PersistentObject{
    //{
    // pjmedia_endpt        *endpt;     /**< Media endpoint.        */
    // pjmedia_codec_mgr        *codec_mgr;     /**< Codec manager instance.    */
    // pjmedia_stream_info       si;        /**< Creation parameter.        */
    // pjmedia_port      port;      /**< Port interface.        */
    // pjmedia_channel      *enc;       /**< Encoding channel.      */
    // pjmedia_channel      *dec;       /**< Decoding channel.      */

    // pj_pool_t            *own_pool;      /**< Only created if not given  */

    // pjmedia_dir           dir;       /**< Stream direction.      */
    // void         *user_data;     /**< User data.         */
    // pj_str_t          cname;     /**< SDES CNAME         */

    // pjmedia_transport        *transport;     /**< Stream transport.      */

    // pjmedia_codec        *codec;     /**< Codec instance being used. */
    // pjmedia_codec_param       codec_param;   /**< Codec param.           */
    // pj_int16_t           *enc_buf;       /**< Encoding buffer, when enc's
                         // ptime is different than dec.
                         // Otherwise it's NULL.        */

    // unsigned          enc_samples_per_pkt;
    // unsigned          enc_buf_size;  /**< Encoding buffer size, in
                         // samples.            */
    // unsigned          enc_buf_pos;   /**< First position in buf.     */
    // unsigned          enc_buf_count; /**< Number of samples in the
                         // encoding buffer.        */

    // unsigned          plc_cnt;       /**< # of consecutive PLC frames*/
    // unsigned          max_plc_cnt;   /**< Max # of PLC frames        */

    // unsigned          vad_enabled;   /**< VAD enabled in param.      */
    // unsigned          frame_size;    /**< Size of encoded base frame.*/
    // pj_bool_t             is_streaming;  /**< Currently streaming?. This
                         // is used to put RTP marker
                         // bit.                */
    // pj_uint32_t           ts_vad_disabled;/**< TS when VAD was disabled. */
    // pj_uint32_t           tx_duration;   /**< TX duration in timestamp.  */

    // pj_mutex_t           *jb_mutex;
    // pjmedia_jbuf     *jb;        /**< Jitter buffer.         */
    // char          jb_last_frm;   /**< Last frame type from jb    */
    // unsigned          jb_last_frm_cnt;/**< Last JB frame type counter*/

    // pjmedia_rtcp_session     rtcp;       /**< RTCP for incoming RTP.     */

    // pj_uint32_t           rtcp_last_tx;  /**< RTCP tx time in timestamp  */
    // pj_uint32_t           rtcp_interval; /**< Interval, in timestamp.    */
    // pj_bool_t             initial_rr;    /**< Initial RTCP RR sent       */
    // pj_bool_t                rtcp_sdes_bye_disabled;/**< Send RTCP SDES/BYE?*/
    // void         *out_rtcp_pkt;  /**< Outgoing RTCP packet.      */
    // unsigned          out_rtcp_pkt_size;
                        // /**< Outgoing RTCP packet size. */

    // /* RFC 2833 DTMF transmission queue: */
    // int               tx_event_pt;   /**< Outgoing pt for dtmf.      */
    // int               tx_dtmf_count; /**< # of digits in tx dtmf buf.*/
    // struct dtmf           tx_dtmf_buf[32];/**< Outgoing dtmf queue.      */

    // /* Incoming DTMF: */
    // int               rx_event_pt;   /**< Incoming pt for dtmf.      */
    // int               last_dtmf;     /**< Current digit, or -1.      */
    // pj_uint32_t           last_dtmf_dur; /**< Start ts for cur digit.    */
    // unsigned          rx_dtmf_count; /**< # of digits in dtmf rx buf.*/
    // char          rx_dtmf_buf[32];/**< Incoming DTMF buffer.     */

    // /* DTMF callback */
    // void         (*dtmf_cb)(pjmedia_stream*, void*, int);
    // void          *dtmf_cb_user_data;

// #if defined(PJMEDIA_HANDLE_G722_MPEG_BUG) && (PJMEDIA_HANDLE_G722_MPEG_BUG!=0)
    // /* Enable support to handle codecs with inconsistent clock rate
     // * between clock rate in SDP/RTP & the clock rate that is actually used.
     // * This happens for example with G.722 and MPEG audio codecs.
     // */
    // pj_bool_t             has_g722_mpeg_bug;
                        // /**< Flag to specify whether
                         // normalization process
                         // is needed           */
    // unsigned          rtp_tx_ts_len_per_pkt;
                        // /**< Normalized ts length per packet
                         // transmitted according to
                         // 'erroneous' definition      */
    // unsigned          rtp_rx_ts_len_per_frame;
                        // /**< Normalized ts length per frame
                         // received according to
                         // 'erroneous' definition      */
    // unsigned          rtp_rx_last_cnt;/**< Nb of frames in last pkt  */
    // unsigned          rtp_rx_check_cnt;
                        // /**< Counter of remote timestamp
                         // checking */
// #endif

// #if defined(PJMEDIA_HAS_RTCP_XR) && (PJMEDIA_HAS_RTCP_XR != 0)
    // pj_uint32_t           rtcp_xr_last_tx;  /**< RTCP XR tx time
                                // in timestamp.           */
    // pj_uint32_t           rtcp_xr_interval; /**< Interval, in timestamp. */
    // pj_sockaddr           rtcp_xr_dest;     /**< Additional remote RTCP XR
                            // dest. If sin_family is
                            // zero, it will be ignored*/
    // unsigned          rtcp_xr_dest_len; /**< Length of RTCP XR dest
                                // address          */
// #endif

// #if defined(PJMEDIA_STREAM_ENABLE_KA) && PJMEDIA_STREAM_ENABLE_KA!=0
    // pj_bool_t             use_ka;           /**< Stream keep-alive with non-
                            // codec-VAD mechanism is
                            // enabled?         */
    // pj_timestamp      last_frm_ts_sent; /**< Timestamp of last sending
                                // packet           */
// #endif

// #if TRACE_JB
    // pj_oshandle_t        trace_jb_fd;        /**< Jitter tracing file handle.*/
    // char        *trace_jb_buf;       /**< Jitter tracing buffer.     */
// #endif

    // pj_uint32_t           rtp_rx_last_ts;        /**< Last received RTP timestamp*/
    // pj_status_t           rtp_rx_last_err;       /**< Last RTP recv() error */
    //}
public:
    virtual void writeObject(ContainerNode &node) const throw(Error);
    void readObject(const ContainerNode &node) throw(Error){
        PJ_UNUSED_ARG( node );
    }
    void fromPj(pjmedia_stream &port);
};
struct JsonMediaPort:               public PersistentObject{
public:
    virtual void writeObject(ContainerNode &node) const throw(Error);
    void readObject(const ContainerNode &node) throw(Error){
        PJ_UNUSED_ARG( node );
    }
    void fromPj(pjmedia_port &port);
};
// 102 on_incoming_call
struct JsonOnIncomingCallParam:     public PersistentObject{
    int         callId;
    string      info;
    string      wholeMsg;
    string      srcAddress;
    // void     *pjRxData;
public:
    virtual void writeObject(ContainerNode &node) const throw(Error);
    void readObject(const ContainerNode &node) throw(Error){
        PJ_UNUSED_ARG( node );
    }
    void fromPj(int call_id, pjsip_rx_data &rdata);
};
// 104 on_call_media_state
struct JsonOnMediaStateParam:       public PersistentObject{
    string  Info;
public:
    virtual void writeObject(ContainerNode &node) const throw(Error);
    void readObject(const ContainerNode &node) throw(Error){
        PJ_UNUSED_ARG( node );
    }
    void fromPj(void);
};
// 107 on_stream_created2
struct JsonOnStreamCreatedParam:    public PersistentObject{
    int              CallId;         /// int        call_id
    int              StreamIdx;      // unsigned    streamIdx;
    int              DestroyPort;    // bool        destroyPort;
    JsonMediaStream  Stream;         // void *stream;    // MediaStream stream;      // pjmedia_stream *stream;
    JsonMediaPort    Port;           // void *pPort      // MediaPort   pPort;        // pjmedia_port   *port;
public:
    virtual void writeObject(ContainerNode &node) const throw(Error);
    void readObject(const ContainerNode &node) throw(Error){
        PJ_UNUSED_ARG( node );
    }
    void fromPj(int call_id, pjsua_on_stream_created_param &param);
};
// 108 on_stream_destroyed
struct JsonOnStreamDestroyedParam:  public PersistentObject{
    int              CallId;         /// int        call_id
    int              StreamIdx;      /// unsigned   streamIdx;
    JsonMediaStream  Stream;         // void *stream;    // MediaStream stream;      // pjmedia_stream *stream;
public:
    virtual void writeObject(ContainerNode &node) const throw(Error);
    void readObject(const ContainerNode &node) throw(Error){
        PJ_UNUSED_ARG( node );
    }
    void fromPj(int call_id, pjsua_on_stream_destroyed_param &stream);
};
// 109 on_dtmf_digit
struct JsonOnDtmfDigitParam:        public PersistentObject{
    int CallId;
    string Digit;
public:
    virtual void writeObject(ContainerNode &node) const throw(Error);
    void readObject(const ContainerNode &node) throw(Error){
        PJ_UNUSED_ARG( node );
    }
    void fromPj(int call_id, pjsua_on_dtmf_digit_param &str);
};
// 111 on_call_transfer_request2
struct JsonOnTransferRequest2Param: public PersistentObject{
    int CallId;

public:
    virtual void writeObject(ContainerNode &node) const throw(Error);
    void readObject(const ContainerNode &node) throw(Error){
        PJ_UNUSED_ARG( node );
    }
    void fromPj(int call_id, pjsua_on_call_transfer_request2_param &str);
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
        PJ_UNUSED_ARG( node );
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
        PJ_UNUSED_ARG( node );
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
        PJ_UNUSED_ARG( node );
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
        PJ_UNUSED_ARG( node );
    }
    void fromPj                     (pjsip_transaction &tsx);
    Json_SipTransaction(){
    }
};
// 111111111111111111111111111111111111111111111111111111111
struct Json_TimerEvent:             public PersistentObject{
    // (Void*) Timer entry, corresponds to pj_timer_entry
    Json_TimerEntry                 entry;  
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        PJ_UNUSED_ARG( node );
    }
    Json_TimerEvent(){
    }
};
// 222222222222222222222222222222222222222222222222222222222
struct Json_TxMsgEvent:             public PersistentObject{
    Json_SipTxData  tdata;
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        PJ_UNUSED_ARG( node );
    }
    Json_TxMsgEvent(){
    }
};
// 333333333333333333333333333333333333333333333333333333333
struct Json_RxMsgEvent:             public PersistentObject{
    Json_SipRxData  rdata;
public:
    virtual void writeObject        (ContainerNode &node) const throw(Error);
    void readObject                 (const ContainerNode &node) throw(Error){
        PJ_UNUSED_ARG( node );
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
        PJ_UNUSED_ARG( node );
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
        PJ_UNUSED_ARG( node );
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
        PJ_UNUSED_ARG( node );
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
        PJ_UNUSED_ARG( node );
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
        PJ_UNUSED_ARG( node );
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
        PJ_UNUSED_ARG( node );
    }
    void fromPj                     (const pjsip_event &ev);
    Json_SipEvent() : type          (PJSIP_EVENT_UNKNOWN), pjEvent(NULL){
    }
};

/**
 * @}  PJSUA2
 */
} // namespace pj

// 结构0 虚执行/虚销毁
typedef struct PendingJob{
    /** Perform the job */
    virtual void execute(bool is_pending) = 0;

    /** Virtual destructor */
    virtual ~PendingJob() {}
}PendingJob;
// 结构1 call_id/回调参数/实执行
typedef struct PendingOnDtmfDigitCallback : public PendingJob{
    int call_id;
    pj::JsonOnDtmfDigitParam prm; // OnDtmfDigitParam prm;

    virtual void execute(bool is_pending){
        PJ_UNUSED_ARG(is_pending);

        // Call *call = Call::lookup(call_id);
        // if (!call)
            // return;

        // call->onDtmfDigit(prm);
    }
}PendingOnDtmfDigitCallback;

#endif  /* __PJSUA2_FOCUSUA_HPP__ */
