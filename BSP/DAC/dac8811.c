#include "BSP/DAC/dac8811.h"

/*******************************************
函数名称：Dac7811__IO_Init
功    能：初始化SPI总线引脚
参    数：无
返回值  ：无
********************************************/
void DAC8811_IO_Init()        //DAC7811 SPI初始化
{
  //Init GPIOM
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
  // Check if the peripheral access is enabled.
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM))
	{
	}	
	GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6);
	
	GPIOPadConfigSet(GPIO_PORTM_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

}

/*******************************************
函数名称：DAC_Conver
功    能：对一个16位二进制命令作出响应
参    数：temp-16位二进制命令
返回值  ：无
********************************************/

void DAC8811_Transform(uint16_t temp)
{
        uint8_t i;
        DAC8811_CLK_CLR;
        delay_us(1);
        DAC8811_CS_CLR;     //拉低片选，开启数据传输
        delay_us(1);   
        for(i=0;i<16;i++)
        {
        	if(temp & 0x8000) {DAC8811_SDA_SET;} //数据最低位为0则置低数据线，否则拉高
            else  {DAC8811_SDA_CLR;}
            DAC8811_CLK_SET;
            delay_us(1);
            temp<<=1;
            delay_us(1);
            DAC8811_CLK_CLR;        //上升沿读取数据
        }
        DAC8811_CS_SET;
        delay_us(1);
        DAC8811_CLK_SET; 
}

/*******************************************
函数名称： VoltOfData
功    能：将模拟电压值转换为16位二进制数
参    数：out_volt-模拟电压值
返回值  ：16位二进制数
补充：//(uint)(out_volt*4095)/(2*2.048) 先将电压值转化为0~4095的整数
        //0x0fff&  转化成16位二进制数，后12位为数据位
********************************************/
uint16_t VoltOfData(float out_volt) //说明ref为参考源out_volt为输出模拟电压值
{ 
   int temp2;
   temp2=(unsigned int)(out_volt*10700+32768);
   return(temp2&0xffff);
}//将电压值转换为对应的16位数字量函数

/*******************************************
函数名称： Write_Data
功    能：像通道写数据
参    数：out_volt-模拟电压值
返回值  ：无
补充：//(uint)(out_volt*4095)/(2*2.048) 先将电压值转化为0~4095的整数
        //0x0fff&  转化成16位二进制数，后12位为数据位
        //0xc000|  前面加上4位为1100（命令位）：快速模式，正常功耗，写数据到A通道
********************************************/
void Write_Data(float out_volt)
{
   int Data;
   Data=VoltOfData(out_volt);
   DAC8811_Transform(Data);
}

/*******************************************
Function name              :ADS1115_DemoTask
Function use               :Run the AD9959 to set Frequency of channel 2,3
Function parameter         :None
Function return            :None
********************************************/
void DAC8811_DemoTask(float DAC8811Value)
{	
	DAC8811_IO_Init();
	Write_Data(DAC8811Value);
}

