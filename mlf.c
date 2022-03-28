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
int num;
void sort()
{
    struct process temp; // temp has to be a struct instead of int
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
    }
}

int main() {
    /* Create random generator */
    time_t t;
    srand((unsigned) time(&t));

    /* Initialize variables */
    int numProcesses = rand() % 10 + 5; // Make the number of processes a number from 5 to 10
    int quantum1 = rand() % 10 + 2; // Make quantum1 a random number from 2 to numProcesses
    int quantum2 = rand() % 10 + 4; // Make quantum2 a random number from 4 to numProcesses
    int i2, total = 0;

    /*  Fill arrays with random data */
    for (int i = 0; i < numProcesses; i++) {
        queue1[i].pid = i + 1; // set pid
        queue1[i].burst = rand() % 20 + 1; // Assign random numbers to process between 1 and 20
        queue1[i].arrival = rand() % numProcesses; // Make arrival time random number between 0 and number of Processes
        queue1[i].remaining = queue1[i].burst; // Remaining time is initalized to burst time
    }

    /* Sort the queue */
    sort();
    total = queue1[0].arrival; // Set the total time to start at the arrival time of the first processes

    printf("\nProcess\t\tRemaining Time\tWait Time\tTurnaround Time\t\t");
    for (int i = 0; i < numProcesses; i++) {
        /* Case 1: Process is completed */
        if (queue1[i].remaining <= quantum1) {
            total+=queue1[i].remaining;
            queue1[i].remaining = 0;
            queue1[i].wait = total - queue1[i].arrival - queue1[i].burst;
            queue1[i].turnaround = total - queue1[i].arrival;
            printf("\nP%d\t\t%d\t\t%d\t\t%d",queue1[i].pid,queue1[i].burst,queue1[i].wait,queue1[i].turnaround);
        }
        /* Case 2: Process cannot be completed within time quantum */
        else {
            total+=quantum1;
            queue2[i2].wait = total; // Set how long it's been waiting for
            queue1[i].remaining -= quantum1; // Subtract quantum 1 from remaining time
            queue2[i2].burst, queue2[i2].remaining = queue1[i].remaining;
            queue2[i2].pid = queue1[i].pid;
            i2++;
        }
    }
    return 0;
}
