#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>
#include <microhttpd.h>
#include <pigpio.h>

#define PIN_1 26
#define PIN_2 20
#define PIN_3 21
#define HTTP_PORT 8080

static enum MHD_Result serve_html(struct MHD_Connection *connection)
{
	const char *page = "<!DOCTYPE html>"
					   "<html>"
					   "<head>"
					   "<title>Pi Summoner</title>"
					   "<style>"
					   "body { font-family: Arial, sans-serif; background-color: #f0f0f0; text-align: center; padding-top: 50px; }"
					   ".button-grid { display: grid; grid-template-columns: auto auto; justify-content: center; gap: 10px; }"
					   "button { background-color: #4CAF50; color: white; padding: 15px 32px; text-align: center; text-decoration: none;"
					   "display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; border: none; border-radius: 4px; }"
					   "button:hover { background-color: #45a049; }"
					   "</style>"
					   "</head>"
					   "<body>"
					   "<h2>Pi Summoner</h2>"
					   "<div class=\"button-grid\">"
					   "<button onclick=\"fetch('/1')\">Pin 26</button>"
					   "<button onclick=\"fetch('/long_1')\">Long press Pin 26</button>"
					   "<button onclick=\"fetch('/2')\">Pin 20</button>"
					   "<button onclick=\"fetch('/long_2')\">Long press Pin 20</button>"
					   "<button onclick=\"fetch('/3')\">Pin 21</button>"
					   "<button onclick=\"fetch('/long_3')\">Long press Pin 21</button>"
					   "</div>"
					   "</body>"
					   "</html>";

	struct MHD_Response *response;
	response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
	int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
	MHD_destroy_response(response);

	return ret;
}

static enum MHD_Result handle_request(void *cls, struct MHD_Connection *connection,
									  const char *url, const char *method,
									  const char *version, const char *upload_data,
									  size_t *upload_data_size, void **ptr)
{
	int pin;
	bool long_press = false;

	syslog(LOG_INFO, "Received request: %s", url);

	if (strcmp(url, "/") == 0)
		return serve_html(connection);

	if (strcmp(url, "/1") == 0)
		pin = PIN_1;
	else if (strcmp(url, "/2") == 0)
		pin = PIN_2;
	else if (strcmp(url, "/3") == 0)
		pin = PIN_3;
	else if (strcmp(url, "/long_1") == 0)
	{
		pin = PIN_1;
		long_press = true;
	}
	else if (strcmp(url, "/long_2") == 0)
	{
		pin = PIN_2;
		long_press = true;
	}
	else if (strcmp(url, "/long_3") == 0)
	{
		pin = PIN_3;
		long_press = true;
	}
	else
	{
		syslog(LOG_ERR, "Invalid request: %s", url);
		const char *errorPage = "Error: Invalid request";
		struct MHD_Response *response = MHD_create_response_from_buffer(strlen(errorPage), (void *)errorPage, MHD_RESPMEM_PERSISTENT);
		int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
		MHD_destroy_response(response);
		return ret;
	}

	// Turn the GPIO pin on for 1 second to turn on/off the PC
	gpioWrite(pin, 1);

	// Long press for force shutdown
	if (long_press)
	{
		time_sleep(8);
	}
	else
	{
		time_sleep(1);
	}

	gpioWrite(pin, 0);

	const char *page = "OK";
	struct MHD_Response *response;
	response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
	int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
	MHD_destroy_response(response);

	return ret;
}

int main()
{
	openlog("PiSummoner", LOG_PID | LOG_CONS, LOG_USER);

	if (gpioInitialise() < 0)
	{
		fprintf(stderr, "Failed to initialize the GPIO\n");
		return 1;
	}

	gpioSetMode(PIN_1, PI_OUTPUT);
	gpioSetMode(PIN_2, PI_OUTPUT);
	gpioSetMode(PIN_3, PI_OUTPUT);

	struct MHD_Daemon *daemon;
	daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, HTTP_PORT, NULL, NULL, &handle_request, NULL, MHD_OPTION_END);

	if (daemon == NULL)
	{
		fprintf(stderr, "Failed to start the web service\n");
		return 1;
	}

	getchar();

	MHD_stop_daemon(daemon);
	gpioTerminate();
	closelog();
	return 0;
}
