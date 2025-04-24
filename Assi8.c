#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void FCFS(int requests[], int n, int head);
void SSTF(int requests[], int n, int head);
void SCAN(int requests[], int n, int head, int disk_size, char direction[]);
void C_SCAN(int requests[], int n, int head, int disk_size, char direction[]);

int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, head, disk_size, choice;
    char direction[10];

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    do {
        printf("\nChoose Disk Scheduling Algorithm:\n");
        printf("1. FCFS (First Come First Serve)\n");
        printf("2. SSTF (Shortest Seek Time First)\n");
        printf("3. SCAN\n");
        printf("4. C-SCAN\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3 || choice == 4) {
            printf("Enter direction (left/right): ");
            scanf("%s", direction);
        }

        switch (choice) {
            case 1:
                FCFS(requests, n, head);
                break;
            case 2:
                SSTF(requests, n, head);
                break;
            case 3:
                SCAN(requests, n, head, disk_size, direction);
                break;
            case 4:
                C_SCAN(requests, n, head, disk_size, direction);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}


void FCFS(int requests[], int n, int head) {
    int total = 0;
    printf("\nFCFS Disk Scheduling Order: %d", head);

    for (int i = 0; i < n; i++) {
        total += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", requests[i]);
    }

    printf("\nTotal Head Movement: %d\n", total);
}

void SSTF(int requests[], int n, int head) {
    int total = 0, visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    printf("\nSSTF Disk Scheduling Order: %d", head);

    for (int count = 0; count < n; count++) {
        int min = INT_MAX, idx = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && abs(requests[i] - head) < min) {
                min = abs(requests[i] - head);
                idx = i;
            }
        }
        if (idx == -1) break;
        visited[idx] = 1;
        total += min;
        head = requests[idx];
        printf(" -> %d", requests[idx]);
    }

    printf("\nTotal Head Movement: %d\n", total);
}

void SCAN(int requests[], int n, int head, int disk_size, char direction[]) {
    int total = 0;
    int left[n], right[n], l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    qsort(left, l, sizeof(int), cmpfunc);
    qsort(right, r, sizeof(int), cmpfunc);

    printf("\nSCAN Disk Scheduling Order: %d", head);

    if (strcmp(direction, "left") == 0) {
        for (int i = l - 1; i >= 0; i--) {
            total += abs(head - left[i]);
            head = left[i];
            printf(" -> %d", head);
        }
        total += head;
        head = 0;
        printf(" -> 0");

        for (int i = 0; i < r; i++) {
            total += abs(right[i] - head);
            head = right[i];
            printf(" -> %d", head);
        }
    } else {
        for (int i = 0; i < r; i++) {
            total += abs(right[i] - head);
            head = right[i];
            printf(" -> %d", head);
        }
        total += abs((disk_size - 1) - head);
        head = disk_size - 1;
        printf(" -> %d", head);

        for (int i = l - 1; i >= 0; i--) {
            total += abs(head - left[i]);
            head = left[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Head Movement: %d\n", total);
}

void C_SCAN(int requests[], int n, int head, int disk_size, char direction[]) {
    int total = 0;
    int left[n], right[n], l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    qsort(left, l, sizeof(int), cmpfunc);
    qsort(right, r, sizeof(int), cmpfunc);

    printf("\nC-SCAN Disk Scheduling Order: %d", head);

    if (strcmp(direction, "left") == 0) {
        for (int i = l - 1; i >= 0; i--) {
            total += abs(head - left[i]);
            head = left[i];
            printf(" -> %d", head);
        }
        total += head;
        head = 0;
        printf(" -> 0");

        total += (disk_size - 1);
        head = disk_size - 1;
        printf(" -> %d", head);

        for (int i = r - 1; i >= 0; i--) {
            total += abs(head - right[i]);
            head = right[i];
            printf(" -> %d", head);
        }
    } else {
        for (int i = 0; i < r; i++) {
            total += abs(right[i] - head);
            head = right[i];
            printf(" -> %d", head);
        }
        total += abs((disk_size - 1) - head);
        head = disk_size - 1;
        printf(" -> %d", head);

        total += head;
        head = 0;
        printf(" -> 0");

        for (int i = 0; i < l; i++) {
            total += abs(left[i] - head);
            head = left[i];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Head Movement: %d\n", total);
}

