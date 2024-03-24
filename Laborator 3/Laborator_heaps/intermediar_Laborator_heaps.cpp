// Laborator_heaps.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//Determinarea parintilor/copiilor din sir:

int find_parent(int i)
{
    return i / 2;
}

int find_right(int i)
{
    return 2 * i + 1;
}

int find_left(int i)
{
    return 2 * i;
}



void MaxHeapify(int a[], int i,int n)
{
    int left = find_left(i);
    int right = find_right(i);
    int maxim;

    if (left < n && a[left] > a[i])
    {
        maxim = left;
    }
    else
    {
        maxim = i;
    }
    if (right < n && a[right] > a[maxim])
    {
        maxim = right;
    }
    if (maxim != i)
    {
        int aux=a[i];
        a[i] = a[maxim];
        a[maxim] = aux;
        MaxHeapify(a, maxim, n);
    }
}


//Varianta Bottom-up
void Build_Max_Heap(int a[],int n)
{
    for (int i = n / 2; i >= 0; i--)
    {
        MaxHeapify(a, i, n);
    }
}

//max of 3:
/*
int index_max(int a[],int i)
{   
    int a1 = a[i];
    int b = a[find_left[i]];
    int c = a[find_right[i]];
    if (a[i] > a[find_left[i]])
    {
        if (a[i] > c)
            return a;
    }
    else
    {
        if (b > c)
            return c;
    }
    return b;
}

//Varianta top-down
void Heapify(int a[], int i)
{
    int maxim = index_max(a,i);
    int(maxim != i)
    {
        int aux = a[maxim];
        a[maxim] = a[i];
        a[i] = aux;
        Heapify(a, maxim);
    }
}
*/
int main()
{
    //Testare bottom_up
    int n,a[100];
    std::cout << "n=";
    std :: cin >> n;

    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    Build_Max_Heap(a, n); // bottom-up
    
    for (int i = 0; i < n; i++)
    {
        std::cout<< a[i]<<' ';
    }

}
