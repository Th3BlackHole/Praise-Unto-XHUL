

#ifndef RANDOMESOLANG_FUNCTIONS_H
#define RANDOMESOLANG_FUNCTIONS_H

#include "Random.h"

enum func{
    comp =0,
    chin =1,
    chot =2,
    nuin =3,
    nuut =4,
    adds =5,
    subs =6,
    mult =7,
    divs =8,
    mods =9, /* Done */
    ifcb =10,
    eels =11,
    whle =12,
    from =13,
    brak =14,
    stcp =15, /* Done */
    strv =16,
    stad =17,
};

typedef struct{
    int fname;
    long args[4];
}Functions;


/*
 * ------------------------------------------
 * Function Definitions
 * ------------------------------------------
 */

bool cmp(int op); /* Compares two integers randomly */
void cin(void); /* Puts the character from stdin on top of the stack */
void cout(void); /* Outputs top character in the stack */
void nin(void); /* Get an integer from stdin and outputs it to stack */
void nout(void); /* Outputs the number from the stack and prints it */
void add(void); /* Adds the two top numbers and returns it to the stack */
void sub(void); /* Subtracts the second number in stack from the top and returns it to the stack */
void mul(void); /* Multiplies the top two numbers and returns it to the stack */
void mod(void); /* Finds the Modulo of the top two numbers and return it to the stack */



/* CRITICAL FUNCTIONS */
void exec(Functions* func); /* Executes a given function from a Function struct */
void cblock(const Functions* funcs, int size); /* Executes a code block for use in loops and ifs */
void stkadd(long l); /* Adds a value to the stack */
long pstack(void); /* Pulls a number from the top of the stack */
void stkcpy(void); /* Copies the top value in the stack */
void stkrev(void); /* Reverses the order of the stack*/

/*
 * ------------------------------------------
 * Functions
 * ------------------------------------------
 */
enum {eq =0, le, lt, gt, ge};
bool cmp(int op){
    long v1 = pstack();
    long v2 = pstack();

    switch(op){
        case 0: return v1 == v2;
        case 1: return v1 <= v2;
        case 2: return v1 < v2;
        case 3: return v1 > v2;
        case 4: return v1 >= v2;
        default:
            puts("Uh Oh");
    }
    return false;
}

void add(void){
    long int v1= pstack();
    long int v2= pstack();
    stkadd(v1+v2);
}

void sub(void){
    long int v1 = pstack();
    long int v2 =pstack();
    stkadd(v2-v1);
}

void mul(void){
    long int v1 =pstack();
    long int v2 =pstack();
    stkadd(v1*v2);
}

void divd(void){
    long int v1=pstack();
    long int v2=pstack();
    stkadd(v2/v1);
}

void mod(void){
    long int v1=pstack();
    long int v2=pstack();
    stkadd(v1%v2);
}

void cin(void){
    char c;
    scanf_s("%c", &c);
    stkadd(c);
}

void cout(void){
    printf("%c",pstack());
}

void nin(void){
    long int n;
    scanf_s("%d",&n);
    stkadd(n);
}

void nout(void){
    printf("%d",pstack());
}

/* args[0] is cmp condition, args[1] is size of array */
bool ifstmt(Functions* func){
    if(cmp(func[0].args[0])){
        int tmp = func[0].args[1];
        func++;
        cblock(func, tmp);
        return true;
    }
    return false;
}

void elstmt(Functions* func){
    if(!cmp(func[0].args[0])){
        int tmp = func[0].args[1];
        func++;
        cblock(func,tmp);
    }
}


bool looping = false;
void wloop(Functions* func){
    int tmp = func[0].args[1];
    func++;
    while(looping){
        cblock(func,tmp);
    }
}

void floop(Functions* func){
    int tmp = func[0].args[1];
    int len = func[0].args[2];
    func++;
    for(int i =0; i< len; i++){
        cblock(func, len);
    }
}

void cblock(const Functions* funcs, int size){
    for(int i = 0; i<size; i++){
        exec(&funcs[i]);
    }
}


/* Runs the program */
void exec(Functions* func){
    //RAMCONSUMER(); /* Yummy Yummy */
    switch(func[0].fname){
        case comp:
            cmp(func[0].args[0]);
            return;
        case chin:
            cin();
            return;
        case chot:
            cout();
            return;
        case nuin:
            nin();
            return;
        case nuut:
            nout();
            return;
        case adds:
            add();
            return;
        case subs:
            sub();
            return;
        case mult:
            mul();
            return;
        case divs:
            divd();
            return;
        case mods:
            mod();
            return;
        case ifcb: /* The big double digits */
            ifstmt(func);
            return;
        case eels:
            elstmt(func);
            return;
        case whle:
            wloop(func);
            return;
        case from:
            floop(func);
            return;
        case stcp:
            stkcpy();
            return;
        case strv:
            stkrev();
            return;
        case stad:
            stkadd(func[0].args[0]);
            return;
        default: RAMCONSUMER();
    }
}

/* Stack Functions */
typedef struct stack {
    long stklen;
    long* stk;
}Stack;

Stack stack = {.stklen =0};

void stkadd(long l){
    stack.stklen++;
    stack.stk = (long*) realloc(stack.stk, sizeof(long) * stack.stklen);
    stack.stk[stack.stklen-1] = l;
}

long pstack(void){
    stack.stk = (long*) realloc(stack.stk, sizeof(long) * stack.stklen);
    long temp = stack.stk[stack.stklen-1];
    stack.stklen--;
    return temp;
}

void stkcpy(void){
    stack.stklen++;
    stack.stk = (long*) realloc(stack.stk, sizeof(long) * stack.stklen);
    long temp = stack.stk[stack.stklen-1];
    stack.stk[stack.stklen-1]=temp;
}

void stkrev(void){
    long temp[stack.stklen];
    for(int i =0; i<stack.stklen; i++) temp[i] = stack.stk[i];
    for(int i =0; i<stack.stklen; i++) stack.stk[stack.stklen-1-i] = temp[i];
}

void stkfree(void){
    free(stack.stk);
    free(&stack);
}

/*
 * ------------------------------------------
 * Its Interpreting Time
 * ------------------------------------------
 */







#endif //RANDOMESOLANG_FUNCTIONS_H
