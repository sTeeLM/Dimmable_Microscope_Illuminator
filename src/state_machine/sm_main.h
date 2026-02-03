#ifndef __DMI_SM_MAIN_H__
#define __DMI_SM_MAIN_H__

#include <stdint.h>

#include "task.h"

enum sm_states_main
{
  SM_MAIN_STOP,    // 待机状态
  SM_MAIN_IDLE,        // 空闲状态
  SM_MAIN_BRIGHT,      // 调整亮度
  SM_MAIN_COLOR,       // 调整色温
};

const struct sm_state_slot code sm_function_main[];

#endif
