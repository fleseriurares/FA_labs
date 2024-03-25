#include <iostream>

using namespace std;

int main()
{
    int a[100];
    for(int i=0;i<99;i++)
        a[i]=i;
int     i=-20;
    cout<<a[-i];
    return 0;
}
