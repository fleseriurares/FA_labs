#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    int n, min, max,sir[100];
    scanf("%d",&n);
    scanf("%d",&min);
    scanf("%d",&max);
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
        sir[i]=rand()%(max-min+1)+min;
    }

    ///adaugare la finalul fisierului
    FILE *f=fopen("output.txt","a");
    fprintf(f,"\n");
    for(int i=0;i<n;i++)
    {
        fprintf(f,"%d ",sir[i]);
    }
    return 0;
}
