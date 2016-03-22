#include <pebble.h>
#include "main.h"

static Window *main_window, *zero_window, *one_window, *info_window;
MenuLayer *menu_layer;

TextLayer *time_layer;

int which_row;

static void menu_draw_header(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
	
}

static void menu_draw_row(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
	switch(cell_index->row) {
		case 0:
			menu_cell_basic_draw(ctx, cell_layer, STOP_NAMES[0], DESTS[0], NULL);
			break;
		case 1:
			menu_cell_basic_draw(ctx, cell_layer, STOP_NAMES[1], DESTS[1], NULL);
			break;
		case 2:
			menu_cell_basic_draw(ctx, cell_layer, STOP_NAMES[2], DESTS[2], NULL);
			break;
		case 3:
			menu_cell_basic_draw(ctx, cell_layer, STOP_NAMES[3], DESTS[3], NULL);
			break;
		case 4:
			menu_cell_basic_draw(ctx, cell_layer, STOP_NAMES[4], DESTS[4], NULL);
			break;	
	}
}

static void menu_draw_separator(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
	
}

static uint16_t menu_get_rows(MenuLayer *menu_layer, uint16_t section_index, void *data) {
	return tot_stops;
	tot_stops = 0;
}

static void menu_select(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
	int row = cell_index->row;
	
	APP_LOG(APP_LOG_LEVEL_INFO, "Selected row: %d", row);
	which_row = row;
	window_stack_push(info_window, true);
}

static void main_window_load(Window *window) {
	GRect bounds = layer_get_bounds(window_get_root_layer(window));
	
	menu_layer = menu_layer_create(bounds);
	menu_layer_set_normal_colors(menu_layer, GColorWhite, GColorBlack);
	menu_layer_set_highlight_colors(menu_layer, GColorVividCerulean, GColorWhite);
	
	menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks) {
		.draw_header = menu_draw_header,
		.draw_row = menu_draw_row,
		.get_num_rows = menu_get_rows,
		.draw_separator = menu_draw_separator,
		.select_click = menu_select,
	});
	
	menu_layer_set_click_config_onto_window(menu_layer, window);
	layer_add_child(window_get_root_layer(window), menu_layer_get_layer(menu_layer));
}

static void main_window_unload(Window *window) {
	
}

static void info_window_load(Window *window) {
	GRect bounds = layer_get_bounds(window_get_root_layer(window));
	
	time_layer = text_layer_create(GRect(0, 15, bounds.size.w, bounds.size.h));
	text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS));
	text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
	
	static char arrival[5];
	snprintf(arrival, sizeof(arrival), "%d", TIMES[which_row]);
	
	text_layer_set_text(time_layer, arrival);
	layer_add_child(window_get_root_layer(info_window), text_layer_get_layer(time_layer));
}

static void info_window_unload(Window *window) {
	
}

static void zero_window_load(Window *window) {
	window_set_background_color(window, GColorOrange);
}

static void zero_window_unload(Window *window) {
	
}

static void init() {
	main_window = window_create();

	window_set_window_handlers(main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload
	});
	
	zero_window = window_create();

	window_set_window_handlers(zero_window, (WindowHandlers) {
		.load = zero_window_load,
		.unload = zero_window_unload
	});
	
	info_window = window_create();

	window_set_window_handlers(info_window, (WindowHandlers) {
		.load = info_window_load,
		.unload = info_window_unload
	});
	
	init_appmessage();
	
	window_stack_push(main_window, true);
}

static void deinit() {

}

int main(void) {
	init();
  app_event_loop();
 	deinit();
}