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

#ifndef __MAL_ULONG_LIST_H_INCLUDED__
#define __MAL_ULONG_LIST_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

mal_ulong_list_t *mal_ulong_list_new(unsigned int element_count);

void mal_ulong_list_destroy(mal_ulong_list_t **self_p);

unsigned int mal_ulong_list_get_element_count(mal_ulong_list_t *self);

bool *mal_ulong_list_get_presence_flags(mal_ulong_list_t *self);

mal_ulong_t *mal_ulong_list_get_content(mal_ulong_list_t *self);

int mal_ulong_list_add_encoding_length_malbinary(mal_ulong_list_t *self,
    mal_encoder_t *encoder, void *cursor);

int mal_ulong_list_encode_malbinary(mal_ulong_list_t *self,
    mal_encoder_t *encoder, void *cursor);

int mal_ulong_list_decode_malbinary(mal_ulong_list_t *self,
    mal_decoder_t *decoder, void *cursor);

//  Self test of this class
void mal_ulong_list_test(bool verbose);

#ifdef __cplusplus
}
#endif

#endif
