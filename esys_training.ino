#include "vlib.h"

bool led_state = 0;
bool base_state = 0;

// Runs once at startup
void setup() {
  // Set up hardware interrupts 
  irq_setup();

  // Initialize onboard LED
  pinMode(LED_BUILTIN, OUTPUT);
}

// Runs repeatedly thenceforth
void loop() {
  int high_timer = timer % 128;
  int base_timer = timer % 2048;
  
  bool led_on = true;
  bool led_flickering = (base_timer >= 1024);

  led_on = false;
  if (led_flickering) {
    if (high_timer < 96) {
      led_on = true;
    }
  }

  digitalWrite(LED_BUILTIN, led_on);
}
