/*
 *	Main Device (Slider)
 *
 *	Controls LED strip and capacitive touch sensors. Communicates with host
 *	through the Chunithm slider serial protocol.
 */
#ifndef MAIN_DEV_H
#define MAIN_DEV_H

void maindev_init();
void maindev_loop();

#endif
