#ifndef __DMI_BUTTON_H__
#define __DMI_BUTTON_H__

#include "cext.h"
#include "task.h"

#include <stdint.h>

void button_initialize(void);
void button_proc(enum task_events ev);
void button_scan_proc(enum task_events ev);

void button_reset_fast(void);

void button_reset_wake_from_key_press(void);
bit button_wake_from_key_press(void);

void button_reset_state(void);

#endif
