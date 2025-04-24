#include <stdio.h>
#include<stdbool.h>

void needMatrix(int n, int m, int Max[n][m], int Need[n][m], int Alloc[n][m]) {
    printf("\nCalculating Need Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Alloc[i][j];
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }
}

void display(int n, int m, int Max[n][m], int Need[n][m], int Alloc[n][m], int Available[m]) {
    printf("\nProcess\tAllocated\tMax\t\tNeed\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", Alloc[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < m; j++) {
            printf("%d ", Max[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < m; j++) {
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }

    printf("\nAvailable Resources:\n");
    for (int j = 0; j < m; j++) {
        printf("R%d: %d\t", j, Available[j]);
    }
    printf("\n");
}
bool isSafe(int n, int m, int Alloc[n][m], int Need[n][m], int Available[m]){
int work[m];
int Finish[n];
int safeSeq[n];

  for(int i=0;i<m;i++){
 	work[i]=Available[i];
     }
  for(int i=0;i<n;i++){
  	Finish[i]=false;
  	}
  int count =0;
  while(count < n){
	  bool found = false;
  for(int i=0;i<n;i++){
	  if(!Finish[i]){
	  bool canFinish =true;
	for(int j = 0;j<m;j++){
	if(Need[i][j] > work[j]){
	canFinish =false;
		break;
				}
			}
	if(canFinish){
	for(int j=0;j<m;j++){
	work[j]=work[j]+Alloc[i][j];
				}
	safeSeq[count++]=i;
	Finish[i] =true;
	found =true;
			}
   	 	 }	
  			
  		}
  if(!found)break;
  	}
  for (int i = 0; i < n; i++) {
        if (!Finish[i]) {
            printf("\nSystem is in an UNSAFE state!\n");
            return false;
        }
    }
   printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int n, m;

    printf("Enter number of processes (n): ");
    scanf("%d", &n);
    printf("Enter number of resource types (m): ");
    scanf("%d", &m);

    int Alloc[n][m];
    int Max[n][m];
    int Need[n][m];
    int Available[m];

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("For Process P%d:\n", i);
        for (int j = 0; j < m; j++) {
            printf("Allocation[%d][%d]: ", i, j);
            scanf("%d", &Alloc[i][j]);
        }
    }

    printf("Enter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("For Process P%d:\n", i);
        for (int j = 0; j < m; j++) {
            printf("Max[%d][%d]: ", i, j);
            scanf("%d", &Max[i][j]);
        }
    }

    printf("Enter Available Resources:\n");
    for (int j = 0; j < m; j++) {
        printf("Available[%d]: ", j);
        scanf("%d", &Available[j]);
    }

    needMatrix(n, m, Max, Need, Alloc);
    display(n, m, Max, Need, Alloc, Available);

    return 0;
}

