#include "sm_main.h"
#include "task.h"
#include "sm.h"
#include "cext.h"
#include "debug.h"
#include "gpio.h"
#include "delay.h"


static void do_main_init(uint8_t to_func, uint8_t to_state, enum task_events ev)
{
    
}

static const struct sm_trans_slot code  sm_trans_main_init[] = {
  {NULL, NULL, NULL, NULL}
};


const struct sm_state_slot code sm_function_main[] = {
  {"SM_MAIN_INIT", sm_trans_main_init},
};