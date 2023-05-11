/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      md5.cpp
 * \brief     Copy of md5.c by Ulrich Drepper <drepper@gnu.ai.mit.edu>, 1995.
 *
 *
 * \details   Compiled as C++ and hacked to get it compiling by Steve Price
 *
 */

#include "md5.h"

#undef TRUE
#undef FALSE
#define FALSE ((int)1)
#define TRUE ((int)0)

/* It is unfortunate that C does not provide an operator for
   cyclic rotation.  Hope the C compiler is smart enough.
   gcc 2.95.4 seems to be --aaronl */
#define CYCLIC(w, s) (w = (w << s) | (w >> (32 - s)))

//----------------------------------------------------------------------------
//--------md5.c
//----------------------------------------------------------------------------

/* md5.c - Functions to compute MD5 message digest of files or memory blocks
 *         according to the definition of MD5 in RFC 1321 from April 1992.
 */

/* Written by Ulrich Drepper <drepper@gnu.ai.mit.edu>, 1995.  */

/* Handle endian-ness */
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define SWAP(n) (n)
#else
#define SWAP(n) \
  ((n << 24) | ((n & 65280) << 8) | ((n & 16711680) >> 8) | (n >> 24))
#endif

/* Initialize structure containing state of computation.
   (RFC 1321, 3.3: Step 3)  */
void
md5_init_ctx(struct md5_ctx* ctx) {
  ctx->A = 0x67452301;
  ctx->B = 0xefcdab89;
  ctx->C = 0x98badcfe;
  ctx->D = 0x10325476;

  ctx->total[0] = ctx->total[1] = 0;
  ctx->buflen = 0;
}

/* Process the remaining bytes in the internal buffer and the usual
   prolog according to the standard and write the result to RESBUF.
   IMPORTANT: On some systems it is required that RESBUF is correctly
   aligned for a 32 bits value.  */
void*
md5_finish_ctx(struct md5_ctx* ctx, void* resbuf) {
  /* Take yet unprocessed bytes into account.  */
  md5_uint32 bytes = ctx->buflen;
  size_t pad;

  /* Now count remaining bytes.  */
  ctx->total[0] += bytes;
  if (ctx->total[0] < bytes)
    ++ctx->total[1];

  pad = bytes >= 56 ? 64 + 56 - bytes : 56 - bytes;
  memset(&ctx->buffer[bytes], 0, pad);
  ctx->buffer[bytes] = 0x80;

  /* Put the 64-bit file length in *bits* at the end of the buffer.  */
  *(md5_uint32*)&ctx->buffer[bytes + pad] = SWAP(ctx->total[0] << 3);
  *(md5_uint32*)&ctx->buffer[bytes + pad + 4] =
      SWAP(((ctx->total[1] << 3) | (ctx->total[0] >> 29)));

  /* Process last bytes.  */
  md5_process_block(ctx->buffer, bytes + pad + 8, ctx);

  /* Put result from CTX in first 16 bytes following RESBUF.  The result is
     always in little endian byte order, so that a byte-wise output yields
     to the wanted ASCII representation of the message digest.
     IMPORTANT: On some systems it is required that RESBUF is correctly
     aligned for a 32 bits value.  */
  ((md5_uint32*)resbuf)[0] = SWAP(ctx->A);
  ((md5_uint32*)resbuf)[1] = SWAP(ctx->B);
  ((md5_uint32*)resbuf)[2] = SWAP(ctx->C);
  ((md5_uint32*)resbuf)[3] = SWAP(ctx->D);

  return resbuf;
}

/* Compute MD5 message digest for bytes read from STREAM.  The
   resulting message digest number will be written into the 16 bytes
   beginning at RESBLOCK.  */
int
md5_stream(FILE* stream, void* resblock) {
  /* Important: BLOCKSIZE must be a multiple of 64.  */
// static const int BLOCKSIZE = 4096;
#define BLOCKSIZE 4096
  struct md5_ctx ctx;
  char buffer[BLOCKSIZE + 72];
  size_t sum;

  /* Initialize the computation context.  */
  md5_init_ctx(&ctx);

  /* Iterate over full file contents.  */
  while (1) {
    /* We read the file in blocks of BLOCKSIZE bytes.  One call of the
       computation function processes the whole buffer so that with the
       next round of the loop another block can be read.  */
    size_t n;
    sum = 0;

    /* Read block.  Take care for partial reads.  */
    do {
      n = fread(buffer + sum, 1, BLOCKSIZE - sum, stream);

      sum += n;
    } while (sum < BLOCKSIZE && n != 0);
    if (n == 0 && ferror(stream))
      return 1;

    /* If end of file is reached, end the loop.  */
    if (n == 0)
      break;

    /* Process buffer with BLOCKSIZE bytes.  Note that
       BLOCKSIZE % 64 == 0
    */
    md5_process_block(buffer, BLOCKSIZE, &ctx);
  }

  /* Add the last bytes if necessary.  */
  if (sum > 0)
    md5_process_bytes(buffer, sum, &ctx);

  /* Construct result in desired memory.  */
  md5_finish_ctx(&ctx, resblock);
  return 0;
}

/* Compute MD5 message digest for LEN bytes beginning at BUFFER.  The
   result is always in little endian byte order, so that a byte-wise
   output yields to the wanted ASCII representation of the message
   digest.  */
void*
md5_buffer(const char* buffer, size_t len, void* resblock) {
  struct md5_ctx ctx;

  /* Initialize the computation context.  */
  md5_init_ctx(&ctx);

  /* Process whole buffer but last len % 64 bytes.  */
  md5_process_bytes(buffer, len, &ctx);

  /* Put result in desired memory area.  */
  return md5_finish_ctx(&ctx, resblock);
}

void
md5_process_bytes(const void* buffer, size_t len, struct md5_ctx* ctx) {
  /* When we already have some bits in our internal buffer concatenate
     both inputs first.  */
  if (ctx->buflen != 0) {
    size_t left_over = ctx->buflen;
    size_t add = 128 - left_over > len ? len : 128 - left_over;

    memcpy(&ctx->buffer[left_over], buffer, add);
    ctx->buflen += add;

    if (left_over + add > 64) {
      md5_process_block(ctx->buffer, (left_over + add) & ~63, ctx);
      /* The regions in the following copy operation cannot overlap.  */
      memcpy(
          ctx->buffer,
          &ctx->buffer[(left_over + add) & ~63],
          (left_over + add) & 63);
      ctx->buflen = (left_over + add) & 63;
    }

    buffer = (const char*)buffer + add;
    len -= add;
  }

  /* Process available complete blocks.  */
  if (len > 64) {
    md5_process_block(buffer, len & ~63, ctx);
    buffer = (const char*)buffer + (len & ~63);
    len &= 63;
  }

  /* Move remaining bytes in internal buffer.  */
  if (len > 0) {
    memcpy(ctx->buffer, buffer, len);
    ctx->buflen = len;
  }
}

/* These are the four functions used in the four steps of the MD5 algorithm
   and defined in the RFC 1321.  The first function is a little bit optimized
   (as found in Colin Plumbs public domain implementation).  */
/* #define FF(b, c, d) ((b & c) | (~b & d)) */
#define FF(b, c, d) (d ^ (b & (c ^ d)))
#define FG(b, c, d) FF(d, b, c)
#define FH(b, c, d) (b ^ c ^ d)
#define FI(b, c, d) (c ^ (b | ~d))

/* Process LEN bytes of BUFFER, accumulating context into CTX.
   It is assumed that LEN % 64 == 0.  */
void
md5_process_block(const void* buffer, size_t len, struct md5_ctx* ctx) {
  md5_uint32 correct_words[16];
  const md5_uint32* words = (const md5_uint32*)buffer;
  size_t nwords = len / sizeof(md5_uint32);
  const md5_uint32* endp = words + nwords;
  static const md5_uint32 C_array[] = {/* round 1 */
                                       0xd76aa478,
                                       0xe8c7b756,
                                       0x242070db,
                                       0xc1bdceee,
                                       0xf57c0faf,
                                       0x4787c62a,
                                       0xa8304613,
                                       0xfd469501,
                                       0x698098d8,
                                       0x8b44f7af,
                                       0xffff5bb1,
                                       0x895cd7be,
                                       0x6b901122,
                                       0xfd987193,
                                       0xa679438e,
                                       0x49b40821,
                                       /* round 2 */
                                       0xf61e2562,
                                       0xc040b340,
                                       0x265e5a51,
                                       0xe9b6c7aa,
                                       0xd62f105d,
                                       0x2441453,
                                       0xd8a1e681,
                                       0xe7d3fbc8,
                                       0x21e1cde6,
                                       0xc33707d6,
                                       0xf4d50d87,
                                       0x455a14ed,
                                       0xa9e3e905,
                                       0xfcefa3f8,
                                       0x676f02d9,
                                       0x8d2a4c8a,
                                       /* round 3 */
                                       0xfffa3942,
                                       0x8771f681,
                                       0x6d9d6122,
                                       0xfde5380c,
                                       0xa4beea44,
                                       0x4bdecfa9,
                                       0xf6bb4b60,
                                       0xbebfbc70,
                                       0x289b7ec6,
                                       0xeaa127fa,
                                       0xd4ef3085,
                                       0x4881d05,
                                       0xd9d4d039,
                                       0xe6db99e5,
                                       0x1fa27cf8,
                                       0xc4ac5665,
                                       /* round 4 */
                                       0xf4292244,
                                       0x432aff97,
                                       0xab9423a7,
                                       0xfc93a039,
                                       0x655b59c3,
                                       0x8f0ccc92,
                                       0xffeff47d,
                                       0x85845dd1,
                                       0x6fa87e4f,
                                       0xfe2ce6e0,
                                       0xa3014314,
                                       0x4e0811a1,
                                       0xf7537e82,
                                       0xbd3af235,
                                       0x2ad7d2bb,
                                       0xeb86d391};

  static const char P_array[] = {
      0, 1, 2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, /* 1 */
      1, 6, 11, 0,  5,  10, 15, 4,  9,  14, 3,  8,  13, 2,  7,  12, /* 2 */
      5, 8, 11, 14, 1,  4,  7,  10, 13, 0,  3,  6,  9,  12, 15, 2, /* 3 */
      0, 7, 14, 5,  12, 3,  10, 1,  8,  15, 6,  13, 4,  11, 2,  9 /* 4 */
  };

  static const char S_array[] = {
      7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21};

  md5_uint32 A = ctx->A;
  md5_uint32 B = ctx->B;
  md5_uint32 C = ctx->C;
  md5_uint32 D = ctx->D;

  /* First increment the byte count.  RFC 1321 specifies the possible
     length of the file up to 2^64 bits.  Here we only compute the
     number of bytes.  Do a double word increment.  */
  ctx->total[0] += len;
  if (ctx->total[0] < len)
    ++ctx->total[1];

  /* Process all bytes in the buffer with 64 bytes in each round of
     the loop.  */
  while (words < endp) {
    md5_uint32* cwp = correct_words;
    md5_uint32 A_save = A;
    md5_uint32 B_save = B;
    md5_uint32 C_save = C;
    md5_uint32 D_save = D;

    const md5_uint32* pc;
    const char* pp;
    const char* ps;
    int i;
    md5_uint32 temp;

    for (i = 0; i < 16; i++) {
      cwp[i] = SWAP(words[i]);
    }
    words += 16;

    pc = C_array;
    pp = P_array;
    ps = S_array;

    for (i = 0; i < 16; i++) {
      temp = A + FF(B, C, D) + cwp[(int)(*pp++)] + *pc++;
      CYCLIC(temp, ps[i & 3]);
      temp += B;
      A = D;
      D = C;
      C = B;
      B = temp;
    }

    ps += 4;
    for (i = 0; i < 16; i++) {
      temp = A + FG(B, C, D) + cwp[(int)(*pp++)] + *pc++;
      CYCLIC(temp, ps[i & 3]);
      temp += B;
      A = D;
      D = C;
      C = B;
      B = temp;
    }
    ps += 4;
    for (i = 0; i < 16; i++) {
      temp = A + FH(B, C, D) + cwp[(int)(*pp++)] + *pc++;
      CYCLIC(temp, ps[i & 3]);
      temp += B;
      A = D;
      D = C;
      C = B;
      B = temp;
    }
    ps += 4;
    for (i = 0; i < 16; i++) {
      temp = A + FI(B, C, D) + cwp[(int)(*pp++)] + *pc++;
      CYCLIC(temp, ps[i & 3]);
      temp += B;
      A = D;
      D = C;
      C = B;
      B = temp;
    }

    /* Add the starting values of the context.  */
    A += A_save;
    B += B_save;
    C += C_save;
    D += D_save;
  }

  /* Put checksum in context given as argument.  */
  ctx->A = A;
  ctx->B = B;
  ctx->C = C;
  ctx->D = D;
}

//----------------------------------------------------------------------------
//--------end of md5.c
//----------------------------------------------------------------------------
