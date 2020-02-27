#include "maindev.h"
#include "sidedev.h"

#include <Arduino.h>

void setup() {
	Serial.begin(9600);
	maindev_init();
	sidedev_init();
}

void loop() {
	maindev_loop();
	sidedev_loop();
}
