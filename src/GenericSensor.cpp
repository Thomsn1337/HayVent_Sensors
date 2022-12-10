/*
|----------------------------------------------------|
|   Arduino library for I2C sensors                  |
|   LM75 and AM2320                                  |
|                                                    |
|   (C) 2022, Thomas Steifler                        |
|   Licensed under the GNU General Public License    |
|                                                    |
|   GenericSensor:                                   |
|   General purpose library for I2C communication    |
|----------------------------------------------------|
*/

#include "GenericSensor.h"

GenericSensor::GenericSensor(uint8_t addr)
{
    address = addr; // Set address to provided value
    Wire.begin();   // Start default I2C interface
}

uint8_t GenericSensor::read8Bit(uint8_t reg)
{
    Wire.beginTransmission(address);
    Wire.write(reg); // Set the register pointer
    Wire.endTransmission();

    Wire.requestFrom(address, 1); // Request 1 Byte from the register
    uint8_t data = Wire.read();   // Read the Byte
    Wire.endTransmission();
    return data;
}

uint16_t GenericSensor::read16Bit(uint8_t reg)
{
    Wire.beginTransmission(address);
    Wire.write(reg); // Set the register pointer
    Wire.endTransmission();

    Wire.requestFrom(address, 2); // Request 2 Bytes
    // Set the high Byte and the low Byte together
    uint16_t data = Wire.read() << 8;
    data |= Wire.read();
    Wire.endTransmission();
    return data;
}

void GenericSensor::write8Bit(uint8_t reg, uint8_t data)
{
    Wire.beginTransmission(address);
    Wire.write(reg);  // Set register pointer
    Wire.write(data); // Write date to register
    Wire.endTransmission();
}

void GenericSensor::write16Bit(uint8_t reg, uint16_t data)
{
    Wire.beginTransmission(address);
    Wire.write(reg);            // Set register pointer
    Wire.write(highByte(data)); // Write high Byte to register
    Wire.write(lowByte(data));  // Write low Byte to register
    Wire.endTransmission();
}