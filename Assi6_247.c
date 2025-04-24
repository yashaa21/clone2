#include <stdio.h>
#include <stdbool.h>
#include <string.h> 

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void firstFit(int blockSize[], int m, int processSize[], int n);
void bestFit(int blockSize[], int m, int processSize[], int n);
void worstFit(int blockSize[], int m, int processSize[], int n);
void nextFit(int blockSize[], int m, int processSize[], int n);
void printOutput(int allocation[], int n, int processSize[]);

int main() {
    int m, n;

    printf("Enter the number of blocks (max %d): ", MAX_BLOCKS);
    scanf("%d", &m);
    if (m <= 0 || m > MAX_BLOCKS) {
        printf("Invalid number of blocks!\n");
        return 1;
    }

    printf("Enter the number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &n);
    if (n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes!\n");
        return 1;
    }

    int blockSize[MAX_BLOCKS];
    int processSize[MAX_PROCESSES];
    int originalBlockSize[MAX_BLOCKS];

    printf("\nEnter the block sizes:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d -> ", i + 1);
        scanf("%d", &blockSize[i]);
        originalBlockSize[i] = blockSize[i]; // For resetting
    }

    printf("\nEnter process sizes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d -> ", i + 1);
        scanf("%d", &processSize[i]);
    }

    int ch;
    do {
        // Reset blockSize for fresh allocation every time
        for (int i = 0; i < m; i++) {
            blockSize[i] = originalBlockSize[i];
        }

        printf("\nChoose the memory allocation technique:\n");
        printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Next Fit\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("\nFirst Fit Allocation:\n");
                firstFit(blockSize, m, processSize, n);
                break;
            case 2:
                printf("\nBest Fit Allocation:\n");
                bestFit(blockSize, m, processSize, n);
                break;
            case 3:
                printf("\nWorst Fit Allocation:\n");
                worstFit(blockSize, m, processSize, n);
                break;
            case 4:
                printf("\nNext Fit Allocation:\n");
                nextFit(blockSize, m, processSize, n);
                break;
            case 5:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (ch != 5);

    return 0;
}

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printOutput(allocation, n, processSize);
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printOutput(allocation, n, processSize);
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printOutput(allocation, n, processSize);
}

void nextFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES];
    int j = 0, lastAllocated = 0;

    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n; i++) {
        int start = lastAllocated;
        bool allocated = false;

        do {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                lastAllocated = j;
                allocated = true;
                break;
            }
            j = (j + 1) % m;
        } while (j != start);

        if (!allocated) {
            allocation[i] = -1;
        }
    }
    printOutput(allocation, n, processSize);
}

void printOutput(int allocation[], int n, int processSize[]) {
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    printf("-----------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d", allocation[i] + 1);
        } else {
            printf("Not Allocated");
        }
        printf("\n");
    }
}

