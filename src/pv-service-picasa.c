#include <libsoup/soup.h>

#define PVMOD_NAME "PICASA"
#include "pv-types.h"

#define GOOGLE_ACCOUNT_URL "http://www.google.com/accounts/"
#define PICASA_AUTH_URL  "https://www.google.com/accounts/ClientLogin"
#define PICASA_SERVICE_NAME "lh2"
#define PICASA_AUTH_MIMETYPE "application/x-www-form-urlencoded"
#define MYGROUP "PICASA"

static void picasa_login_cb(SoupSession *session, SoupMessage *msg, gpointer data) {
  pvservice_t *pvs = (pvservice_t *)data;
  GKeyFile *kf = NULL;
  gchar *auth_token;
  gchar *body = NULL;
  gint len = msg->response_body->length+strlen(MYGROUP) + 3;

  DD("status = %d\n", msg->status_code);

  pvs->is_login = FALSE;
  kf = g_key_file_new();

  body = g_malloc0(len);
  g_sprintf(body, "["MYGROUP"]\n%s", msg->response_body->data);
  g_key_file_load_from_data(kf, body, len, G_KEY_FILE_NONE, NULL);

  if(msg->status_code == 200) {
    auth_token = g_key_file_get_value(kf, MYGROUP, "Auth", NULL);
    DD("token = %s\n", auth_token);
    pvs->is_login = TRUE;
  } else {
    gchar *error = NULL;

    error = g_key_file_get_value(kf, MYGROUP, "Error", NULL);
    if(pvc->login_error) g_free(pvc->login_error);
    pvc->login_error = g_strdup(error);

    if(strcmp(error, "CaptchaRequired") == 0) {
      gchar *url = NULL, *captcha_token = NULL, *captcha_url = NULL;
      url = g_key_file_get_value(kf, MYGROUP, "Url", NULL);
      if(pvc->login_error) g_free(pvc->login_error);
      captcha_token = g_key_file_get_value(kf, MYGROUP, "CaptchaToken", NULL);
      captcha_url = g_key_file_get_value(kf, MYGROUP, "CaptchaUrl", NULL);
    } else {
    }
  }

  g_key_file_free(kf);
}

gint pv_service_picasa_login(pvcore_t *pvc, gchar *username, gchar *password, gchar *captcha) {
  SoupMessage *msg = NULL;
  gchar *body = NULL;

  body = g_strdup_printf("accountType=HOSTED_OR_GOOGLE&Email=%s&Passwd=%s&service=%s&source=soup-demo", username, password, PICASA_SERVICE_NAME, pvc->agent);
  msg = soup_message_new("POST", PICASA_AUTH_URL);
  soup_message_set_request(msg, PICASA_AUTH_MIMETYPE, SOUP_MEMORY_COPY, body, strlen(body));
  soup_session_queue_message(session, msg, picasa_login_cb, pvc);

  return 0;
}

pm_network_t * pn_startup(gchar *email, gchar *passwd) {
  pm_network_t *pn = NULL;

  pn = g_new0(1, sizeof(pm_network_t));
  pn->ss = soup_session_async_new_with_options(NULL);
  pn->email = g_strdup(email);
  pn->passwd = g_strdup(passwd);
}

gint pn_client_login(pm_network_t *pn, client_login_cb_t logincb) {
  gchar *body = NULL, *url = NULL;
  SoupMessage *msg = NULL;

  body = g_strdup_printf("accountType=HOSTED_OR_GOOGLE&Email=%s&Passwd=%s&service=%s&source=%s", pn->email, pn->passwd, PM_SERVICE_NAME, PM_CLIENT_NAME);
  msg = soup_message_new("POST", PM_AUTH_URL);
  soup_message_set_request (msg, "application/x-www-form-urlencoded",SOUP_MEMORY_COPY, body, strlen (body));
  soup_session_send_message (pn->ss, msg);
}

void pn_shutdown(pm_network_t *pn) {
  if(pn) {
    if(pn->email)
      g_free(pn->email);
    if(pn->passwd)
      g_free(pn->passwd);
    if(pn->ss)
      g_object_unref(pn->ss);

    g_free(pn);
  }
}


