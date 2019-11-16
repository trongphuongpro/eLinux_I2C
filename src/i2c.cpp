#include <iostream>
#include <cstdio>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "i2c.h"


using namespace BBB;
using namespace std;


I2C::I2C(uint8_t address) {
	this->address = address;
	this->file = -1;
	this->open();
}


I2C::~I2C() {
	if(this->file != -1) 
		close();
}


int I2C::open() {
	if ((this->file = ::open(I2C_2_PATH, O_RDWR)) < 0) {
		perror("Fail to open i2c bus\n");
		return -1;
	}
	if (ioctl(this->file, I2C_SLAVE, this->address) < 0) {
		perror("Fail to connect to device at this address\n");
		return -1;
	}
	return 0;
}


int I2C::close() {
	close(this->file);
	this->file = -1;
}


uint8_t I2C::read(uint32_t reg) {
	uint8_t data;

	if (::write(this->file, &reg, 1) != 1) {
		perror("Failed to reset the read address\n");
		return -1;
	}

	if (::read(this->file, &date, 1) != 1) {
		perror("Fail to read in the value\n");
		return -1;
	}
	return data;
}


uint8_t* I2C::readBuffer(uint32_t reg, uint32_t num) {
	uint8_t* data = calloc(num, 1);

	if (::write(this->file, &reg, 1) != 1) {
		perror("Failed to reset the read address\n");
		return -1;
	}

	if (::read(this->file, &date, num) != num) {
		perror("Fail to read in the buffer\n");
		return NULL;
	}

	return data;
}


int I2C::write(uint32_t reg, uint8_t value) {
	uint8_t buffer[2] = {reg, value};

	if (::write(this->file, buffer, 2) != 2) {
		perror("Failed to write the register\n");
		return -1;
	}

	return 0;
}


int I2C::writeBuffer(uint32_t reg, uint8_t *buffer, uint32_t num) {
	for (uint32_t i = 0; i < num; i++) {
		ret = this->write(reg+i, buffer[i]);
		if (ret == -1) {
			return -1;
		}
	}
	return 0;
}