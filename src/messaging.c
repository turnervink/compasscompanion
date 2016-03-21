#include <pebble.h>
#include "main.h"

static uint8_t title_amt = 0;
static char** stop_titles;

const char* STOP_NAMES[5] = {};
int tot_stops;

const char* DESTS[5] = {};
const char* TIMES[5] = {};

void init_appmessage() {
	app_message_register_inbox_received(inbox_received_handler);
	app_message_register_inbox_dropped(inbox_dropped_callback);
	app_message_register_outbox_failed(outbox_failed_callback);
	app_message_register_outbox_sent(outbox_sent_callback);
	
	// Create buffers based on what we are sending/receiving
	int buffer_in = dict_calc_buffer_size(15, 25);
	int buffer_out = dict_calc_buffer_size(1, sizeof(int32_t));
	app_message_open(buffer_in, buffer_out);
}

void inbox_received_handler(DictionaryIterator *iter, void *context) {
	Tuple *stop_title_tup = dict_find(iter, KEY_STOP_ROUTES);
	Tuple *destination_tup = dict_find(iter, KEY_STOP_DESTS);
	Tuple *arrival_time_tup = dict_find(iter, KEY_ARRIVAL_TIMES);
	Tuple *number_of_stops_tup = dict_find(iter, KEY_NUM_OF_STOPS);
	
	if (stop_title_tup) {
		APP_LOG(APP_LOG_LEVEL_INFO, "Stops: %s", destination_tup->value->cstring);
	}
	
	if (destination_tup) {
		APP_LOG(APP_LOG_LEVEL_INFO, "Destinations: %s", destination_tup->value->cstring);
	}
	
	if (arrival_time_tup) {
		APP_LOG(APP_LOG_LEVEL_INFO, "Arrival times: %s", arrival_time_tup->value->cstring);
	}
	
	//int number_of_stops;
	if (number_of_stops_tup) {
		APP_LOG(APP_LOG_LEVEL_INFO, "Number of stops: %d", number_of_stops_tup->value->int8);
		//number_of_stops = number_of_stops_tup->value->int8;
	}
	
	Tuple *routes0 = dict_find(iter, KEY_ROUTE_0);
	Tuple *routes1 = dict_find(iter, KEY_ROUTE_1);
	Tuple *routes2 = dict_find(iter, KEY_ROUTE_2);
	Tuple *routes3 = dict_find(iter, KEY_ROUTE_3);
	Tuple *routes4 = dict_find(iter, KEY_ROUTE_4);
	
	Tuple *dests0 = dict_find(iter, KEY_DEST_0);
	Tuple *dests1 = dict_find(iter, KEY_DEST_1);
	Tuple *dests2 = dict_find(iter, KEY_DEST_2);
	Tuple *dests3 = dict_find(iter, KEY_DEST_3);
	Tuple *dests4 = dict_find(iter, KEY_DEST_4);
	
	Tuple *times0 = dict_find(iter, KEY_TIME_0);
	Tuple *times1 = dict_find(iter, KEY_TIME_1);
	Tuple *times2 = dict_find(iter, KEY_TIME_2);
	Tuple *times3 = dict_find(iter, KEY_TIME_3);
	Tuple *times4 = dict_find(iter, KEY_TIME_4);
	
	if (routes0) {
		APP_LOG(APP_LOG_LEVEL_INFO, "routes0: %s", routes0->value->cstring);
		STOP_NAMES[0] = routes0->value->cstring;
		tot_stops = tot_stops + 1;
	}
	
	if (routes1) {
		APP_LOG(APP_LOG_LEVEL_INFO, "routes1: %s", routes1->value->cstring);
		STOP_NAMES[1] = routes1->value->cstring;
		tot_stops = tot_stops + 1;
	}
	
	if (routes2) {
		APP_LOG(APP_LOG_LEVEL_INFO, "routes2: %s", routes2->value->cstring);
		STOP_NAMES[2] = routes2->value->cstring;
		tot_stops = tot_stops + 1;
	}
	
	if (routes3) {
		APP_LOG(APP_LOG_LEVEL_INFO, "routes3: %s", routes3->value->cstring);
		STOP_NAMES[3] = routes3->value->cstring;
		tot_stops = tot_stops + 1;
	}
	
	if (routes4) {
		APP_LOG(APP_LOG_LEVEL_INFO, "routes4: %s", routes4->value->cstring);
		STOP_NAMES[4] = routes4->value->cstring;
		tot_stops = tot_stops + 1;
	}
	
	
	
	if (dests0) {
		APP_LOG(APP_LOG_LEVEL_INFO, "dests0: %s", dests0->value->cstring);
		DESTS[0] = dests0->value->cstring;
	}
	
	if (dests1) {
		APP_LOG(APP_LOG_LEVEL_INFO, "dests1: %s", dests1->value->cstring);
		DESTS[1] = dests1->value->cstring;
	}
	
	if (dests2) {
		APP_LOG(APP_LOG_LEVEL_INFO, "dests2: %s", dests2->value->cstring);
		DESTS[2] = dests2->value->cstring;
	}
	
	if (dests3) {
		APP_LOG(APP_LOG_LEVEL_INFO, "dests3: %s", dests3->value->cstring);
		DESTS[3] = dests3->value->cstring;
	}
	
	if (dests4) {
		APP_LOG(APP_LOG_LEVEL_INFO, "dests4: %s", dests4->value->cstring);
		DESTS[4] = dests4->value->cstring;
	}
	
	
	
	
	if (times0) {
		APP_LOG(APP_LOG_LEVEL_INFO, "times0: %s", times0->value->cstring);
		TIMES[0] = times0->value->cstring;
	}
	
	if (times1) {
		APP_LOG(APP_LOG_LEVEL_INFO, "times1: %s", times1->value->cstring);
		TIMES[1] = times1->value->cstring;
	}
	
	if (times2) {
		APP_LOG(APP_LOG_LEVEL_INFO, "times2: %s", times2->value->cstring);
		TIMES[2] = times2->value->cstring;
	}
	
	if (times3) {
		APP_LOG(APP_LOG_LEVEL_INFO, "times3: %s", times3->value->cstring);
		TIMES[3] = times3->value->cstring;
	}
	
	if (times4) {
		APP_LOG(APP_LOG_LEVEL_INFO, "times4: %s", times4->value->cstring);
		TIMES[4] = times4->value->cstring;
	}
	
	/*int a;
	for (a = 0; a < 3; a = a + 1) {
		Tuple *routes0 = dict_find(iter, KEY_ROUTE_0);
		
		APP_LOG(APP_LOG_LEVEL_INFO, "routes0: %s", routes0->value->cstring);
	}*/
	
	menu_layer_reload_data(menu_layer);
	
	
	/*const uint8_t key_count = 15;
	const uint32_t size = dict_calc_buffer_size(key_count, 25);
	uint8_t buffer[size];
	
	Tuple *tuple = dict_read_begin_from_buffer(iter, buffer, size);
	while(tuple) {
		switch(tuple->key) {
			case KEY_ROUTE_0:
				APP_LOG(APP_LOG_LEVEL_INFO, "routes0: %s", tuple->value->cstring);
				break;
		}
		tuple = dict_read_next(iter);
	}*/
	
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