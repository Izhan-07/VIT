// 21BCB0007
// FCFS (FIRST COME FIRST SERVE) Scheduling

#include <stdio.h>
#include <stdlib.h>

struct Process {
    int arrv; // Arrival Time
    int burst; // Busrst Time
    int ct; // Completion Time
    int tat; // Turn Around Time
    int wt; // Waiting Time
    int pid; // Process id number
};

void update_after_ct(struct Process* p) {
    p->tat = p->ct - p->arrv;
    p->wt = p->tat - p->burst;
}

void display(struct Process* p) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", p->pid, p->arrv, p->burst, p->ct, p->tat, p->wt);
}

float average(struct Process* P, int n, const char* var) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        if (var == "arrv")
            total += P[i].arrv;
        else if (var == "burst")
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

    printf("Pid:AT BT\n");
    for (int i = 0; i < n; i++) {
        P[i].pid = counter++;
        printf("P%d :", i);
        scanf("%d %d", &P[i].arrv, &P[i].burst);
    }

    // Sorting processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (P[j].arrv > P[j + 1].arrv) {
                struct Process temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }

    printf("process\tArrival\tburst\tcomp.\tturn-ar\twaiting\n");
    printf("id\ttime\ttime\ttime\ttime\ttime\n");
    P[0].ct = P[0].arrv + P[0].burst;
    update_after_ct(&P[0]);
    display(&P[0]);

    for (int i = 1; i < n; i++) {
        if (P[i].arrv < P[i - 1].ct) {
            P[i].ct = P[i - 1].ct + P[i].burst;
        } 
        else 
        {
            P[i].ct = P[i].arrv + P[i].burst;
        }
        update_after_ct(&P[i]);
        display(&P[i]);
    }

    printf("Average Turn-around time: %f\n", average(P, n, "tat"));
    printf("Average waiting time: %f\n", average(P, n, "wt"));
    
    free(P);
    return 0;
}

// 21BCB0007