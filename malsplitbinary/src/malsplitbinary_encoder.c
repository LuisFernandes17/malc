#include "malsplitbinary.h"

mal_encoder_t *malsplitbinary_encoder_new() {
  mal_encoder_t *self = (mal_encoder_t *) malloc(sizeof(mal_encoder_t));
  if (!self)
    return NULL;

  self->encoding_format_code = MALSPLITBINARY_FORMAT_CODE;
  self->varint_supported = true;
  self->logger = CLOG_WARN_LEVEL;

  malsplitbinary_init_encode_functions(self);

  return self;
}

void *malsplitbinary_encoder_new_cursor() {
  malsplitbinary_cursor_t *cursor = (malsplitbinary_cursor_t *) malloc(sizeof(malsplitbinary_cursor_t));
  if (! cursor) return NULL;

  malsplitbinary_cursor_reset(cursor);

  return (void *) cursor;
}

int malsplitbinary_encoder_add_string_encoding_length(mal_encoder_t *self,
    mal_string_t *to_encode, void *cursor) {
  return malbinary_encoder_add_string_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_presence_flag_encoding_length(
    mal_encoder_t *self, unsigned int length, void *cursor) {
  int rc = 0;
  if (length > 1)
    ((malsplitbinary_cursor_t *) cursor)->bitfield_length += length;
  else
    ((malsplitbinary_cursor_t *) cursor)->bitfield_length += MALSPLITBINARY_PRESENCE_FLAG_SIZE;
  return rc;
}

int malsplitbinary_encoder_add_short_form_encoding_length(mal_encoder_t *self,
    long to_encode, void *cursor) {
  return malbinary_encoder_add_short_form_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_integer_encoding_length(mal_encoder_t *self,
    mal_integer_t to_encode, void *cursor) {
  return malbinary_encoder_add_integer_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_list_size_encoding_length(mal_encoder_t *self,
    unsigned int to_encode, void *cursor) {
  return malbinary_encoder_add_list_size_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_small_enum_encoding_length(mal_encoder_t *self,
    unsigned int to_encode, void *cursor) {
  return malbinary_encoder_add_small_enum_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_medium_enum_encoding_length(mal_encoder_t *self,
    unsigned int to_encode, void *cursor) {
  return malbinary_encoder_add_medium_enum_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_large_enum_encoding_length(mal_encoder_t *self,
    unsigned int to_encode, void *cursor) {
  return malbinary_encoder_add_large_enum_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_identifier_encoding_length(mal_encoder_t *self,
    mal_identifier_t *to_encode, void *cursor) {
  return malbinary_encoder_add_identifier_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_uinteger_encoding_length(mal_encoder_t *self,
    mal_uinteger_t to_encode, void *cursor) {
  return malbinary_encoder_add_uinteger_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_uri_encoding_length(mal_encoder_t *self,
    mal_uri_t *to_encode, void *cursor) {
  return malbinary_encoder_add_uri_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_time_encoding_length(mal_encoder_t *self,
    mal_time_t to_encode, void *cursor) {
  return malbinary_encoder_add_time_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_uoctet_encoding_length(mal_encoder_t *self,
    mal_uoctet_t to_encode, void *cursor) {
  return malbinary_encoder_add_uoctet_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_long_encoding_length(mal_encoder_t *self,
    mal_long_t to_encode, void *cursor) {
  return malbinary_encoder_add_long_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_ushort_encoding_length(mal_encoder_t *self,
    mal_ushort_t to_encode, void *cursor) {
  return malbinary_encoder_add_ushort_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_boolean_encoding_length(mal_encoder_t *self,
    mal_boolean_t to_encode, void *cursor) {
  int rc = 0;
  ((malsplitbinary_cursor_t *) cursor)->bitfield_length +=  MALSPLITBINARY_PRESENCE_FLAG_SIZE;
  return rc;
}

int malsplitbinary_encoder_add_blob_encoding_length(mal_encoder_t *self,
    mal_blob_t *to_encode, void *cursor) {
  return malbinary_encoder_add_blob_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_encode_string(mal_encoder_t *self,
    void *cursor, mal_string_t *to_encode) {
  return malbinary_encoder_encode_string(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_presence_flag(mal_encoder_t *self,
    void *cursor, bool present) {
  return malsplitbinary_encoder_encode_boolean(self, cursor, present);
}

int malsplitbinary_encoder_encode_short_form(mal_encoder_t *self,
    void *cursor, long to_encode) {
  return malbinary_encoder_encode_short_form(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_integer(mal_encoder_t *self,
    void *cursor, mal_integer_t to_encode) {
  return malbinary_encoder_encode_integer(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_list_size(mal_encoder_t *self,
    void *cursor, unsigned int list_size) {
  return malbinary_encoder_encode_list_size(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, list_size);
}

int malsplitbinary_encoder_encode_small_enum(mal_encoder_t *self,
    void *cursor, int to_encode) {
  return malbinary_encoder_encode_small_enum(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_medium_enum(mal_encoder_t *self,
    void *cursor, int to_encode) {
  return malbinary_encoder_encode_medium_enum(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_large_enum(mal_encoder_t *self,
    void *cursor, int to_encode) {
  return malbinary_encoder_encode_large_enum(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_uri(mal_encoder_t *self,
    void *cursor, mal_uri_t *to_encode) {
  return malbinary_encoder_encode_uri(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_blob(mal_encoder_t *self,
    void *cursor, mal_blob_t *to_encode) {
  return malbinary_encoder_encode_blob(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_time(mal_encoder_t *self,
    void *cursor, mal_time_t to_encode) {
  return malbinary_encoder_encode_time(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_uinteger(mal_encoder_t *self,
    void *cursor, mal_uinteger_t to_encode) {
  return malbinary_encoder_encode_uinteger(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_identifier(mal_encoder_t *self,
    void *cursor, mal_identifier_t *to_encode) {
  return malbinary_encoder_encode_identifier(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_uoctet(mal_encoder_t *self,
    void *cursor, mal_uoctet_t to_encode) {
  return malbinary_encoder_encode_uoctet(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_long(mal_encoder_t *self,
    void *cursor, mal_long_t to_encode) {
  return malbinary_encoder_encode_long(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_ushort(mal_encoder_t *self,
    void *cursor, mal_ushort_t to_encode) {
  return malbinary_encoder_encode_ushort(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_boolean(mal_encoder_t *self,
    void *cursor, mal_boolean_t to_encode) {
  int rc = 0;
  char *bitfield = malsplitbinary_cursor_get_bitfield_ptr((malsplitbinary_cursor_t *) cursor);
  //printf("---- bitfield_idx = %d\n", ((malsplitbinary_cursor_t *) cursor)->bitfield_idx);//NTA tmp
  if (to_encode)
    ((malsplitbinary_cursor_t *) cursor)->most_significant = ((malsplitbinary_cursor_t *) cursor)->bitfield_idx;

  bitfield[(((malsplitbinary_cursor_t *) cursor)->bitfield_idx) >> 3] |=
      to_encode << ((((malsplitbinary_cursor_t *) cursor)->bitfield_idx) & 7);

  ((malsplitbinary_cursor_t *) cursor)->bitfield_idx++;
  return rc;
}

int malsplitbinary_encoder_encode_attribute_tag(mal_encoder_t *self, void *cursor, unsigned char to_encode) {
  return malbinary_encoder_encode_attribute_tag(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_add_duration_encoding_length(mal_encoder_t *self,
    mal_duration_t to_encode, void *cursor) {
  return malbinary_encoder_add_duration_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_float_encoding_length(mal_encoder_t *self,
    mal_float_t to_encode, void *cursor) {
  return malbinary_encoder_add_float_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_double_encoding_length(mal_encoder_t *self,
    mal_double_t to_encode, void *cursor) {
  return malbinary_encoder_add_double_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_octet_encoding_length(mal_encoder_t *self,
    mal_octet_t to_encode, void *cursor) {
  return malbinary_encoder_add_octet_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_short_encoding_length(mal_encoder_t *self,
    mal_short_t to_encode, void *cursor) {
  return malbinary_encoder_add_short_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_ulong_encoding_length(mal_encoder_t *self,
    mal_ulong_t to_encode, void *cursor) {
  return malbinary_encoder_add_ulong_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_finetime_encoding_length(mal_encoder_t *self,
    mal_finetime_t to_encode, void *cursor) {
  return malbinary_encoder_add_finetime_encoding_length(self, to_encode, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_encode_duration(mal_encoder_t *self,
    void *cursor, mal_duration_t to_encode) {
  return malbinary_encoder_encode_duration(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_float(mal_encoder_t *self,
    void *cursor, mal_float_t to_encode) {
  return malbinary_encoder_encode_float(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_double(mal_encoder_t *self,
    void *cursor, mal_double_t to_encode) {
  return malbinary_encoder_encode_double(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_octet(mal_encoder_t *self,
    void *cursor, mal_octet_t to_encode) {
  return malbinary_encoder_encode_octet(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_short(mal_encoder_t *self,
    void *cursor, mal_short_t to_encode) {
  return malbinary_encoder_encode_short(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_ulong(mal_encoder_t *self,
    void *cursor, mal_ulong_t to_encode) {
  return malbinary_encoder_encode_ulong(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_encode_finetime(mal_encoder_t *self,
    void *cursor, mal_finetime_t to_encode) {
  return malbinary_encoder_encode_finetime(self, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor, to_encode);
}

int malsplitbinary_encoder_add_attribute_tag_encoding_length(mal_encoder_t *encoder,
    unsigned char attribute_tag, void *cursor) {
  return malbinary_encoder_add_attribute_tag_encoding_length(encoder, attribute_tag, &((malsplitbinary_cursor_t *) cursor)->malbinary_cursor);
}

int malsplitbinary_encoder_add_attribute_encoding_length(mal_encoder_t *malsplitbinary_encoder,
    unsigned char attribute_tag, union mal_attribute_t self, void *cursor) {
  int rc = 0;
  switch (attribute_tag) {
  case MAL_BLOB_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_blob_encoding_length(malsplitbinary_encoder, self.blob_value, cursor);
    break;
  case MAL_BOOLEAN_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_boolean_encoding_length(malsplitbinary_encoder, self.boolean_value, cursor);
    break;
  case MAL_DURATION_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_duration_encoding_length(malsplitbinary_encoder, self.duration_value, cursor);
    break;
  case MAL_FLOAT_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_float_encoding_length(malsplitbinary_encoder, self.float_value, cursor);
    break;
  case MAL_DOUBLE_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_double_encoding_length(malsplitbinary_encoder, self.double_value, cursor);
    break;
  case MAL_IDENTIFIER_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_identifier_encoding_length(malsplitbinary_encoder, self.identifier_value, cursor);
    break;
  case MAL_OCTET_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_octet_encoding_length(malsplitbinary_encoder, self.octet_value, cursor);
    break;
  case MAL_UOCTET_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_uoctet_encoding_length(malsplitbinary_encoder, self.uoctet_value, cursor);
    break;
  case MAL_SHORT_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_short_encoding_length(malsplitbinary_encoder, self.short_value, cursor);
    break;
  case MAL_USHORT_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_ushort_encoding_length(malsplitbinary_encoder, self.ushort_value, cursor);
    break;
  case MAL_INTEGER_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_integer_encoding_length(malsplitbinary_encoder, self.integer_value, cursor);
    break;
  case MAL_UINTEGER_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_uinteger_encoding_length(malsplitbinary_encoder, self.uinteger_value, cursor);
    break;
  case MAL_LONG_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_long_encoding_length(malsplitbinary_encoder, self.long_value, cursor);
    break;
  case MAL_ULONG_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_ulong_encoding_length(malsplitbinary_encoder, self.ulong_value, cursor);
    break;
  case MAL_STRING_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_string_encoding_length(malsplitbinary_encoder, self.string_value, cursor);
    break;
  case MAL_TIME_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_time_encoding_length(malsplitbinary_encoder, self.time_value, cursor);
    break;
  case MAL_FINETIME_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_finetime_encoding_length(malsplitbinary_encoder, self.finetime_value, cursor);
    break;
  case MAL_URI_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_add_uri_encoding_length(malsplitbinary_encoder, self.uri_value, cursor);
    break;
  default:
    //nothing to do
    break;
  }
  return rc;
}

int malsplitbinary_encoder_encode_attribute(mal_encoder_t *malsplitbinary_encoder,
    void *cursor, unsigned char attribute_tag, union mal_attribute_t self) {
  int rc = 0;
  switch (attribute_tag) {
  case MAL_BLOB_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_blob(malsplitbinary_encoder, cursor, self.blob_value);
    break;
  case MAL_BOOLEAN_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_boolean(malsplitbinary_encoder, cursor, self.boolean_value);
    break;
  case MAL_DURATION_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_duration(malsplitbinary_encoder, cursor, self.duration_value);
    break;
  case MAL_FLOAT_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_float(malsplitbinary_encoder, cursor, self.float_value);
    break;
  case MAL_DOUBLE_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_double(malsplitbinary_encoder, cursor, self.double_value);
    break;
  case MAL_IDENTIFIER_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_identifier(malsplitbinary_encoder, cursor, self.identifier_value);
    break;
  case MAL_OCTET_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_octet(malsplitbinary_encoder, cursor, self.octet_value);
    break;
  case MAL_UOCTET_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_uoctet(malsplitbinary_encoder, cursor, self.uoctet_value);
    break;
  case MAL_SHORT_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_short(malsplitbinary_encoder, cursor, self.short_value);
    break;
  case MAL_USHORT_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_ushort(malsplitbinary_encoder, cursor, self.ushort_value);
    break;
  case MAL_INTEGER_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_integer(malsplitbinary_encoder, cursor, self.integer_value);
    break;
  case MAL_UINTEGER_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_uinteger(malsplitbinary_encoder, cursor, self.uinteger_value);
    break;
  case MAL_LONG_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_long(malsplitbinary_encoder, cursor, self.long_value);
    break;
  case MAL_ULONG_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_ulong(malsplitbinary_encoder, cursor, self.ulong_value);
    break;
  case MAL_STRING_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_string(malsplitbinary_encoder, cursor, self.string_value);
    break;
  case MAL_TIME_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_time(malsplitbinary_encoder, cursor, self.time_value);
    break;
  case MAL_FINETIME_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_finetime(malsplitbinary_encoder, cursor, self.finetime_value);
    break;
  case MAL_URI_ATTRIBUTE_TAG:
    rc = malsplitbinary_encoder_encode_uri(malsplitbinary_encoder, cursor, self.uri_value);
    break;
  default:
    //nothing to do
    break;
  }
  return rc;
}

// TODO (AF): The malsplitbinary encoding functions should be private and only used through
// the mal_encoder_t structure.

void malsplitbinary_init_encode_functions(mal_encoder_t *self) {
  mal_encoder_initialize_functions(self,
      malsplitbinary_encoder_new_cursor,
      malsplitbinary_cursor_reset,
      malsplitbinary_encoder_cursor_init,
      malsplitbinary_cursor_destroy,
      malsplitbinary_cursor_get_length,
      malsplitbinary_cursor_get_offset,
      malsplitbinary_cursor_assert,
      malsplitbinary_encoder_add_string_encoding_length,
      malsplitbinary_encoder_add_presence_flag_encoding_length,
      malsplitbinary_encoder_add_short_form_encoding_length,
      malsplitbinary_encoder_add_integer_encoding_length,
      malsplitbinary_encoder_add_identifier_encoding_length,
      malsplitbinary_encoder_add_uinteger_encoding_length,
      malsplitbinary_encoder_add_uri_encoding_length,
      malsplitbinary_encoder_add_time_encoding_length,
      malsplitbinary_encoder_add_uoctet_encoding_length,
      malsplitbinary_encoder_add_long_encoding_length,
      malsplitbinary_encoder_add_ushort_encoding_length,
      malsplitbinary_encoder_add_boolean_encoding_length,
      malsplitbinary_encoder_add_blob_encoding_length,
      malsplitbinary_encoder_add_list_size_encoding_length,
      malsplitbinary_encoder_add_small_enum_encoding_length,
      malsplitbinary_encoder_add_medium_enum_encoding_length,
      malsplitbinary_encoder_add_large_enum_encoding_length,
      malsplitbinary_encoder_add_duration_encoding_length,
      malsplitbinary_encoder_add_float_encoding_length,
      malsplitbinary_encoder_add_double_encoding_length,
      malsplitbinary_encoder_add_octet_encoding_length,
      malsplitbinary_encoder_add_short_encoding_length,
      malsplitbinary_encoder_add_ulong_encoding_length,
      malsplitbinary_encoder_add_finetime_encoding_length,
      malsplitbinary_encoder_add_attribute_tag_encoding_length,
      malsplitbinary_encoder_add_attribute_encoding_length,

      mal_entitykey_add_encoding_length_malbinary,
      mal_entityrequest_add_encoding_length_malbinary,
      mal_file_add_encoding_length_malbinary,
      mal_idbooleanpair_add_encoding_length_malbinary,
      mal_namedvalue_add_encoding_length_malbinary,
      mal_pair_add_encoding_length_malbinary,
      mal_subscription_add_encoding_length_malbinary,
      mal_updateheader_add_encoding_length_malbinary,

      mal_blob_list_add_encoding_length_malbinary,
      mal_boolean_list_add_encoding_length_malbinary,
      mal_double_list_add_encoding_length_malbinary,
      mal_duration_list_add_encoding_length_malbinary,
      mal_entitykey_list_add_encoding_length_malbinary,
      mal_entityrequest_list_add_encoding_length_malbinary,
      mal_file_list_add_encoding_length_malbinary,
      mal_finetime_list_add_encoding_length_malbinary,
      mal_float_list_add_encoding_length_malbinary,
      mal_idbooleanpair_list_add_encoding_length_malbinary,
      mal_identifier_list_add_encoding_length_malbinary,
      mal_integer_list_add_encoding_length_malbinary,
      mal_interactiontype_list_add_encoding_length_malbinary,
      mal_long_list_add_encoding_length_malbinary,
      mal_namedvalue_list_add_encoding_length_malbinary,
      mal_octet_list_add_encoding_length_malbinary,
      mal_pair_list_add_encoding_length_malbinary,
      mal_qoslevel_list_add_encoding_length_malbinary,
      mal_sessiontype_list_add_encoding_length_malbinary,
      mal_short_list_add_encoding_length_malbinary,
      mal_string_list_add_encoding_length_malbinary,
      mal_subscription_list_add_encoding_length_malbinary,
      mal_time_list_add_encoding_length_malbinary,
      mal_uinteger_list_add_encoding_length_malbinary,
      mal_ulong_list_add_encoding_length_malbinary,
      mal_uoctet_list_add_encoding_length_malbinary,
      mal_updateheader_list_add_encoding_length_malbinary,
      mal_updatetype_list_add_encoding_length_malbinary,
      mal_uri_list_add_encoding_length_malbinary,
      mal_ushort_list_add_encoding_length_malbinary,

      malsplitbinary_encoder_encode_string,
      malsplitbinary_encoder_encode_presence_flag,
      malsplitbinary_encoder_encode_short_form,
      malsplitbinary_encoder_encode_small_enum,
      malsplitbinary_encoder_encode_medium_enum,
      malsplitbinary_encoder_encode_large_enum,
      malsplitbinary_encoder_encode_integer,
      malsplitbinary_encoder_encode_list_size,
      malsplitbinary_encoder_encode_uri,
      malsplitbinary_encoder_encode_blob,
      malsplitbinary_encoder_encode_time,
      malsplitbinary_encoder_encode_uinteger,
      malsplitbinary_encoder_encode_identifier,
      malsplitbinary_encoder_encode_uoctet,
      malsplitbinary_encoder_encode_long,
      malsplitbinary_encoder_encode_ushort,
      malsplitbinary_encoder_encode_boolean,
      malbinary_write16,//TODO ?
      malbinary_write32,//TODO ?
      malbinary_write64,//TODO ?
      malsplitbinary_encoder_encode_duration,
      malsplitbinary_encoder_encode_float,
      malsplitbinary_encoder_encode_double,
      malsplitbinary_encoder_encode_octet,
      malsplitbinary_encoder_encode_short,
      malsplitbinary_encoder_encode_ulong,
      malsplitbinary_encoder_encode_finetime,
      malsplitbinary_encoder_encode_attribute,
      malsplitbinary_encoder_encode_attribute_tag,

      mal_entitykey_encode_malbinary,
      mal_entityrequest_encode_malbinary,
      mal_file_encode_malbinary,
      mal_idbooleanpair_encode_malbinary,
      mal_namedvalue_encode_malbinary,
      mal_pair_encode_malbinary,
      mal_subscription_encode_malbinary,
      mal_updateheader_encode_malbinary,

      mal_blob_list_encode_malbinary,
      mal_boolean_list_encode_malbinary,
      mal_double_list_encode_malbinary,
      mal_duration_list_encode_malbinary,
      mal_entitykey_list_encode_malbinary,
      mal_entityrequest_list_encode_malbinary,
      mal_file_list_encode_malbinary,
      mal_finetime_list_encode_malbinary,
      mal_float_list_encode_malbinary,
      mal_idbooleanpair_list_encode_malbinary,
      mal_identifier_list_encode_malbinary,
      mal_integer_list_encode_malbinary,
      mal_interactiontype_list_encode_malbinary,
      mal_long_list_encode_malbinary,
      mal_namedvalue_list_encode_malbinary,
      mal_octet_list_encode_malbinary,
      mal_pair_list_encode_malbinary,
      mal_qoslevel_list_encode_malbinary,
      mal_sessiontype_list_encode_malbinary,
      mal_short_list_encode_malbinary,
      mal_string_list_encode_malbinary,
      mal_subscription_list_encode_malbinary,
      mal_time_list_encode_malbinary,
      mal_uinteger_list_encode_malbinary,
      mal_ulong_list_encode_malbinary,
      mal_uoctet_list_encode_malbinary,
      mal_updateheader_list_encode_malbinary,
      mal_updatetype_list_encode_malbinary,
      mal_uri_list_encode_malbinary,
      mal_ushort_list_encode_malbinary);
}

void malsplitbinary_encoder_test(bool verbose) {
  printf(" * malsplitbinary_encoder: ");
  if (verbose)
    printf("\n");

//  @selftest
// ...
//  @end
  printf("OK\n");
}

