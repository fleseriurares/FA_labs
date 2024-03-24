#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int main()
{
    int v[MAX_SIZE];
    int n;
    FILE *f;
    f=fopen("input.txt","r");
    if(f==NULL)
        printf("Nu se poate deschide");

    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        fscanf(f,"%d",&v[i]);
    }

    FILE *f2;
    f2=fopen("output.txt","w");

    for(int i=n-1;i>=0;i--)
    {
        fprintf(f2,"%d ",v[i]);
    }
    fclose(f);
    fclose(f2);

    return 0;
}
