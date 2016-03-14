/*
 */

#ifndef __MAL_STRING_LIST_H_INCLUDED__
#define __MAL_STRING_LIST_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

mal_string_list_t *mal_string_list_new(unsigned int element_count);

void mal_string_list_destroy(mal_string_list_t **self_p);

unsigned int mal_string_list_get_element_count(mal_string_list_t *self);

mal_string_t **mal_string_list_get_content(mal_string_list_t *self);

int mal_string_list_add_encoding_length_malbinary(mal_string_list_t *self,
    malbinary_encoder_t *encoder, unsigned int *encoding_length);

int mal_string_list_encode_malbinary(mal_string_list_t *self,
    malbinary_encoder_t *encoder, char *bytes, unsigned int *offset);

int mal_string_list_decode_malbinary(mal_string_list_t *self,
    malbinary_decoder_t *decoder, char *bytes, unsigned int *offset);

void mal_string_list_print(mal_string_list_t *self);

//  Self test of this class
void mal_string_list_test(bool verbose);

#ifdef __cplusplus
}
#endif

#endif
