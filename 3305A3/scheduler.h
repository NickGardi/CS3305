/******************************************************************************
*
* scheduler.h
*
******************************************************************************/

#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdlib.h>
#include <stdio.h>


#include "job.h"
#include "d_linked_list.h"
#include "helper.h"

job_t *get_next_job(int, d_linked_list_t*);

job_t *fcfs(d_linked_list_t* jobs);
job_t *lifo(d_linked_list_t* jobs);
job_t *sjf(d_linked_list_t* jobs);
job_t *rr(d_linked_list_t* jobs);

#endif
