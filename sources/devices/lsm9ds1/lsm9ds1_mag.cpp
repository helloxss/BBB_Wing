#include "lsm9ds1_mag.h"
#include "lsm9ds1_registers.h"

using namespace devices;

Lsm9ds1::Mag::Mag(const char* filename):
    I2cDevice(filename)
{}

uint8_t Lsm9ds1::Mag::i2cAddress() const
{
    return LSM9DS1_M;
}

bool Lsm9ds1::Mag::checkDevicePresent()
{
    return this->i2cRead(WHO_AM_I_M) == WHO_AM_I_M_RSP;
}

float Lsm9ds1::Mag::calcResolution(MagScale scale)
{
    switch (scale)
    {
    case MagScale4: return 4.0f / 32768.0f;
    case MagScale8: return 8.0f / 32768.0f;
    case MagScale12: return 12.0f / 32768.0f;
    case MagScale16: return 16.0f / 32768.0f;
    default:
        return 1.0f;
    }
}

void Lsm9ds1::Mag::initMag()
{
    this->i2cWrite(CTRL_REG1_M, 0xC0);
    this->i2cWrite(CTRL_REG2_M, 0x00);
    this->i2cWrite(CTRL_REG3_M, 0x00);
    this->i2cWrite(CTRL_REG4_M, 0x0C);
    this->i2cWrite(CTRL_REG5_M, 0x00);

    this->setMagSampleRate(MagSampleRate80);
    this->setMagScale(MagScale4);
}

void Lsm9ds1::Mag::setMagSampleRate(MagSampleRate rate)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG1_M);
    ctrl &= 0xFF ^ (0x7 << 2);
    ctrl |= (rate << 2);
    this->i2cWrite(CTRL_REG1_M, ctrl);
}

void Lsm9ds1::Mag::setMagScale(MagScale scale)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG2_M);
    ctrl &= 0xFF ^ (0x3 << 5);
    ctrl |= (scale << 5);
    this->i2cWrite(CTRL_REG2_M, ctrl);

    m_resolution = this->calcResolution(scale);
}

int16_t Lsm9ds1::Mag::readMagRaw(Axes axis)
{
    uint8_t regAddrL, regAddrH;

    switch (axis) {
    case AxisX:
        regAddrL = OUT_X_L_M;
        regAddrH = OUT_X_H_M;
        break;
    case AxisY:
        regAddrL = OUT_Y_L_M;
        regAddrH = OUT_Y_H_M;
        break;
    case AxisZ:
        regAddrL = OUT_Z_L_M;
        regAddrH = OUT_Z_H_M;
        break;
    }

    return this->i2cRead(regAddrH) << 8 | this->i2cRead(regAddrL);
}

float Lsm9ds1::Mag::readMag(Axes axis)
{
    return m_resolution * this->readMagRaw(axis);
}
