#include "sched.h"

#define MAX_TICKETS 5
#define MIN_TICKETS 1
/* Structure to store RR thread-specific fields */
struct lottery_data {
	int tickets ;
};

static int task_new_lottery(task_t* t)
{
	struct lottery_data* cs_data=malloc(sizeof(struct lottery_data));

		if (!cs_data)
			return 1;  /* Cannot reserve memory */

		/* initialize tickets rand*/
		srand(time(NULL));
		cs_data->tickets = (rand() % MAX_TICKETS+MIN_TICKETS);

		t->tcs_data=cs_data;
		return 0;
}

static void task_free_lottery(task_t* t)
{
	if (t->tcs_data) {
		free(t->tcs_data);
		t->tcs_data=NULL;
	}
}

static task_t* pick_next_task_lottery(runqueue_t* rq)
{
	task_t* t=head_slist(&rq->tasks);

	/* Current is not on the rq -> let's remove it */
	if (t) 
		remove_slist(&rq->tasks,t);

	return t;
}


static int compare_tasks_cpu_burst(void *t1,void *t2)
{

	task_t* tsk1=(task_t*)t1;
	task_t* tsk2=(task_t*)t2;

	return tsk1->prio-tsk2->prio; //prioridad de tarea
}

static void enqueue_task_lottery(task_t* t,runqueue_t* rq, int preempted)
{

	if (t->on_rq || is_idle_task(t))
		return;


	if (t->flags & TF_INSERT_FRONT) {
		//Clear flag
		t->flags&=~TF_INSERT_FRONT;
		sorted_insert_slist_front(&rq->tasks, t, 1, compare_tasks_cpu_burst);  //Push task
	} else
		sorted_insert_slist(&rq->tasks, t, 1, compare_tasks_cpu_burst);  //Push task

	/* If the task was not using the current CPU, check whether a preemption is in order or not */
		if (!preempted) {
			task_t* current=rq->cur_task;

			/* Trigger a preemption if this task has a shorter CPU burst than current */
			if (preemptive_scheduler) {
				rq->need_resched=TRUE;
				current->flags|=TF_INSERT_FRONT; /* To avoid unfair situations in the event
	                                                another task with the same length wakes up as well*/
			}
		}

}
static void task_tick_lottery(runqueue_t* rq)
{




	task_t* current=rq->cur_task;
	struct lottery_data* cs_data=(struct lottery_data*) current->tcs_data;

	if (is_idle_task(current))
		return;

	cs_data->tickets--; /* Charge tick */

	if (cs_data->tickets<=0)
		rq->need_resched=TRUE; //Force a resched !!
}

static task_t* steal_task_lottery(runqueue_t* rq)
{
	task_t* t=tail_slist(&rq->tasks);

	if (t) 
		remove_slist(&rq->tasks,t);

	return t;
}

sched_class_t lottery_sched= {
	.task_new		=	task_new_lottery,
	.task_free		=	task_free_lottery,
	.pick_next_task	=	pick_next_task_lottery,
	.enqueue_task	=	enqueue_task_lottery,
	.task_tick		=	task_tick_lottery,
	.steal_task		=	steal_task_lottery
};
