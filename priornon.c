#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int is_completed;
};

void priority_non_preemptive() {
    int n, i, j;
    float avg_waiting_time = 0, avg_turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nEnter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process %d (lower number = higher priority): ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].is_completed = 0;
    }

    int completed = 0, current_time = 0;
    int gantt_process[100], gantt_start[100], gantt_end[100];
    int g_index = 0;

    while (completed != n) {
        int idx = -1;
        int min_priority = 9999;

        for (i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed) {
                if (processes[i].priority < min_priority) {
                    min_priority = processes[i].priority;
                    idx = i;
                } else if (processes[i].priority == min_priority) {
                    if (processes[i].arrival_time < processes[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            gantt_start[g_index] = current_time;
            gantt_process[g_index] = processes[idx].pid;

            current_time += processes[idx].burst_time;
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            gantt_end[g_index] = current_time;

            avg_turnaround_time += processes[idx].turnaround_time;
            avg_waiting_time += processes[idx].waiting_time;
            processes[idx].is_completed = 1;
            completed++;
            g_index++;
        } else {
            // IDLE time
            gantt_start[g_index] = current_time;
            gantt_process[g_index] = -1; // -1 means IDLE
            current_time++;
            gantt_end[g_index] = current_time;
            g_index++;
        }
    }

    // Print table
    printf("\nPID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n\n ");

    // Top bar
    for (i = 0; i < g_index; i++) {
        printf("--------");
    }
    printf("\n|");

    // Process names
    for (i = 0; i < g_index; i++) {
        if (gantt_process[i] == -1)
            printf(" IDLE  |");
        else
            printf(" P%-4d |", gantt_process[i]);
    }

    printf("\n ");

    // Bottom bar
    for (i = 0; i < g_index; i++) {
        printf("--------");
    }

    printf("\n");

    // Timeline
    printf("%d", gantt_start[0]);
    for (i = 0; i < g_index; i++) {
        printf("      %d", gantt_end[i]);
    }

    printf("\n");

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time / n);
}

int main() {
    priority_non_preemptive();
    return 0;
}

