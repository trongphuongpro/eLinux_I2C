#include <iostream>
#include "i2c.h"
#include "datetime.h"


#define DS1307 	0x68
#define BUFFERSIZE	7

using namespace BBB;
using namespace std;

const char* weekdays[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char* months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
						"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};


uint8_t bcd2dec(uint8_t value) {
	return value / 16 * 10 + value % 16;
}


uint8_t dec2bcd(uint8_t value) {
	return value / 10 * 16 + value % 10;
}


int rtc_getTime(I2C *bus, DateTime *datetime) {

	uint8_t buffer[BUFFERSIZE];

	// reset DS1307 pointer
	bus->send(DS1307, 0x00);
	bus->receiveBuffer(DS1307, buffer, BUFFERSIZE);

	if (buffer == NULL) {
		cout << "Fail to read buffer" << endl;
		return FAILED;
	}

	datetime->second = bcd2dec(buffer[0] & 0x7F);
	datetime->minute = bcd2dec(buffer[1]);
	datetime->hour = bcd2dec(buffer[2] & 0x3F);
	datetime->dayofweek = bcd2dec(buffer[3]);
	datetime->date = bcd2dec(buffer[4]);
	datetime->month = bcd2dec(buffer[5]);
	datetime->year = bcd2dec(buffer[6]) + 2000;

	return SUCCESS;
}


int rtc_setTime(I2C* bus, DateTime *datetime) {
	uint8_t buffer[BUFFERSIZE+1];

	buffer[0] = 0;
	buffer[1] = dec2bcd(datetime->second);
	buffer[2] = dec2bcd(datetime->minute);
	buffer[3] = dec2bcd(datetime->hour);
	buffer[4] = dec2bcd(datetime->dayofweek);
	buffer[5] = dec2bcd(datetime->date);
	buffer[6] = dec2bcd(datetime->month);
	buffer[7] = dec2bcd(datetime->year - 2000);

	bus->sendBuffer(DS1307, buffer, BUFFERSIZE+1);

	return SUCCESS;
}


void rtc_show(DateTime *datetime) {
	printf("Time: \'%s %s %2d %02d:%02d:%02d %d\'\n", weekdays[datetime->dayofweek-1],
													months[datetime->month-1],
													datetime->date,
													datetime->hour,
													datetime->minute,
													datetime->second,
													datetime->year);
}



int main() {

	I2C bus(I2C::I2C2);
	DateTime dt;

	rtc_getTime(&bus, &dt);
	rtc_show(&dt);

	dt.year = 2020;
	rtc_setTime(&bus, &dt);
	rtc_getTime(&bus, &dt);
	rtc_show(&dt);

}