#ifndef CONFIG_H
#define CONFIG_H

#define SERIAL_SPEED 115200 ///< Baud rate for Serial. Don't care for CDC ports.
#define I2C_SPEED 400000 ///< I2C clock rate. Maximum for MPR121 is 400k.

#define CL_ADDR 0x5b ///< I2C address for left capacitive sensor
#define CR_ADDR 0x5a ///< I2C address for right capacitive sensor
#define MPR_MODE_QUICK ///< Report binary. 0 or 128
// #define MPR_MODE_PRECISE ///< Report pressure. Slower than quick.
// #define MPR_MODE_ADVANCED ///< Experimental 2-finger detection.

#define LED_TYPE NEOPIXEL ///< LED strip type
#define LED_PIN 8 ///< LED pin

#define IR_PIN_START A0
#define IR_PIN_END A5
#define IR_DEBUG_PIN 9
#define IR_ACTIVATION 20
// #define IR_MODE_ANALOG
#define IR_MODE_ACTIVEHIGH
// #define IR_MODE_ACTIVELOW

#endif
