#ifndef __TESTAREA_TESTSERVICE_TESTFULLCOMPOSITE_H_INCLUDED__
#define __TESTAREA_TESTSERVICE_TESTFULLCOMPOSITE_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


// fields accessors for composite testarea_testservice_testfullcomposite
mal_boolean_t testarea_testservice_testfullcomposite_get_boolfield(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_set_boolfield(testarea_testservice_testfullcomposite_t * self, mal_boolean_t boolfield);
bool testarea_testservice_testfullcomposite_intfield_is_present(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_intfield_set_present(testarea_testservice_testfullcomposite_t * self, bool is_present);
mal_integer_t testarea_testservice_testfullcomposite_get_intfield(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_set_intfield(testarea_testservice_testfullcomposite_t * self, mal_integer_t intfield);
mal_string_t * testarea_testservice_testfullcomposite_get_stringfield(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_set_stringfield(testarea_testservice_testfullcomposite_t * self, mal_string_t * stringfield);
mal_blob_t * testarea_testservice_testfullcomposite_get_blobfield(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_set_blobfield(testarea_testservice_testfullcomposite_t * self, mal_blob_t * blobfield);
testarea_testenumeration_t testarea_testservice_testfullcomposite_get_enumfield(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_set_enumfield(testarea_testservice_testfullcomposite_t * self, testarea_testenumeration_t enumfield);
testarea_testservice_testcomposite_t * testarea_testservice_testfullcomposite_get_compfield(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_set_compfield(testarea_testservice_testfullcomposite_t * self, testarea_testservice_testcomposite_t * compfield);
mal_boolean_list_t * testarea_testservice_testfullcomposite_get_boollistfield(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_set_boollistfield(testarea_testservice_testfullcomposite_t * self, mal_boolean_list_t * boollistfield);
mal_integer_list_t * testarea_testservice_testfullcomposite_get_intlistfield(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_set_intlistfield(testarea_testservice_testfullcomposite_t * self, mal_integer_list_t * intlistfield);
mal_string_list_t * testarea_testservice_testfullcomposite_get_stringlistfield(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_set_stringlistfield(testarea_testservice_testfullcomposite_t * self, mal_string_list_t * stringlistfield);
mal_blob_list_t * testarea_testservice_testfullcomposite_get_bloblistfield(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_set_bloblistfield(testarea_testservice_testfullcomposite_t * self, mal_blob_list_t * bloblistfield);
testarea_testenumeration_list_t * testarea_testservice_testfullcomposite_get_enumlistfield(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_set_enumlistfield(testarea_testservice_testfullcomposite_t * self, testarea_testenumeration_list_t * enumlistfield);
testarea_testservice_testcomposite_list_t * testarea_testservice_testfullcomposite_get_complistfield(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_set_complistfield(testarea_testservice_testfullcomposite_t * self, testarea_testservice_testcomposite_list_t * complistfield);
unsigned char testarea_testservice_testfullcomposite_attributefield_get_attribute_tag(testarea_testservice_testfullcomposite_t * self);
void testarea_testservice_testfullcomposite_attributefield_set_attribute_tag(testarea_testservice_testfullcomposite_t * self, unsigned char attribute_tag);

// default constructor
testarea_testservice_testfullcomposite_t * testarea_testservice_testfullcomposite_new(void);

// encoding functions related to transport malbinary
int testarea_testservice_testfullcomposite_add_encoding_length_malbinary(testarea_testservice_testfullcomposite_t * self, mal_encoder_t * encoder, void * cursor);
int testarea_testservice_testfullcomposite_encode_malbinary(testarea_testservice_testfullcomposite_t * self, mal_encoder_t * encoder, void * cursor);
int testarea_testservice_testfullcomposite_decode_malbinary(testarea_testservice_testfullcomposite_t * self, mal_decoder_t * decoder, void * cursor);

// destructor
void testarea_testservice_testfullcomposite_destroy(testarea_testservice_testfullcomposite_t ** self_p);

// test function
void testarea_testservice_testfullcomposite_test(bool verbose);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __TESTAREA_TESTSERVICE_TESTFULLCOMPOSITE_H_INCLUDED__
