#include <pebble.h>
#include "main.h"

static uint8_t title_amt = 0;
static char** stop_titles;

void init_appmessage() {
	app_message_register_inbox_received(inbox_received_handler);
	app_message_register_inbox_dropped(inbox_dropped_callback);
	app_message_register_outbox_failed(outbox_failed_callback);
	app_message_register_outbox_sent(outbox_sent_callback);
	
	// Create buffers based on what we are sending/receiving
	int buffer_in = dict_calc_buffer_size(10, sizeof(char), sizeof(int32_t), sizeof(int32_t), sizeof(int32_t), sizeof(char), sizeof(int8_t), sizeof(int8_t), sizeof(int8_t), sizeof(int8_t), sizeof(int8_t), sizeof(int8_t), sizeof(int8_t), sizeof(int8_t), sizeof(int16_t));
	int buffer_out = dict_calc_buffer_size(1, sizeof(int32_t));
	app_message_open(buffer_in, buffer_out);
}

void inbox_received_handler(DictionaryIterator *iter, void *context) {
	Tuple *stop_title_tup = dict_find(iter, KEY_STOP_ROUTES);
	Tuple *destination_tup = dict_find(iter, KEY_STOP_DESTS);
	Tuple *arrival_time_tup = dict_find(iter, KEY_ARRIVAL_TIMES);
	
	if (stop_title_tup) {
		APP_LOG(APP_LOG_LEVEL_INFO, "Stops: %s", destination_tup->value->cstring);
	}
	
	if (destination_tup) {
		APP_LOG(APP_LOG_LEVEL_INFO, "Destinations: %s", destination_tup->value->cstring);
	}
	
	if (arrival_time_tup) {
		APP_LOG(APP_LOG_LEVEL_INFO, "Arrival times: %s", arrival_time_tup->value->cstring);
	}
	
	menu_layer_reload_data(menu_layer);
}

void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped, %d", reason);
}

void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed");
}

void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}