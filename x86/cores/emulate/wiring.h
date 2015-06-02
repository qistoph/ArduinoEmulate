#ifndef WIRING_H
#define WIRING_H

#include <inttypes.h>

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define LOW 0x0
#define HIGH 0x1

#define F(x) x

typedef uint8_t byte;

void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
unsigned long millis();
void delay(unsigned long ms);
void captureSigInt(int n);

void init();
void setup();
void loop();

#endif
