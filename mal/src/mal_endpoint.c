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

struct _mal_endpoint_t {
  mal_ctx_t *mal_ctx;
  mal_uri_t *uri;
  long transaction_id_counter;

  void *endpoint_data;
};

mal_endpoint_t *mal_endpoint_new(
    mal_ctx_t *mal_ctx,
    mal_uri_t *uri) {
  mal_endpoint_t *self = (mal_endpoint_t *) malloc(sizeof(mal_endpoint_t));
  if (!self)
    return NULL;

  self->mal_ctx = mal_ctx;
  self->uri = strdup(uri);
  self->transaction_id_counter = 0L;

  mal_ctx_create_endpoint(mal_ctx, self);

  return self;
}

mal_endpoint_t *mal_endpoint_actor(
    mal_ctx_t *mal_ctx,
    void *endpoint_data) {
  mal_endpoint_t *self = (mal_endpoint_t *) malloc(sizeof(mal_endpoint_t));
  if (!self)
    return NULL;

  self->mal_ctx = mal_ctx;
  self->uri = strdup("actor");
  self->transaction_id_counter = 0L;

  self->endpoint_data = endpoint_data;

  return self;
}

void mal_endpoint_destroy(mal_endpoint_t **self_p) {
  if (*self_p) {
    mal_endpoint_t *self = *self_p;
    free(self->uri);

    mal_ctx_destroy_endpoint(self->mal_ctx, &self->endpoint_data);

    free(self);
    *self_p = NULL;
  }
}

/**
 * Get the reference to the MAL context of the end-point.
 */
mal_ctx_t *mal_endpoint_get_mal_ctx(mal_endpoint_t *self) {
  return self->mal_ctx;
}

/**
 * Get the EndPoint URI.
 */
mal_uri_t *mal_endpoint_get_uri(mal_endpoint_t *self) {
  return self->uri;
}

long mal_endpoint_get_next_transaction_id_counter(mal_endpoint_t *self) {
  return self->transaction_id_counter++;
}

// Used by the transport implementation to retrieve specific datas associated to the EndPoint.
void *mal_endpoint_get_endpoint_data(mal_endpoint_t *self) {
  return self->endpoint_data;
}

//  Used by the transport implementation to set specific datas associated to the EndPoint.
void mal_endpoint_set_endpoint_data(mal_endpoint_t *self, void *endpoint_data) {
  self->endpoint_data = endpoint_data;
}

int mal_endpoint_init_operation(mal_endpoint_t *self,
    mal_message_t *message, mal_uri_t *uri_to, bool set_tid) {
   return mal_ctx_init_operation(self->mal_ctx, self, message, uri_to, set_tid);
}

int mal_endpoint_return_operation(mal_endpoint_t *self,
    mal_message_t *init_message, mal_message_t *result_message,
    bool is_error_message) {
  mal_message_set_uri_to(result_message,
      mal_message_get_uri_from(init_message));
  mal_message_set_free_uri_to(result_message, false);
  mal_message_set_uri_from(result_message, self->uri);
  mal_message_set_free_uri_from(result_message, false);
  mal_message_set_transaction_id(result_message,
      mal_message_get_transaction_id(init_message));
  mal_message_set_is_error_message(result_message, is_error_message);

  return mal_ctx_send_message(self->mal_ctx, self, result_message);
}

int mal_endpoint_recv_message(
    mal_endpoint_t *self,
    mal_message_t **message) {
  return mal_ctx_recv_message(self->mal_ctx, self, message);
}

void mal_endpoint_test(bool verbose) {
  printf(" * mal_endpoint: ");
  if (verbose)
    printf("\n");

  //  @selftest
  // ...
  //  @end
  printf("OK\n");
}
