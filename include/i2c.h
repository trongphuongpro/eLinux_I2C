#ifndef __I2C__
#define __I2C__

#define I2C_PATH	"/dev/i2c-"

namespace BBB {

class I2C {
public:
	enum BUS {I2C1=1, I2C2=2};

	I2C(BUS bus, uint8_t address);
	~I2C();

	virtual int open();
	virtual void close();

	virtual uint8_t read(uint8_t reg);
	virtual int readBuffer(uint8_t reg, void *buffer, uint16_t num);
	virtual int write(uint8_t reg, uint8_t value);
	virtual int writeBuffer(uint8_t reg, const void *buffer, uint16_t num);

private:
	uint8_t address;
	int file;
	std::string filename;
};

} /* namespace BBB */

#endif /* __I2C__ */