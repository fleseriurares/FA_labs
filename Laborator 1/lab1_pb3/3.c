#include <stdio.h>
#include <stdlib.h>

int main()
{
    float n;
    FILE *f=fopen("fisier.txt","w");
    for(float n=100;n<=10000;n=n+100)
    {
    fprintf(f,"%f,",n);
    fprintf(f,"%f,",100*log(n));
    fprintf(f,"%f,",10*n);
    fprintf(f,"%f,",n*log(n));
    fprintf(f,"%f,",0.1*n*n);
    fprintf(f,"%f,",0.01*n*n*n);
    fprintf(f,"\n");
    }
    return 0;
}
