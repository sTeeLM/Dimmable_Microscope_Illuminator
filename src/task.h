#ifndef __DMI_TASK_H__
#define __DMI_TASK_H__

#include <stdint.h>

// max 32
enum task_events
{
  EV_KEY_SCAN            = 0, // 扫描按键
  EV_250MS               = 1, // 大约每250ms转一下
  EV_1S                  = 2, // 大约每1s转一下 
  EV_KEY_DOWN            = 3, // key按下
  EV_KEY_PRESS           = 4, // key短按
  EV_KEY_LPRESS          = 5, // key长按 
  EV_KEY_UP              = 6, // key抬起
  EV_KEY_CC              = 7, // key逆时针旋转，细粒度
  EV_KEY_F_CC            = 8, // key逆时针旋转，粗粒度，F for fast！  
  EV_KEY_C               = 9, // key顺时针旋转
  EV_KEY_F_C             = 10, // key顺时针旋转 ，粗粒度，F for fast！   
  EV_TIMEO               = 11, // 超时了
  EV_CNT  
};

extern uint16_t ev_bits0;
extern uint16_t ev_bits1;

extern const char * code task_names[];

typedef void (*TASK_PROC)(enum task_events);

void task_initialize (void);

void task_dump(void);

// 这些宏也在中断里被调用，所以不能是带参数函数，只能拿宏实现了
#define task_set(ev1)             \
  do{                             \
    if(ev1 < 16)                  \
      ev_bits0 |= 1<<ev1;         \
    else                          \
      ev_bits1 |= 1<<(ev1 - 16);  \
  }while(0)

#define task_clr(ev1)               \
  do{                               \
    if(ev1 < 16)                    \
      ev_bits0 &= ~(1<<ev1);        \
    else                            \
      ev_bits1 &= ~(1<<(ev1 - 16)); \
  }while(0)
    
#define  task_test(ev1)             \
  (ev1 < 16 ? (ev_bits0 & (1<<ev1)) : (ev_bits1 & (1<<(ev1 - 16))))

void task_run(void);

#endif