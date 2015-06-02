#ifndef FAKESERIAL_H
#define FAKESERIAL_H

#include "Print.h"

class FakeSerial : public Print {
	public:
		void begin(long);
		uint8_t available(void);
		int read(void);
		void end();

		virtual void write(uint8_t);
};

extern FakeSerial Serial;

#endif
