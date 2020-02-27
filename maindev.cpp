#include "maindev.h"

#include "config.h"

#include <FastLED.h>
#include "mpr121.h"
#include "mpr121-config.h"
#include "serial.h"

static MPR121 capl, capr;
static bool auto_scan = false;

static void slider_set_led();
static void slider_scan_start();
static void slider_scan_stop();
static void slider_reset();
static void slider_get_board_info();
static void slider_scan();

#define CLAMP(val, lo, hi) (val < lo ? lo : (val > hi ? hi : val))

void maindev_init() {
	Serial.begin(SERIAL_SPEED);
	Serial.setTimeout(0);
	Wire.setClock(I2C_SPEED);
	capl.begin(CL_ADDR);
	capl.init();
	capl.run();
	capr.begin(CR_ADDR);
	capr.init();
	capr.run();
	FastLED.addLeds<LED_TYPE, LED_PIN>((CRGB *) slider_req.leds, 16);
}

void maindev_loop() {
	switch(sliderserial_readreq()) {
		case SLIDER_CMD_SET_LED:
			slider_set_led();
			break;
		case SLIDER_CMD_AUTO_SCAN_START:
			slider_scan_start();
			break;
		case SLIDER_CMD_AUTO_SCAN_STOP:
			slider_scan_stop();
			break;
		case SLIDER_CMD_RESET:
			slider_reset();
			break;
		case SLIDER_CMD_GET_BOARD_INFO:
			slider_get_board_info();
			break;
		default:
			slider_scan();
	}
	sliderserial_writeresp();
}

#define BSD_HASH(checksum, ch) do {\
	checksum = (checksum >> 1) + ((checksum & 1) << 15);\
	checksum += ch;\
} while(0);

static void slider_set_led() {
	static uint16_t prev_hash = -1;
	if (slider_tx_pending) {
		return;
	}
	uint8_t r, g, b;
	CRGB * leds = (CRGB *) slider_req.leds;
	uint16_t hash = 0;
	for (int i=0; i<16; i++) {
		// Note that the input and output buffer overlaps.
		b = slider_req.leds[i*6+0];
		r = slider_req.leds[i*6+1];
		g = slider_req.leds[i*6+2];
		leds[i].r = r;
		BSD_HASH(hash, r);
		leds[i].g = g;
		BSD_HASH(hash, g);
		leds[i].b = b;
		BSD_HASH(hash, b);
	}
	if (hash != prev_hash) {
		prev_hash = hash;
		FastLED.show();
	}
	slider_req.cmd = 0;
}

static void slider_scan_start() {
	auto_scan = true;
	// No ACK
	slider_scan();
}

static void slider_scan_stop() {
	auto_scan = false;
	slider_resp.syn = 0xff;
	slider_resp.cmd = SLIDER_CMD_AUTO_SCAN_STOP;
	slider_resp.size = 0;
	slider_req.cmd = 0;
}

static void slider_reset() {
	capl.init();
	capl.run();
	capr.init();
	capr.run();
	slider_resp.syn = 0xff;
	slider_resp.cmd = SLIDER_CMD_RESET;
	slider_resp.size = 0;
	slider_req.cmd = 0;
}

static void slider_get_board_info() {
	slider_resp.syn = 0xff;
	slider_resp.cmd = SLIDER_CMD_GET_BOARD_INFO;
	slider_resp.size = sizeof(slider_resp.version);
	strcpy(slider_resp.version, "15330   \xA0" "06712\xFF" "\x90");
	slider_req.cmd = 0;
}

static void slider_scan() {
	if (!auto_scan || slider_tx_pending) {
		return;
	}
	slider_resp.syn = 0xff;
	slider_resp.cmd = SLIDER_CMD_AUTO_SCAN;
	slider_resp.size = sizeof(slider_resp.pressure);
#ifdef MPR_MODE_QUICK
	uint32_t sensors;
	sensors |= ((uint32_t)(uint8_t)capr.touched()) << 8;
	sensors |= (uint32_t)(uint8_t)capl.touched();
	for (int i=0; i<16; i++) {
		if (sensors & (1<<i)) {
			slider_resp.pressure[31-(i*2+0)] = 128;
		} else {
			slider_resp.pressure[31-(i*2+0)] = 0;
		}
		slider_resp.pressure[31-(i*2+1)] = 0;
	}
#endif
#ifdef MPR_MODE_PRECISE
	int16_t bv, fd, pressure;
	for (int i=0; i<8; i++) {
		bv = capl.baselineData(i);
		fd = capl.filteredData(i);
		pressure = bv - fd - MPR121CONF_TTH + 20;
		slider_resp.pressure[31-(i*2+0)] = CLAMP(pressure, 0, 255);
		slider_resp.pressure[31-(i*2+1)] = 0;
		bv = capr.baselineData(i);
		fd = capr.filteredData(i);
		pressure = bv - fd;
		slider_resp.pressure[31-(16+i*2)] = CLAMP(pressure, 0, 255);
		slider_resp.pressure[31-(16+i*2+1)] = 0;
	}
#endif
#ifdef MPR_MODE_ADVANCED
#error Not Implemented
#endif
}
