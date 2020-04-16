#include <iostream>
#include <cstdlib>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "i2c.h"


using namespace BBB;
using namespace std;


I2C::I2C(BUS bus) {
	this->filename = I2C_PATH + to_string(bus);
	this->file = -1;
	open();
}


I2C::~I2C() {
	if(this->file != -1) 
		close();
}


int I2C::open() {
	if ((this->file = ::open(this->filename.c_str(), O_RDWR)) < 0) {
		perror("Fail to open i2c bus\n");
		return -1;
	}
	
	return 0;
}


void I2C::close() {
	::close(this->file);
	this->file = -1;
}


uint8_t I2C::receive(uint8_t slave) {
	uint8_t data;

	if (ioctl(this->file, I2C_SLAVE, slave) < 0) {
		perror("Fail to connect to device at this address\n");
		return -1;
	}

	if (::read(this->file, &data, 1) != 1) {
		perror("Fail to read in the value\n");
		return -1;
	}

	return data;
}


int I2C::receiveBuffer(uint8_t slave, void *buffer, int num) {
	uint8_t *data = (uint8_t*)buffer;

	if (ioctl(this->file, I2C_SLAVE, slave) < 0) {
		perror("Fail to connect to device at this address\n");
		return -1;
	}

	if (::read(this->file, data, num) != num) {
		perror("Failed to read in the buffer\n");
		return -1;
	}

	return 0;
}


int I2C::send(uint8_t slave, uint8_t data) {
	if (ioctl(this->file, I2C_SLAVE, slave) < 0) {
		perror("Fail to connect to device at this address\n");
		return -1;
	}

	if (::write(this->file, &data, 1) != 1) {
		perror("Failed to write data\n");
		return -1;
	}

	return 0;
}


int I2C::sendBuffer(uint8_t slave, const void *buffer, int num) {
	if (ioctl(this->file, I2C_SLAVE, slave) < 0) {
		perror("Fail to connect to device at this address\n");
		return -1;
	}

	const uint8_t *data = (const uint8_t*)buffer;

	if (::write(this->file, data, num) != num) {
		perror("Failed to write buffer\n");
		return -1;
	}

	return 0;
}