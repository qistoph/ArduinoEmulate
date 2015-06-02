#include "FakeSerial.h"

#include "wiring.h"

#include <conio.h>

#define RX_BUFFER_SIZE 512

struct ring_buffer {
	unsigned char buffer[RX_BUFFER_SIZE];
	int head;
	int tail;
};

ring_buffer rx_buffer = { { 0 }, 0, 0 };

inline void store_char(unsigned char c, ring_buffer *rx_buffer) {
	int i = (rx_buffer->head + 1) % RX_BUFFER_SIZE;

	if(i != rx_buffer->tail) {
		rx_buffer->buffer[rx_buffer->head] = c;
		rx_buffer->head = i;
	}
}

void read_stdin_to_buffer() {
	int c;
	
	while(kbhit()) {
		c = getch();
		printf("c: %d\n", c);
		if(c == 0x03) { captureSigInt(0); }
		
		store_char((unsigned char)c, &rx_buffer);
	}
}

void FakeSerial::begin(long baud) {
}

uint8_t FakeSerial::available() {
	read_stdin_to_buffer();
	return (RX_BUFFER_SIZE + rx_buffer.head - rx_buffer.tail) % RX_BUFFER_SIZE;
}

int FakeSerial::read() {
	printf("read\n");
	if(rx_buffer.head == rx_buffer.tail) {
		return -1;
	} else {
		unsigned char c = rx_buffer.buffer[rx_buffer.tail];
		rx_buffer.tail = (rx_buffer.tail + 1) % RX_BUFFER_SIZE;

		printf("c: %d\n", c);

		// Some substitution to return Serial chars
		switch(c) {
			case '\n': c = 13; break;
		}
		return c;
	}
}

void FakeSerial::end() {
}

void FakeSerial::write(uint8_t c) {
	putchar(c);
}

FakeSerial Serial;
