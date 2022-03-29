/* Authors: Thomas Anderson and Jonathan Lamoureux */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i, j, k, y;
int p_one_tickets;
int p_two_tickets;
int p_three_tickets;
time_t t;

int main() {

    //user input for amount of tickets

    printf("Please enter the amount of tickets to give to process 1:");
    scanf("%d", &p_one_tickets);

    int ticketone[p_one_tickets];

    printf("Please enter the amount of tickets to give to process 2:");
    scanf("%d", &p_two_tickets);

    int tickettwo[p_two_tickets];

    printf("Please enter the amount of tickets to give to process 3: ");
    scanf("%d", &p_three_tickets);

    int ticketthree[p_three_tickets];

    int arr_size = p_one_tickets + p_two_tickets + p_three_tickets;

    int tickets[arr_size];

    //setting the indices in an array

    for (i = 0; i < p_one_tickets; i++) {
        tickets[i] = 1;
    }

    for (i = p_one_tickets; i < p_one_tickets + p_two_tickets; i++) {
        tickets[i] = 2;
    }

    for (i = p_one_tickets + p_two_tickets; i < p_one_tickets + p_two_tickets + p_three_tickets; i++) {
        tickets[i] = 3;
    }

    //random number generator

    srand((unsigned) time(&t));

    j = 0;
    k = 0;
    y = 0;

    for (i=0; i<100; i++) {
        int rand_num = rand() % arr_size;
        if(tickets[rand_num] == 1) {
            j++;

        } else if(tickets[rand_num] == 2) {
            k++;

        } else if(tickets[rand_num] == 3){
            y++;

        } else {
            printf("Test");
        }
    }

    //Print results

    printf("\nProcess one was ran %d%% of the time with %d tickets.", j, p_one_tickets);
    printf("\nProcess two was ran %d%% of the time with %d tickets.", k, p_two_tickets);
    printf("\nProcess three was ran %d%% of the time with %d tickets.", y, p_three_tickets);
    printf("\nThere was a total of 100 processes ran with a total pool of %d tickets given out.", arr_size);

}

