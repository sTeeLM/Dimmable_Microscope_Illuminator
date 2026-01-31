#ifndef __DMI_LED_H__
#define __DMI_LED_H__

#include <stdint.h>

typedef struct _led_cfg_t
{
  uint16_t brightness; /* 0 ~ 1000*/
  uint16_t color;      /* 0 ~ 1000*/
#define LED_STATE_ADJ_BRIGHT 0
#define LED_STATE_ADJ_COLOR  1
  uint8_t  last_state; // 0->brightness, 1->color
}led_cfg_t;

extern led_cfg_t led_cfg;

void led_factory_reset(void);
void led_initialize(void);

void led_inc_color(bit fast);
void led_dec_color(bit fast);
void led_inc_brightness(bit fast);
void led_dec_brightness(bit fast);
uint16_t led_get_brightness(void);
uint16_t led_get_color(void);
uint8_t led_get_last_state();
void led_set_last_state(uint8_t val);

#endif