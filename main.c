/* Authors: Thomas Anderson and Jonathan Lamoureux */
/* Attributions: https://www.thecrazyprogrammer.com/2015/09/round-robin-scheduling-program-in-c.html */
#include <stdio.h>
#include <stdlib.h>

int main() {
    /* Create random generator */
    time_t t;
    srand((unsigned) time(&t));

    /* Initialize variables */
    int quantum = rand() % 10 + 1; // Make quantum a random number from 1 to 10
    int numProcesses = rand() % 5 + 3; // Make num_processes a random number from 3 to 7
    int burstTimes[numProcesses]; // Set process variable to equal to number of processes
    int arrivalTimes[numProcesses]; // Create arrival times
    int temp[numProcesses]; // Temporary array for functional purposes
    int remaining = numProcesses; // set remaining processes to the total number of processes
    int i, total, waitTime, turnaroundTime = 0; // functional purposes

    /*  Fill arrays with random data */
    for (int i = 0; i < numProcesses; i++) {
        burstTimes[i] = rand() % 20 + 1; // Assign random numbers to process between 1 and 20
    }
    for (int i = 0; i < numProcesses; i++) {
        arrivalTimes[i] = rand() % numProcesses + 1; // Make processes arrive at a number between 1 and the total number of processes
    }

    /* Round Robin function */
    for (total = 0, i = 0; remaining != 0;) {
        int completed;

        /* Case 1: burst time is less than quantum time */
        if (burstTimes[i] <= quantum && burstTimes[i] > 0) {
            total += burstTimes[i]; // Add remainder of burst times to total time elapsed
            burstTimes[i] = 0;
            completed = 1;

        /* Case 2: burst time is not empty, and also greater than the quantum time*/
        } else if (burstTimes[i] > 0) {
            burstTimes[i] -= quantum;
            total += quantum;
        }

        /* Case 3: process is completed */
        if(burstTimes[i] == 0 && completed == 1) {
            remaining--; // There is 1 less process remaining
            printf("Process %d completed\n", i + 1);
            completed = 0;
            waitTime += total - arrivalTimes[i];// - burstTimes[i];
            turnaroundTime += total - arrivalTimes[i];
        }
        if (i == numProcesses - 1) {
            i = 0; // Reset the counter
        } else if (arrivalTimes[i + 1] <= total) {
            i++; // If the current process hasn't arrived yet, go to the next one
        } else {
            i = 0;
        }
    }

    printf("### Round Robin Scheduling ###\n");
    printf("Time Quantum is: %d\n", quantum);
    printf("Number of Processes: %d\n", numProcesses);
    printf("Average Waiting Time = %f\n", waitTime * 1.0 / numProcesses);
    printf("Avg Turnaround Time = %f", turnaroundTime * 1.0 / numProcesses);
    return 0;
}
