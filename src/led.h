#ifndef __DMI_LED_H__
#define __DMI_LED_H__

#include <stdint.h>

typedef struct _led_cfg_t
{
  uint8_t brightness;
}led_cfg_t;

extern led_cfg_t led_cfg;

void led_factory_reset(void);
void led_initialize(void);

#endif