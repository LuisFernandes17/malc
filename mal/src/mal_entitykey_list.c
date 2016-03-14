/*
 */

#include "mal.h"

mal_entitykey_list_t *mal_entitykey_list_new(unsigned int element_count) {
  mal_entitykey_list_t *self = (mal_entitykey_list_t *) malloc(
      sizeof(mal_entitykey_list_t));
  if (!self)
    return NULL;

  self->element_count = element_count;
  self->content = (mal_entitykey_t **) malloc(
      sizeof(mal_entitykey_t *) * element_count);

  return self;
}

void mal_entitykey_list_destroy(mal_entitykey_list_t **self_p) {
  if (*self_p) {
    mal_entitykey_list_t *self = *self_p;
    unsigned int list_size = self->element_count;
    mal_entitykey_t **content = self->content;
    for (int i = 0; i < list_size; i++) {
      mal_entitykey_destroy(&content[i]);
    }
    free(self->content);
    free(self);
    *self_p = NULL;
  }
}

unsigned int mal_entitykey_list_get_element_count(
    mal_entitykey_list_t *self) {
  return self->element_count;
}

mal_entitykey_t **mal_entitykey_list_get_content(
    mal_entitykey_list_t *self) {
  return self->content;
}

int mal_entitykey_list_add_encoding_length_malbinary(
    mal_entitykey_list_t *self, malbinary_encoder_t *encoder,
    unsigned int *encoding_length) {
  int rc = 0;
  unsigned int list_size = self->element_count;
  malbinary_encoder_add_list_size_encoding_length(encoder, list_size,
      encoding_length);
  // Presence flags
  (*encoding_length) += list_size;
  mal_entitykey_t **content = self->content;
  for (int i = 0; i < list_size; i++) {
    mal_entitykey_t *list_element = content[i];
    if (list_element != NULL) {
      rc = mal_entitykey_add_encoding_length_malbinary(list_element,
          encoder, encoding_length);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}

int mal_entitykey_list_encode_malbinary(mal_entitykey_list_t *self,
    malbinary_encoder_t *encoder, char *bytes, unsigned int *offset) {
  int rc = 0;
  unsigned int list_size = self->element_count;
  malbinary_encoder_encode_list_size(encoder, bytes, offset, list_size);
  mal_entitykey_t **content = self->content;
  for (int i = 0; i < list_size; i++) {
    mal_entitykey_t *list_element = content[i];
    bool presence_flag = (list_element != NULL);
    rc = malbinary_encoder_encode_presence_flag(encoder, bytes, offset,
        presence_flag);
    if (rc < 0)
      return rc;
    if (presence_flag) {
      rc = mal_entitykey_encode_malbinary(list_element, encoder, bytes,
          offset);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}

int mal_entitykey_list_decode_malbinary(mal_entitykey_list_t *self,
    malbinary_decoder_t *decoder, char *bytes, unsigned int *offset) {
  int rc = 0;
  unsigned int list_size;
  malbinary_decoder_decode_list_size(decoder, bytes, offset, &list_size);
  mal_entitykey_t **list_content = (mal_entitykey_t **) malloc(
      sizeof(mal_entitykey_t *) * list_size);
  for (int i = 0; i < list_size; i++) {
    mal_entitykey_t *list_element;
    bool presence_flag;
    rc = malbinary_decoder_decode_presence_flag(decoder, bytes, offset,
        &presence_flag);
    if (rc < 0)
      return rc;
    if (presence_flag) {
      list_element = mal_entitykey_new();
      rc = mal_entitykey_decode_malbinary(list_element, decoder, bytes,
          offset);
      if (rc < 0)
        return rc;
    } else {
      list_element = NULL;
    }
    list_content[i] = list_element;
  }
  self->element_count = list_size;
  self->content = list_content;
  return rc;
}

void mal_entitykey_list_test(bool verbose) {
  printf(" * mal_entitykey_list: ");
  if (verbose)
    printf("\n");

//  @selftest
// ...
//  @end
  printf("OK\n");
}

