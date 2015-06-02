#include "EEPRom.h"

#include <stdio.h>
#include <memory.h>

#define EEPROM_FILE "eeprom.dat"

void eeprom_read_block (void *__dst, unsigned int offset, unsigned int __n) {
	unsigned char* dst = (unsigned char*)__dst;
	memcpy(dst, EEPROM.memory+offset, __n);
}

void eeprom_write_block (void *__dst, unsigned int offset, unsigned int __n) {
	unsigned char* dst = (unsigned char*)__dst;
	memcpy(EEPROM.memory+offset, dst, __n);
}

EEPROMClass::EEPROMClass() {
	printf("Load EEPROM file");
	FILE* pFile = fopen(EEPROM_FILE, "r");
	if(!pFile) {
		printf(" - doesn't exist\n");
		return;
	}

	size_t read = fread(memory, 1, EEPROM_SIZE, pFile);
	fclose(pFile);
	
	printf(" (%ld bytes)\n", read);
}

EEPROMClass::~EEPROMClass() {
}

uint8_t EEPROMClass::read(int address) {
	return memory[address];
}

void EEPROMClass::write(int address, uint8_t value) {
	memory[address] = value;
}

void EEPROMClass::saveToFile() {
	FILE* pFile = fopen(EEPROM_FILE, "w");
	if(!pFile) return;

	printf("Save EEPROM file");
	int written = fwrite(memory, 1, EEPROM_SIZE, pFile);
	fclose(pFile);
	printf(" (%d bytes)\n", written);
}

EEPROMClass EEPROM;
