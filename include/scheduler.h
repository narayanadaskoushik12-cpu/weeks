#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_PROCESSES 50

typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int priority;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} PCB;

void sched_init(void);
int  sched_create(int pid, int burst, int priority, int arrival);
void sched_list(void);
void sched_clear(void);
void sched_run_fcfs(void);
void sched_run_sjf(void);
void sched_run_rr(int quantum);
void sched_run_priority(void);
void sched_gantt(void);
void sched_stats(void);
int  sched_handle(char **args);

#endif
