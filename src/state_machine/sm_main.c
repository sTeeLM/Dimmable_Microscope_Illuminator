#include "sm_main.h"
#include "task.h"
#include "sm.h"
#include "cext.h"
#include "debug.h"
#include "gpio.h"
#include "delay.h"
#include "led.h"
#include "tm1650.h"
#include "clock.h"
#include "eerom.h"

#define MAIN_IDLE_SEC 10


static void do_main_bright(uint8_t to_func, uint8_t to_state, enum task_events ev)
{
  uint16_t bright;

  if(sm_cur_state == SM_MAIN_BRIGHT_IDLE) {
    tm1650_enable_display(1);
    tm1650_clear();
  }
  
  led_set_last_state(LED_STATE_ADJ_BRIGHT);
  
  clock_set_timer(MAIN_IDLE_SEC); // every call reset timer
  
  if(ev == EV_KEY_C) {
    led_inc_brightness(0);
  } else if(ev == EV_KEY_F_C) {
    led_inc_brightness(1);
  } else if(ev == EV_KEY_CC) {
    led_dec_brightness(0);
  } else if(ev == EV_KEY_F_CC) {
    led_dec_brightness(1);
  }
  
  bright = led_get_brightness();
  
  if(bright != 1000) {
    tm1650_set_dig(3, 0, 'B');
    tm1650_set_dig(2, 0, bright / 100 + 0x30);
    tm1650_set_dig(1, 1, (bright % 100) / 10 + 0x30);
    tm1650_set_dig(0, 0, bright % 10 + 0x30);
  } else {
    tm1650_set_dig(3, 0, 'B');
    tm1650_set_dig(2, 0, '1');
    tm1650_set_dig(1, 0, '0');
    tm1650_set_dig(0, 1, '0');    
  }
  
  // 每次按下KEY也保存状态
  if(ev == EV_KEY_PRESS && sm_cur_state == SM_MAIN_COLOR) {
    eerom_save_config();
  }  
}

static void do_main_color(uint8_t to_func, uint8_t to_state, enum task_events ev)
{
  uint16_t color;
  
  if(sm_cur_state == SM_MAIN_COLOR_IDLE) {
    tm1650_enable_display(1);
    tm1650_clear();
  }
  
  led_set_last_state(LED_STATE_ADJ_COLOR);
  
  clock_set_timer(MAIN_IDLE_SEC);
  
  if(ev == EV_KEY_C) {
    led_inc_color(0);
  } else if(ev == EV_KEY_F_C) {
    led_inc_color(1);
  } else if(ev == EV_KEY_CC) {
    led_dec_color(0);
  } else if(ev == EV_KEY_F_CC) {
    led_dec_color(1);
  }
  color = led_get_color();
  
  if(color != 1000) {
    tm1650_set_dig(3, 0, 'C');
    tm1650_set_dig(2, 0, color / 100 + 0x30);
    tm1650_set_dig(1, 1, (color % 100) / 10 + 0x30);
    tm1650_set_dig(0, 0, color % 10 + 0x30);
  } else {
    tm1650_set_dig(3, 0, 'C');
    tm1650_set_dig(2, 0, '1');
    tm1650_set_dig(1, 0, '0');
    tm1650_set_dig(0, 1, '0');    
  }
  
  // 每次按下KEY也保存状态
  if(ev == EV_KEY_PRESS && sm_cur_state == SM_MAIN_BRIGHT) {
    eerom_save_config();
  }  
}

static void do_main_bright_idle(uint8_t to_func, uint8_t to_state, enum task_events ev)
{
  CDBG("do_main_bright_idle ev = %bu\n", ev);
  tm1650_enable_display(0);
  tm1650_clear();
  eerom_save_config(); // 进入空闲状态就保存一下状态
}

static void do_main_color_idle(uint8_t to_func, uint8_t to_state, enum task_events ev)
{
  CDBG("do_main_color_idle ev = %bu\n", ev);
  tm1650_enable_display(0);
  tm1650_clear();
  eerom_save_config();
}

static const struct sm_trans_slot code  sm_trans_main_bright_idle[] = { 
  {EV_KEY_C, SM_MAIN, SM_MAIN_BRIGHT, do_main_bright},
  {EV_KEY_CC, SM_MAIN, SM_MAIN_BRIGHT, do_main_bright}, 
  {EV_KEY_F_C, SM_MAIN, SM_MAIN_BRIGHT, do_main_bright},
  {EV_KEY_F_CC, SM_MAIN, SM_MAIN_BRIGHT, do_main_bright},  
  {EV_KEY_PRESS, SM_MAIN, SM_MAIN_BRIGHT, do_main_bright},    
  {NULL, NULL, NULL, NULL}
};

static const struct sm_trans_slot code  sm_trans_main_bright[] = {  
  {EV_KEY_C, SM_MAIN, SM_MAIN_BRIGHT, do_main_bright},
  {EV_KEY_CC, SM_MAIN, SM_MAIN_BRIGHT, do_main_bright}, 
  {EV_KEY_F_C, SM_MAIN, SM_MAIN_BRIGHT, do_main_bright},
  {EV_KEY_F_CC, SM_MAIN, SM_MAIN_BRIGHT, do_main_bright},  
  {EV_KEY_PRESS, SM_MAIN, SM_MAIN_COLOR, do_main_color}, 
  {EV_TIMEO, SM_MAIN, SM_MAIN_BRIGHT_IDLE, do_main_bright_idle},  
  {NULL, NULL, NULL, NULL}
};

static const struct sm_trans_slot code  sm_trans_main_color_idle[] = { 
  {EV_KEY_C, SM_MAIN, SM_MAIN_COLOR, do_main_color},
  {EV_KEY_CC, SM_MAIN, SM_MAIN_COLOR, do_main_color}, 
  {EV_KEY_F_C, SM_MAIN, SM_MAIN_COLOR, do_main_color},
  {EV_KEY_F_CC, SM_MAIN, SM_MAIN_COLOR, do_main_color},  
  {EV_KEY_PRESS, SM_MAIN, SM_MAIN_COLOR, do_main_color}, 
  {NULL, NULL, NULL, NULL}
};

static const struct sm_trans_slot code  sm_trans_main_color[] = { 
  {EV_KEY_C, SM_MAIN, SM_MAIN_COLOR, do_main_color},
  {EV_KEY_CC, SM_MAIN, SM_MAIN_COLOR, do_main_color}, 
  {EV_KEY_F_C, SM_MAIN, SM_MAIN_COLOR, do_main_color},
  {EV_KEY_F_CC, SM_MAIN, SM_MAIN_COLOR, do_main_color},  
  {EV_KEY_PRESS, SM_MAIN, SM_MAIN_BRIGHT, do_main_bright}, 
  {EV_TIMEO, SM_MAIN, SM_MAIN_COLOR_IDLE, do_main_color_idle}, 
  {NULL, NULL, NULL, NULL}
};

const struct sm_state_slot code sm_function_main[] = {
  {"SM_MAIN_BRIGHT_IDLE", sm_trans_main_bright_idle},
  {"SM_MAIN_COLOR_IDLE", sm_trans_main_color_idle},  
  {"SM_MAIN_BRIGHT", sm_trans_main_bright}, 
  {"SM_MAIN_COLOR", sm_trans_main_color},
};