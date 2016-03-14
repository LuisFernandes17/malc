/* */
#include "pubsub_app.h"

// state
struct _pubsub_app_mysubscriber_t {
  mal_uri_t *broker_uri;
  mal_blob_t *authentication_id;
  mal_qoslevel_t qoslevel;
  mal_uinteger_t priority;
  mal_identifier_list_t *domain;
  mal_identifier_t *network_zone;
  mal_sessiontype_t session;
  mal_identifier_t *session_name;
  int encoding_format_code;
  void *encoder;
  void *decoder;
};

pubsub_app_mysubscriber_t *pubsub_app_mysubscriber_new(mal_uri_t *broker_uri,
    mal_blob_t *authentication_id, mal_qoslevel_t qoslevel,
    mal_uinteger_t priority, mal_identifier_list_t *domain,
    mal_identifier_t *network_zone, mal_sessiontype_t session,
    mal_identifier_t *session_name, int encoding_format_code, void *encoder,
    void *decoder) {
  pubsub_app_mysubscriber_t *self = (pubsub_app_mysubscriber_t *) malloc(
      sizeof(pubsub_app_mysubscriber_t));
  if (!self)
    return NULL;

  self->broker_uri = broker_uri;
  self->authentication_id = authentication_id;
  self->qoslevel = qoslevel;
  self->priority = priority;
  self->domain = domain;
  self->network_zone = network_zone;
  self->session = session;
  self->session_name = session_name;
  self->encoding_format_code = encoding_format_code;
  self->encoder = encoder;
  self->decoder = decoder;
  return self;
}

int pubsub_app_mysubscriber_get_encoding_format_code(
    pubsub_app_mysubscriber_t *self) {
  return self->encoding_format_code;
}

void *pubsub_app_mysubscriber_get_encoder(pubsub_app_mysubscriber_t *self) {
  return self->encoder;
}

void *pubsub_app_mysubscriber_get_decoder(pubsub_app_mysubscriber_t *self) {
  return self->decoder;
}

mal_uri_t *pubsub_app_mysubscriber_get_broker_uri(
    pubsub_app_mysubscriber_t *self) {
  return self->broker_uri;
}

mal_blob_t *pubsub_app_mysubscriber_get_authentication_id(
    pubsub_app_mysubscriber_t *self) {
  return self->authentication_id;
}

mal_identifier_list_t *pubsub_app_mysubscriber_get_domain(
    pubsub_app_mysubscriber_t *self) {
  return self->domain;
}

mal_identifier_t *pubsub_app_mysubscriber_get_network_zone(
    pubsub_app_mysubscriber_t *self) {
  return self->network_zone;
}

mal_uinteger_t pubsub_app_mysubscriber_get_priority(
    pubsub_app_mysubscriber_t *self) {
  return self->priority;
}

mal_qoslevel_t pubsub_app_mysubscriber_get_qoslevel(
    pubsub_app_mysubscriber_t *self) {
  return self->qoslevel;
}

mal_sessiontype_t pubsub_app_mysubscriber_get_session(
    pubsub_app_mysubscriber_t *self) {
  return self->session;
}

mal_identifier_t *pubsub_app_mysubscriber_get_session_name(
    pubsub_app_mysubscriber_t *self) {
  return self->session_name;
}

int pubsub_app_mysubscriber_initialize(void *self, mal_actor_t *mal_actor) {
  int rc = 0;

  printf("### pubsub_app_mysubscriber_initialize\n");
  rc = mal_routing_register_consumer_pubsub_handler(
      mal_actor_get_router(mal_actor),
      TESTAREA_AREA_NUMBER,
      TESTAREA_AREA_VERSION,
      TESTAREA_TESTSERVICE_SERVICE_NUMBER,
      TESTAREA_TESTSERVICE_TESTMONITOR_OPERATION_NUMBER,
      pubsub_app_mysubscriber_testregister_ack,
      pubsub_app_mysubscriber_testderegister_ack,
      pubsub_app_mysubscriber_testnotify);

  pubsub_app_mysubscriber_t *subscriber = (pubsub_app_mysubscriber_t *) self;

  // initiate a SUBSCRIBE interaction
  mal_uri_t *broker_uri = subscriber->broker_uri;

  mal_subscription_t *subscription = mal_subscription_new();
  mal_identifier_t *subscriptionid = mal_identifier_new("test-sub");
  mal_subscription_set_subscriptionid(subscription, subscriptionid);
  mal_entityrequest_list_t *entities = mal_entityrequest_list_new(0);
  // TODO: add some EntityRequests
  /* 
  mal_entityrequest_t *entityrequest = mal_entityrequest_new();
  mal_identifier_list_t *identifiers = mal_identifier_list_new(1);
  mal_identifier_t **identifiers_content = mal_identifier_list_get_content(identifiers);
  identifiers_content[0] = mal_identifier_new("A.B.C");
  entityrequest->subdomain = identifiers;
  mal_entityrequest_t **entityrequest_content = mal_entityrequest_list_get_content(entities);
  entityrequest_content[0] = entityrequest;
  mal_identifier_list_print(identifiers);
  */
  mal_subscription_set_entities(subscription, entities);

  unsigned int body_length = 0;

  rc = mal_register_add_encoding_length(subscriber->encoding_format_code,
      subscriber->encoder, subscription, &body_length);
  if (rc < 0)
    return rc;

  mal_message_t *register_message = mal_message_new(
      subscriber->authentication_id, subscriber->qoslevel, subscriber->priority,
      subscriber->domain, subscriber->network_zone, subscriber->session,
      subscriber->session_name, body_length);

  unsigned int offset = mal_message_get_body_offset(register_message);
  char *bytes = mal_message_get_body(register_message);

  rc = mal_register_encode(subscriber->encoding_format_code, bytes, &offset, subscriber->encoder, subscription);
  assert(rc == 0);

  printf("=== register send... %s\n", broker_uri);
  rc = testarea_testservice_testmonitor_register(mal_actor_get_mal_endpoint(mal_actor),
      register_message, broker_uri);
  if (rc < 0)
    return rc;

  mal_subscription_destroy(&subscription);

  return rc;
}

int pubsub_app_mysubscriber_finalize(void *self, mal_actor_t *mal_actor) {
  int rc = 0;
  // ...
  return rc;
}

int pubsub_app_mysubscriber_testregister_ack(void *self, mal_ctx_t *mal_ctx,
    mal_endpoint_t *mal_endpoint, mal_message_t *message) {
  int rc = 0;
  printf("******** pubsub_app_mysubscriber_register_ack\n");
  return rc;
}

int pubsub_app_mysubscriber_testderegister_ack(void *self, mal_ctx_t *mal_ctx,
    mal_endpoint_t *mal_endpoint, mal_message_t *message) {
  int rc = 0;
  printf("******** pubsub_app_mysubscriber_deregister_ack\n");
  return rc;
}

int pubsub_app_mysubscriber_testnotify(void *self, mal_ctx_t *mal_ctx,
    mal_endpoint_t *mal_endpoint, mal_message_t *message) {
  int rc = 0;
  pubsub_app_mysubscriber_t *subscriber = (pubsub_app_mysubscriber_t *) self;

  printf("#### pubsub_app_mysubscriber_testnotify: %d, %d\n",
      mal_message_get_interaction_stage(message),
      mal_message_is_error_message(message));

  // Get response parameter.
  unsigned int offset = mal_message_get_body_offset(message);
  char *bytes = mal_message_get_body(message);

  /*
  mal_identifier_t *subscriptionid;
  rc = mal_notify_decode_subscriptionid(subscriber->encoding_format_code, bytes,
      &offset, subscriber->decoder, &subscriptionid);
  if (rc < 0)
    return rc;
  */

  mal_updateheader_list_t *updateheader_list;
  rc = mal_publish_decode_updateheader_list(subscriber->encoding_format_code,
      bytes, &offset, subscriber->decoder, &updateheader_list);
  if (rc < 0)
    return rc;

  unsigned int uh_count = mal_updateheader_list_get_element_count(updateheader_list);
  printf("== updateheader_list \n\tcount = %d\n", uh_count);
  assert(uh_count > 0);
  mal_updateheader_t **updateheaders = mal_updateheader_list_get_content(updateheader_list);
  printf("\tsrc_uri = %s\n", mal_updateheader_get_source_uri(updateheaders[uh_count-1]));
  printf("\tfirstsubkey = %s\n\n", mal_entitykey_get_firstsubkey(mal_updateheader_get_entitykey(updateheaders[uh_count-1])));

  printf("== testupdate_list\n");
  testarea_testservice_testupdate_list_t *parameter_0;
  rc = testarea_testservice_testmonitor_update_decode_0(subscriber->encoding_format_code,
      bytes, &offset, subscriber->decoder, &parameter_0);
  assert(rc == 0);

  // process the update list
  unsigned int count = testarea_testservice_testupdate_list_get_element_count(parameter_0);
  printf("\tcount = %d\n", count);

  testarea_testservice_testupdate_t ** content_list = testarea_testservice_testupdate_list_get_content(parameter_0);
  mal_string_t *string = testarea_testservice_testupdate_get_stringfield(content_list[0]);
  printf("\tcontent_0 = %s\n\n", string);

  /*
  mal_identifier_destroy(&subscriptionid);
  */
  mal_updateheader_list_destroy(&updateheader_list);
  printf("destroy parameter_0\n");
  testarea_testservice_testupdate_list_destroy(&parameter_0);
  printf("destroy MAL result message\n");
  mal_message_destroy(&message, mal_ctx);

  printf("Subscriber done.\n");
  return rc;
}

void pubsub_app_mysubscriber_test(bool verbose) {
  printf(" * pubsub_app_mysubscriber_test: ");
  if (verbose)
    printf("\n");

  //  @selftest
  // ...
  //  @end
  printf("OK\n");
}
