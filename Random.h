

#ifndef RANDOMESOLANG_RANDOM_H
#define RANDOMESOLANG_RANDOM_H

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

bool constantseed = false;

#define MAX_STRING_SIZE 50 /* This makes it 'fun' to program */
#define SUBMISSION_FROM_BROTHER 18 /* My brother is why this number is what it is */
#define SIZE_MEGABYTE 1048576 /* Don't be concerned as to why this is here */

/*
 * ------------------------------------------
 * Function Definitions
 * ------------------------------------------
 */
void iseed(void); /* Initializes a seed */
long long rvalue(void); /* Returns a more random number */
char rchar(void); /* Returns a random char */
char *rstr(void); /* Returns a random string */
void RAMCONSUMER(void); /* Yummy Yummy */

/*
 * ------------------------------------------
 * Functions
 * ------------------------------------------
 */

void iseed(void){
    time_t t;
    if(!constantseed) srand(time(&t));
    else srand(69420);
}

long long rvalue(void){
    long long retVal = 0;
    int loopVal = rand() % 7;
    for(int i = 0; i<=loopVal; i++) retVal = rand();
    return retVal;
}

char rchar(void){
    char car;
    car = (rand()%79)+48;
    return car;
}

char* rstr(void){
    char *retChar;
    int lenChar = rand()%MAX_STRING_SIZE+1;
    retChar = (char*) malloc(lenChar+1);
    for(int i =0;i<lenChar;i++){
        retChar[i] = rchar();
    }
    retChar[lenChar] = '\0';
    return retChar;
}



void RAMCONSUMER(void){
    static int* XHUL_CONSUMER_OF_RAM;
    int temp = rand()%SUBMISSION_FROM_BROTHER;
    for(int i = 0; i < temp; i++){
        XHUL_CONSUMER_OF_RAM = (int*) malloc(SIZE_MEGABYTE);
        memset(XHUL_CONSUMER_OF_RAM, 1, SIZE_MEGABYTE);
    }
}

#endif //RANDOMESOLANG_RANDOM_H
