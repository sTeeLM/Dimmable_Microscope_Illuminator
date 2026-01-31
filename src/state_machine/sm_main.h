#ifndef __DMI_SM_MAIN_H__
#define __DMI_SM_MAIN_H__

#include <stdint.h>

#include "task.h"

enum sm_states_main
{
  SM_MAIN_BRIGHT_IDLE, // 空闲状态(来自于调整亮度)，关闭数码管显示
  SM_MAIN_COLOR_IDLE,  // 空闲状态(来自于调整色温)，关闭数码管显示
  SM_MAIN_BRIGHT,      // 调整亮度
  SM_MAIN_COLOR,       // 调整色温
};

const struct sm_state_slot code sm_function_main[];

#endif
