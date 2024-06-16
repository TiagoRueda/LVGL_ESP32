#include "http.h"

static void event_handler(void *arg, esp_event_base_t event_base,
                          int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY)
        {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(HTAG, "retry to connect to the AP");
        }
        else
        {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(HTAG, "connect to the AP fail");
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(HTAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void connect_wifi(void)
{
    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .password = EXAMPLE_ESP_WIFI_PASS,
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(HTAG, "wifi_init_sta finished.");

    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);

    if (bits & WIFI_CONNECTED_BIT)
    {
        ESP_LOGI(HTAG, "connected to ap SSID:%s password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    }
    else if (bits & WIFI_FAIL_BIT)
    {
        ESP_LOGI(HTAG, "Failed to connect to SSID:%s, password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    }
    else
    {
        ESP_LOGE(HTAG, "UNEXPECTED EVENT");
    }
    vEventGroupDelete(s_wifi_event_group);
}

esp_err_t send_web_page(httpd_req_t *req)
{
    if (web >= 1)
        response = httpd_resp_send(req, main_resp, HTTPD_RESP_USE_STRLEN);
    else
    	response = httpd_resp_send(req, wait_resp, HTTPD_RESP_USE_STRLEN);
    return response;
}
esp_err_t get_req_handler(httpd_req_t *req)
{
    return send_web_page(req);
}

esp_err_t down_handler(httpd_req_t *req)
{
    ctrl_http = 1;
    char status_atual [] = "Down";
    sprintf(main_resp, "%s%s%s", main1_resp, status_atual, main2_resp);
    web = ctrl_http;
    return send_web_page(req);
}

esp_err_t up_handler(httpd_req_t *req)
{
    ctrl_http = 2;
    char status_atual [] = "Up";
    sprintf(main_resp, "%s%s%s", main1_resp, status_atual, main2_resp);
    web = ctrl_http;
    return send_web_page(req);
}

esp_err_t back_handler(httpd_req_t *req)
{
    ctrl_http = 3;
    char status_atual [] = "Back";
    sprintf(main_resp, "%s%s%s", main1_resp, status_atual, main2_resp);
    web = ctrl_http;
    return send_web_page(req);
}

esp_err_t enter_handler(httpd_req_t *req)
{
    ctrl_http = 4;
    char status_atual [] = "Enter";
    sprintf(main_resp, "%s%s%s", main1_resp, status_atual, main2_resp);
    web = ctrl_http;
    return send_web_page(req);
}

httpd_uri_t uri_get = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = get_req_handler,
    .user_ctx = NULL};

httpd_uri_t uri_down = {
    .uri = "/down",
    .method = HTTP_GET,
    .handler = down_handler,
    .user_ctx = NULL};

httpd_uri_t uri_up = {
    .uri = "/up",
    .method = HTTP_GET,
    .handler = up_handler,
    .user_ctx = NULL};

httpd_uri_t uri_back = {
    .uri = "/back",
    .method = HTTP_GET,
    .handler = back_handler,
    .user_ctx = NULL};

httpd_uri_t uri_enter = {
    .uri = "/enter",
    .method = HTTP_GET,
    .handler = enter_handler,
    .user_ctx = NULL};

httpd_handle_t setup_server(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_register_uri_handler(server, &uri_get);
        httpd_register_uri_handler(server, &uri_down);
        httpd_register_uri_handler(server, &uri_up);
        httpd_register_uri_handler(server, &uri_back);
        httpd_register_uri_handler(server, &uri_enter);
    }

    return server;
}

void http_main()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(HTAG, "ESP_WIFI_MODE_STA");
    connect_wifi();

    web = 0;

    setup_server();
}
