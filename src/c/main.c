#include <pebble.h>
#include "src/c/window.h"
// static Window *s_main_window;
// static TextLayer *s_time_layer;




// static void main_window_load(Window *window) {

//     Layer *window_layer = window_get_root_layer(window);
//   GRect bounds = layer_get_bounds(window_layer);

//   // Create the TextLayer with specific bounds
//   s_time_layer = text_layer_create(
//       GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));

//   // Improve the layout to be more like a watchface
//   text_layer_set_background_color(s_time_layer, GColorClear);
//   text_layer_set_text_color(s_time_layer, GColorBlack);
//   text_layer_set_text(s_time_layer, "00:00");
//   text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
//   text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

//   // Add it as a child layer to the Window's root layer
//   layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  
// }

// static void main_window_unload(Window *window) {
//   text_layer_destroy(s_time_layer);
// }



static void init() {

win_main_init();
  
}

static void deinit() {
 

}

int main(void) {
  init();
  app_event_loop();
  deinit();
}