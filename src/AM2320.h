/*
|----------------------------------------------------|
|   Arduino library for I2C sensors                  |
|   LM75 and AM2320                                  |
|                                                    |
|   (C) 2022, Thomas Steifler                        |
|   Licensed under the GNU General Public License    |
|                                                    |
|   AM2320                                           |
|   Library to use temperature and                   |
|   humidity sensor AM2320                           |
|----------------------------------------------------|
*/

#ifndef AM2320_H
#define AM2320_H

#include <Arduino.h>
#include <Wire.h>

#define AM2320_DEFAULT_ADDRESS 0x5C
#define AM2320_READ_REGISTER 0x03

#define AM2320_REGISTER_HUMIDITY 0x00
#define AM2320_REGISTER_TEMPERATURE 0x02

#define AM2320_MIN_TIMEOUT 90

class AM2320
{
public:
    AM2320();
    float readTemperature();
    float readHumidity();

protected:
    unsigned long _timestamp;
    uint8_t _data[6];
    bool Wakeup(uint16_t timeout = 3000);
    void readRegister(uint8_t reg);
};

#endif