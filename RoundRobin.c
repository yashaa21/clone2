#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void findTime_RR(struct Process processes[], int n) {
    int completed[n];
    int remaining_time[n]; // Track remaining burst time
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
        remaining_time[i] = processes[i].burst_time;
    }

    int current_time = 0;
    int completed_processes = 0;
    int time_quantum;

    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    printf("\nGantt Chart:\n");
    printf("------------------------------------------------------------------------------------------------\n");
    
    // Round Robin Scheduling
    while (completed_processes < n) {
        int executed = 0; // Flag to track if at least one process executes

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && remaining_time[i] > 0) {
                executed = 1; // Process found and will execute
                
                printf("| P[%d] %d ", processes[i].pid, current_time);

                if (remaining_time[i] > time_quantum) {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                } else {
                    current_time += remaining_time[i];
                    processes[i].waiting_time = current_time - processes[i].arrival_time - processes[i].burst_time;
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    processes[i].completion_time = current_time;
                    remaining_time[i] = 0;
                    completed_processes++;
                }
            }
        }

        if (!executed) {
            current_time++; // If no process executes, move time forward
        }
    }

    printf("| %d |\n", current_time);
    printf("------------------------------------------------------------------------------------------------\n");
}

// Function to print process details
void printProcesses_RR(struct Process processes[], int n) {
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("P[%d]\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time,
               processes[i].completion_time);
    }

    float avg_waiting_time = 0.0, avg_turnaround_time = 0.0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

void perform_RR() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nEnter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    findTime_RR(processes, n);
    printProcesses_RR(processes, n);


}
int main(){
perform_RR();
}
