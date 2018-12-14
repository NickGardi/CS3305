/******************************************************************************
*
* scheduler.c 
*
******************************************************************************/
#include "scheduler.h"

#define FCFS 0
#define LIFO 1
#define SJF 2
#define RR 3

job_t *get_next_job(int mode, d_linked_list_t* jobs) {
	int i;
	if (mode == FCFS) {
		job_t *job;
		job = dequeue(jobs);
		return job;
	}else if (mode == LIFO){
		job_t *job;
		job = pop(jobs);
		return job;
	}else if (mode == SJF){
		job_t *list;
		job_t *job = dequeue(jobs);
		for(i=0;i<jobs->size;i++){
			list = dequeue(jobs);
			if(job->required_time > list->required_time){
				enqueue(jobs, job);
				job = list;			
			}else{
				enqueue(jobs, list);
			}		
		}
	return job;
	}else if (mode == RR){
		job_t *job;
		job = dequeue(jobs);
		if (jobs == NULL){
			job = pop(jobs);
			return job;
		}
	}else{
		printf("Invalid scheduling type");	
	}

}
