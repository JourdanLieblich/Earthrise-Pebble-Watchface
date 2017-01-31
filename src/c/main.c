#include <pebble.h>
#include "src/c/window.h"
#include "src/c/bitmap.h"

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