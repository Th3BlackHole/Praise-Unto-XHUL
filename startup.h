

#ifndef RANDOMESOLANG_STARTUP_H
#define RANDOMESOLANG_STARTUP_H

#include "Random.h"
#include "functions.h"
#include "annoyance.h"
#include <limits.h>

#define STANDARD_ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define UPPERCASE_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define NUMBERS "0123456789"
#define CONSTANT_SO_I_DONT_HAVE_TO_CHANGE_IT_LATER 18

/*
 * ------------------------------------------
 * Function Definitions
 * ------------------------------------------
 */

char defnum(int inum); /* Redefines the characters for numbers */
int undefnum(char cnum); /* Undefines the new definitions */
void pnnum(void); /* Prints the new characters for 0-9 */
char* itok(int num); /* Initalizes the tokens */
int funcintp(char* funcname); /* Interprets function name from the randomization */
void startup(void); /* Called on start */
void wexit(void); /* Called on exit */
int funcintp(char* funcname); /* Return int from char* */
bool fchk(char* str); /* checks file */
void intp(char* fname);

/*
 * ------------------------------------------
 * Functions
 * ------------------------------------------
 */

char defnum(int inum){
    static char str[11] = "\n ";
    if(str[0] == 10){ /* Only on startup */
        str[10] = '\0';
        for(int i = 0; i<11; i++) {
            str[i] =rchar();
        }
        bool numr = false;
        while(!numr){
            int c1 =0;
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    if(i != j && str[i] == str[j]){
                        if(str[j]==126) str[j] = 48;
                        else str[j] += 1;
                        c1++;
                    }
                } /* End inner loop */
            } /* End Outer Loop */
            if(c1>0) numr = false;
            else numr = true;
            c1 = 0;
        } /* End while loop */
    } /* End startup If */
    return str[inum];
}

int undefnum(char cnum){
    static char nums[11] = "\n ";
    if(nums[0]==10){
        nums[10] = '\0';
        for(int i =0; i<11; i++) nums[i] = defnum(i);
    }
    for(int i =0; i<11; i++)
        if(nums[i] == cnum) return i;

    return -47; /* ERROR CASE */
}

void pnnum(void){
    printf("-----------------------------------------------------\n");
    printf(" |\t\tNUMBER REDEFINITIONS\t\t   | \n");
    printf("-----------------------------------------------------\n");
    for(int i=0;i<10;i++)
        printf("|%d| == '%c'\n",i,defnum(i));
}

void ptok(void){
    printf("-----------------------------------------------------\n");
    printf(" |\t\tTOKEN DEFINITIONS\t\t   | \n");
    printf("-----------------------------------------------------\n");
    printf("COMPARE = \t\t<|%s|>\n", itok(0));
    printf("CHARACTER IN = \t\t<|%s|>\n", itok(1));
    printf("CHARACTER OUT = \t<|%s|>\n", itok(2));
    printf("NUMBER IN = \t\t<|%s|>\n", itok(3));
    printf("NUMBER OUT = \t\t<|%s|>\n", itok(4));
    printf("ADDITION = \t\t<|%s|>\n", itok(5));
    printf("SUBTRACTION = \t\t<|%s|>\n", itok(6));
    printf("MULTIPLICATION = \t<|%s|>\n", itok(7));
    printf("DIVISION = \t\t<|%s|>\n", itok(8));
    printf("MODULO = \t\t<|%s|>\n", itok(9));
    printf("IF STATEMENT = \t\t<|%s|>\n", itok(10));
    printf("ELSE STATEMENT = \t<|%s|>\n", itok(11));
    printf("WHILE LOOP = \t\t<|%s|>\n", itok(12));
    printf("FOR LOOP = \t\t<|%s|>\n", itok(13));
    printf("BREAK = \t\t<|%s|>\n", itok(14));
    printf("STACK COPY = \t\t<|%s|>\n", itok(15));
    printf("STACK REVERSE = \t<|%s|>\n", itok(16));
    printf("STACK ADD = \t\t<|%s|>\n", itok(17));
}

char* itok(int num){
    static char* funcs[CONSTANT_SO_I_DONT_HAVE_TO_CHANGE_IT_LATER] = {"\n "}; /* 17 is a placeholder */
    if(funcs[0][0]==10){ /* Initializes things */
        for(int i =0; i < CONSTANT_SO_I_DONT_HAVE_TO_CHANGE_IT_LATER; i++){
            funcs[i] = rstr();
        }
        bool numr = false;
        while(!numr){
            int c1 =0;
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    if(i != j && funcs[i] == funcs[j]){
                        funcs[j] =rstr();
                        c1++;
                    }
                } /* End inner loop */
            } /* End Outer Loop */
            if(c1>0) numr = false;
            else numr = true;
            c1 = 0;
        } /* End while loop */
    } /* End startup */
    return funcs[num];
}

int undeftok(char* tok){
    static char* tokens[CONSTANT_SO_I_DONT_HAVE_TO_CHANGE_IT_LATER] = {"\n "};
    if(tokens[0][0]==10){
        for(int i =0; i<CONSTANT_SO_I_DONT_HAVE_TO_CHANGE_IT_LATER; i++)
            tokens[i] = itok(i);
    }
    for(int j =0; j<CONSTANT_SO_I_DONT_HAVE_TO_CHANGE_IT_LATER; j++){
        if(strncmp(tok, tokens[j], strlen(tokens[j]-1))==0)
            return j;
    }
    return -47;
}

void wexit(void){
    incalev(-25);
    restime();
}

void startup(void){
    iseed();
    incalev(25);
    atexit(wexit);
    pnnum();
    ptok();
    printf("-----------------------------------------------------\n");
    printf(" |\t\tXHUL DEMANDS YOUR FILE\t\t   | \n");
    printf("-----------------------------------------------------\n");
    char buf[1000];
    scanf_s("%s", buf);

    if(fchk(buf)){
        prun();
        /* Start Interpreting Here */
        intp(buf);

    } else {
        puts("XHUL cannot read this file he is deeply annoyed");
        exit(-69); /* Nice */
    }
}

bool fchk(char* str){
    FILE* fp =fopen(str, "r");
    if(fp==NULL){
        fclose(fp);
        incalev(100);
        return false;
    }
    fclose(fp);
    if(strstr(str, ".XHUL")){
        incalev(-25);
        return true;
    }
    incalev(100);
    return false;
}



void intp(char* fname){
    FILE* fp = fopen(fname, "r");
    if(fp==NULL){
        puts("Uh Oh");
        exit(-69); /* Still a funny Number */
    }
    int ntok = 1;
    int lpos = 0;
    int nfunc = 0;
    int cpos = 0;
    long long fpos[10]; /* Shows where the program enters a new scope */
    int floopl = 0;
    bool floop = false;
    bool wloop = false;
    bool elifpos = false;
    bool skippos = false;
    bool stloop = false;
    char c;
    long n;

    Functions curfunc; /* Current Function */

    do{ /* Loops until the file ends */
        char buf[1000];
        fgets(buf, 1000, fp);
        char* token;
        /* Get program Level */
        lpos = (int) strspn(buf, "    ");
        lpos /= 4;

        long args[20];

        for(int i =0; i < 20; i++){
            args[i] = LONG_MIN;
        }

        for(int i =0; i< strlen(buf); i++){
            if(buf[i]==10) buf[i] = '\0';
        }



        //printf("%d\n", floopl);
        if(floop && floopl-- == 0){
            floop = false;
            cpos--;
        }

        if(floop && lpos <cpos){
            fsetpos(fp, &(fpos[cpos]));
            continue;
        }

        if(skippos==true && lpos > cpos)
            continue;

        if(wloop==true && lpos < cpos){
            fsetpos(fp, &(fpos[cpos]));
            continue;
        }

        if(feof(fp)){
            if(wloop||floop) {
                fsetpos(fp, &(fpos[cpos]));
            }
        }


        /* Tokenizes the line */
        token = strtok(buf, " ");
        ntok =1;
        if(token!=NULL) curfunc.fname = undeftok(token);
        while(token!=NULL){
            token = strtok(NULL, " ");
            if(token!=NULL) args[ntok-1] = atol(token);
            ntok++;
        }



        //printf("%d\n",curfunc.fname);
        switch(curfunc.fname){
            case comp:
                if(args[0]!=LONG_MIN){
                    if(args[1]!=LONG_MIN&&args[2]!=LONG_MIN){
                        stkadd(args[2]);
                        stkadd(args[0]);
                        cmp(args[1]);
                        break;
                    }
                    cmp(args[0]);
                    break;
                }
                break;
            case chin:
                scanf_s("%c", &c);
                stkadd(c);
                break;
            case chot:
                printf("%c",pstack() );
                break;
            case nuin:
                scanf_s("%d", &n);
                stkadd(n);
                break;
            case nuut:
                printf("%ld\n", pstack() );
                break;
            case adds:
                for(int i =0; i < 2; i++){
                    if(args[i]!=LONG_MIN) stkadd(args[i]);
                }
                add();
                break;
            case subs:
                for(int i =0; i < 2; i++){
                    if(args[i]!=LONG_MIN) stkadd(args[i]);
                }
                sub();
                break;
            case mult:
                for(int i =0; i < 2; i++){
                    if(args[i]!=LONG_MIN) stkadd(args[i]);
                }
                mul();
                break;
            case divs:
                for(int i =0; i < 2; i++){
                    if(args[i]!=LONG_MIN) stkadd(args[i]);
                }
                divd();
                break;
            case mods:
                for(int i =0; i < 2; i++){
                    if(args[i]!=LONG_MIN) stkadd(args[i]);
                }
                mod();
                return;
            case ifcb:
                if(args[2]!=LONG_MIN){
                    stkadd(args[2]);
                    stkadd(args[0]);
                }else if(args[1]!=LONG_MIN){
                    stkadd(args[0]);
                }

                if(cmp(args[1])){ /* True Statement */
                    cpos++;
                } else { /* False Statement */
                    elifpos = true;
                    skippos = true; /* Skips Functions until lpos is < cpos +1 */
                }
                break;
            case eels:
                if(elifpos){
                    cpos++;
                    continue;
                } else {
                    skippos = true;
                }
                break;
            case whle:
                cpos++;
                fgetpos(fp, &(fpos[cpos]));
                wloop = true;
                break;
            case from:
                floop = true;
                floopl = args[0];
                cpos++;
                fgetpos(fp, &(fpos[cpos]));
                break;
            case brak: /* Need to Work On Loops to properly Break out of it */
                cpos--;
                wloop = false;
                break;
            case stcp:
                stkcpy();
                break;
            case strv:
                stkrev();
                break;
            case stad:
                for(int i =0; i<20; i++){
                    if(args[i]!=LONG_MIN) stkadd(args[i]);
                }
                break;
        }




    }while(!feof(fp));/* End of FIlE */
    fclose(fp);
}



#endif //RANDOMESOLANG_STARTUP_H