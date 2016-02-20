#include <pebble.h>
#include "main.h"

static Window *main_window, *zero_window, *one_window;
MenuLayer *menu_layer;

static void menu_draw_header(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
	
}

static void menu_draw_row(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
	switch(cell_index->row) {
		case 0:
			menu_cell_basic_draw(ctx, cell_layer, "11111", "Destination", NULL);
			break;
		case 1:
			menu_cell_basic_draw(ctx, cell_layer, "22222", "Destination", NULL);
			break;
		case 2:
			menu_cell_basic_draw(ctx, cell_layer, "33333", "Destination", NULL);
			break;
		case 3:
			menu_cell_basic_draw(ctx, cell_layer, "44444", "Destination", NULL);
			break;
		case 4:
			menu_cell_basic_draw(ctx, cell_layer, "55555", "Destination", NULL);
			break;	
	}
}

static void menu_draw_separator(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
	
}

static uint16_t menu_get_rows(MenuLayer *menu_layer, uint16_t section_index, void *data)
{
	return 3;
}

static void menu_select(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
	int row = cell_index->row;
	
	if (row == 0) {
		APP_LOG(APP_LOG_LEVEL_INFO, "Row is 0");
		window_stack_push(zero_window, true);
	}
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