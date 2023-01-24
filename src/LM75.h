/*
|----------------------------------------------------|
|   Arduino library for I2C sensors                  |
|   LM75 and AM2320                                  |
|                                                    |
|   (C) 2022, Thomas Steifler                        |
|   Licensed under the GNU General Public License    |
|                                                    |
|   LM75:                                            |
|   Library to use temperature sensor LM75           |
|----------------------------------------------------|
*/

#ifndef LM75_H
#define LM75_H

#define LM75_DEFAULT_ADDRESS 0x48

#include <Arduino.h>
#include <Wire.h>

class LM75
{
public:
    // Register structure
    struct Registers
    {
        uint8_t Temperature;
        uint8_t Configuration;
        uint8_t T_Hyst;
        uint8_t T_OS;
    };

    // Available sensor modes
    struct Modes
    {
        uint8_t Comparator;
        uint8_t Interrupt;
    };

    // Available OS polarities
    struct Polarities
    {
        uint8_t ActiveLow;
        uint8_t ActiveHigh;
    };

    // Available Fault Queue possibilities
    struct Faults
    {
        uint8_t Single;
        uint8_t Double;
        uint8_t Quad;
        uint8_t Multi;
    };

    // Constructor; If no value is provided, it uses the default address (0x48)
    LM75(uint8_t addr = LM75_DEFAULT_ADDRESS);

    float getTemperature(); // Reads current temperature
    float getHyst();        // Reads overtemperature shutdown temperature
    float getOS();          // Reads hysteresis temperature

    void setHyst(float temperature);      // Sets hysteresis temperature
    void setOS(float temperature);        // Sets O.S. temperature
    void setMode(uint8_t mode);           // Sets Operation mode
    void setOSPolarity(uint8_t polarity); // Sets O.S. polarity
    void setFaultQueue(uint8_t fault);    // Sets number of faults before O.S. trigger

protected:
    uint8_t getConfigReg();            // Reads configuration register
    void setConfigReg(uint8_t config); // Sets configuration register

    void write8Bit(uint8_t reg, uint8_t data);   // Write to 8-Bit register
    void write16Bit(uint8_t reg, uint16_t data); // Write to 16-Bit register
    uint8_t read8Bit(uint8_t reg);               // Read from 8-Bit register
    uint16_t read16Bit(uint8_t reg);             // Read from 16-Bit register

    uint8_t address; // Address of the sensor
};

// Make these structures available globally
extern LM75::Modes Mode;
extern LM75::Polarities Polarity;
extern LM75::Faults Fault;

#endif