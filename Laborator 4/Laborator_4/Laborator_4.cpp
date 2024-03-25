// Laborator_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
@30225
*@author Fleseriu Ioan-Rares
*
*Grupa 30225
* 
*   Analiza QuickSort:
*    La inceput am prezentat analiza algoritmului  Quicksort in cele 3 cazuri: favorabil, defavorabil si mediu statistic.
*   Dupa cum ne spune si teoria, pentru CAZURILE FAVORABILE si MEDIU STATISTIC, algoritmul prezinta o crestere cu o complexitate de O(nlogn),
* atat in ceea ce priveste numarul de atribuiri, cat si numarul de comparatii, prezentand astfel o eficienta destul de ridicata.
*   
    Pentru cazul DEFAVORABIL, in schimb, algoritmul are o complexitate de O(n^2), atat pentru atribuiri, cat si pentru comparatii,
* dupa cum se vede si din grafice(sunt functii patratice).
*   Cu toate acestea, cazul defavorabil poate fi evitat in majoritatea cazurilor, folosind o randomizare sau un algoritm de median of 3, pentru alegerea pivotului.
* 
*  Am implementat atat algoritmul cu pivotul ca fiind elementul din mijloc(astfel aveam o alegere buna a cazului favorabil, fiind chiar sirul crescator), cat si
algoritmul in care pivotul este ultimul element(unde cazul defavorabil este tot sirul ordonat crescator).

    Analiza Heapsort vs QuickSort:
    
    Pentru CAZUL FAVORABIL, putem observa ca algoritmul QuickSort este mai eficient decat HeapSort. Desi ambele au aceasi complexitate(O(nlogn)), QuickSort
are evident mai putine atribuiri si comparatii per iteratie.
    
    Pentru CAZUL MEDIU STATISTIC, asemanator cazului anterior, QuickSort este mai eficient decat Heapsort, atat in ceea ce priveste asignarile, cat si in ceea
  ce priveste comparatiiel. Cu toate acestea, putem observa din grafic ca Heapsort are o evolutie mai "lina" decat QuickSort, valorile osciland putin mai mult
  la QuickSort, ceea ce este de asteptat atunci cand lua in calcul implementarea acestui algoritm.

    Pentru CAZUL DEFAVORABIL, spre deosebire de cazurile anterioare, Heapsort prezinta o performanta mai buna decat QuickSort, atat in cazul asignarilor cat si
 in cazul comparatiior. Dupa cum ne spune si teoria, pe cand Heapsort are o complexitate in cazul defavorabil de O(nlogn), QuickSort are o complexitate de O(n^2),
 ceea ce induce o diferenta mare a performantei odata cu cresterea numarului de elemente al sirului( dupa cum se observa si in grafic, cresterea QuickSortului este
 mult mai mare decat cea a Heapsortului).

    Pentru analiza unui algoritm de sortare iterativ vs recursiv am ales Bubble Sort
   
   Analiza Bubble Sort iterativ vs recursiv:
    
*   In toate cele 3 cazuri: favorabil, defavorabil si mediu statistic, ambii algoritmi prezinta aceeasi performanta, astfel incat diferenta consta in trecerea la
* o noua iteratie, astfel operatiile de comparare si de atribuire raman la fel.
* Deci, in ceea ce priveste cresterea operatiilor acestor algoritmi, ambii prezinta o crestere patratica, care este defapt si complexitatea BubbleSort(O(n^2)).
*   In schimb, cand observam cresterea timpului de rulare, observam ca algoritmul iterativ este putin mai eficient.
*   Acest lucru poate fi explicat prin folosirea stivei de catre apelurile recursive, care, desi la numere mai mici ale numarului de elemente al sirului pare
nesemnificativa, pentru numere mai mari se arata o diferenta mai mare, ceea ce ne arata ca nu este atat de eficient sa alegem un algoritm recursiv, la un volum
mare de informatie, daca exista o varianta iterativa pentru algoritmul folosit.
    Timpul la bubble sort, dupa multe teste(70-100/iteratie) se vede ca difera destul de tare intre cele doua variante.


    PS: Dupa cum ne era sugera in laborator, sa facem mai multe teste, valorile timpului sunt usor "amplificate" in functie de numarul testelor,
    insa ofera o mai buna vizualizare a diferentei dintre cei 2 algoritmi.

*/

#include <iostream>
#include "Profiler.h"
#include <stdlib.h>     
#include <time.h>
using namespace std;

Profiler p("Cazul_mediu-statistic");

//HEAPSORT CU IMPLEMENTARE BOTTOM-UP:

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


void MaxHeapify(int a[], int i, int n,int nr)
{
   Operation atribuiri = p.createOperation("HeapSort_atribuiri", nr);
   Operation comparari = p.createOperation("HeapSort_comparari", nr);
    int left = find_left(i);
    int right = find_right(i);
    int maxim;


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
        if (a[right] > a[maxim])
            maxim = right;
    }

    if (maxim != i)
    {
        atribuiri.count(3);
        int aux = a[i];
        a[i] = a[maxim];
        a[maxim] = aux;
        MaxHeapify(a, maxim, n,nr);
    }
    p.addSeries("HeapSort_total", "HeapSort_atribuiri", "HeapSort_comparari");
}


//Varianta Bottom-up
void Build_Max_Heap(int a[], int n)
{
    for (int i = n / 2; i >= 0; i--)
    {
        MaxHeapify(a, i, n,n);
    }
}

//Heapsort:

void Heapsort(int a[], int n)
{
    Operation atribuiri = p.createOperation("HeapSort_atribuiri", n);
   Operation comparari = p.createOperation("HeapSort_comparari", n);
    int heapsize = n;
    Build_Max_Heap(a, n);
    for (int i = n - 1; i >= 1; i--)
    {
        atribuiri.count(3);
        int aux = a[i];
        a[i] = a[0];
        a[0] = aux;
        heapsize = heapsize - 1;
        MaxHeapify(a, 0, heapsize,n);
    }
}

//QUICKSORT:



int Partition(int a[],int l,int  r,int n)
{
    Operation atribuiri = p.createOperation("QuickSort_atribuiri", n);
    Operation comparari = p.createOperation("QuickSort_comparari", n);
    int x = a[(r+l)/2]; // alegem pivotul ca fiinid elementul din mijloc, pentru a evita pe cat posibil cazul nefavorabil
    atribuiri.count();
    int i = l;
    int j = r;

    while (i <= j)
    {   
        comparari.count();
        while (a[i] < x)
        {
            comparari.count();
            i++;
        }
        comparari.count();
        while (a[j] > x)
        {
            comparari.count();
            j--;
        }
        if (i <= j)
        {
            atribuiri.count(3);
            std::swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    p.addSeries("QuickSort_total", "QuickSort_atribuiri", "QuickSort_comparari");
    return i;
}

void QuickSort(int a[], int l, int r,int n)
{
    if (l < r)
    {
        int q = Partition(a, l, r,n);
        QuickSort(a, l, q - 1,n);
        QuickSort(a, q+1, r,n);
    }
}

//BUBBLE SORT ITERATIC SI RECURSIV:

void bubble_sort_it(int a[], int n)
{
    Operation atribuiri = p.createOperation("BubbleIterativ_atribuiri", n);
    Operation comparari = p.createOperation("BubbleIterativ_comparari", n);
    int ind, aux;
    do {
        ind = 1;
        for (long i = 0; i < n - 1; i++)
        {
            comparari.count();
            if (a[i] > a[i + 1])
            {
                atribuiri.count(3);
                aux = a[i];
                a[i] = a[i + 1];
                a[i + 1] = aux;
                ind = 0;
            }
        }
        n--;
    } while (ind == 0);
    p.addSeries("BubbleIterativ_total", "BubbleIterativ_atribuiri", "BubbleIterativ_comparari");
}

//BUBBLE SORT RECURSIV

void bubble_sort_rec(int a[], int n,int nr)
{
    Operation atribuiri = p.createOperation("BubbleRecursiv_atribuiri", nr);
    Operation comparari = p.createOperation("BubbleRecursiv_comparari", nr);
    if (n == 1)
    {
        return;
    }
    int ind = 0;

    for (int i = 0; i < n-1; i++)
    {
        comparari.count();
        if (a[i] > a[i + 1])
        {
            atribuiri.count(3);
            std::swap(a[i], a[i + 1]);
            ind = 1;
        }
    }
    p.addSeries("BubbleRecursiv_total", "BubbleRecursiv_atribuiri", "BubbleRecursiv_comparari");
    if (ind == 0)
        return;
   
    bubble_sort_rec(a, n - 1,nr);

}

//Quicksort last element pivot

int Partition_last(int a[], int l, int r,int n)
{
    Operation atribuiri = p.createOperation("QuickSort_atribuiri", n);
    Operation comparari = p.createOperation("QuickSort_comparari", n);
    atribuiri.count();
    int x = a[r];
    int i =l - 1;
    for (int j = l; j <= r - 1; j++)
    {
        comparari.count();
        if (a[j] <= x)
        {
            i++;
            atribuiri.count(3);
            std::swap(a[i], a[j]);
        }
       
    }
    atribuiri.count(3);
    std::swap(a[i+1], a[r]);
    p.addSeries("QuickSort_total", "QuickSort_atribuiri", "QuickSort_comparari");
    return i + 1;
}

void Quicksort_last(int a[], int l, int r,int n)
{
    if (l < r)
    {
        int piv = Partition_last(a, l, r,n);
        Quicksort_last(a, l, piv - 1,n);
        Quicksort_last(a, piv + 1, r,n);
    }
}



//Randomized Select

int randomized_partition(int a[], int l, int r,int n)
{
    srand(time(NULL));
    int i = rand() % (r-l+1)+l;
    std::swap(a[i], a[r]);
    return Partition_last(a, l, r,n);

}

int randomized_select(int a[], int l, int r, int i,int n) // returneaza al i-lea cel mai mic element al sirului
{
    if (l == r)
    {
        return a[l];
    }
    int q = randomized_partition(a, l, r,n);
    int k = q - l + 1;
    if (i == k)
    {
        return a[q];
    }
    else if (i < k)
    {
        return randomized_select(a, l, q - 1, i,n);
    }
    else
    {
        return randomized_select(a, q+1, r, i-k,n);   
    }
}

void copy_array(int a[], int b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        b[i] = a[i];
    }
}

void Fill_arraywith_x(int a[], int n, int x)
{
    for (int i = 0; i <= n; i++)
    {
        a[i] = x;
    }
}

int main()
{
    char terminat;
    int a[10000],b[10000];
    int n;
    int c[10000];
    char alegere;
    std::cout << "Alege(T/G):";
    std::cin >> alegere;
    if (alegere == 'G')
    {
       //Mediu STATISTIC
        
        for (int j = 1; j <= 5; j++)
        {
           
            for (int i = 100; i <= 10000; i = i + 100)
            {

                FillRandomArray(a, i, 100, 10000, false, 0);

                QuickSort(a, 1, i, i);
            }
        }
        p.divideValues("QuickSort_atribuiri", 5);
        p.divideValues("QuickSort_comparari", 5);
        p.divideValues("QuickSort_total", 5);

        p.createGroup("MediuStatistic_nr_atribuiri", "QuickSort_atribuiri");
        p.createGroup("MediuStatistic_comparari", "QuickSort_comparari");
        p.createGroup("MediuStatistic_total", "QuickSort_total");

        p.reset("Favorabil");
        
        //FAVORABIL QUICKSORT
        for (int i = 100; i <= 10000; i = i + 100)
        {          
            FillRandomArray(a, i, 100, 10000, false, 1);
            QuickSort(a, 1, i, i);
        }

        p.createGroup("Favorabil_nr_atribuiri", "QuickSort_atribuiri");
        p.createGroup("Favorabil_comparari", "QuickSort_comparari");
        p.createGroup("Favorabil_total", "QuickSort_total");

        p.reset("Defavorabil_quick");

        //DEFAVORABIL QUICKSORT
        for (int i = 100; i <= 10000; i = i + 100)
        {
            int x;
            srand(time(NULL));
            x = rand() % 100;
            Fill_arraywith_x(a, i, x);
            Quicksort_last(a, 1, i, i);
        }

        p.createGroup("Defavorabil_nr_atribuiri", "QuickSort_atribuiri");
        p.createGroup("Defavorabil_comparari", "QuickSort_comparari");
        p.createGroup("Defavorabil_total", "QuickSort_total");
        

        //HEAPSORT VS QUICKSORT
        p.reset("favorabil_ambele");

        std::cout << "\n";
        for (int i = 100; i <= 10000; i = i + 200)
        {

          
            FillRandomArray(a, i, 100, 10000, false, 1);
            QuickSort(a, 1, i, i);
            FillRandomArray(a, i, 100, 10000, false, 2);
            Heapsort(a, i);
        }

        p.createGroup("Favorabil_nr_atribuiri", "QuickSort_atribuiri", "HeapSort_atribuiri");
        p.createGroup("Favorabil_comparari", "QuickSort_comparari", "HeapSort_comparari");
        p.createGroup("Favorabil_total", "QuickSort_total", "HeapSort_total");

        //QUICKSORT ANALIZA+ ANALIZA COMPARATIVA QUICKSORT SI HEAPSORT
        //CAZ MEDIU-STATISTIC
        p.reset("Defavorabil_ambele");
        
        for (int i = 100; i <= 10000; i = i + 200)
        {
           
            int x;
            FillRandomArray(a, i, 100, 10000, false, 1);
            Quicksort_last (a, 1, i, i);
            FillRandomArray(a, i, 100, 10000, false, 1);
            Heapsort(a, i);
        }

        p.createGroup("Defavorabil_nr_atribuiri", "QuickSort_atribuiri", "HeapSort_atribuiri");
        p.createGroup("Defavorabil_nr_atribuiri", "HeapSort_atribuiri");
        p.createGroup("Defavorabil_comparari", "QuickSort_comparari", "HeapSort_comparari");
        p.createGroup("Defavorabil_comparari", "HeapSort_comparari");
        p.createGroup("Defavorabil_total", "QuickSort_total", "HeapSort_total");
        p.createGroup("Defavorabil_total_heapsort_nu se observa", "HeapSort_total");


        p.reset("MediuStatistic_ambele");

       for (int j = 1; j <= 5; j++)
        { 
            for (int i = 100; i <= 10000; i = i + 200)
            {
              
                FillRandomArray(a, i, 100, 10000, false, 0);
                copy_array(a, b, i);
                QuickSort(a, 1, i, i);
               
                Heapsort(b, i);
            }
        }
        p.divideValues("QuickSort_atribuiri", 5);
        p.divideValues("QuickSort_comparari", 5);
        p.divideValues("QuickSort_total", 5);

        p.divideValues("HeapSort_atribuiri", 5);
        p.divideValues("HeapSort_comparari", 5);
        p.divideValues("HeapSort_total", 5);

        p.createGroup("MediuStatistic_nr_atribuiri", "QuickSort_atribuiri", "HeapSort_atribuiri");
        p.createGroup("MediuStatistic_comparari", "QuickSort_comparari", "HeapSort_comparari");
        p.createGroup("MediuStatistic_total", "QuickSort_total", "HeapSort_total");
        
        //ANALIZA BUBBLE SORT ITERATIV VS RECURSIV
         p.reset("Bubble_favorabil");
         
        for (int i = 100; i <= 10000; i = i + 200)
        {
            FillRandomArray(a, i, 100, 10000, false, 1);
            bubble_sort_it(a, i);
            bubble_sort_rec(a, i,i);
        }

        p.createGroup("Favorabil_nr_atribuiri", "BubbleIterativ_atribuiri", "BubbleRecursiv_atribuiri");
        p.createGroup("Favorabil_comparari", "BubbleIterativ_comparari", "BubbleRecursiv_comparari");
        p.createGroup("Favorabil_total", "BubbleIterativ_total", "BubbleRecursiv_total");

     
       for (int i = 100; i <= 10000; i=i+200)
       {
        
           FillRandomArray(a, i, 100, 10000, false, 1);
           p.startTimer("Bubble_sort_it_time", i);
           for (int test = 0; test < 500; ++test) {
               copy_array(a, c, i);
               bubble_sort_it(c, i);

           }
           p.stopTimer("Bubble_sort_it_time", i);
           p.startTimer("Bubble_sort_rec_time", i);
           for (int test = 0; test < 500; ++test) {
               copy_array(a, b, i);
               bubble_sort_rec(b, i,i);
           }
           p.stopTimer("Bubble_sort_rec_time", i);

       }
       p.createGroup("Analiza timp favorabil bubble iterativ vs recursiv","Bubble_sort_rec_time","Bubble_sort_it_time");
       

        //Defavorabil - in cazul in care am luat pivotul la mijloc, cazul defavorabil va fi atunci cand toate elementele sunt egale

       p.reset("Bubble_defavorabil");

           for (int i = 100; i <= 10000; i = i + 200)
           {
               FillRandomArray(a, i, 100, 10000, false, 2);
               bubble_sort_it(a, i);
               FillRandomArray(a, i, 100, 10000, false, 2);
               bubble_sort_rec(a, i,i);
           }
       
       p.createGroup("Defavorabil_nr_atribuiri", "BubbleIterativ_atribuiri", "BubbleRecursiv_atribuiri");
       p.createGroup("Defavorabil_comparari", "BubbleIterativ_comparari", "BubbleRecursiv_comparari");
       p.createGroup("Defavorabil_total", "BubbleIterativ_total", "BubbleRecursiv_total");

        
       for (int i = 100; i <= 10000; i=i+200)
       {
          
           FillRandomArray(a, i, 100, 10000, false, 2);
           p.startTimer("Bubble_sort_it_time", i);
           for (int test = 0; test < 70; ++test) {
               copy_array(a, c, i);
               bubble_sort_it(c, i);

           }
           p.stopTimer("Bubble_sort_it_time", i);
           p.startTimer("Bubble_sort_rec_time", i);
           for (int test = 0; test < 40; ++test) {
               copy_array(a, b, i);
               bubble_sort_rec(b, i,i);
           }
           p.stopTimer("Bubble_sort_rec_time", i);

       }
       p.createGroup("Analiza timp defavorabil bubble iterativ vs recursiv","Bubble_sort_rec_time","Bubble_sort_it_time");

       
       p.reset("Bubble_mediu-statistic");
     
       for(int j = 1; j <= 5; j++)
       {
           
           for (int i = 100; i <= 10000; i = i + 200)
           {
               FillRandomArray(a, i, 100, 10000, false, 0);
               copy_array(a, b, i);
               bubble_sort_it(a, i);
               bubble_sort_rec(b, i,i);
           }
       }
       p.divideValues("BubbleIterativ_atribuiri", 5);
       p.divideValues("BubbleIterativ_comparari", 5);
       p.divideValues("BubbleIterativ_total", 5);

       p.divideValues("BubbleRecursiv_atribuiri", 5);
       p.divideValues("BubbleRecursiv_comparari", 5);
       p.divideValues("BubbleRecursiv_total", 5);

       p.createGroup("Mediu-Statistic_nr_atribuiri", "BubbleIterativ_atribuiri", "BubbleRecursiv_atribuiri");
       p.createGroup("Mediu-Statistic_comparari", "BubbleIterativ_comparari", "BubbleRecursiv_comparari");
       p.createGroup("Mediu-Statistic_total", "BubbleIterativ_total", "BubbleRecursiv_total");
       
       //Analiza timpului in caz mediu statistic
//p.reset("time");

     

       for (int i = 100; i <= 10000; i=i+200)
       {    
           FillRandomArray(a, i, 100, 10000, false, 0);
           p.startTimer("Bubble_sort_it_time", i);
           for (int test = 0; test <60; ++test) {
               copy_array(a, c, i);
               bubble_sort_it(c, i);

           }
           p.stopTimer("Bubble_sort_it_time", i);
           p.startTimer("Bubble_sort_rec_time", i);
           for (int test = 0; test < 30; ++test) {
               copy_array(a, b, i);
               bubble_sort_rec(b, i,i);
           }
           p.stopTimer("Bubble_sort_rec_time", i);

       }
       p.createGroup("Analiza timp bubble iterativ vs recursiv","Bubble_sort_rec_time","Bubble_sort_it_time");
       p.showReport();
    }
    else
    {
        std::cout << "Heapsort:\n";
        std::cout << "n=";
        std::cin >> n;

        for (int i = 0; i < n; i++)
        {
            std::cin >> a[i];
        }
        Heapsort(a, n);
        for (int i = 0; i < n; i++)
        {
            std::cout << a[i] << ' ';
        }

        std::cout << "\nQuick:\n";
        std::cout << "n=";
        std::cin >> n;
        for (int i = 0; i < n; i++)
        {
            std::cin >> a[i];
        }
        QuickSort(a, 0, n - 1,n);
        for (int i = 0; i < n; i++)
        {
            std::cout << a[i] << ' ';
        }

        /*std::cout << "BubbleSort_rec:\n";
        std::cout << "n=";
        std::cin >> n;

        for (int i = 0; i < n; i++)
        {
            std::cin >> a[i];
        }
        bubble_sort_rec(a, n);;
        for (int i = 0; i < n; i++)
        {
            std::cout << a[i] << ' ';
        }*/

        //randomized select
        std::cout << "\nRandomized-Select\n";
        std::cout << "n=";
        std::cin >> n;

        for (int i = 1; i <= n; i++)
        {
            std::cin >> a[i];
        }
        int i;
        std::cout << "Al i-lea cel mai mic element\n i=";
        std::cin >> i;

        int el= randomized_select(a, 1, n, i,n);

        std::cout << "Elementul este: " << el;


        std::cout << "Gata?(D/N): ";
        std::cin >> terminat;
    }
}