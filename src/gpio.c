#include "gpio.h"
#include "debug.h"


void gpio_initialize(void)
{
 
  P0M0 = 0x00;
  P0M1 = 0xFF;
  P1M0 = 0x0C;  // SCL, SDA 开漏输出，DMI1，DMI2推挽输出
  P1M1 = 0xFC;
  P2M0 = 0x00;
  P2M1 = 0xFF;
  P3M0 = 0x00;
  P3M1 = 0xFC;  // serial 准双向口
  P4M0 = 0x00;
  P4M1 = 0xFF;
  P5M0 = 0x00;
  P5M1 = 0xFF;
  
  I2C_SDA   = 1;
  I2C_SCL   = 1;
  
  LED_DIM1  = 0;
  LED_DIM2  = 0;  
}


