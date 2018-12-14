#include "simulate.h"

int memory, max_memory;
FILE *fp;
linked_stack_t *jobs;

void simulate(int memory_value, linked_stack_t *stack)
{
	int i;
  	int k;
  	//stack of jobs
  	jobs = stack;
	//memory
  	max_memory = memory_value;
  	memory = max_memory;
	//file pointer
  	fp = fopen(SYSTEM_OUTPUT, "w");
  	//array of threads
  	pthread_t thread[NUMBER_OF_THREADS];
	//while there are jobs on stack
  	while(jobs->size != 0){
		//loop NUMBER_OF_THREADS times
    		for(i = 0; i < NUMBER_OF_THREADS; i++){
			//if job is not null
      			if (jobs->head != NULL){
			   //pop job	
      			   job_t *job = pop(jobs);
      			   //check for available memory.
      			   //if there is not enough memory, move to the next job or exit.
      			   if (job->required_memory > max_memory) {
      			     print_exceed_memory(fp, job->number);
      			     continue;
      			   }
			   //amount of available memory
      			   int memory_left = memory - job->required_memory;
      			   //if job will consume more memory than available, push it back onto stack and go to next job
      			   if (memory == 0 || memory_left < 0) {
      			     print_insufficient_memory(fp, job->number);
      			     push(jobs, job);
      			     continue;
      			   }
      			   //start the job.
      			   print_allocate_memory(fp, memory, job->required_memory);
       				 pthread_create(&thread[i], NULL, do_work, job);
       				 //update currently available memory.
       				 memory = memory_left;
     				 }  
      				else{
        				break;
     				 }
   		 }
    		for( k = 0; k < i; k++){
     			 pthread_join(thread[k], NULL);
   		 }
  	}

  	fclose(fp);
}



void *do_work(void *input)
{
   //input is a job object
   job_t *job = (job_t *)input;
   //job is running
   print_starting(fp, job->number);
   //sleep for required time
   sleep(job->required_time);
   //memory being deallocated
   print_deallocate_memory(fp, memory, job->required_memory);
   //update memory
   memory = memory + job->required_memory;
   //job has finished
   print_completed(fp, job->number);
}
