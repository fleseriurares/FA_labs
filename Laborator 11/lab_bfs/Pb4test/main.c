#include <stdio.h>
#include <stdlib.h>

int insert(int *v1, int n1, int c1, int *v2, int n2, int pos)
{
	if(c1<n1+n2){
	return -1;
	}

	for(int i=pos,k=0;k<n2;i++, k++){
	   v1[n1+k]=v1[i];
	   v1[i]=v2[k];
	}

	return 0;
}



int main()
{
    int n1,n2,c;
    printf("n1=");
    scanf("%d",&n1);
    printf("capacitate v1=");
    scanf("%d",&c);
    int *v1=(int*)malloc(c*sizeof(int));
    printf("Cititi elementele vectorului 1: ");
    for(int i=0;i<n1;i++){
    	scanf("%d",&v1[i]);
    }

    printf("n2=");
    scanf("%d",&n2);
    int *v2=(int*)malloc(n2*sizeof(int));
    printf("Cititi elementele vectorului 2: ");
    for(int i=0;i<n2;i++){
    	scanf("%d",&v2[i]);
    }

    int pos;
    printf("pos= ");
    scanf("%d",&pos);

    if(insert(v1,n1,c,v2,n2,pos)==0){
    for(int i=0;i<n1+n2;i++)
    {
    	printf("%d ", v1[i]);
    }
    }else
    {
    	printf("Capacitatea e prea mica");
    }

    return 0;
}
