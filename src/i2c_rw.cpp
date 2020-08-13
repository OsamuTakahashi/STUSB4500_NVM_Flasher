#include "i2c_rw.h"
#include <Wire.h>

int I2C_Read_USB_PD(uint8_t Port, uint16_t Address ,uint8_t *DataR ,uint16_t Length)
{
    Wire.beginTransmission(STUSBxx_DEVICEID_7BIT);
    Wire.write((uint8_t)Address);
    int error = Wire.endTransmission();

    if (error == 0) {
        Wire.requestFrom(STUSBxx_DEVICEID_7BIT,Length);
        Wire.write(Address);
        while(Length > 0) {
            *DataR++ = Wire.read();
            Length--;
        }
    }
    return error;
}


int I2C_Write_USB_PD(uint8_t Port, uint16_t Address ,uint8_t *DataW ,uint16_t Length)
{
    Wire.beginTransmission(STUSBxx_DEVICEID_7BIT);
    Wire.write((uint8_t)Address);
    while(Length > 0) {
        Wire.write(*DataW++);
        Length--;
    }
    return Wire.endTransmission();
}