#ifndef __I2C__
#define __I2C__

#include <cstdint>

#define I2C_2_PATH	"/dev/i2c-2"

namespace BBB {

class I2C {
public:
	I2C(uint8_t address);
	~I2C();

	virtual int open();
	virtual int close();
	
	virtual uint8_t readRegister(uint32_t reg);
	virtual uint8_t* readRegisters(uint32_t reg, uint32_t num);
	virtual int writeRegister(uint32_t reg, uint8_t value);
	virtual int writeRegisters(uint32_t reg, uint8_t *buffer);

private:
	uint8_t address;
	int file;
};

} /* namespace BBB */

#endif /* __I2C__