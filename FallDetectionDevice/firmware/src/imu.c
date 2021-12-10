#include "imu.h"
#include "definitions.h"

double getAccelX()
{
    uint8_t accel_0_reg = ICM42605_ACCEL_DATA_X0;
    uint8_t accel_1_reg = ICM42605_ACCEL_DATA_X1;
    
    uint8_t accel_0_data;
    uint8_t accel_1_data;
    
    
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &accel_0_reg, 1, &accel_0_data, 1);
    while(SERCOM0_I2C_IsBusy());
    
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &accel_1_reg, 1, &accel_1_data, 1);
    while(SERCOM0_I2C_IsBusy());
    
    short raw_accel_x = (short) ((accel_1_data << 8) | accel_0_data);
    
    return raw_accel_x * ACCEL_SCALE / 32768.0;
}

double getAccelY()
{
    uint8_t accel_0_reg = ICM42605_ACCEL_DATA_Y0;
    uint8_t accel_1_reg = ICM42605_ACCEL_DATA_Y1;
    
    uint8_t accel_0_data;
    uint8_t accel_1_data;
    
    
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &accel_0_reg, 1, &accel_0_data, 1);
    while(SERCOM0_I2C_IsBusy());
    
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &accel_1_reg, 1, &accel_1_data, 1);
    while(SERCOM0_I2C_IsBusy());
    
    short raw_accel_y = (short) ((accel_1_data << 8) | accel_0_data);
    
    return raw_accel_y * ACCEL_SCALE / 32768.0;
}

double getAccelZ()
{
    uint8_t accel_0_reg = ICM42605_ACCEL_DATA_Z0;
    uint8_t accel_1_reg = ICM42605_ACCEL_DATA_Z1;
    
    uint8_t accel_0_data;
    uint8_t accel_1_data;
    
    
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &accel_0_reg, 1, &accel_0_data, 1);
    while(SERCOM0_I2C_IsBusy());
    
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &accel_1_reg, 1, &accel_1_data, 1);
    while(SERCOM0_I2C_IsBusy());
    
    short raw_accel_z = (short) ((accel_1_data << 8) | accel_0_data);
    
    return raw_accel_z * ACCEL_SCALE / 32768.0;
}

double getGyroX()
{
    uint8_t gyro_0_reg = ICM42605_GYRO_DATA_X0;
    uint8_t gyro_1_reg = ICM42605_GYRO_DATA_X1;
    
    uint8_t gyro_0_data;
    uint8_t gyro_1_data;
    
    
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &gyro_0_reg, 1, &gyro_0_data, 1);
    while(SERCOM0_I2C_IsBusy());
    
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &gyro_1_reg, 1, &gyro_1_data, 1);
    while(SERCOM0_I2C_IsBusy());
    
    short raw_gyro_x = (short) ((gyro_1_data << 8) | gyro_0_data);
    
    return raw_gyro_x * GYRO_SCALE / 32768.0;
}

double getGyroY()
{
    uint8_t gyro_0_reg = ICM42605_GYRO_DATA_Y0;
    uint8_t gyro_1_reg = ICM42605_GYRO_DATA_Y1;
    
    uint8_t gyro_0_data;
    uint8_t gyro_1_data;
    
    
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &gyro_0_reg, 1, &gyro_0_data, 1);
    while(SERCOM0_I2C_IsBusy());
    
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &gyro_1_reg, 1, &gyro_1_data, 1);
    while(SERCOM0_I2C_IsBusy());
    
    short raw_gyro_y = (short) ((gyro_1_data << 8) | gyro_0_data);
    
    return raw_gyro_y * GYRO_SCALE / 32768.0;
}

double getGyroZ()
{
    uint8_t gyro_0_reg = ICM42605_GYRO_DATA_Z0;
    uint8_t gyro_1_reg = ICM42605_GYRO_DATA_Z1;
    
    uint8_t gyro_0_data;
    uint8_t gyro_1_data;
    
    
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &gyro_0_reg, 1, &gyro_0_data, 1);
    while(SERCOM0_I2C_IsBusy());
    
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &gyro_1_reg, 1, &gyro_1_data, 1);
    while(SERCOM0_I2C_IsBusy());
    
    short raw_gyro_z = (short) ((gyro_1_data << 8) | gyro_0_data);
    
    return raw_gyro_z * GYRO_SCALE / 32768.0;
}

void setAccelParam()
{
    uint8_t regData;
    uint8_t regAddr = ICM42605_ACCEL_CONFIG0;
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &regAddr, 1, &regData, 1);
    while(SERCOM0_I2C_IsBusy());
    
    regData = regData & 0x10;
  
    switch(ACCEL_FREQ)
    {
        case 8000:
            regData |= 0x3;
            break;
        case 4000:
            regData |= 0x4;
            break;
        case 2000:
            regData |= 0x5;
            break;
        case 1000:
            regData |= 0x6;
            break;
        case 200:
            regData |= 0x7;
            break;
        case 100:
            regData |= 0x8;
            break;
        default:
            regData |= 0x3;
            break;
    }
    switch(ACCEL_SCALE)
    {
        case 16:
            regData |= 0;
            break;
        case 8:
            regData |= (1 << 5);
            break;
        case 4:
            regData |= (2 << 5);
            break;
        case 2:
            regData |= (3 << 5);
            break;
    }
    
    uint8_t accel_config[2] = {regAddr, regData};
    SERCOM0_I2C_Write(0x69, accel_config, 2);
    while(SERCOM0_I2C_IsBusy());
            
}


void setGyroParam()
{
    uint8_t regData;
    uint8_t regAddr = ICM42605_GYRO_CONFIG0;
    SERCOM0_I2C_WriteRead(ICM42605_ADDRESS, &regAddr, 1, &regData, 1);
    while(SERCOM0_I2C_IsBusy());
    
    regData = regData & 0x10;
  
    switch(GYRO_FREQ)
    {
        case 8000:
            regData |= 0x3;
            break;
        case 4000:
            regData |= 0x4;
            break;
        case 2000:
            regData |= 0x5;
            break;
        case 1000:
            regData |= 0x6;
            break;
        case 200:
            regData |= 0x7;
            break;
        case 100:
            regData |= 0x8;
            break;
        default:
            regData |= 0x3;
            break;
    }
    switch(GYRO_SCALE)
    {
        case 2000:
            regData |= 0;
            break;
        case 1000:
            regData |= (1 << 5);
            break;
        case 500:
            regData |= (2 << 5);
            break;
        case 250:
            regData |= (3 << 5);
            break;
    }
    
    uint8_t gyro_config[2] = {regAddr, regData};
    SERCOM0_I2C_Write(0x69, gyro_config, 2);
    while(SERCOM0_I2C_IsBusy());
            
}