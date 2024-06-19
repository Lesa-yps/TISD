#ifndef SIMULATE_DINAM_H
#define SIMULATE_DINAM_H

#include "const_struct.h"
#include "help_func.h"

#include <string.h>

int simulate_dinam(int talk, int own, double min_time_come, double max_time_come, double min_time_work, double max_time_work,\
                   struct Inf_oueue *infa_q1, struct AO *ao1);

#endif // SIMULATE_DINAM_H
