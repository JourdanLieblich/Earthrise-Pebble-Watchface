#include <pebble.h>
#include "vibeOnDisconnect.h"

//Simply responds to a false conn with a long pulse,
//could be upgraded with a "Go back dummy!" note
void bluetoothVerify(bool conn){
  
  if(!conn){
    vibes_long_pulse();
  }
  
}

//Initialize the functionality and set the connection hanler
//to the above function
void vibe_init(void){
  
    connection_service_subscribe((ConnectionHandlers) {
    .pebble_app_connection_handler = bluetoothVerify
  });
  
}

void vibe_dinit(void){
  
}
