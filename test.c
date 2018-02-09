#include<stdio.h>
#include<stdlib.h>

int add(int a,int b)
{
    return a+b;
}

int addvalue=1;

void set(int v)
{
    addvalue=v;
}

int get()
{
    return addvalue;
}

void* func;

void regfunc(void* addr)
{
    printf("regfunc.\n");
    func = addr;
}

int testfunc(int a,int b)
{
    return ((int (*)(int,int))func)(a,b);
}


