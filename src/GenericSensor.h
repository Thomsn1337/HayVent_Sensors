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

#ifndef GENERIC_SENSOR_H
#define GENERIC_SENSOR_H

#include <Arduino.h>
#include <Wire.h>

class GenericSensor
{
public:
    // Constructor; Provide sensor address
    GenericSensor(uint8_t addr);

    // Write to 8-Bit register
    void write8Bit(uint8_t reg, uint8_t data);
    // Write to 16.Bit register
    void write16Bit(uint8_t reg, uint16_t data);

    // Read from 8-Bit register
    uint8_t read8Bit(uint8_t reg);
    // Read from 16-Bit register
    uint16_t read16Bit(uint8_t reg);

protected:
    // Store the sensor address
    uint8_t address;
};

#endif