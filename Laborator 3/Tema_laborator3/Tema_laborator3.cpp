// Laborator_heaps.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
*@author Fleseriu Ioan-Rares
*
*Grupa 30225
* 
* Analiza si Compararea a doua metode de construire a structurii de date heap: Bottom-Up si Top-Down
* 
* Interpretare personala:
* 
* Am comparat cele 2 metode de implementare a heap-urilor, in cazurile mediu statistic si defavorabil, precum se cerea in laborator. 
* Apoi, am implementat heapsort si am demonstrat corectitudinea celor 3 algoritmi.
* 
*   In cazul mediu statistic, dupa cum era si de asteptat, implementarea bottom-up se arata a fi mai eficienta, 
* atat in ceea ce priveste atribuirile cat si in ceea ce priveste compararile. Cu toatea acestea, dupa cum se observa si pe grafic,
* diferenta nu este una foarte mare.
* 
*   In cazul defavorabil, algoritmul bottom-up este de asemenea mai eficient, de data aceasta cu diferente mai mari ale graficelor,
* atat in privinta atribuirilor, cat si in privinta comparatilor, deci si la timpul total.
*   
*  In ceea ce priveste cresterea prezentata pe grafic, ambii algoritmi prezinta o crestere aparent liniara(desi algoritmul top-down are complexitate O(nlogn))
*   
*    Complexitati: -> algoritm bottom-up : O(n)
*                 -> algoritm top-down: O(nlogn)
*                 -> heapsort: O(nlogn) - algoritm optimal
*          
*       
*                                     
*
*/


#include <iostream>
#include "Profiler.h"   

using namespace std;

Profiler p("Cazul_defavorabil");

//Determinarea parintilor/copiilor din sir:

int find_parent(int i)
{
    if (i % 2 == 0)             //Am facut aceasta modificare deoarece iteratiile mele incep de la 0
        return i / 2 - 1;
    return i / 2;


}

int find_right(int i)
{
    return 2 * i + 2; // deoarece sirul incepe cu iteratia 0
}

int find_left(int i)
{

    return 2 * i + 1; // deoarece sirul incepe cu iteratia 0
}

void MaxHeapify(int a[], int i, int n)
{
    int left = find_left(i);
    int right = find_right(i);
    int maxim;

    Operation atribuiri = p.createOperation("bottom_up_atribuiri", n);
    Operation comparari = p.createOperation("bottom_up_comparari", n);

    
    if (left < n)
    {
        comparari.count();
        if (a[left] > a[i])
            maxim = left;
        else
            maxim = i;
    }
    else
    {
        maxim = i;
    }

    if (right < n)
    {
        comparari.count();
        if(a[right] > a[maxim])
         maxim = right;
    }

    if (maxim != i)
    {
        atribuiri.count(3);
        int aux = a[i];
        a[i] = a[maxim];
        a[maxim] = aux;
        MaxHeapify(a, maxim, n);
    }
    p.addSeries("bottom_up_final", "bottom_up_atribuiri", "bottom_up_comparari");
}


//Varianta Bottom-up
void Build_Max_Heap(int a[], int n)
{
    for (int i = n / 2; i >= 0; i--)
    {
        MaxHeapify(a, i, n);
    }
}

//Heapsort:

void Heapsort(int a[], int n)
{
    int heapsize = n;
    Build_Max_Heap(a, n);
    for (int i = n - 1; i >= 1; i--)
    {
       
        int aux = a[i];
        a[i] = a[0];
        a[0] = aux;
        heapsize = heapsize - 1;
        MaxHeapify(a, 0, heapsize);
    }
}

//max of 3:

int index_max(int a[], int i, int n)
{
    int b = i, c = i;
    if (find_left(i) < n)
        b = find_left(i);
    if (find_right(i) < n)
        c = find_right(i);
    

    if (a[i] >= a[b])
    {
        if (a[i] >= a[c])
            return i;
        else
            return c;
    }
    else
    {
        if (a[b] > a[c])
            return find_right(i);
        else
            return find_left(i);
    }
}



void copy_array(int a[], int b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        b[i] = a[i];
    }
}

//Varianta top-down
void Insert_top_down(int a[], int i, int  n)
{
    Operation atribuiri = p.createOperation("top_down_atribuiri", n);
    Operation comparari = p.createOperation("top_down_comparari", n);

    comparari.count();
    while (i > 0 && a[find_parent(i)] < a[i])
    {   comparari.count();
        atribuiri.count(3);
        int aux = a[i];
        a[i] = a[find_parent(i)];
        a[find_parent(i)] = aux;
        i = find_parent(i);
    }
    p.addSeries("top_down_final", "top_down_atribuiri", "top_down_comparari");
}

void Build_Max_Heap_top_down(int a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        Insert_top_down(a, i, n);
    }
}

int main()
{
   char alegere;
   
 //  std::cout << "1=TEST; 0=GENERARE\n";
    std::cout << "Alege (T/G): ";
    std::cin >> alegere;
    if (alegere == 'G')
    {
int a[10000],b[10000];
        //DEFAVORABIL

        for (int i = 100; i <= 10000; i = i + 100)
        {
            FillRandomArray(a, i, 100, 10000, false, 1);
            Build_Max_Heap(a, i);
            FillRandomArray(a, i, 100, 10000, false, 1);
            Build_Max_Heap_top_down(a, i); // top-down
        }

        p.createGroup("Defavorabil_nr_atribuiri", "top_down_atribuiri", "bottom_up_atribuiri");
        p.createGroup("Defavorabil_nr_atribuiri_bottom_up(pentru_a_se_observa_mai_bine)", "bottom_up_atribuiri");
        p.createGroup("Defavorabil_nr_comparari_bottom_up(pentru_a_se_observa_mai_bine)", "bottom_up_comparari");
        p.createGroup("Defavorabil_comparari", "top_down_comparari", "bottom_up_comparari");
        p.createGroup("Defavorabil_total", "top_down_final", "bottom_up_final");
        p.createGroup("Defavorabil_total_bottom_up(pentru_a_se_observa_mai_bine)","bottom_up_final");

        p.reset("MediuStatistic");
        
        //CAZ_MEDIUSTATISTIC
        for (int j = 1; j <= 5; j++)
        {
            for (int i = 100; i <= 10000; i = i + 100)
            {
                FillRandomArray(a, i, 100, 10000, false, 0);
                copy_array(a, b, i);
                Build_Max_Heap(a, i); // bottom-up
                Build_Max_Heap_top_down(b, i); // top-down
            }
        }

        p.divideValues("bottom_up_atribuiri", 5);
        p.divideValues("bottom_up_comparari", 5);
        p.divideValues("bottom_up_final", 5);

        p.divideValues("top_down_atribuiri", 5);
        p.divideValues("top_down_comparari", 5);
        p.divideValues("top_down_final", 5);

        p.createGroup("MediuStatistic_nr_atribuiri", "top_down_atribuiri", "bottom_up_atribuiri");
        p.createGroup("MediuStatistic_comparari", "top_down_comparari", "bottom_up_comparari");
        p.createGroup("MediuStatistic_total", "top_down_final", "bottom_up_final");

        

     
        p.showReport();
    }
    else
    {
        //Demo bottom_up
        int n, a[100];
        std::cout << "Bottom-up:";
        std::cout << "n=";
        std::cin >> n;

        for (int i = 0; i < n; i++)
        {
            std::cin >> a[i];
        }
        Build_Max_Heap(a, n); // bottom-up

        for (int i = 0; i < n; i++)
        {
            std::cout << a[i] << ' ';
        }

        std::cout << "\n";


        //Demo top_down
        std::cout << "Top-down:";
        std::cout << "n=";
        std::cin >> n;

        for (int i = 0; i < n; i++)
        {
            std::cin >> a[i];
        }
        Build_Max_Heap_top_down(a, n);

        for (int i = 0; i < n; i++)
        {
            std::cout << a[i] << ' ';
        }

        std::cout << "\n";

        //Demo heapsort
        int b[100];
        repeta:
        std::cout << "Heapsort:";
        std::cout << "n=";
        std::cin >> n;
   

        for (int i = 0; i < n; i++)
        {
            std::cin >> b[i];
        }
        
        Heapsort(b, n); 

        for (int i = 0; i < n; i++)
        {
            std::cout << b[i] << ' ';
        }
    
    cout << "\nSe repeta testul heapsort?:(D/N)  "; //pentru a se incerca mai multe teste
    char test;
    std::cin >> test;
    if (test == 'D')
        goto repeta;
 }
}
