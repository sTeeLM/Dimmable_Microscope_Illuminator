#include <STC8G.H>

#include "button.h"
#include "cext.h"
#include "task.h"
#include "debug.h"
#include "sm.h"
#include "delay.h"
#include "gpio.h"
#include "clock.h"

// 连续转多少个刻度之后，变成粗调（增大step）
#define KEY_MAX_FAST_CNT 10
#define KEY_LPRESS_DELAY 3

static bit key_down;
static bit key_lpress_send;
static uint32_t key_down_sec;
static uint8_t key_down_cnt;
static uint8_t key_c_cnt;
static uint8_t key_cc_cnt;

void button_initialize(void)
{
  CDBG("button_initialize\n");  
  EX0 = 1;
  IT0 = 1; // 下降沿触发 
  EX1 = 1;
  IT1 = 1; // 下降沿触发
  
  key_c_cnt  = 0;
  key_cc_cnt = 0;
  key_down   = 0;
  key_lpress_send = 0;
  key_down_sec = 0;
  key_down_cnt = 0;
}

static void button_A_ISR (void) interrupt 0 using 1
{
  delay_10us(10);
  
  if(!BUTTON_INT0) {
    if(!BUTTON_A && !BUTTON_B) {
      if(key_c_cnt < KEY_MAX_FAST_CNT) {
        task_set(EV_KEY_C);
        key_c_cnt ++;
      } else {
        task_set(EV_KEY_F_C);
      }
      key_cc_cnt = 0;
    } else if(!BUTTON_A && BUTTON_B){
      if(key_cc_cnt < KEY_MAX_FAST_CNT) {
        task_set(EV_KEY_CC);
        key_cc_cnt ++;
      } else {
        task_set(EV_KEY_F_CC);
      }
      key_c_cnt = 0;
    }
  }

  IE0 = 0;
}

static void button_KEY_ISR (void) interrupt 2 using 1
{
  key_cc_cnt = key_c_cnt = 0;
  IE1 = 0;
}

void button_scan_proc(enum task_events ev)
{
  if(!BUTTON_KEY) {
    if(key_down == 0) {
      key_down = 1;
      task_set(EV_KEY_DOWN);
      key_down_sec = clock_get_now_sec();
    }
  } else {
    if(key_down == 1) {
      if(!key_lpress_send) {
        task_set(EV_KEY_PRESS);
      }
      key_down = 0;
      key_lpress_send = 0;
      task_set(EV_KEY_UP);
    }
  }
  
 
  if(key_down) {
    if(clock_diff_now_sec(key_down_sec) > KEY_LPRESS_DELAY) {
      task_set(EV_KEY_LPRESS);
      key_lpress_send = 1;
    }
  }
}

void button_proc(enum task_events ev)
{

  switch (ev) {
    case EV_KEY_CC:
      CDBG("button_proc EV_KEY_CC\n");  
      break;           
    case EV_KEY_C:
      CDBG("button_proc EV_KEY_C\n");  
      break; 
    case EV_KEY_F_CC:
      CDBG("button_proc EV_KEY_F_CC\n");  
      break;           
    case EV_KEY_F_C:
      CDBG("button_proc EV_KEY_F_C\n");  
      break; 
    case EV_KEY_DOWN:
      CDBG("button_proc EV_KEY_DOWN\n");  
      break; 
    case EV_KEY_PRESS:
      CDBG("button_proc EV_KEY_PRESS\n");  
      break;           
    case EV_KEY_LPRESS:
      CDBG("button_proc EV_KEY_LPRESS\n");  
      break;     
    case EV_KEY_UP:
      CDBG("button_proc EV_KEY_UP\n");  
      break;     
    default:
      ;
  }
  sm_run(ev);
}
