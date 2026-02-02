#include "sm.h"
#include "led.h"
#include "debug.h"
#include "task.h"
#include "sm_main.h"

uint8_t sm_cur_function;
uint8_t sm_cur_state;

static const struct sm_function_slot code sm_function[] =
{
  {"SM_MAIN", sm_function_main}, 
};

uint8_t sm_cur_function;
uint8_t sm_cur_state;

void sm_initialize(void)
{
  CDBG(("sm_initialize\n"));
  sm_cur_function = SM_MAIN;
  sm_cur_state = SM_MAIN_IDLE;
  task_set(EV_KEY_PRESS);
}


void sm_run(enum task_events ev)
{
  struct sm_trans_slot * p_trans = NULL;
  
  p_trans = sm_function[sm_cur_function].function_states_array[sm_cur_state].state_trans_array;
  
  while(p_trans && p_trans->sm_proc) {
    if(p_trans->event == ev) {
      p_trans->sm_proc(p_trans->to_function, p_trans->to_state, ev);
      CDBG("[%s][%s][%s]->[%s][%s]\n",
        task_names[ev],
        sm_function[sm_cur_function].function_name,
        sm_function[sm_cur_function].function_states_array[sm_cur_state].state_name,
        sm_function[p_trans->to_function].function_name,
        sm_function[p_trans->to_function].function_states_array[p_trans->to_state].state_name
      );
      sm_cur_function = p_trans->to_function;
      sm_cur_state    = p_trans->to_state;
      break;
    }
    p_trans ++;
  }
}


