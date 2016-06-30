/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2016 CNES
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 */

#ifndef __MALZMQ_H_INCLUDED__
#define __MALZMQ_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include "mal.h"
#include "malbinary.h"
#include "czmq.h"
#include "zmq.h"

//  MALZMQ API version macros for compile-time API detection

#define MALZMQ_VERSION_MAJOR 1
#define MALZMQ_VERSION_MINOR 0
#define MALZMQ_VERSION_PATCH 0

#define MALZMQ_MAKE_VERSION(major, minor, patch) \
    ((major) * 10000 + (minor) * 100 + (patch))
#define MALZMQ_VERSION \
		MALZMQ_MAKE_VERSION(MALZMQ_VERSION_MAJOR, MALZMQ_VERSION_MINOR, MALZMQ_VERSION_PATCH)

extern clog_logger_t malzmq_logger;

void malzmq_set_log_level(int level);

#define MALZMQ_PROTOCOL_VERSION 1

typedef struct _malzmq_ctx_t malzmq_ctx_t;
typedef struct _malzmq_header_t malzmq_header_t;

int malzmq_add_message_encoding_length(malzmq_header_t *malzmq_header,
    mal_message_t *message, mal_encoder_t *encoder,
    void *cursor);

int malzmq_encode_message(malzmq_header_t *malzmq_header,
    mal_message_t *message, mal_encoder_t *encoder, void *cursor);

int malzmq_decode_message(malzmq_header_t *malzmq_header,
    mal_message_t *message, mal_decoder_t *decoder, void *cursor);

int malzmq_decode_uri_to(malzmq_header_t *malzmq_header,
	mal_decoder_t *decoder, char *bytes, unsigned int length, mal_uri_t **uri_to);

void malzmq_test(bool verbose);

//  Public API classes
#include "malzmq_ctx.h"
#include "malzmq_header.h"

#ifdef __cplusplus
}
#endif

#endif
