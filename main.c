/* Authors: Thomas Anderson and Jonathan Lamoureux */
/* Attributions: https://www.thecrazyprogrammer.com/2015/09/round-robin-scheduling-program-in-c.html */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    /* Create random generator */
    time_t t;
    srand((unsigned) time(&t));

    /* Initialize variables */
    int numProcesses = rand() % 5 + 3; // Make num_processes a random number from 3 to 7
    int quantum = rand() % numProcesses + 1; // Make quantum a random number from 1 to numProcesses
    int burstTimes[numProcesses]; // Set process variable to equal to number of processes
    // int arrivalTimes[numProcesses]; // Create arrival times
    int temp[numProcesses], totalProcesses[numProcesses]; // Temporary array for functional purposes
    int remaining = numProcesses; // set remaining processes to the total number of processes
    int i, j, min, total, turnaroundTime = 0; // functional purposes
    int waitTime = 0;
    struct Processes *ptr;
    /*  Fill arrays with random data */
    for (int i = 0; i < numProcesses; i++) {
        burstTimes[i] = rand() % 20 + 1; // Assign random numbers to process between 1 and 20
        temp[i] = burstTimes[i];
    }

    for (int i = 0; i < numProcesses; i++) {
        printf("P%d\t", i+1);
    }
    printf("\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("%d\t", burstTimes[i]);
    }
    printf("\n\n");
    /* Round Robin function */
    for (total = 0, i = 0; remaining != 0;) {
        int completed;

        // if (arrivalTimes[i] <= total) {
            /* Case 1: burst time is less than quantum time */
            if (temp[i] <= quantum & temp[i] > 0) {
                total += temp[i]; // Add remainder of burst times to total time elapsed
                temp[i] = 0;
                completed = 1;
                printf("|P%d|", i+1);
                /* Case 2: burst time is not empty, and also greater than the quantum time*/
            } else if (temp[i] > 0) {
                temp[i] -= quantum;
                total += quantum;
                printf("|P%d|", i+1);
            }

            /* Case 3: process is completed */
            if (temp[i] == 0 && completed == 1) {
                remaining--; // There is 1 less process remaining
                //printf("Process P%d completed, Burst time %d, arrival time %d, total time %d\n", i + 1, burstTimes[i], 0, total);
                completed = 0;
                waitTime += total - 0 - burstTimes[i];
                turnaroundTime += total - 0;
                totalProcesses[i] = total;
            }
            if (i == numProcesses - 1) {
                i = 0; // Reset the counter
            } else {
                i++;
            }
        /*} else if (i == numProcesses - 1) {
            i = 0;
            total += 1;
        } else {
            i++;
        }*/
    }

    printf("\n\n### Round Robin Scheduling ###\n");
    printf("Time Quantum is: %d\n", quantum);
    printf("Number of Processes: %d\n", numProcesses);
    printf("Average Waiting Time = %f\n", waitTime * 1.0 / numProcesses);
    printf("Avg Turnaround Time = %f\n", turnaroundTime * 1.0 / numProcesses);
    for (int i = 0; i < numProcesses; i++) {
        printf("P%d\t", i+1);
    }
    printf("\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("%d\t", totalProcesses[i]);
    }
    printf("\n");
    return 0;
}
