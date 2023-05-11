// ========================================================================

#ifndef _testtok_H
#define _testtok_H

#define API_VERSION 0x12345678

#ifdef __cplusplus
extern "C"
{
#endif

/* reserved commands -- not available in the public PERL interface */
#define CMD_noop 		-1
#define CMD_unlockPIM 		-2
#define CMD_forceUnlockPIM	-3

/* token */
#define TOK_no 100
#define TOK_yes 101
#define TOK_off 102
#define TOK_on 103
#define TOK_disabled 104
#define TOK_enabled 105
#define TOK_auto 106
#define TOK_NACK 107
#define TOK_ACK 108
#define TOK_none 109
#define TOK_error 110
#define TOK_COUNT 111

/* state */
#define STATEVAR_response 0
#define STATEVAR_msgId 1
#define STATEVAR_command 2
#define STATEVAR_succeeded 3
#define STATEVAR_buildNo 4
#define STATEVAR_debug 5
#define STATEVAR_logTrace 6
#define STATEVAR_logVerbose 7
#define STATEVAR_logMatlab 8
#define STATEVAR_logConsole 9
#define STATEVAR_uptime 10
#define STATEVAR_t 11
#define STATEVAR_dt 12
#define STATEVAR_block 13
#define STATEVAR_canceller 14
#define STATEVAR_track 15
#define STATEVAR_trackN 16
#define STATEVAR_lockN 17
#define STATEVAR_Ta 18
#define STATEVAR_Tb 19
#define STATEVAR_CNL3 20
#define STATEVAR_CNL5 21
#define STATEVAR_CNL7 22
#define STATEVAR_FOM0 23
#define STATEVAR_FOM1 24
#define STATEVAR_FOM2 25
#define STATEVAR_FOM3 26
#define STATEVAR_pFOM 27
#define STATEVAR_dFOM 28
#define STATEVAR_stimRe 29
#define STATEVAR_stimIm 30
#define STATEVAR_pimGain 31
#define STATEVAR_period 32
#define STATEVAR_pMin 33
#define STATEVAR_pimState 34
#define STATEVAR_adaptCanceller 35
#define STATEVAR_adaptOrthogonalisation 36
#define STATEVAR_branches 37
#define STATEVAR_mask 38
#define STATEVAR_afStart 39
#define STATEVAR_dlBbSrc 40
#define STATEVAR_ulBbSrc 41
#define STATEVAR_ulBbDst 42
#define STATEVAR_srcBw 43
#define STATEVAR_dstBw 44
#define STATEVAR_dl0 45
#define STATEVAR_dl1 46
#define STATEVAR_dl2 47
#define STATEVAR_f0 48
#define STATEVAR_f1 49
#define STATEVAR_f2 50
#define STATEVAR_fd0 51
#define STATEVAR_fd1 52
#define STATEVAR_tssi0 53
#define STATEVAR_tssi1 54
#define STATEVAR_tssi2 55
#define STATEVAR_tssiPim 56
#define STATEVAR_testCase 57
#define STATEVAR_n 58
#define STATEVAR_addr 59
#define STATEVAR_data 60
#define STATEVAR_COUNT 61

/* command */
#define CMD_apiVersion 0
#define CMD_set 1
#define CMD_get 2
#define CMD_restart 3
#define CMD_search 4
#define CMD_initialSearch 5
#define CMD_dispersiveSearch 6
#define CMD_update 7
#define CMD_start 8
#define CMD_stop 9
#define CMD_startTssi 10
#define CMD_stopTssi 11
#define CMD_orthogonalise 12
#define CMD_pdp 13
#define CMD_avgPdp 14
#define CMD_enableStim 15
#define CMD_disableStim 16
#define CMD_dump 17
#define CMD_reset 18
#define CMD_runTest 19
#define CMD_frd 20
#define CMD_fwr 21
#define CMD_capture 22
#define CMD_getCoeffs 23
#define CMD_xcorr 24
#define CMD_COUNT 25



#ifdef __cplusplus
}
#endif

#endif	/* _testtok_H */
