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

#include "mal.h"

struct _mal_string_list_t {
  unsigned int element_count;
  mal_string_t **content;
};

mal_string_list_t *mal_string_list_new(unsigned int element_count) {
  mal_string_list_t *self = (mal_string_list_t *) calloc(1, sizeof(mal_string_list_t));
  if (!self)
    return NULL;

  self->content = (mal_string_t **) calloc(element_count, sizeof(mal_string_t *));
  if (!self->content && (element_count > 0))
  {
    free(self->content);
    free(self);
    return NULL;
  }
  self->element_count = element_count;
  return self;
}

void mal_string_list_destroy(mal_string_list_t ** self_p)
{
  if ((*self_p)->element_count > 0)
  {
    for (int i = 0; i < (*self_p)->element_count; i++)
    {
      if ((*self_p)->content[i] != NULL)
        mal_string_destroy(&(*self_p)->content[i]);
    }
    free((*self_p)->content);
  }
  free (*self_p);
  (*self_p) = NULL;
}

unsigned int mal_string_list_get_element_count(mal_string_list_t *self) {
  return self->element_count;
}

mal_string_t **mal_string_list_get_content(mal_string_list_t *self) {
  return self->content;
}

int mal_string_list_add_encoding_length_malbinary(mal_string_list_t *self,
    mal_encoder_t *encoder, void *cursor) {
  int rc = 0;
  unsigned int list_size = self->element_count;
  rc = mal_encoder_add_list_size_encoding_length(encoder, list_size, cursor);
  if (rc < 0)
    return rc;
  for (int i = 0; i < list_size; i++)
  {
    mal_string_t *list_element = self->content[i];
    bool presence_flag = (list_element != NULL);
    rc = mal_encoder_add_presence_flag_encoding_length(encoder, presence_flag, cursor);
    if (rc < 0)
      return rc;
    if (presence_flag)
    {
      rc = mal_encoder_add_string_encoding_length(encoder, list_element, cursor);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}

int mal_string_list_encode_malbinary(mal_string_list_t *self,
    mal_encoder_t *encoder, void *cursor) {
  int rc = 0;
  unsigned int list_size = self->element_count;
  rc = mal_encoder_encode_list_size(encoder, cursor, list_size);
  if (rc < 0)
    return rc;
  mal_string_t **content = self->content;
  for (int i = 0; i < list_size; i++)
  {
    mal_string_t *list_element = content[i];
    bool presence_flag = (list_element != NULL);
    rc = mal_encoder_encode_presence_flag(encoder, cursor, presence_flag);
    if (rc < 0)
      return rc;
    if (presence_flag)
    {
      rc = mal_encoder_encode_string(encoder, cursor, list_element);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}

int mal_string_list_decode_malbinary(mal_string_list_t *self,
    mal_decoder_t *decoder, void *cursor) {
  int rc = 0;
  unsigned int list_size;
  rc = mal_decoder_decode_list_size(decoder, cursor, &list_size);
  if (rc < 0)
    return rc;
  if (list_size == 0)
  {
    self->element_count = 0;
    self->content = NULL;
    return 0;
  }
  self->content = (mal_string_t **) calloc(list_size, sizeof(mal_string_t *));
  if (self->content == NULL)
    return -1;
  self->element_count = list_size;
  for (int i = 0; i < list_size; i++)
  {
    bool presence_flag;
    rc = mal_decoder_decode_presence_flag(decoder, cursor, &presence_flag);
    if (rc < 0)
      return rc;
    if (presence_flag)
    {
      rc = mal_decoder_decode_string(decoder, cursor, &self->content[i]);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}

// TODO: Needs better integration with logging subsystem.
void mal_string_list_print(mal_string_list_t *self) {
  clog_debug_no_header(mal_logger, "mal_string_list(");
  clog_debug_no_header(mal_logger, "element_count=%d", self->element_count);
  clog_debug_no_header(mal_logger, ",content=");
  for (int i = 0; i < self->element_count; i++) {
    clog_debug_no_header(mal_logger, "%s,", self->content[i]);
  }
  clog_debug_no_header(mal_logger, ")");
}

void mal_string_list_test(bool verbose) {
  printf(" * mal_string_list: ");
  if (verbose)
    printf("\n");

//  @selftest
// ...
//  @end
  printf("OK\n");
}

