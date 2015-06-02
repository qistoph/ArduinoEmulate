#include "wiring.h"

#include <Arduino.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
//#include <fcntl.h>

#include "EEPROM.h"

void pinMode(uint8_t pin, uint8_t mode) {
	printf("Pin %d is now %s.\n", pin, mode==OUTPUT?"output":"input");
}

void digitalWrite(uint8_t pin, uint8_t value) {
	printf("Pin %d is now %s.\n", pin, value==HIGH?"high":"low");
}

unsigned long millis() {
	struct timeval now;
	gettimeofday(&now, NULL);

	return now.tv_sec*1000 + now.tv_usec/1000;
}

unsigned long micros() {
	struct timeval now;
	gettimeofday(&now, NULL);

	return now.tv_sec*1000*1000 + now.tv_usec;
}

void delay(unsigned long ms) {
	struct timeval start, now;
	gettimeofday(&start, NULL);

	do {
		gettimeofday(&now, NULL);
	} while(((unsigned long)now.tv_sec*1000U + (unsigned long)now.tv_usec/1000U) - ((unsigned long)start.tv_sec*1000U + (unsigned long)start.tv_usec/1000U) < ms);
}

void captureSigInt(int n) {
	EEPROM.saveToFile();
  //system("stty icanon echo");
	exit(0);
}

void init() {
  // This allows for getchar to be non blocking
  //system("stty -icanon -echo");
  //fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
  //signal(SIGINT, &captureSigInt);
}

int main(void) {
	init();

	setup();

	for(;;)
		loop();

	return 0;
}
