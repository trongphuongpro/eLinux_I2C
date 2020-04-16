#ifndef __I2C__
#define __I2C__

#define I2C_PATH	"/dev/i2c-"

namespace BBB {

class I2C {
public:
	enum BUS {I2C1=1, I2C2=2};

	I2C(BUS bus);
	~I2C();

	virtual uint8_t receive(uint8_t slave);
	virtual int receiveBuffer(uint8_t slave, void *buffer, int len);
	virtual int send(uint8_t slave, uint8_t value);
	virtual int sendBuffer(uint8_t slave, const void *buffer, int len);

private:
	int file;
	std::string filename;

	int open();
	void close();
};

} /* namespace BBB */

#endif /* __I2C__ */