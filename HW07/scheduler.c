#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Struct {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int completed;
};


int sort_by_arrival(const void *a, const void *b) {
    const struct Struct *p1 = a;
    const struct Struct *p2 = b;
    return p1->arrival_time - p2->arrival_time;
}


void display_results(struct Struct p[], int n) {
    double total_wt = 0, total_tat = 0, total_rt = 0;

    printf("\nPID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time, p[i].response_time);

        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        total_rt += p[i].response_time;
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);
}


void show_gantt(int order[], int n) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++)
        printf(" P%d |", order[i]);
    printf("\n");
}

// FCFS Scheduling
void fcfs(struct Struct p[], int n) {
    qsort(p, n, sizeof(struct Struct), sort_by_arrival);

    int time = 0, order[n];
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time)
            time = p[i].arrival_time;

        p[i].waiting_time = time - p[i].arrival_time;
        p[i].response_time = p[i].waiting_time;
        time += p[i].burst_time;
        p[i].turnaround_time = time - p[i].arrival_time;

        order[i] = p[i].pid;
    }

    show_gantt(order, n);
    display_results(p, n);
}

// SJF Scheduling
void sjf(struct Struct p[], int n) {
    struct Struct temp[n];
    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
        temp[i].completed = 0;
    }

    int time = 0, done = 0, order[n], index = 0;

    while (done < n) {
        int chosen = -1, min_bt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!temp[i].completed && temp[i].arrival_time <= time) {
                if (temp[i].burst_time < min_bt) {
                    min_bt = temp[i].burst_time;
                    chosen = i;
                } else if (temp[i].burst_time == min_bt &&
                           temp[i].arrival_time < temp[chosen].arrival_time) {
                    chosen = i;
                }
            }
        }

        if (chosen == -1) {
            int next = INT_MAX;
            for (int i = 0; i < n; i++)
                if (!temp[i].completed && temp[i].arrival_time < next)
                    next = temp[i].arrival_time;
            time = next;
            continue;
        }

        temp[chosen].waiting_time = time - temp[chosen].arrival_time;
        temp[chosen].response_time = temp[chosen].waiting_time;
        time += temp[chosen].burst_time;
        temp[chosen].turnaround_time = time - temp[chosen].arrival_time;
        temp[chosen].completed = 1;
        order[index++] = temp[chosen].pid;
        done++;
    }

    show_gantt(order, index);
    display_results(temp, n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Struct p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }

    printf("\n=== First Come First Served (FCFS) ===\n");
    struct Struct copy[n];
    for (int i = 0; i < n; i++) copy[i] = p[i];
    fcfs(copy, n);

    printf("\n=== Shortest Job First (SJF) ===\n");
    sjf(p, n);

    return 0;
}

