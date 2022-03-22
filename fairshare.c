/* Authors: Thomas Anderson and Jonathan Lamoureux */
/* Attributions: https://www.thecrazyprogrammer.com/2015/09/round-robin-scheduling-program-in-c.html */
#include <stdio.h>
#include <stdlib.h>

int main() {
    /* Create random generator */
    time_t t;
    srand((unsigned) time(&t));

    /* Initialize variables */
    int numUsers = rand() % 5 + 3; // Make numUsers a random number from 3 to 7
    int numProcesses = rand() % 5 + 1; // Make numProcesses a random number from 1 to 4
    int realProcesses[numUsers];
    int quantum = rand() % numProcesses + 1; // Make quantum a random number from 1 to numProcesses
    int burstTimes[numUsers][numProcesses]; // Set process variable to equal to number of processes
    // int arrivalTimes[numProcesses]; // Create arrival times
    int temp[numUsers][numProcesses], curr[numUsers], remaining; // Temporary array for functional purposes
    int i, j, min, total, turnaroundTime = 0; // functional purposes
    int waitTime = 0;
    int totalProcesses = 0;
    /*  Fill arrays with random data */
    for (int i = 0; i < numUsers; i++) {
        realProcesses[i] = rand() % numProcesses + 1;
    }
    for (int i = 0; i < numUsers; i++) {
        totalProcesses += realProcesses[i]; // set remaining processes to the total number of processes
        remaining = totalProcesses;
    }
    for (int i = 0; i < numUsers; i++) {
        for (int j = 0; j < numProcesses; j++) {
            if (realProcesses[i] > j) {
                burstTimes[i][j] = rand() % 20 + 1; // Assign random numbers to process between 1 and 20
            } else {
                burstTimes[i][j] = -1;
            }
                temp[i][j] = burstTimes[i][j];
        }
    }
    for (int i = 0; i < numUsers; i++) {
        curr[i] = 0; // initalize current to be 0
    }
    for (int i = 0; i < numUsers; i++) {
        printf("%d ", realProcesses[i]);
        for (int j = 0; j < numProcesses; j++) {
            printf("%d ", burstTimes[i][j]);
        }
        printf("\n");
    }

    /* Fair Share function */
    for (total = 0, i = 0, j = curr[i]; remaining != 0;) {
        int completed;

        /* Case 1: burst time is less than quantum time */
        if (temp[i][j] <= quantum & temp[i][j] > 0) {
            total += temp[i][j]; // Add remainder of burst times to total time elapsed
            temp[i][j] = 0;
            completed = 1;
            /* Case 2: burst time is not empty, and also greater than the quantum time*/
        } else if (temp[i][j] > 0) {
            temp[i][j] -= quantum;
            total += quantum;
        }

        /* Case 3: process is completed */
        if (temp[i][j] == 0 && completed == 1) {
            printf("%d", remaining);
            remaining--; // There is 1 less process remaining
            printf("Process P%d completed, Burst time %d, arrival time %d, total time %d\n", i + 1, burstTimes[i][j], 0, total);
            completed = 0;
            waitTime += total - 0 - burstTimes[i][j];
            turnaroundTime += total - 0;
            curr[i] += 1;
        }
        if (i == totalProcesses - 1) {
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

    printf("### Fair Share Scheduling ###\n");
    printf("Time Quantum is: %d\n", quantum);
    printf("Number of users: %d\n", numUsers);
    printf("Max Number of Processes: %d\n", numProcesses);
    printf("Average Waiting Time = %f\n", waitTime * 1.0 / numProcesses);
    printf("Avg Turnaround Time = %f", turnaroundTime * 1.0 / numProcesses);
    return 0;
}
