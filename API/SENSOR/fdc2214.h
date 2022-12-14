/*
 * fdc2214.h
 *
 *  Created on: 2018��7��8��
 *      Author: 83456
 */

#ifndef FDC2214_H_
#define FDC2214_H_

/*=====��׼��ͷ�ļ� =============*/
#include <stdint.h>
#include <stdbool.h>
#include "BPS/I2C_drv.h"
#include "BPS/uartstdio.h"

//�궨��FDC2214��ַ
#define FDC2214_ADDR_L              0x2A
#define FDC2214_ADDR_H              0x2B

//�궨��Ĵ�����ַ
#define FDC2214_DATA_CH0            0x00
#define FDC2214_DATA_LSB_CH0        0x01
#define FDC2214_DATA_CH1            0x02
#define FDC2214_DATA_LSB_CH1        0x03
#define FDC2214_DATA_CH2            0x04
#define FDC2214_DATA_LSB_CH2        0x05
#define FDC2214_DATA_CH3            0x06
#define FDC2214_DATA_LSB_CH3        0x07

#define FDC2214_RCOUNT_CH0          0x08
#define FDC2214_RCOUNT_CH1          0x09
#define FDC2214_RCOUNT_CH2          0x0A
#define FDC2214_RCOUNT_CH3          0x0B

#define FDC2114_OFFSET_CH0          0x0C
#define FDC2114_OFFSET_CH1          0x0D
#define FDC2114_OFFSET_CH2          0x0E
#define FDC2114_OFFSET_CH3          0x0F

#define FDC2214_SETTLECOUNT_CH0     0x10
#define FDC2214_SETTLECOUNT_CH1     0x11
#define FDC2214_SETTLECOUNT_CH2     0x12
#define FDC2214_SETTLECOUNT_CH3     0x13

#define FDC2214_CLOCK_DIVIDERS_CH0  0x14
#define FDC2214_CLOCK_DIVIDERS_CH1  0x15
#define FDC2214_CLOCK_DIVIDERS_CH2  0x16
#define FDC2214_CLOCK_DIVIDERS_CH3  0x17

#define FDC2214_STATUS              0x18
#define FDC2214_ERROR_CONFIG        0x19
#define FDC2214_CONFIG              0x1A
#define FDC2214_MUX_CONFIG          0x1B
#define FDC2214_RESET_DEV           0x1C

#define FDC2214_DRIVE_CURRENT_CH0   0x1E
#define FDC2214_DRIVE_CURRENT_CH1   0x1F
#define FDC2214_DRIVE_CURRENT_CH2   0x20

#define FDC2214_DRIVE_CURRENT_CH3   0x21
#define FDC2214_MANUFACTURER_ID     0x7E
#define FDC2214_DEVICE_ID           0x7F


/************CONFIG REGISTER*****************/
#define ACTIVE_CHAN_CH0             0x0000              //��CH0��ʼ
#define ACTIVE_CHAN_CH1             0x4000
#define ACTIVE_CHAN_CH2             0x8000
#define ACTIVE_CHAN_CH3             0xC000

#define SLEEP_MODE_EN               0x2000
#define SLEEP_MODE_DIS              0x0000          //

#define SENSOR_ACTIVATE_SEL_FULL    0x0000         //
#define SENSOR_ACTIVATE_SEL_LOW     0x0800

#define REF_CLK_SRC_IN              0x0000
#define REF_CLK_SRC_EX              0x0200               //

#define INTB_DIS                    0x0000             //
#define INTB_EN                     0x0080

#define HIGH_CURRENT_DRV            0x0040
#define NORMAL_CURRENT_DRV          0x0000       //

#define CONFIG_RESERVED             0x1401


/************MUX_CONFIG REGISTER*****************/
#define AUTOSCAN_EN                 0x8000          //
#define AUTOSCAN_DIS                0x0000

#define RR_SEQUENCE_01              0x0000           //
#define RR_SEQUENCE_012             0x2000       //2114,2214 ONLY
#define RR_SEQUENCE_0123            0x4000       //2114,2214 ONLY

#define DEGLITCH_1M                 0x0001
#define DEGLITCH_3_3M               0x0004
#define DEGLITCH_10M                0x0005     //
#define DEGLITCH_33M                0x0007

#define MUX_CONFIG_RESERVED         0x0208


/************RCOUNT_CHx REGISTER*****************
 * conversion time is : 1/N * (TSAMPLE �C settling time �C channel switching delay)
 *                      = 1/2 (10,000 �C 4 �C 1) = 4.9975 ms
 * Conversion Time (tCx)= (CHx_RCOUNT*16)/fREFx
 * CHx_RCOUNT = tCx * fREFx /16 = (4.9975 * 40 * 10^3) /16 = 12493 (ENOB > 13 bits)
 * */

#define CHx_RCOUNT                  0x30CD   //Use CH0 CH1
//#define CHx_RCOUNT                  0xFFFF


/************OFFSET_CHx REGISTER*****************/
#define CHx_OFFSET                  0x0000  //not used


/************SETTLECOUNT_CHx REGISTER*****************
 * CHx_SETTLECOUNT > Vpk �� fREFx �� C �� ��2 / (32 �� IDRIVEX) --> 7.5 -->10
 * Vpk = 1.68V fREFx = 40MHz C = 53pF IDRIVEX = 0.146mA
 * settling time =  (CHx_SETTLECOUNT*16) �� fREFx = 4 us
 * */
#define CHx_SETTLECOUNT             0x000A


/************CLOCK_DIVIDERS_CHx REGISTER*****************/
#define CHx_FIN_SEL_DIV_1           0x1000
#define CHx_FIN_SEL_DIV_2           0x2000     // fSENSORx = 5.15 MHz single-end

#define CHx_FREF_DIVIDER            0x0001     // fREFx > 4*fSENSORx = 20.6 MHz --> 40MHz
                                               // fREFx = fClk / CHx_FREF_DIVIDER

#define CLOCK_DIVIDERS_CHx_RESERVED 0x0000


/************STATUS REGISTER*****************/
//For interrupt, not used


/************STATUS_CONFIG REGISTER*****************/
//For interrupt, not used


/************RESET_DEV REGISTER*****************/
#define RESET_DEV                   0x8000

//FDC2112 2114 ONLY
#define OUTPUT_GAIN_1               0x0000      //
#define OUTPUT_GAIN_4               0x0200
#define OUTPUT_GAIN_8               0x0400
#define OUTPUT_GAIN_16              0x0600


/************DRIVE_CURRENT_CHx REGISTER*****************/
#define CHx_IDRIVE                  0x7800      // IDRIVE =0.146mA for Vpk = 1.68V

/************CONFIGURATION*****************/
#define CLOCK_DIVIDERS_CHx_CONFIG           ( CHx_FIN_SEL_DIV_2 \
                                    | CHx_FREF_DIVIDER | CLOCK_DIVIDERS_CHx_RESERVED )

#define DRIVE_CURRENT_CHx_CONFIG    CHx_IDRIVE

#define SETTLECOUNT_CHx_CONFIG      CHx_SETTLECOUNT

#define RCOUNT_CHx_CONFIG           CHx_RCOUNT

#define MUX_CONFIG                           ( AUTOSCAN_EN | MUX_CONFIG_RESERVED \
                                    | RR_SEQUENCE_01 | DEGLITCH_10M )

#define CONFIG                               ( ACTIVE_CHAN_CH0 | SLEEP_MODE_DIS \
                                    | SENSOR_ACTIVATE_SEL_FULL | REF_CLK_SRC_EX \
                                    | CONFIG_RESERVED )


/************FOUR CHANNEL CONFIGURATION*****************/
#define CLOCK_DIVIDERS_CHx_CONFIG_4         ( CHx_FIN_SEL_DIV_2 \
                                    | CHx_FREF_DIVIDER | CLOCK_DIVIDERS_CHx_RESERVED )

#define DRIVE_CURRENT_CHx_CONFIG_4  CHx_IDRIVE      // ?

#define SETTLECOUNT_CHx_CONFIG_4    CHx_SETTLECOUNT

#define RCOUNT_CHx_CONFIG_4         CHx_RCOUNT      //ÿ��ͨ����������ʱ30ms

#define MUX_CONFIG_4                        ( AUTOSCAN_EN | MUX_CONFIG_RESERVED \
                                    | RR_SEQUENCE_0123 | DEGLITCH_10M )

#define CONFIG_4                            ( ACTIVE_CHAN_CH0 | SLEEP_MODE_DIS \
                                    | SENSOR_ACTIVATE_SEL_FULL | REF_CLK_SRC_EX \
                                    | CONFIG_RESERVED )
//ͨ����
typedef enum
{
    FDC2214_Channel_0 = 0x00, //ͨ��0
    FDC2214_Channel_1 = 0x01, //ͨ��1
    FDC2214_Channel_2 = 0x02, //ͨ��2
    FDC2214_Channel_3 = 0x03  //ͨ��3
}FDC2214_channel_t;

extern float capacitance_0 , capacitance_1 ;
extern float capacitance_2 , capacitance_3 ;

void FDC2214_Write16(uint8_t Slve_Addr, uint8_t reg, uint16_t data);
uint16_t FDC2214_Read16(uint8_t Slve_Addr, uint8_t reg);
extern uint8_t FDC2214_GetChannelData(FDC2214_channel_t channel, uint32_t *data);
void FDC2214_SetRcount(FDC2214_channel_t channel, uint16_t rcount);
void FDC2214_SetSettleCount(FDC2214_channel_t channel, uint16_t count);
void FDC2214_SetChannelClock(FDC2214_channel_t channel, uint16_t set);
void FDC2214_SetINTB(uint8_t mode);
void FDC2214_SetActiveChannel(FDC2214_channel_t channel);
void FDC2214_SetSleepMode(uint8_t mode);
void FDC2214_SetCurrentMode(uint8_t mode);
void FDC2214_SetClockSource(uint8_t src);
void FDC2214_SetHighCurrentMode(uint8_t mode);
void FDC2214_SetMUX_CONFIG(uint16_t mux_config);
void FDC2214_Set_CONFIG(uint16_t config);
void FDC2214_Reset(void);
void FDC2214_SetDriveCurrent(FDC2214_channel_t channel, uint16_t current);
//double FDC2214_CalculateFrequency(FDC2214_channel_t channel, uint32_t datax);
//double FDC2214_CalculateCapacitance(FDC2214_channel_t channel, double frequency, float inductance, float capacitance);
extern void FDC2214_Init(void);
extern float KalmanFilter_0(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R);
extern float KalmanFilter_1(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R);
extern float KalmanFilter_2(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R);
extern float KalmanFilter_3(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R);
extern void FDC2214_Data_Analysis(void);

#endif /* FDC2214_H_ */
