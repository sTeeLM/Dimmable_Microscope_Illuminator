#ifndef __DMI_BUTTON_H__
#define __DMI_BUTTON_H__

#include "cext.h"
#include "task.h"

#include <stdint.h>

void button_initialize(void);
void button_proc(enum task_events ev);

#endif
