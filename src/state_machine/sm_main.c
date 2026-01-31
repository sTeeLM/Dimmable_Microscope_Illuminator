#include "sm_main.h"
#include "task.h"
#include "sm.h"
#include "cext.h"
#include "debug.h"
#include "gpio.h"
#include "delay.h"
#include "led.h"


static void do_main_init(uint8_t to_func, uint8_t to_state, enum task_events ev)
{
    if(ev == EV_KEY_C) {
      led_inc_brightness(0);
    } else if(ev == EV_KEY_F_C) {
      led_inc_brightness(1);
    } else if(ev == EV_KEY_CC) {
      led_dec_brightness(0);
    } else if(ev == EV_KEY_F_CC) {
      led_dec_brightness(1);
    }
}

static const struct sm_trans_slot code  sm_trans_main_init[] = {
  {EV_KEY_C, SM_MAIN, SM_MAIN_INIT, do_main_init},
  {EV_KEY_F_C, SM_MAIN, SM_MAIN_INIT, do_main_init},  
  {EV_KEY_CC, SM_MAIN, SM_MAIN_INIT, do_main_init},
  {EV_KEY_F_CC, SM_MAIN, SM_MAIN_INIT, do_main_init},    
  {NULL, NULL, NULL, NULL}
};


const struct sm_state_slot code sm_function_main[] = {
  {"SM_MAIN_INIT", sm_trans_main_init},
};