#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <microhttpd.h>
#include <pigpio.h>

#define PIN_1 26
#define PIN_2 20
#define PIN_3 21
#define HTTP_PORT 8080

static enum MHD_Result serve_html(struct MHD_Connection *connection) {
    const char *page = "<!DOCTYPE html>"
                       "<html>"
                       "<head><title>Raspberry Pi Controller</title></head>"
                       "<body>"
                       "<button onclick=\"fetch('/1')\">Pin 26</button>"
                       "<button onclick=\"fetch('/2')\">Pin 20</button>"
                       "<button onclick=\"fetch('/3')\">Pin 21</button>"
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

	if(strcmp(url, "/") == 0)
		return serve_html(connection);

	if (strcmp(url, "/1") == 0)
		pin = PIN_1;
	else if(strcmp(url, "/2") == 0)
		pin = PIN_2;
	else if(strcmp(url, "/3") == 0)
		pin = PIN_3;
	else
		return MHD_NO;
	
	//Turn the GPIO pin on for 1 second to turn on/off the PC
	gpioWrite(pin, 1);
	time_sleep(1);
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
	if(gpioInitialise() < 0)
	{
		fprintf(stderr, "Failed to initialize the GPIO\n");
		return 1;
	}

	gpioSetMode(PIN_1, PI_OUTPUT);
	gpioSetMode(PIN_2, PI_OUTPUT);
	gpioSetMode(PIN_3, PI_OUTPUT);

	struct MHD_Daemon *daemon;
	daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, HTTP_PORT, NULL, NULL, &handle_request, NULL, MHD_OPTION_END);

	if(daemon == NULL)
	{
		fprintf(stderr, "Failed to start the web service\n");
		return 1;
	}

	getchar();

	MHD_stop_daemon(daemon);
	gpioTerminate();
	return 0;
}
