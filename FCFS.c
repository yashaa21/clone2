#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void gantChart(struct Process p[], int Schedule[], int n);

// Sort processes by arrival time using bubble sort
void bubsort(struct Process P[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (P[j].arrival_time > P[j + 1].arrival_time) {
                struct Process temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }
}

void fcfs() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process P[n];
    for (int i = 0; i < n; i++) {
        P[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", P[i].pid);
        scanf("%d %d", &P[i].arrival_time, &P[i].burst_time);
    }

    bubsort(P, n);

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (P[i].arrival_time > current_time) {
            current_time = P[i].arrival_time;
        }
        P[i].start_time = current_time;
        current_time += P[i].burst_time;
        P[i].completion_time = current_time;
        P[i].turnaround_time = P[i].completion_time - P[i].arrival_time;
        P[i].waiting_time = P[i].turnaround_time - P[i].burst_time;
    }

    int Schedule[n];
    for (int i = 0; i < n; i++) {
        Schedule[i] = i;
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
    fcfs();
    return 0;
}
