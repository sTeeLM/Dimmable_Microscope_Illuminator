#include <STC8G.H>

#include "button.h"
#include "cext.h"
#include "task.h"
#include "debug.h"
#include "sm.h"
#include "delay.h"
#include "gpio.h"
#include "clock.h"

void button_initialize(void)
{

}

void button_proc(enum task_events ev)
{
  /*
  switch (ev) {
    case EV_KEY_MOD_DOWN:
      CDBG("button_mod_proc EV_KEY_MOD_DOWN\n");  
      break;           
    case EV_KEY_MOD_PRESS:
      CDBG("button_mod_proc EV_KEY_MOD_PRESS\n");  
      break;
    case EV_KEY_MOD_LPRESS:
      CDBG("button_mod_proc EV_KEY_MOD_LPRESS\n");
      break; 
    case EV_KEY_MOD_UP:
      CDBG("button_mod_proc EV_KEY_MOD_UP\n");  
      break;  
    default:
      ;
  }
  */
  sm_run(ev);
}
