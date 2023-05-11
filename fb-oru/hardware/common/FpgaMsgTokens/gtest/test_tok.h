// ========================================================================

#ifndef _testtok_H
#define _testtok_H

#define API_VERSION 0x12345678u

#ifdef __cplusplus
extern "C"
{
#endif

/* token */
#define TOK_NO 100
#define TOK_YES 101
#define TOK_OFF 102
#define TOK_ON 103
#define TOK_disabled 104
#define TOK_enabled 105
#define TOK_auto 106
#define TOK_NACK 107
#define TOK_ACK 108
#define TOK_none 109
#define TOK_error 110

/* state */
#define STATEVAR_response 200
#define STATEVAR_msgId 201
#define STATEVAR_command 202
#define STATEVAR_succeeded 203
#define STATEVAR_buildNo 204
#define STATEVAR_debug 205
#define STATEVAR_logTrace 206
#define STATEVAR_logVerbose 207
#define STATEVAR_logMatlab 208
#define STATEVAR_logConsole 209
#define STATEVAR_uptime 210
#define STATEVAR_t 211
#define STATEVAR_dt 212
#define STATEVAR_block 213
#define STATEVAR_canceller 214
#define STATEVAR_track 215
#define STATEVAR_trackN 216
#define STATEVAR_lockN 217
#define STATEVAR_Ta 218
#define STATEVAR_Tb 219
#define STATEVAR_CNL3 220
#define STATEVAR_CNL5 221
#define STATEVAR_CNL7 222
#define STATEVAR_FOM0 223
#define STATEVAR_FOM1 224
#define STATEVAR_FOM2 225
#define STATEVAR_FOM3 226
#define STATEVAR_pFOM 227
#define STATEVAR_dFOM 228
#define STATEVAR_stimRe 229
#define STATEVAR_stimIm 230
#define STATEVAR_pimGain 231
#define STATEVAR_period 232
#define STATEVAR_pMin 233
#define STATEVAR_pimState 234
#define STATEVAR_adaptCanceller 235
#define STATEVAR_adaptOrthogonalisation 236
#define STATEVAR_branches 237
#define STATEVAR_mask 238
#define STATEVAR_afStart 239
#define STATEVAR_dlBbSrc 240
#define STATEVAR_ulBbSrc 241
#define STATEVAR_ulBbDst 242
#define STATEVAR_srcBw 243
#define STATEVAR_dstBw 244
#define STATEVAR_dl0 245
#define STATEVAR_dl1 246
#define STATEVAR_dl2 247
#define STATEVAR_f0 248
#define STATEVAR_f1 249
#define STATEVAR_f2 250
#define STATEVAR_fd0 251
#define STATEVAR_fd1 252
#define STATEVAR_tssi0 253
#define STATEVAR_tssi1 254
#define STATEVAR_tssi2 255
#define STATEVAR_tssiPim 256
#define STATEVAR_testCase 257
#define STATEVAR_n 258
#define STATEVAR_addr 259
#define STATEVAR_data 260

/* command */
#define CMD_apiVersion 300
#define CMD_set 301
#define CMD_get 302
#define CMD_restart 303
#define CMD_search 304
#define CMD_initialSearch 305
#define CMD_dispersiveSearch 306
#define CMD_update 307
#define CMD_start 308
#define CMD_stop 309
#define CMD_startTssi 310
#define CMD_stopTssi 311
#define CMD_orthogonalise 312
#define CMD_pdp 313
#define CMD_avgPdp 314
#define CMD_enableStim 315
#define CMD_disableStim 316
#define CMD_dump 317
#define CMD_reset 318
#define CMD_runTest 319
#define CMD_frd 320
#define CMD_fwr 321
#define CMD_capture 322
#define CMD_getCoeffs 323
#define CMD_xcorr 324



#ifdef __cplusplus
}
#endif

#endif	/* _testtok_H */
