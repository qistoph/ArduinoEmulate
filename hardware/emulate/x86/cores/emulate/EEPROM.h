#ifndef EEPROM_h
#define EEPROM_h

#include <inttypes.h>

#define EEPROM_SIZE 512

void eeprom_read_block (void *__dst, unsigned int offset, unsigned int __n);
void eeprom_write_block (void *__dst, unsigned int offset, unsigned int __n);

class EEPROMClass
{
	public:
		EEPROMClass();
		~EEPROMClass();
		
		uint8_t read(int);
		void write(int, uint8_t);
		
		void saveToFile();
	
	//private:
		uint8_t memory[EEPROM_SIZE];
};

extern EEPROMClass EEPROM;

#endif
