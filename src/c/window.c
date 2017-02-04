#include <pebble.h>
#include "window.h"
#include "bitmap.h"
#include "vibeOnDisconnect.h"

//Window item, time and date text layer and bitmap image pointers
static Window*    s_window;
static TextLayer *s_time_layer, *s_date_layer;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;
static GFont s_time_font;

//Function delarations
static void main_window_load(Window *window);
static void main_window_unload(Window *window);
static void update_time();
static void tick_handler(struct tm *tick_time, TimeUnits units_changed);

//Function to check and update the currently displayed time
static void update_time() {
  
  // Pull the current time and place it into a tm struct
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);

  //And set the time layer to have that information
  text_layer_set_text(s_time_layer, s_buffer);
  
  //Do the same procedure with the date, the %B and %e specify full month and single 
  //digit day "February 4"
  static char d_buffer[16];
  strftime(d_buffer, sizeof(d_buffer), "%B %e", tick_time);
  
  //And set the date layer up with that sweet data point
  text_layer_set_text(s_date_layer, d_buffer);
  

  //bluetoothVerify(connection_service_peek_pebble_app_connection());
  
}

//Function that activates to check the time over a specified duration 
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}


//Initialize the prime window functions and push the window to the stack
void win_main_init(void) {
  
  // Create main Window element and assign to pointer
  s_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  //Set the function that will deal with time
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_window, true);
  
  //And begin to update the time
  update_time();
}

//Destroy the window upon app exit
void win_main_deinit(void){
     window_destroy(s_window);
}

//Loading up the main and only window with all of the watchface elements
static void main_window_load(Window *window) {

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
    
  // Create GBitmap
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_EARTHRISE_2C2);
  
  // Create BitmapLayer to display the GBitmap
  s_background_layer = bitmap_layer_create(bounds);
  
  // Set the bitmap onto the layer and add to the window
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));
  
  
  
   // Create date TextLayer
  s_date_layer = text_layer_create(GRect(-18, 48, 144, 30));
  text_layer_set_text_color(s_date_layer, GColorWhite);
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  text_layer_set_text(s_date_layer, "September 23");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));
  
  
  // Create the TextLayer with specific bounds
  s_time_layer = text_layer_create(
      GRect(-22, PBL_IF_ROUND_ELSE(60, 65), bounds.size.w+50,50));


  //Creation of a GFont custom font
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_GOBOLD_48));
  
  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);


  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  
  //Here is where the function in "vibeOnDisconnect.h" is enacted to see
  //every update of the time if the user has wandered from their phone
  bluetoothVerify(connection_service_peek_pebble_app_connection());
  
}

static void main_window_unload(Window *window) {
  // Destroy GBitmap
gbitmap_destroy(s_background_bitmap);

// Destroy BitmapLayer
bitmap_layer_destroy(s_background_layer);
  
  // Destroy text_layer
  text_layer_destroy(s_time_layer);
}