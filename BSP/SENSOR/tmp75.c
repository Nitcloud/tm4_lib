/*************
 坂本制作
tmp75的配置文件

 2018.2.10
**************/
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "inc/hw_sysctl.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/i2c.h"

#include "APIS/I2C_Init.h"
#include "BSP/sensor/tmp75.h"


uint16_t temp;
float temp_fdegree;
double rate;

void TMP75_configure()
{
    while(I2CWriteOneByte(I2C1_BASE,TMP_ADR,TMP_CONFIG_REG&0x03,TMP_12)!=0);
}

void TMP75_function()
{
    uint16_t ui16TempValue;
    while( I2CReadTwoByte(I2C1_BASE, TMP_ADR,TMP_TEMP_REG & 0x03, &ui16TempValue)!= 0 );

    temp_fdegree = ((ui16TempValue >> 8) & 0xFF) +
                ( (float)( (ui16TempValue >> 4) & 0x0F ) ) * 0.0625;
    rate=(331.45+0.61*temp_fdegree);
}
