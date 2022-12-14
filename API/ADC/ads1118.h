/*************
 坂本制作
ADS1118的配置文件

 2018.2.10
**************/
#ifndef ADS1118_H_
#define ADS1118_H_

#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"

#define ADS1118_SSI_BASE    SSI0_BASE
//***************REG MAP*****************
// bit_0
#define ADS1118_CONFIG_RESERVE             0x0001

#define ADS1118_CONFIG_NOP_CONFIG_VALID    0x0002
#define ADS1118_CONFIG_NOP_CONFIG_INVALID  0x0004

#define ADS1118_CONFIG_PULL_UP_EN          0x0000
#define ADS1118_CONFIG_PULL_UP_DISEN       0x0008

#define ADS1118_CONFIG_TS_MODE_ADC         0x0000
#define ADS1118_CONFIG_TS_MODE_TEMP        0x0010

#define ADS1118_CONFIG_DATA_RATE_8         0x0000
#define ADS1118_CONFIG_DATA_RATE_16        0x0020
#define ADS1118_CONFIG_DATA_RATE_32        0x0040
#define ADS1118_CONFIG_DATA_RATE_64        0x0060
#define ADS1118_CONFIG_DATA_RATE_128       0x0080
#define ADS1118_CONFIG_DATA_RATE_250       0x00A0
#define ADS1118_CONFIG_DATA_RATE_475       0x00C0
#define ADS1118_CONFIG_DATA_RATE_860       0x00E0

#define ADS1118_CONFIG_CONVERT_CONTINUE    0x0000
#define ADS1118_CONFIG_CONVERT_SINGLE      0x0100

#define ADS1118_CONFIG_PGA_6_144           0x0000
#define ADS1118_CONFIG_PGA_4_096           0x0200
#define ADS1118_CONFIG_PGA_2_048           0x0400
#define ADS1118_CONFIG_PGA_1_024           0x0600
#define ADS1118_CONFIG_PGA_0_512           0x0800
#define ADS1118_CONFIG_PGA_0_256           0x0A00

#define ADS1118_CONFIG_MUX_AINp0_AINn1     0x0000
#define ADS1118_CONFIG_MUX_AINp0_AINn3     0x1000
#define ADS1118_CONFIG_MUX_AINp1_AINn3     0x2000
#define ADS1118_CONFIG_MUX_AINp2_AINn4     0x3000
#define ADS1118_CONFIG_MUX_AINp0_AINnGND   0x4000
#define ADS1118_CONFIG_MUX_AINp1_AINnGND   0x5000
#define ADS1118_CONFIG_MUX_AINp2_AINnGND   0x6000
#define ADS1118_CONFIG_MUX_AINp3_AINnGND   0x7000

#define ADS1118_CONFIG_SS_SINGLE_ENABLE    0x8000
#define ADS1118_CONFIG_SS_INVALID          0x0000
// bit_15

#define ADS1118_CONFIG_0     ( ADS1118_CONFIG_RESERVE \
                 | ADS1118_CONFIG_NOP_CONFIG_VALID \
                 | ADS1118_CONFIG_PULL_UP_EN | ADS1118_CONFIG_TS_MODE_ADC \
                 | ADS1118_CONFIG_DATA_RATE_860 | ADS1118_CONFIG_CONVERT_CONTINUE \
                 | ADS1118_CONFIG_PGA_4_096 | ADS1118_CONFIG_MUX_AINp0_AINnGND \
                 | ADS1118_CONFIG_SS_INVALID )

#define ADS1118_CONFIG_1     ( ADS1118_CONFIG_RESERVE \
                 | ADS1118_CONFIG_NOP_CONFIG_VALID \
                 | ADS1118_CONFIG_PULL_UP_EN | ADS1118_CONFIG_TS_MODE_ADC \
                 | ADS1118_CONFIG_DATA_RATE_860 | ADS1118_CONFIG_CONVERT_CONTINUE \
                 | ADS1118_CONFIG_PGA_4_096 | ADS1118_CONFIG_MUX_AINp1_AINnGND \
                 | ADS1118_CONFIG_SS_INVALID )


//*********************外部变量声明*********************

extern uint16_t ui16RangeConvert;

//*********************外部调用函数声明*********************

extern void ADS1118_Configure();

extern void ADS1118_DataGet(float *pfDataValue);

#endif /* ADS1118_H_ */
