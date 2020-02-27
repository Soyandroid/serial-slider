#include "sidedev.h"
#include "config.h"

#include <Arduino.h>
#include <HID-Project.h>

static int16_t ir_activation[6];
const char IR_KEYS[] = "456789";

void sidedev_init() {
	// Initialize IR thresholds
	for (int i = 0; i < 6; i++) {
#ifdef IR_MODE_ANALOG
		int32_t pinval = analogRead(IR_PIN_START + i);
		ir_activation[i] = pinval * IR_ACTIVATION / 100;
#else
		ir_activation[i] = 1024 * IR_ACTIVATION / 100;
#endif
	}
	// Initialize keyboard
	NKROKeyboard.begin();
	// Initialize debug pin
	pinMode(IR_DEBUG_PIN, OUTPUT);
}

#ifdef IR_MODE_ANALOG
#define IR_COND pinval > ir_activation[i]
#endif
#ifdef IR_MODE_ACTIVEHIGH
#define IR_COND pinval > (1024*IR_ACTIVATION/100)
#endif
#ifdef IR_MODE_ACTIVELOW
#define IR_COND pinval < (1024*IR_ACTIVATION/100)
#endif

void sidedev_loop() {
	static uint32_t ir_state = 0;
	// Read IR LEDs
	int debug = LOW;
	bool change = false;
	for (int i = 0; i < 6; i++) {
		int pinval = analogRead(IR_PIN_START + i);
		if (IR_COND) {
			debug = HIGH;
			if (!(ir_state & (1<<i))) {
				NKROKeyboard.add(IR_KEYS[i]);
				ir_state |= 1<<i;
				change = true;
			}
		} else {
			if (ir_state & (1<<i)) {
				NKROKeyboard.remove(IR_KEYS[i]);
				ir_state &= ~(1<<i);
				change = true;
			}
		}
	}
	digitalWrite(IR_DEBUG_PIN, debug);
	if (change) {
		NKROKeyboard.send();
	}
}
