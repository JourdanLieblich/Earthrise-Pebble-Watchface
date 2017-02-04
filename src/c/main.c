#include <pebble.h>
#include "src/c/window.h"
#include "src/c/bitmap.h"
#include "src/c/vibeOnDisconnect.h"

//Initialize the two features, watchface window and vibration upon 
//disconnect from device
static void init() {

  win_main_init();
  vibe_init();
  
}

static void deinit() {
 
}

//Run the app
int main(void) {
  init();
  app_event_loop();
  deinit();
}