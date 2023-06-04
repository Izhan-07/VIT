// 21BCB0007
// Priority Scheduling

#include <stdio.h>
#include <stdlib.h>

struct Process {
    int priority;
    int burst; // Burst Time
    int ct; // Completion Time
    int tat; // Turn Around Time
    int wt; // Waiting Time
    int pid; // Process id number
};


void display(struct Process* p) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", p->pid, p->priority, p->burst, p->ct, p->tat, p->wt);
}

float average(struct Process* P, int n, const char* var) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        if (var == "burst")
            total += P[i].burst;
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
    printf("Enter the number of process:");
    scanf("%d", &n);
    int counter = 0;
    struct Process* P = (struct Process*)malloc(n * sizeof(struct Process));

    printf("Pid:BT Priority\n");
    for (int i = 0; i < n; i++) {
        P[i].pid = counter++;
        printf("P%d :", i);
        scanf("%d %d", &P[i].burst, &P[i].priority);
    }

    // Sorting processes based on priority
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (P[j].priority > P[j + 1].priority) {
                struct Process temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }

    printf("process\tPrior.\tburst\tcomp.\tturn-ar\twaiting\n");
    printf("id\ttime\ttime\ttime\ttime\ttime\n");
    P[0].ct = P[0].burst;
    P[0].wt = 0;
    P[0].tat = P[0].burst; 
    display(&P[0]);

    for (int i = 1; i < n; i++) {
        P[i].ct = P[i - 1].ct + P[i].burst;
        P[i].wt = P[i].ct - P[i].burst; 
        P[i].tat = P[i].wt + P[i].burst;
        display(&P[i]);
    }

    printf("Average Turn-around time: %f\n", average(P, n, "tat"));
    printf("Average waiting time: %f\n", average(P, n, "wt"));
    
    free(P);
    return 0;
}

// 21BCB0007