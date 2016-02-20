#include <pebble.h>
#pragma once

#define KEY_STOP_ROUTES 0
#define KEY_STOP_DESTS 1
#define KEY_ARRIVAL_TIMES 2

MenuLayer *menu_layer;

char* stop_title;
char* destination;
char* arrival_time;

void init_appmessage();
void inbox_received_handler(DictionaryIterator *iter, void *context);
void inbox_dropped_callback(AppMessageResult reason, void *context);
void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
void outbox_sent_callback(DictionaryIterator *iterator, void *context);