#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_completed;
};

void gantChart(struct Process p[], int Schedule[], int n);

void sjf_non_preemptive() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process P[n];
    for (int i = 0; i < n; i++) {
        P[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", P[i].pid);
        scanf("%d %d", &P[i].arrival_time, &P[i].burst_time);
        P[i].is_completed = 0;
    }

    int completed = 0, current_time = 0;
    int Schedule[n], sched_index = 0;

    while (completed != n) {
        int idx = -1;
        int min_bt = 100000; // A large number

        for (int i = 0; i < n; i++) {
            if (P[i].arrival_time <= current_time && !P[i].is_completed) {
                if (P[i].burst_time < min_bt) {
                    min_bt = P[i].burst_time;
                    idx = i;
                } else if (P[i].burst_time == min_bt) {
                    // Tie breaker - choose lower arrival time
                    if (P[i].arrival_time < P[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            P[idx].start_time = current_time;
            P[idx].completion_time = P[idx].start_time + P[idx].burst_time;
            P[idx].turnaround_time = P[idx].completion_time - P[idx].arrival_time;
            P[idx].waiting_time = P[idx].turnaround_time - P[idx].burst_time;
            P[idx].is_completed = 1;
            Schedule[sched_index++] = idx;
            current_time = P[idx].completion_time;
            completed++;
        } else {
            current_time++;
        }
    }

    gantChart(P, Schedule, n);

    printf("\n\nPID\tAT\tBT\tST\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               P[i].pid,
               P[i].arrival_time,
               P[i].burst_time,
               P[i].start_time,
               P[i].completion_time,
               P[i].turnaround_time,
               P[i].waiting_time);
    }

    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        totalTAT += P[i].turnaround_time;
        totalWT += P[i].waiting_time;
    }

    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
}

void gantChart(struct Process p[], int Schedule[], int n) {
    printf("\nGantt Chart:\n\n");

    int current_time = 0;
    int index;

    // Top border
    for (int i = 0; i < n; i++) {
        index = Schedule[i];
        if (current_time < p[index].arrival_time) {
            printf("---------");
            current_time = p[index].arrival_time;
        }
        printf("---------");
        current_time = p[index].completion_time;
    }

    // Process labels or IDLE
    printf("\n|");
    current_time = 0;
    for (int i = 0; i < n; i++) {
        index = Schedule[i];
        if (current_time < p[index].arrival_time) {
            printf(" IDLE |");
            current_time = p[index].arrival_time;
        }
        printf(" P%d   |", p[index].pid);
        current_time = p[index].completion_time;
    }

    // Bottom border
    printf("\n");
    current_time = 0;
    for (int i = 0; i < n; i++) {
        index = Schedule[i];
        if (current_time < p[index].arrival_time) {
            printf("---------");
            current_time = p[index].arrival_time;
        }
        printf("---------");
        current_time = p[index].completion_time;
    }

    // Time markers
    printf("\n0");
    current_time = 0;
    for (int i = 0; i < n; i++) {
        index = Schedule[i];
        if (current_time < p[index].arrival_time) {
            printf("\t%d", p[index].arrival_time);
            current_time = p[index].arrival_time;
        }
        printf("\t%d", p[index].completion_time);
        current_time = p[index].completion_time;
    }

    printf("\n");
}

int main() {
    sjf_non_preemptive();
    return 0;
}

