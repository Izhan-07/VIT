// 21BCB0007
// SJF (Shortest Job First) Scheduling

#include <stdio.h>
#include <stdbool.h>
#include<limits.h>

// Structure to represent a process
typedef struct {
    int pid; // ProcessID
    int at; // Arrival Time
    int bt; // Burst Time
    bool completed;
    int ct; // Completion Time
    int tat; // Turn around Time
    int wt; // Waiting Time
} Process;

// Function to sort the Processes based on arrival time
void sortProcesses(Process P[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (P[j].at > P[j + 1].at) {
                Process temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }
}

// Function to find the process with the shortest burst time
int findShortestJob(Process P[], int n, int currentTime) {
    int shortestJob = -1;
    int shortestBurstTime = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (P[i].at <= currentTime && !P[i].completed) {
            if (P[i].bt < shortestBurstTime) {
                shortestBurstTime = P[i].bt;
                shortestJob = i;
            }
        }
    }

    return shortestJob;
}

// Function to execute the SJF scheduling algorithm and calculate completion time, turnaround time, and waiting time
void executeSJF(Process P[], int n) {
    sortProcesses(P, n);

    int currentTime = 0;

    printf("\nGantt Chart:\n");

    while (true) {
        int shortestJob = findShortestJob(P, n, currentTime);

        if (shortestJob == -1)
            break;

        printf("P%d ", P[shortestJob].pid);

        P[shortestJob].ct = currentTime + P[shortestJob].bt;
        P[shortestJob].tat = P[shortestJob].ct - P[shortestJob].at;
        P[shortestJob].wt = P[shortestJob].tat - P[shortestJob].bt;

        P[shortestJob].completed = true;
        currentTime += P[shortestJob].bt;
    }

    printf("\n\nProcess\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (P[j].pid == i + 1) {
                printf("P%d\t%d\t\t%d\t\t%d\n", P[j].pid, P[j].ct,
                       P[j].tat, P[j].wt);
                break;
            }
        }
    }
}

float average(Process P[], int n, const char* var) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        if (var == "at")
            total += P[i].at;
        else if (var == "bt")
            total += P[i].bt;
        else if (var == "ct")
            total += P[i].ct;
        else if (var == "tat")
            total += P[i].tat;
        else if (var == "wt")
            total += P[i].wt;
        else
            total += P[i].pid;
    }
    return (float)total / n;
}

int main() {
    int n;

    printf("Enter the number of Process: ");
    scanf("%d", &n);

    Process P[n];

    printf("Pid:AT BT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d %d", &P[i].at, &P[i].bt);

        P[i].pid = i + 1;
        P[i].completed = false;
    }

    executeSJF(P, n);

    printf("Average Turn-around time: %f\n", average(P, n, "tat"));
    printf("Average waiting time: %f\n", average(P, n, "wt"));

    return 0;
}

// 21BCB0007
// By Izhan Ahmed H