#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "idt.h"

#define PROCESS_COUNT 2

struct process_state {
  struct cpu_state cpu;
  struct stack_state stack;
};

void sched_update_process(unsigned int id, struct process_state *state);
struct process_state *sched_get_next_process(unsigned int current);

#endif 
