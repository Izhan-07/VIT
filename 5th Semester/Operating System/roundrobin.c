// 21BCB0007
// Round Robin Scheduling

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct P
{
    int at; //Arrival Time
    int bt; //Burst Time
    int st[20]; // Start Time
    int wt; //Waiting Time
    int ft; // Final Time
    int tat; // Turn-around Time
    int pid; // ProcessID
};

void display(struct P* p, int n, int (*s)[20])
{
    // Printing output
    printf("Process number ");
    printf("Arrival time ");
    printf("Burst time ");
    printf("\tStart time");
    int j = 0;
    while (j != 10)
    {
        j += 1;
        printf(" ");
    }
    printf("\t\tFinal time");
    printf("\tWait Time ");
    printf("\tTurnAround Time \n");

    for (int i = 0; i < n; i++)
    {
        printf("%d \t\t", p[i].pid);
        printf("%d \t\t", p[i].at);
        printf("%d \t", p[i].bt);
        j = 0;
        int v = 0;
        while (s[i][j] != -1)
        {
            printf("%d ", p[i].st[j]);
            j++;
            v += 3;
        }
        while (v != 40)
        {
            printf(" ");
            v += 1;
        }
        printf("%d \t\t", p[i].ft);
        printf("%d \t\t", p[i].wt);
        printf("%d \n", p[i].tat);
    }

}

int main()
{
    int n, i, j;
    int quant;
    // Taking Input
    printf("Enter the no. of process:");
    scanf("%d", &n);
    struct P p[n];

    printf("Enter the quantum:");
    scanf("%d", &quant);

    printf("Pid:AT BT\n");
    for (i = 0; i < n; i++)
    {
        p[i].pid = i+1;
        printf("P%d: ", p[i].pid);
        scanf("%d %d", &(p[i].at), &(p[i].bt));
    }

    // Declaring variables
    int c = n, s[n][20];
    float time = 0, mini = INT_MAX, b[n], a[n];

    // Initializing burst and arrival time arrays
    int index = -1;
    for (i = 0; i < n; i++)
    {
        b[i] = p[i].bt;
        a[i] = p[i].at;
        for (j = 0; j < 20; j++)
        {
            s[i][j] = -1;
        }
    }

    int tot_wt, tot_tat;
    tot_wt = 0;
    tot_tat = 0;
    bool flag = false;

    while (c != 0)
    {

        mini = INT_MAX;
        flag = false;

        for (i = 0; i < n; i++)
        {
            float p = time + 0.1;
            if (a[i] <= p && mini > a[i] && b[i] > 0)
            {
                index = i;
                mini = a[i];
                flag = true;
            }
        }
        // if at =1 then loop gets out hence set flag to false
        if (!flag)
        {
            time++;
            continue;
        }

        // calculating start time
        j = 0;

        while (s[index][j] != -1)
        {
            j++;
        }

        if (s[index][j] == -1)
        {
            s[index][j] = time;
            p[index].st[j] = time;
        }

        if (b[index] <= quant)
        {
            time += b[index];
            b[index] = 0;
        }
        else
        {
            time += quant;
            b[index] -= quant;
        }

        if (b[index] > 0)
        {
            a[index] = time + 0.1;
        }

        // calculating arrival,burst,final times
        if (b[index] == 0)
        {
            c--;
            p[index].ft = time;
            p[index].wt = p[index].ft - p[index].at - p[index].bt;
            tot_wt += p[index].wt;
            p[index].tat = p[index].bt + p[index].wt;
            tot_tat += p[index].tat;
        }

    }

    // To display the table output
    display(p, n, s);
    
    // Calculating average wait time and turnaround time
    double avg_wt, avg_tat;
    avg_wt = tot_wt / (float)n;
    avg_tat = tot_tat / (float)n;

    // Printing average wait time and turnaround time
    printf("The average wait time is : %lf\n", avg_wt);
    printf("The average TurnAround time is : %lf\n", avg_tat);

    return 0;
}

// 21BCB0007
