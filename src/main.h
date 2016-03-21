#include <pebble.h>
#pragma once

#define KEY_STOP_ROUTES 0
#define KEY_STOP_DESTS 1
#define KEY_ARRIVAL_TIMES 2
#define KEY_NUM_OF_STOPS 3
#define KEY_ROUTE_0 10
#define KEY_ROUTE_1 11
#define KEY_ROUTE_2 12
#define KEY_ROUTE_3 13
#define KEY_ROUTE_4 14

#define KEY_DEST_0 20
#define KEY_DEST_1 21
#define KEY_DEST_2 22
#define KEY_DEST_3 23
#define KEY_DEST_4 24

#define KEY_TIME_0 30
#define KEY_TIME_1 31
#define KEY_TIME_2 32
#define KEY_TIME_3 33
#define KEY_TIME_4 34

MenuLayer *menu_layer;

char stop_title[100];
char destination;
char arrival_time;

void init_appmessage();
void inbox_received_handler(DictionaryIterator *iter, void *context);
void inbox_dropped_callback(AppMessageResult reason, void *context);
void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
void outbox_sent_callback(DictionaryIterator *iterator, void *context);

const char* STOP_NAMES[5];
int tot_stops;

const char* DESTS[5];
const char* TIMES[5];