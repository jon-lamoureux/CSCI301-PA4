/* Authors: Thomas Anderson and Jonathan Lamoureux */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// finally have to use a struct because this is too complicated for just arrays
struct process
{
    int pid;
    int arrival;
    int wait;
    int turnaround;
    int burst;
    int remaining;
    int time;
} queue1[10], queue2[10], queue3[10], queue4[10];

// https://www.tutorialspoint.com/c-program-to-sort-an-array-in-an-ascending-order


int main() {
    /* Create random generator */
    time_t t;
    srand((unsigned) time(&t));

    /* Initialize variables */
    int num = rand() % 5 + 5; // Make the number of processes a number from 5 to 10
    struct process temp; // temp has to be a struct instead of int
    int quantum1 = 2; // Make quantum1 2
    int quantum2 = 4; // Make quantum2 4
    int quantum3 = 6; // Make quantum3 6
    int i2 = 0;
    int i3 = 0;
    int i4 = 0;
    int total = 0;
    int nextQueue = 1; // Determine whether or not the process continues executing the next queue
    /*  Fill arrays with random data */
    for (int i = 0; i < num; i++) {
        queue1[i].pid = i + 1; // set pid
        queue1[i].burst = rand() % 20 + 1; // Assign random numbers to process between 1 and 20
        queue1[i].arrival = rand() % num; // Make arrival time random number between 0 and number of Processes
        queue1[i].remaining = queue1[i].burst; // Remaining time is initialized to burst time
    }

    /* Sort the queue */
    for(int i=0; i < num; i++)
    {
        for(int j= i + 1; j < num; j++)
        {
            if(queue1[i].arrival > queue1[j].arrival)
            {
                temp=queue1[i];
                queue1[i]=queue1[j];
                queue1[j]=temp;
            }
        }
    }    total = queue1[0].arrival; // Set the total time to start at the arrival time of the first processes
    printf("\nProcess\t\tBurst Time\tArrival Time\t");
    for (int i = 0; i < num; i++) {
        printf("\nP%d\t\t%d\t\t%d", queue1[i].pid, queue1[i].burst, queue1[i].arrival);
    }
    printf("\n\nProcess\t\tRemaining Time\tWait Time\tTurnaround Time\tCompleted Under\t");
    for (int i = 0; i < num; i++) {
        /* Case 1: Process is completed */
        if (queue1[i].remaining <= quantum1) {
            total+=queue1[i].remaining;
            queue1[i].remaining = 0;
            queue1[i].wait = total - queue1[i].arrival - queue1[i].burst;
            queue1[i].turnaround = total - queue1[i].arrival;
            printf("\nP%d\t\t%d\t\t%d\t\t%d\t\tRR1", queue1[i].pid, queue1[i].burst, queue1[i].wait, queue1[i].turnaround);
        }
        /* Case 2: Process cannot be completed within time quantum */
        else {
            total += quantum1;
            queue2[i2].wait = total; // Set how long it's been waiting for
            queue1[i].remaining -= quantum1; // Subtract quantum 1 from remaining time
            queue2[i2].burst = queue1[i].remaining;
            queue2[i2].remaining = queue1[i].remaining;
            queue2[i2].pid = queue1[i].pid;
            i2++;
            nextQueue = 2;
        }
    }
    if (nextQueue != 2) return 0;
    for (int i = 0; i < i2; i++) {
        /* Case 1: Process is completed */
        if (queue2[i].remaining <= quantum2) {
            total += queue2[i].remaining;
            queue2[i].remaining = 0;
            queue2[i].wait = total - queue2[i].arrival - queue2[i].burst;
            queue2[i].turnaround = total - queue2[i].arrival;
            printf("\nP%d\t\t%d\t\t%d\t\t%d\t\tRR2", queue2[i].pid, queue2[i].burst, queue2[i].wait, queue2[i].turnaround);
        }
        /* Case 2: Process cannot be completed within time quantum */
        else {
            total += quantum2;
            queue3[i3].wait = total; // Set how long it's been waiting for
            queue2[i].remaining -= quantum2; // Subtract quantum 1 from remaining time
            queue3[i3].burst = queue2[i].remaining;
            queue3[i3].remaining = queue2[i].remaining;
            queue3[i3].pid = queue2[i].pid;
            i3++;
            nextQueue = 3;
        }
        }
    if (nextQueue != 3) return 0;
    for (int i = 0; i < i3; i++) {
        /* Case 1: Process is completed */
        if (queue3[i].remaining <= quantum3) {
            total += queue3[i].remaining;
            queue3[i].remaining = 0;
            queue3[i].wait = total - queue3[i].arrival - queue3[i].burst;
            queue3[i].turnaround = total - queue3[i].arrival;
            printf("\nP%d\t\t%d\t\t%d\t\t%d\t\tRR3", queue3[i].pid, queue3[i].burst, queue3[i].wait, queue3[i].turnaround);
        }
        /* Case 2: Process cannot be completed within time quantum */
        else {
            total += quantum3;
            queue4[i4].wait = total; // Set how long it's been waiting for
            queue3[i].remaining -= quantum3; // Subtract quantum 1 from remaining time
            queue4[i4].burst = queue3[i].remaining;
            queue4[i4].remaining = queue3[i].remaining;
            queue4[i4].pid = queue3[i].pid;
            i4++;
            nextQueue = 4;
        }
    }
    if (nextQueue != 4) return 0;
    for (int i = 0; i < i4; i++) {
        if (i == 0) {
            queue4[i].time = queue4[i].burst + total - quantum1 - quantum2 - quantum3;
        } else{
            queue4[i].time = queue4[i - 1].time + queue4[i].burst;
        }
    }
    for (int i = 0; i < i4; i++) {
        queue4[i].turnaround = queue4[i].time;
        queue4[i].wait = queue4[i].turnaround - queue3[i].burst;
        printf("\nP%d\t\t%d\t\t%d\t\t%d\t\tFCFS", queue4[i].pid, queue4[i].burst, queue4[i].wait, queue4[i].turnaround);
    }
    return 0;
}
