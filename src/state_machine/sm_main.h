#ifndef __DMI_SM_MAIN_H__
#define __DMI_SM_MAIN_H__

#include <stdint.h>

#include "task.h"

enum sm_states_main
{
  SM_MAIN_INIT,
};

const struct sm_state_slot code sm_function_main[];

#endif
