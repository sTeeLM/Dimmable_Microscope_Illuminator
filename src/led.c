#include "led.h"
#include "debug.h"
#include "delay.h"

led_cfg_t led_cfg;

void led_factory_reset(void)
{
    
}

void led_initialize(void)
{
  CDBG("led_initialize\n");
  
  CCON = 0x00;
  CMOD = 0x08; //PCA 时钟为系统时钟
  CL = 0x00;
  CH = 0x00;  
  
  CCAPM0 = 0x42; //PCA 模块0 为PWM 工作模式
  PCA_PWM0 = 0xc0; //PCA 模块0 输出10 位PWM
  CCAP0L = 0x20; //PWM 占空比为96.875%[(400H-20H)/400H]
  CCAP0H = 0x20;
  
  CR = 1; //启动PCA 计时器
}