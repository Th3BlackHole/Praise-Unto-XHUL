
#ifndef RANDOMESOLANG_ANNOYANCE_H
#define RANDOMESOLANG_ANNOYANCE_H

#include "Random.h"

/*
 * ------------------------------------------
 * Function Definitions
 * ------------------------------------------
 */
void incalev(int inc); /* Increases annoyance based on input */
void restime(void); /* Resets the time value */
void prun(void); /* Sometimes doesn't start the interpreting process  */

/*
 * ------------------------------------------
 * Functions
 * ------------------------------------------
 */
void incalev(int inc){
    FILE* fp = fopen("XHUL'S ANNOYANCE.txt", "r");
    long int ctime = time(0);
    if(fp==NULL){
        fclose(fp);
        fp = fopen("XHUL'S ANNOYANCE.txt", "w");
        fprintf(fp, "%d\n%d", 10, ctime);
        fclose(fp);
        return;
    }
    int curlev =0;
    long long atime;
    fscanf(fp, "%d\n%d", &curlev, &atime);
    fclose(fp);
    fp = fopen("XHUL'S ANNOYANCE.txt", "w");
    if(inc<0) curlev -= (rand()%inc)+1;
    else curlev += (rand()%inc)+1;
    curlev = (curlev < 0 ? 0 : curlev);
    fprintf(fp, "%d\n%d", curlev, atime);
    fclose(fp);
}

void restime(void){
    FILE* fp =fopen("XHUL'S ANNOYANCE.txt", "r");
    long long ctime = time(0);
    if(fp==NULL){
        fclose(fp);
        fp = fopen("XHUL'S ANNOYANCE.txt", "w");
        fprintf(fp, "%d\n%d", 10, ctime);
        fclose(fp);
        return;
    }
    int curlev =0;
    fscanf(fp, "%d", &curlev);
    fclose(fp);
    fp = fopen("XHUL'S ANNOYANCE.txt", "w");
    fprintf(fp, "%d\n%d", curlev, ctime);
    fclose(fp);
}

void prun(void){
    FILE* fp = fopen("XHUL'S ANNOYANCE.txt", "r");
    int curlev = 0;
    int atime = 0, ctime = time(0);
    double weight;
    fscanf(fp, "%d\n%d",&curlev, &atime);
    fclose(fp);
    weight = log((double) curlev);
    if(ctime-atime <=300) weight *= 1.15;
    double randst = ( (double)(rvalue()%100)+1)/50;
    randst-=(weight/10);
    if(randst <0.25){
        puts("XHUL has decided not to run your program");
        exit(-69);
    }
    incalev(25);
}






#endif //RANDOMESOLANG_ANNOYANCE_H