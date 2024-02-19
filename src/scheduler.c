#include "scheduler.h"

static struct process_state processes[PROCESS_COUNT];

void sched_update_process(unsigned int id, struct process_state *state) {
  processes[id] = *state;
}

struct process_state *sched_get_next_process(unsigned int current) {

  return &processes[(current + 1) % PROCESS_COUNT];
}
