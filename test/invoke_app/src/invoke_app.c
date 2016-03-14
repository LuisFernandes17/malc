/* */
#include "invoke_app.h"

//  --------------------------------------------------------------------------
//  Selftest
int invoke_app_create_provider(
    bool verbose,
    mal_ctx_t *mal_ctx,
    mal_uri_t *provider_uri,
    malbinary_encoder_t *encoder,
    malbinary_decoder_t *decoder) {
  int rc = 0;

  printf(" * invoke_app_create_provider: %s\n", provider_uri);

  invoke_app_myprovider_t *provider = invoke_app_myprovider_new(MALBINARY_FORMAT_CODE, encoder, decoder);

//  mal_actor_t *provider_actor =
  mal_actor_new(
      mal_ctx,
      provider_uri, provider,
      invoke_app_myprovider_initialize, invoke_app_myprovider_finalize);

  return rc;
}

int invoke_app_create_consumer(
    bool verbose,
    mal_ctx_t *mal_ctx,
    mal_uri_t *provider_uri,
    malbinary_encoder_t *encoder,
    malbinary_decoder_t *decoder) {
  int rc = 0;

  printf(" * invoke_app_create_consumer: \n");

  mal_blob_t *authentication_id = mal_blob_new(0);
  mal_qoslevel_t qoslevel = MAL_QOSLEVEL_ASSURED;
  mal_uinteger_t priority = 4;
  mal_identifier_list_t *domain = mal_identifier_list_new(0);
  mal_identifier_t *network_zone = mal_identifier_new("Network Zone");
  mal_sessiontype_t session = MAL_SESSIONTYPE_LIVE;
  mal_identifier_t *session_name = mal_identifier_new("LIVE");

  invoke_app_myconsumer_t *consumer = invoke_app_myconsumer_new(provider_uri,
      authentication_id, qoslevel, priority, domain, network_zone, session,
      session_name, MALBINARY_FORMAT_CODE, encoder, decoder);

  mal_uri_t *consumer_uri = mal_ctx_create_uri(mal_ctx, "invoke_app/myconsumer");
  printf("invoke_app: consumer URI: %s\n", consumer_uri);

//  mal_actor_t *consumer_actor =
  mal_actor_new(
      mal_ctx,
      consumer_uri, consumer,
      invoke_app_myconsumer_initialize, invoke_app_myconsumer_finalize);

  return rc;
}

void invoke_app_test(bool verbose) {
  printf(" * invoke_app_test: \n");

  //  @selftest
  mal_ctx_t *mal_ctx = mal_ctx_new();

  malbinary_encoder_t *encoder = malbinary_encoder_new(false, true);
  malbinary_decoder_t *decoder = malbinary_decoder_new(false, true);

  // All the MAL header fields are passed
  malzmq_header_t *malzmq_header = malzmq_header_new(NULL, true, 0, true, NULL, NULL, NULL, NULL);

  // This test uses the same encoding configuration at the MAL/ZMQ transport
  // level (MAL header encoding) and at the application
  // level (MAL message body encoding)
  malzmq_ctx_t *malzmq_ctx = malzmq_ctx_new(
      mal_ctx,
      NULL,                 // Use default transformation of MAL URI to ZMQ URI
      "localhost", "6666",
		  malzmq_header,
		  encoder, decoder,
		  true);

  mal_uri_t *provider_uri = mal_ctx_create_uri(mal_ctx, "invoke_app/myprovider");

  invoke_app_create_provider(verbose, mal_ctx, provider_uri, encoder, decoder);
  invoke_app_create_consumer(verbose, mal_ctx, provider_uri, encoder, decoder);

  //  @end
  printf("OK\n");

  // Start blocks until interrupted (see zloop).
  malzmq_ctx_start(malzmq_ctx);

  mal_ctx_destroy(&mal_ctx);
  malzmq_ctx_destroy(&malzmq_ctx);
}
