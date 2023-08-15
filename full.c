#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include "optiheads.h"

void main()
{
    //Dimension of problem and Declaration 1
    int i, j, k, n;
    printf("Please enter the dimension of problem:");
    scanf("%d", &n);

    float a[n], b[n], accu;
    int popno;
    float *ra, *pop, *fun, seed1=3141592;

    FILE *filin;
    filin=fopen("func1.text","w+");


    //Taking the range of each dimension
    for(i=0; i<n; i++)
    {
        printf("Enter a%d:", i+1);
        scanf("%f", &a[i]);
        printf("Enter b%d:", i+1);
        scanf("%f", &b[i]);
    }


    //Population Generation
    printf("Enter the population size:");
    scanf("%d", &popno);

    pop=malloc(sizeof(float)*(popno*n));
    fun=malloc(sizeof(float)*(popno));

    ra=randfrac(popno*n,seed1);

    for(j=0;j<popno;j++)
    {
        for(i=0;i<n;i++)
        {
            *(pop+n*j+i)=*(a+i)+(*(ra+n*i+j))*(*(b+i)-(*(a+i)));
        }
    }


    //Send Initial population to file
    for(i=0;i<popno;i++)
    {
        for(j=0;j<n;j++)
        {
            fprintf(filin, "%f ", *(pop+n*i+j));
        }
        fprintf(filin, "\t");
    }
    fprintf(filin, "\n");


    //Declaration 2
    float fit[popno], fittot=0, fitprob[popno], fitprobcum[popno], *globmin;

    float lambda, crossprob, *crossra, seed2=2718181897;
    int check[popno], crossp;
    float tem1, tem2;
    int brea=0;

    int gamno;
    float mutprob, *mutra, seed3=11235813;
    float *alp, *gam, *de, seed4=5698745;
    int decide=1;
    gam=malloc(sizeof(float)*n);

    int re=0,repeat;
    float *let;
    let=malloc(sizeof(float)*2);


    //Parameter designation
    printf("Enter weight to Crossover:");
    scanf("%f", &lambda);
    printf("Enter crossover probability:");
    scanf("%f", &crossprob);
    crossp=(float)popno*crossprob;

    printf("Enter terms in Muhlenbein's function:");
    scanf("%d", &gamno);
    printf("Enter Mutation probability:");
    scanf("%f", &mutprob);

    printf("Enter the max no. of iterations:");
    scanf("%d", &repeat);

    float *minfunc, *minfuncind, *elitpop;
    minfunc=malloc(sizeof(float)*repeat);
    minfuncind=malloc(sizeof(float)*repeat);
    elitpop=malloc(sizeof(float)*n*repeat);


    //Genetic Algorithm
    for(re=0;re<repeat;re++)
    {
        //Functional Evaluation
        for(j=0;j<popno;j++)
        {
            fun[j]=ackley(n, pop, j);
        }

        printf("\n");
        for(i=0;i<popno;i++)
        {
            printf("%f ", *(fun+i));
        }
        printf("\n");


        //Data extraction for Elitism
        let=mini(fun,popno);
        *(minfunc+re)=*let;
        *(minfuncind+re)=*(let+1);

        for(i=0;i<n;i++)
        {
            *(elitpop+i+n*re)=*(pop+i+n*((int)*(minfuncind+re)));
        }


        //Roulette Distribution
        fittot=0;

        for(i=0;i<popno;i++)
        {
            *(fit+i)=1/(*(fun+i));
            if(i==(int)*(minfuncind+re))
            {
                *(fit+i)=0;
            }
            fittot=fittot+(*(fit+i));
        }

        printf("\n");
        for(i=0;i<popno;i++)
        {
            printf("%f ", *(fit+i));
        }
        printf("\n");

        for(i=0;i<popno;i++)
        {
            *(fitprob+i)=*(fit+i)/fittot;

            if(i==0)
            {
                *(fitprobcum+i)=*(fitprob+i);
            }
            else
            {
                *(fitprobcum+i)=*(fitprob+i)+(*(fitprobcum+i-1));
            }
        }

        printf("\n");
        for(i=0;i<popno;i++)
        {
            printf("%f ", *(fitprob+i));
        }
        printf("\n");

        printf("\n");
        for(i=0;i<popno;i++)
        {
            printf("%f ", *(fitprobcum+i));
        }
        printf("\n");


        //Crossover
        crossra=randfrac(crossp, seed2+567835*re);

        for(i=0;i<crossp;i++)
        {
            printf("%f ", *(crossra+i));
        }

        printf("\n");

        for(i=0;i<popno;i++)
        {
            check[i]=0;
        }

        for(i=0;i<crossp;i++)
        {
            for(j=0;j<popno;j++)
            {
                if(j!=0)
                {
                    if(*(crossra+i)<fitprobcum[j] && *(crossra+i)>fitprobcum[j-1])
                    {
                        check[j]=1;
                    }
                }
                else
                {
                    if(*(crossra+i)<fitprobcum[j] && fitprobcum[i]>0)
                    {
                        check[j]=1;
                    }
                }
            }
        }

        check[(int)*(minfuncind+re)]=1;

        for(i=0;i<popno;i++)
        {
            printf("\n%d", check[i]);
        }
        printf("\n");
        for(i=0;i<popno;i++)
        {
            if(*(check+i)==1 && i!=(popno-1))
            {
                for(j=i+1;j<popno;j++)
                {
                    if(*(check+j)==1)
                    {
                        for(k=0;k<n;k++)
                        {
                            tem1=*(pop+n*i+k);
                            tem2=*(pop+n*j+k);
                            *(pop+n*i+k)=lambda*tem1+(1-lambda)*tem2;
                            *(pop+n*j+k)=lambda*tem2+(1-lambda)*tem1;
                            brea=1;
                        }
                    }
                    if(brea==1)
                    {
                        i=j;
                        brea=0;
                        break;
                    }
                }
            }
        }


        //Mutation
        mutra=randfrac(popno, seed3+ 7685*re);

        for(i=0;i<popno;i++)
        {
            if(*(mutra+i) < mutprob)
            {
                *(check+i)=1;
            }
            else
            {
                *(check+i)=0;
            }
        }

        alp=randfrac(gamno*n, seed4+4524*re);

        for(i=0;i<n;i++)
        {
            *(gam+i)=0;
        }

        for(j=0;j<n;j++)
        {
            for(i=0;i<gamno;i++)
            {
                *(gam+j)=*(gam+j)+(*(alp+i+j*gamno))/pow(2,i+1);
            }
        }

        for(i=0;i<popno;i++)
        {
            if(*(check+i)==1)
            {
                for(k=0;k<n;k++)
                {
                    de=randfrac(1,seed4+13945*re+100*k);
                    if(*de<0.5)
                    {
                        decide=1;
                    }
                    else
                    {
                        decide=-1;
                    }
                    *(pop+n*i+k)=*(pop+n*i+k)+0.1*decide*(b[k]-a[k])*(*(gam+k));
                }
            }
        }


        //Elitism
        for(i=0;i<n;i++)
        {
            *(pop+i+n*((int)*(minfuncind+re)))=*(elitpop+i+n*re);
        }


        // Print population
        for(i=0;i<popno;i++)
        {
            for(j=0;j<n;j++)
            {
                printf("%f ", *(pop+n*i+j));
            }
            printf("\n");
        }

        //Send to a File
        for(i=0;i<popno;i++)
        {
            for(j=0;j<n;j++)
            {
                fprintf(filin, "%f ", *(pop+n*i+j));
            }
            fprintf(filin, "\t");
//            fprintf(filin, "%f\t", *(fun+i));
        }
        fprintf(filin, "\n");
    }
    fclose(filin);

    globmin=mini(minfunc, repeat);

    printf("\n\n The Minima is %f at ", *(globmin));
    for(i=0;i<n;i++)
    {
        printf("x%d=%f, ", i+1, *(elitpop+i+n*((int)*(globmin+1))));
    }
    printf("\n");
}
