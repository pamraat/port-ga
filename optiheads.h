#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#define pi 3.1415926535897932384

float *randfrac(int i, float seed)
{
    srand(time(0)+seed);
    int n;
    float *r;

    r=malloc(sizeof(int)*i);

    for(n=0;n<i;n++)
    {
        r[n]=rand()/(float)RAND_MAX;
    }
    return r;
}

float ackley(int n, float *x, int i)
{
    float y, a1=0, a2=0;
    int j;

    for(j=0; j<n; j++)
    {
        a1=a1+pow(*(x+n*i+j),2);
    }
    a1=-sqrt(a1/n)/5;

    for(j=0; j<n; j++)
    {
        a2=a2+cos((*(x+n*i+j))*2*pi);
    }
    a2=a2/n;

    y=-20*exp(a1)-exp(a2)+exp(1)+20;
    return y;
}

float booth(int n, float *x, int i)
{
    float y;

    y=pow((*(x+n*i)+2*(*(x+n*i+1))-7),2)+pow((2*(*(x+n*i))+*(x+n*i+1)-5),2);

    return y;
}

float *maxi(float *arr, int n)
{
    int i, j;

    float *re;

    re=malloc(sizeof(float)*2);

    *re=*arr;

    for(i=0;i<n;i++)
    {
        if(*(arr+i)>*re)
        {
            *re=*(arr+i);
            *(re+1)=i;
        }
    }

    return re;
}

float *mini(float *arr, int n)
{
    int i, j;

    float *re;

    re=malloc(sizeof(float)*2);

    *re=*arr;

    for(i=0;i<n;i++)
    {
        if(*(arr+i)<*re)
        {
            *re=*(arr+i);
            *(re+1)=i;
        }
    }

    return re;
}
