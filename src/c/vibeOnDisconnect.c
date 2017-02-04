#include <pebble.h>
#include "vibeOnDisconnect.h"

static BitmapLayer *BTlayer;

static void bluetoothVerify(bool conn){
  layer_set_hidden(bitmap_layer_get_layer(BTlayer), conn);
  
  if(!conn){
    vibes_long_pulse();
  }
}

void vibe_init(void){
  
    connection_service_subscribe((ConnectionHandlers) {
    .pebble_app_connection_handler = bluetoothVerify
  });
  
}

void vibe_dinit(void){
  
}
