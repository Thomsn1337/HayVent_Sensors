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

#include "LM75.h"

// **************************************
// Public stuff
// **************************************

// Initialise register structure
LM75::Registers Register = {
    .Temperature = 0,
    .Configuration = 1,
    .T_Hyst = 2,
    .T_OS = 3,
};

// Initialise available operation modes
LM75::Modes Mode = {
    .Comparator = (0 << 1),
    .Interrupt = (1 << 1),
};

// Initialise available O.S. polarities
LM75::Polarities Polarity = {
    .ActiveLow = (0 << 2),
    .ActiveHigh = (1 << 2),
};

// Initialise Fault Queue possibilities
LM75::Faults Fault = {
    .Single = (0 << 3),
    .Double = (1 << 3),
    .Quad = (2 << 3),
    .Multi = (3 << 3),
};

// Constructor interited from parent
LM75::LM75(uint8_t addr) : GenericSensor(addr)
{
}

// Reads temperature register (in °C)
float LM75::getTemperature()
{
    return read16Bit(Register.Temperature) / 256.0f;
}

// Reads hysteresis temperature register
float LM75::getHyst()
{
    return read16Bit(Register.T_Hyst) / 256.0f;
}

// Reads O.S. temperature register
float LM75::getOS()
{
    return read16Bit(Register.T_OS) / 256.0f;
}

// Sets hysteresis temperature
void LM75::setHyst(float temperature)
{
    write16Bit(Register.T_Hyst, (uint16_t)(temperature * 256.0));
}

// Sets O.S. temperature
void LM75::setOS(float temperature)
{
    write16Bit(Register.T_OS, (uint16_t)(temperature * 256.0));
}

// Sets operation mode
void LM75::setMode(uint8_t mode)
{
    setConfigReg((getConfigReg() & ~(Mode.Interrupt)) | mode);
}

// Sets O.S. polarity
void LM75::setOSPolarity(uint8_t polarity)
{
    setConfigReg((getConfigReg() & ~(Polarity.ActiveHigh)) | polarity);
}

// Sets number of faults before O.S. trigger
void LM75::setFaultQueue(uint8_t fault)
{
    setConfigReg((getConfigReg() & ~(Fault.Multi)) | fault);
}

// **************************************
// Protected stuff
// **************************************

// Reads configuration register
uint8_t LM75::getConfigReg()
{
    return read8Bit(Register.Configuration);
}

// sets configuration register
void LM75::setConfigReg(uint8_t config)
{
    write8Bit(Register.Configuration, config);
}