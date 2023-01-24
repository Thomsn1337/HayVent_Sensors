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

#include "AM2320.h"

AM2320::AM2320()
{
    Wire.begin();
    _timestamp = millis();
}

// ****************************************
// Publuc
// ****************************************

float AM2320::readHumidity()
{
    readRegister(AM2320_REGISTER_HUMIDITY);
    while (millis() - _timestamp < AM2320_MIN_TIMEOUT)
    {
        yield();
    }
    _timestamp = millis();
    return (((_data[2] << 8) | _data[3]) / 10.0);
}

float AM2320::readTemperature()
{
    readRegister(AM2320_REGISTER_TEMPERATURE);
    while (millis() - _timestamp < AM2320_MIN_TIMEOUT)
    {
        yield();
    }
    _timestamp = millis();
    return (((_data[2] << 8) | _data[3]) / 10.0);
}

// ****************************************
// Protected
// ****************************************

bool AM2320::Wakeup(uint16_t timeout)
{
    uint64_t start = micros();
    while (micros() - start < timeout)
    {
        Wire.beginTransmission(AM2320_DEFAULT_ADDRESS);
        if (Wire.endTransmission() == 0)
            return true;
        yield();
    }
    return false;
}

void AM2320::readRegister(uint8_t reg)
{
    Wakeup();

    Wire.beginTransmission(0x5C);
    Wire.write(0x03);
    Wire.write(reg);
    Wire.write(2);
    Wire.endTransmission();

    uint8_t dataBytes = Wire.requestFrom(AM2320_DEFAULT_ADDRESS, 6);
    if (dataBytes == 0)
        return;

    for (uint8_t i = 0; i < dataBytes; i++)
    {
        _data[i] = Wire.read();
    }
    _timestamp = millis();
    return;
}