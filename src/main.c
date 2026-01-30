#include <STC8G.H>

#include "debug.h"
#include "eerom.h"
#include "gpio.h"
#include "com.h"
#include "tm1650.h"
#include "led.h"
#include "delay.h"
#include "task.h"
#include "clock.h"
#include "button.h"
#include "sm.h"
#include "task.h"

void main(void)
{

  EA = 1; 
  
  debug_initialize();
  gpio_initialize();
  com_initialize();
  
  eerom_initialize();
  tm1650_initialize();
  led_initialize();
  
  clock_initialize();
  button_initialize();
  
  task_initialize();
  sm_initialize();
  
  while(1) {
    task_run();
  }
}