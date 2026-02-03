#include <STC8G.H>

#include "led.h"
#include "debug.h"
#include "delay.h"

led_cfg_t led_cfg;

/* 0~1023 */
static void led_set_ds(uint8_t index, uint16_t value)
{
  uint8_t tmp = 0;
  
  // bits 9~10
  tmp = (value & 0x300) >> 4;
  tmp |= (value & 0x300) >> 6;
  tmp |= (value  == 0x3ff) ? 0x3 : 0;
  tmp |= 0xc0;  
  
  if(index == 0) {
    PCA_PWM0 = tmp;
    // bits 1~8
    CCAP0L = (value & 0xff);
    CCAP0H = (value & 0xff);
  } else {
    PCA_PWM1 = tmp;
    
    // bits 1~8
    CCAP1L = (value & 0xff);
    CCAP1H = (value & 0xff);
  }
  
  CL = 0x00;
  CH = 0x00;    

}

static void led_set_brightness_color_internal(uint16_t brightness, uint16_t color)
{
  uint32_t led0, led1;
  led0 = (uint32_t)color * brightness / 1000;
  led1 = (uint32_t)(1000 - color) * brightness / 1000;
  
  led_set_ds(0, 0x3ff - (uint16_t)led0);
  led_set_ds(1, 0x3ff - (uint16_t)led1);  
}

/*
  value from 0~1000
*/
static void led_set_brightness(uint16_t value)
{
  uint32_t dat = (uint32_t)value * 1023 / 1000;
  
  if(dat > 1023) dat = 1023;
  
  led_set_brightness_color_internal(dat, led_cfg.color);
  
  led_cfg.brightness = value;
}

static void led_set_color(uint16_t value)
{
  uint32_t dat = (uint32_t)led_cfg.brightness * 1023 / 1000;
  
  if(dat > 1023) dat = 1023;
  
  led_set_brightness_color_internal(dat, value);
  
  led_cfg.color = value;
}

void led_inc_color(bit fast)
{
  int16_t val;
  
  val = (int16_t)led_get_color();
  
  val += fast ? 10 : 1;
  
  if(val >= 1000)
    val = 1000;
  
  led_set_color((uint16_t)val);
}

void led_dec_color(bit fast)
{
  int16_t val;
  
  val = led_get_color();
  
  val -= fast ? 10 : 1;
  
  if(val < 0)
    val = 0;
  
  led_set_color((uint16_t)val);
}

void led_inc_brightness(bit fast)
{
  int16_t val;
  
  val = led_get_brightness();
  
  val += fast ? 10 : 1;
  
  if(val >= 1000)
    val = 1000;
  
  led_set_brightness((uint16_t)val);
}

void led_dec_brightness(bit fast)
{
  int16_t val;
  
  val = (int16_t)led_get_brightness();
  
  val -= fast ? 10 : 1;
  
  if(val < 0)
    val = 0;
   
  led_set_brightness((uint16_t)val);
}

uint16_t led_get_brightness()
{
  return led_cfg.brightness;
}

uint16_t led_get_color()
{
  return led_cfg.color;
}

/* 
  set brightness to 0
      color to 0
  dont save led_cfg.brightness & led_cfg.color
*/
void led_power_off(void)
{
  led_set_brightness_color_internal(0, 0);
}

/* 
  restore from config
  led_cfg.brightness
  led_cfg.color
*/
void led_power_on(void)
{
  led_set_brightness_color_internal(led_cfg.brightness, led_cfg.color);
}

void led_factory_reset(void)
{
  CDBG("led_factory_reset\n");
  led_cfg.brightness = 500;
  led_cfg.color = 0;  
}

void led_initialize(void)
{
  CDBG("led_initialize\n");
  
  CCON = 0x00;
  CMOD = 0x00; //PCA 时钟为系统时钟/12
  CL = 0x00;
  CH = 0x00;  
  /*
  12位PWM
    当EPCnH=0,XCCAPnH=0及CCAPnH=00H时，PWM固定输出高
    当EPCnH=1,XCCAPnH=3及CCAPnH=FFH时，PWM固定输出低
  
  占空比计算：
    0%[(400H-value)/400H]
    value =  [EPCnH][XCCAPnH[1:0]][CCAPnH], 11 bits
    0x000（占空比100%） -> 0x3FF（占空比0%），一共1024个设置
  */  
  CCAPM0 = 0x42; //PCA 模块0 为PWM工作模式，无中断
  PCA_PWM0 = 0xFF; //PCA 模块0 输出10 位PWM，频率 时钟/(1024*12)
  CCAP0L = 0xFF; //PWM 占空比为0%[(400H-400H)/400H]
  CCAP0H = 0xFF;
  
  CCAPM1 = 0x42; //PCA 模块1 为PWM工作模式，无中断
  PCA_PWM1 = 0xFF; //PCA 模块1 输出10 位PWM，频率 时钟/(1024*12)
  CCAP1L = 0xFF; //PWM 占空比为0%[(400H-400H)/400H]
  CCAP1H = 0xFF;  
  
  led_power_on();
  
  CR = 1; //启动PCA 计时器
}