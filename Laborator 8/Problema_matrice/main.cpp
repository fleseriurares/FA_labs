#include <iostream>

using namespace std;

int main()
{
    int nr,i,j,a[7][7];
    cout<<"nr=";
    cin>>nr;


    for(i=1;i<=6;i++)
    {
        for(j=1;j<=6;j++)
        {
            if(i==j)
            {
                a[i][j]=0;
            }
            else if(i<j)
            {
                a[i][j]=a[j][i]=nr%10;
            }
        }
        nr=nr/10;
    }

    for(i=1;i<=6;i++)
    {
        for(j=1;j<=6;j++)
            cout<<a[i][j]<<' ';
        cout<<endl;
    }

    return 0;
}
