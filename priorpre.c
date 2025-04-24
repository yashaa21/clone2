#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int priority;
    int start_time;
    int response_time;
    int is_started;
};

void gantChart(struct Process p[], int schedule[], int schedule_len);

void priority_preemptive() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process P[n];
    for (int i = 0; i < n; i++) {
        P[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", P[i].pid);
        scanf("%d %d", &P[i].arrival_time, &P[i].burst_time);
        printf("Enter priority for process %d (lower number = higher priority): ", P[i].pid);
        scanf("%d", &P[i].priority);

        P[i].remaining_time = P[i].burst_time;
        P[i].is_started = 0;
    }

    int current_time = 0, completed = 0;
    int schedule[1000], sched_index = 0;

    while (completed != n) {
        int idx = -1, min_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (P[i].arrival_time <= current_time && P[i].remaining_time > 0) {
                if (P[i].priority < min_priority || (P[i].priority == min_priority && P[i].arrival_time < P[idx].arrival_time)) {
                    min_priority = P[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (P[idx].is_started == 0) {
                P[idx].start_time = current_time;
                P[idx].is_started = 1;
            }

            schedule[sched_index++] = idx;
            P[idx].remaining_time--;
            current_time++;

            if (P[idx].remaining_time == 0) {
                P[idx].completion_time = current_time;
                P[idx].turnaround_time = P[idx].completion_time - P[idx].arrival_time;
                P[idx].waiting_time = P[idx].turnaround_time - P[idx].burst_time;
                completed++;
            }
        } else {
            schedule[sched_index++] = -1;  // IDLE
            current_time++;
        }
    }

    gantChart(P, schedule, sched_index);

    printf("\n\nPID\tAT\tBT\tPRI\tST\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            P[i].pid, P[i].arrival_time, P[i].burst_time, P[i].priority,
            P[i].start_time, P[i].completion_time, P[i].turnaround_time, P[i].waiting_time);
    }

    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        totalTAT += P[i].turnaround_time;
        totalWT += P[i].waiting_time;
    }

    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
}

void gantChart(struct Process p[], int schedule[], int len) {
    printf("\nGantt Chart:\n\n");

    // Top border
    for (int i = 0; i < len; i++) {
        printf("--------");
    }

    // Process or IDLE blocks
    printf("\n|");
    for (int i = 0; i < len; i++) {
        if (schedule[i] == -1)
            printf(" IDLE  |");
        else
            printf(" P%-3d |", p[schedule[i]].pid);
    }

    // Bottom border
    printf("\n");
    for (int i = 0; i < len; i++) {
        printf("--------");
    }

    // Time labels
    printf("\n0");
    int time = 0;
    for (int i = 0; i < len; i++) {
        time++;
        printf("\t%d", time);
    }
    printf("\n");
}

int main() {
    priority_preemptive();
    return 0;
}

