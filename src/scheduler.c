#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"

static PCB processes[MAX_PROCESSES];
static int process_count = 0;
static int gantt_pids[200];
static int gantt_times[200];
static int gantt_len = 0;
static char last_algo[32] = "None";

void sched_init(void) {
    process_count = 0;
    gantt_len = 0;
    strcpy(last_algo, "None");
}

int sched_create(int pid, int burst, int priority, int arrival) {
    if (process_count >= MAX_PROCESSES) {
        printf("Error: Process table full\n");
        return 0;
    }
    PCB *p = &processes[process_count++];
    p->pid = pid;
    p->burst_time = burst;
    p->remaining_time = burst;
    p->priority = priority;
    p->arrival_time = arrival;
    p->waiting_time = 0;
    p->turnaround_time = 0;
    p->completion_time = 0;
    printf("Process P%d created (burst=%d, priority=%d, arrival=%d)\n",
           pid, burst, priority, arrival);
    return 1;
}

void sched_list(void) {
    if (process_count == 0) {
        printf("No processes in queue.\n");
        return;
    }
    printf("\n%-6s %-8s %-10s %-10s\n", "PID", "Burst", "Priority", "Arrival");
    printf("------------------------------------\n");
    for (int i = 0; i < process_count; i++) {
        printf("P%-5d %-8d %-10d %-10d\n",
               processes[i].pid, processes[i].burst_time,
               processes[i].priority, processes[i].arrival_time);
    }
}

void sched_clear(void) {
    process_count = 0;
    gantt_len = 0;
    printf("All simulated processes cleared.\n");
}

void sched_gantt(void) {
    if (gantt_len == 0) {
        printf("No Gantt data.\n");
        return;
    }
    printf("Gantt Chart: ");
    for (int i = 0; i < gantt_len; i++) {
        printf("| P%d ", gantt_pids[i]);
    }
    printf("|\n");
    printf("             0");
    for (int i = 0; i < gantt_len; i++) {
        printf("%5d", gantt_times[i]);
    }
    printf("\n");
}

void sched_stats(void) {
    if (process_count == 0) return;
    float total_wait = 0, total_tat = 0;
    printf("\n%-6s %-8s %-10s %-12s\n",
           "PID", "Wait", "Turnaround", "Completion");
    printf("------------------------------------------\n");
    for (int i = 0; i < process_count; i++) {
        printf("P%-5d %-8d %-10d %-12d\n",
               processes[i].pid, processes[i].waiting_time,
               processes[i].turnaround_time, processes[i].completion_time);
        total_wait += processes[i].waiting_time;
        total_tat  += processes[i].turnaround_time;
    }
    printf("\nAverage Waiting Time    : %.2f\n", total_wait / process_count);
    printf("Average Turnaround Time : %.2f\n", total_tat / process_count);
}

void sched_run_fcfs(void) {
    if (process_count == 0) { printf("No processes.\n"); return; }
    for (int i = 0; i < process_count - 1; i++) {
        for (int j = 0; j < process_count - i - 1; j++) {
            if (processes[j].arrival_time > processes[j+1].arrival_time) {
                PCB tmp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = tmp;
            }
        }
    }
    int time = 0;
    gantt_len = 0;
    strcpy(last_algo, "FCFS");
    for (int i = 0; i < process_count; i++) {
        if (time < processes[i].arrival_time)
            time = processes[i].arrival_time;
        processes[i].waiting_time = time - processes[i].arrival_time;
        time += processes[i].burst_time;
        processes[i].completion_time = time;
        processes[i].turnaround_time =
            processes[i].completion_time - processes[i].arrival_time;
        gantt_pids[gantt_len] = processes[i].pid;
        gantt_times[gantt_len] = time;
        gantt_len++;
    }
    printf("=== First-Come-First-Served ===\n");
    sched_gantt();
    sched_stats();
}

void sched_run_sjf(void) {
    if (process_count == 0) { printf("No processes.\n"); return; }
    for (int i = 0; i < process_count - 1; i++) {
        for (int j = 0; j < process_count - i - 1; j++) {
            if (processes[j].burst_time > processes[j+1].burst_time) {
                PCB tmp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = tmp;
            }
        }
    }
    int time = 0;
    gantt_len = 0;
    strcpy(last_algo, "SJF");
    for (int i = 0; i < process_count; i++) {
        if (time < processes[i].arrival_time)
            time = processes[i].arrival_time;
        processes[i].waiting_time = time - processes[i].arrival_time;
        time += processes[i].burst_time;
        processes[i].completion_time = time;
        processes[i].turnaround_time =
            processes[i].completion_time - processes[i].arrival_time;
        gantt_pids[gantt_len] = processes[i].pid;
        gantt_times[gantt_len] = time;
        gantt_len++;
    }
    printf("=== Shortest Job First ===\n");
    sched_gantt();
    sched_stats();
}

void sched_run_rr(int quantum) {
    if (process_count == 0) { printf("No processes.\n"); return; }
    if (quantum <= 0) { printf("Invalid quantum\n"); return; }
    for (int i = 0; i < process_count; i++)
        processes[i].remaining_time = processes[i].burst_time;
    int time = 0, done = 0;
    gantt_len = 0;
    strcpy(last_algo, "Round Robin");
    while (done < process_count) {
        for (int i = 0; i < process_count; i++) {
            if (processes[i].remaining_time <= 0) continue;
            if (processes[i].arrival_time > time) continue;
            int slice = (processes[i].remaining_time < quantum)
                        ? processes[i].remaining_time : quantum;
            processes[i].remaining_time -= slice;
            time += slice;
            gantt_pids[gantt_len] = processes[i].pid;
            gantt_times[gantt_len] = time;
            gantt_len++;
            if (processes[i].remaining_time == 0) {
                processes[i].completion_time = time;
                processes[i].turnaround_time =
                    time - processes[i].arrival_time;
                processes[i].waiting_time =
                    processes[i].turnaround_time - processes[i].burst_time;
                done++;
            }
        }
    }
    printf("=== Round Robin (quantum=%d) ===\n", quantum);
    sched_gantt();
    sched_stats();
}

void sched_run_priority(void) {
    if (process_count == 0) { printf("No processes.\n"); return; }
    for (int i = 0; i < process_count - 1; i++) {
        for (int j = 0; j < process_count - i - 1; j++) {
            if (processes[j].priority > processes[j+1].priority) {
                PCB tmp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = tmp;
            }
        }
    }
    int time = 0;
    gantt_len = 0;
    strcpy(last_algo, "Priority");
    for (int i = 0; i < process_count; i++) {
        if (time < processes[i].arrival_time)
            time = processes[i].arrival_time;
        processes[i].waiting_time = time - processes[i].arrival_time;
        time += processes[i].burst_time;
        processes[i].completion_time = time;
        processes[i].turnaround_time =
            processes[i].completion_time - processes[i].arrival_time;
        gantt_pids[gantt_len] = processes[i].pid;
        gantt_times[gantt_len] = time;
        gantt_len++;
    }
    printf("=== Priority Scheduling ===\n");
    sched_gantt();
    sched_stats();
}

int sched_handle(char **args) {
    if (args[0] == NULL || strcmp(args[0], "sched") != 0)
        return 0;
    if (args[1] == NULL) {
        printf("Usage: sched <create|list|run|gantt|stats|clear>\n");
        return 1;
    }
    if (strcmp(args[1], "create") == 0) {
        if (args[2] && args[3] && args[4] && args[5])
            sched_create(atoi(args[2]), atoi(args[3]),
                         atoi(args[4]), atoi(args[5]));
        else
            printf("Usage: sched create <pid> <burst> <priority> <arrival>\n");
        return 1;
    }
    if (strcmp(args[1], "list") == 0)  { sched_list();  return 1; }
    if (strcmp(args[1], "clear") == 0) { sched_clear(); return 1; }
    if (strcmp(args[1], "gantt") == 0) { sched_gantt(); return 1; }
    if (strcmp(args[1], "stats") == 0) { sched_stats(); return 1; }
    if (strcmp(args[1], "run") == 0) {
        if (args[2] == NULL) {
            printf("Usage: sched run <fcfs|sjf|rr|priority> [quantum]\n");
            return 1;
        }
        if (strcmp(args[2], "fcfs") == 0)     sched_run_fcfs();
        else if (strcmp(args[2], "sjf") == 0) sched_run_sjf();
        else if (strcmp(args[2], "rr") == 0) {
            int q = args[3] ? atoi(args[3]) : 4;
            sched_run_rr(q);
        }
        else if (strcmp(args[2], "priority") == 0) sched_run_priority();
        else printf("Unknown algorithm: %s\n", args[2]);
        return 1;
    }
    printf("Unknown sched command: %s\n", args[1]);
    return 1;
}
