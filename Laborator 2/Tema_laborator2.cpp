// Tema_laborator2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*

*@author Fleseriu Ioan-Rares
*
*Grupa 30225

*Analiza si compararea metodelor directe de sortare( Bubble Sort, Selection Sort si Insertion Sort)
* 
* Interpretare personala:
* 
*   Am comparat cele 3 metode de sortare mentionate mai sus in cazurile: favorabile,defavorabil si mediu statistic.
* Conform instructiunilor din laborator, pentru fiecare caz am afisat cate un grafic in care sa fie evidente diferentele dintre metodele de sortare in cele 3 cazuri,
* iar unde graficele se suprapuneau, sau aveau valori cu mult mai mari/mici una fata de cealalta am prezentat si un grafic separat
* pentru o intelegere mai buna.
* 
*   Pentru Insertion Sort am folosit inserare binara, pentru o eficienta mai sporita.
* 
*   In urma analizei am observat ca:
* 
*       -in cazul favorabil, dupa cum era de asteptat, numarul de atribuiri pentru Bubble Sort si Selection Sort este 0
*       In schimb, la Insertion Sort vom avea cate 2 atribuiri pe iteratie, datorita asignarilor in care elementul se introduce
        pe pozitia pe care era deja ( "val = a[i]" , "a[poz] = val" ) => crestere liniara
        -in acelasi caz, numarul de comparari pentru bubble sort si insertion sort este foarte mic, comparand cu  Selection Sort, unde gasim o crestere quadratica
        
        -in cazul defavorabil,bubble sort are cea mai slaba performanta, avand cel mai mare numar de atribuiri si cel mai mare numar de comparari, toti algoritmii prezinta o complexitate patratica ( O(n^2))
        -se observa totusi ca datorita folosirii insertiei binare, la insertion sort, s-a imbunatatit timmpul gasirii pozitiei de inserare

        -in cazul mediu statistic, am folosit aceleasi 5 siruri generate aleator pentru toate cele 3 metode de sortari
        -aici, putem observa ca cea mai buna performanta, in ceea ce priveste atribuirile, a fost adusa de Selection Sort,iar cea mai slaba de Bubble Sort
        -in ceea ce priveste compararile, cea mai buna performanta a fost adusa de insertion sort, iar cea mai slaba tot de Bubble Sort.

        Complexitati:

        Bubble Sort: -Best case: O(n)
                     -Worst case: O(n^2)

        Selection Sort: - Best case: O(n^2)
                        - Worst case: O(n^2)
        
        Insertion Sort: -Best case: O(n)
                        -Worst case: O(n^2)

        In ceea ce priveste memoria aditionala utilizata: O(1) - pentru fiecare sortare

       In ceea ce priveste stabilitatea, bubble si insertion sort sunt stabile, dar selection sort nu.
*/

#include <iostream>
#include "Profiler.h"

Profiler p("Cazul_favorabil");

void bubble_sort(int a[], int n)
{
    Operation atribuiri = p.createOperation("Bubble_atribuiri", n);
    Operation comparari = p.createOperation("Bubble_comparari", n);
    int ind, aux;
    do {
        ind = 1;
        for (long i = 0; i < n - 1; i++)
        {
            comparari.count();
            if (a[i] > a[i + 1])
            {
                atribuiri.count();
                atribuiri.count();
                atribuiri.count();
                aux = a[i];
                a[i] = a[i + 1];
                a[i + 1] = aux;
                ind = 0;
            }
        }
        n--;   // cel mai mare element va ajunge pe ultima pozitie, deci nu mai e nevoie sa o luam in considerare la urmatoarea parcurgere
    } while (ind == 0);
    p.addSeries("Bubble_final", "Bubble_atribuiri", "Bubble_comparari");
}

void selection_sort(int a[], int n)
{
    Operation atribuiri = p.createOperation("Selection_atribuiri", n);
    Operation comparari = p.createOperation("Selection_comparari", n);
    int jmin, aux, j;
    for (int i = 0; i < n - 1; i++)
    {
        jmin = i;
        for (j = i + 1; j < n; j++)
        {
            comparari.count();
            if (a[j] < a[jmin])
            {
                jmin = j;
            }
        }
        if (jmin != i)
        {
            atribuiri.count();
            atribuiri.count();
            atribuiri.count();
            aux = a[jmin];
            a[jmin] = a[i];
            a[i] = aux;
        }
    }
    p.addSeries("Selection_final", "Selection_atribuiri", "Selection_comparari");
}

void insertion_sort(int a[], int n) //Insertion sort cu inserare binara
{
    Operation atribuiri = p.createOperation("Insertion_atribuiri", n);
    Operation comparari = p.createOperation("Insertion_comparari", n);
    int val;
    for (int i = 1; i < n; i++)
    {
        int dr = i - 1, st = 0, mij, poz = -1;
        //Cautarea pozitiei elementului in partea ordonata a sirului:
        while (st <= dr && poz == -1)
        {

            mij = (dr + st) / 2;
            comparari.count();
            comparari.count(); // se vor face 2 comparari pana in cazul in care se va gasi solutia
            if (a[mij] == a[i])
            {
                poz = mij + 1; //pentru stabilitate am pus mij+1
            }
            else if (a[mij] < a[i])
            {
                st = mij + 1;
            }
            else
            {
                dr = mij - 1;
            }
        }
        if (poz == -1)
        {
            poz = st;
        }

        //inserarea elementului in sirul ordonat:
        atribuiri.count();
        val = a[i];
        for (int j = i; j > poz; j--)
        {
            atribuiri.count();
            a[j] = a[j - 1];
        }
        atribuiri.count();
        a[poz] = val;
    }
    p.addSeries("Insertion_final", "Insertion_atribuiri", "Insertion_comparari");
}

void copy_array(int a[], int b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        b[i] = a[i];
    }
}

void rotate(int a[], int n)
{
    int aux = a[n - 1];
    for (int i = n - 1; i > 0; i--)
    {
        a[i] = a[i - 1];
    }
    a[0] = aux;
}
int main()
{
    int n;
    char alegere;
    std::cout << "Alege: (T/G)  ";
    std::cin >> alegere;
    if (alegere == 'G')
    {
        int a[10000];

        //FAVORABIL
        for (int i = 100; i <= 10000; i = i + 100)
        {
            FillRandomArray(a, i, 100, 10000, false, 1);
            bubble_sort(a, i);
            selection_sort(a, i);
            insertion_sort(a, i);
        }
        
        p.createGroup("Favorabil_nr_atribuiri", "Bubble_atribuiri", "Selection_atribuiri", "Insertion_atribuiri");
        p.createGroup("Favorabil_nr_comparari", "Bubble_comparari", "Selection_comparari", "Insertion_comparari");
        p.createGroup("Favorabil_nr_comparari_insertion ( nu se observa mai sus)","Insertion_comparari"); // intrucat graficele se suprapuneau, conform instructiunilor din laborator, am afisat si grafice separate pentru sortarile care nu erau clar vizibile
        p.createGroup("Favorabil_nr_comparari_bubble ( nu se observa mai sus)", "Bubble_comparari");
        p.createGroup("Favorabil_nr_total", "Bubble_final", "Selection_final", "Insertion_final");
        p.createGroup("Favorabil_nr_total_selection", "Selection_final");
        p.createGroup("Favorabil_nr_total_insertion","Insertion_final");
        p.createGroup("Favorabil_nr_total_bubble", "Bubble_final");


        p.reset("Defavorabil");

        //DEFAVORABIL

        for (long i = 100; i <= 10000; i = i + 100)
        {
            FillRandomArray(a, i, 100, 10000, false, 2);
            bubble_sort(a, i);
            FillRandomArray(a, i, 100, 10000, false, 1);
            //CAZUL DEFAVORABIL PENTRU SELECTION SORT NU ESTE CEL IN CARE NUMERELE SUNT 
            //ORDONATE DESCRESCATOR, CI CEL IN CARE SIRUL ORDONAT E ROTIT LA STANGA SAU LA DREAPTA CU O POZITIE
            rotate(a, i);
            selection_sort(a, i);
            FillRandomArray(a, i, 100, 10000, false, 2);
            insertion_sort(a, i);
        }

        p.createGroup("Defavorabil_nr_atribuiri", "Bubble_atribuiri", "Selection_atribuiri", "Insertion_atribuiri");
        p.createGroup("Defavorabil_nr_atribuiri_selection ( nu se observa mai sus)", "Selection_atribuiri"); //intrucat nu se observa pe grafic evolutia datorita valorilor mari a celorlalte sortari, mai afisez un grafic separat
     
        p.createGroup("Defavorabil_nr_comparari", "Bubble_comparari", "Selection_comparari", "Insertion_comparari");

        p.createGroup("Defavorabil_nr_comparari_insertion ( nu se observa mai sus)", "Insertion_comparari");//intrucat nu se observa pe grafic evolutia datorita valorilor mari a celorlalte sortari, mai afisez un grafic separat
        p.createGroup("Defavorabil_nr_comparari_bubble ( nu se observa mai sus)", "Bubble_comparari");//intrucat nu se observa pe grafic evolutia datorita valorilor mari a celorlalte sortari, mai afisez un grafic separat
        p.createGroup("Defavorabil_nr_total", "Bubble_final", "Selection_final", "Insertion_final");
        p.createGroup("Defavorabil_nr_total_selection", "Selection_final");
        p.createGroup("Defavorabil_nr_total_insertion", "Insertion_final");
        p.createGroup("Defavorabil_nr_total_bubble", "Bubble_final");

        //MEDIU STATISTIC 

        p.reset("mediu statistic");
        int b[10000], c[10000];
        for (int j = 1; j <= 5; j++)
        {
            for (int i = 10; i <= 10000; i = i + 100)
            {
                FillRandomArray(a, i, 100, 10000, false, 0);
                copy_array(a, b, i);
                copy_array(a, c, i); //pentru a ne asigura ca in cazul mediu toate cele trei sortari au aceleai date de intrare
                bubble_sort(a, i);
                selection_sort(b, i);
                insertion_sort(c, i);
            }
        }

        p.divideValues("Bubble_atribuiri", 5);
        p.divideValues("Bubble_comparari", 5);
        p.divideValues("Bubble_total", 5);

        p.divideValues("Selection_atribuiri", 5);
        p.divideValues("Selection_comparari", 5);
        p.divideValues("Selection_total", 5);

        p.divideValues("Insertion_atribuiri", 5);
        p.divideValues("Insertion_comparari", 5);
        p.divideValues("Insertion_total", 5);

        p.createGroup("MediuStatistic_nr_atribuiri", "Bubble_atribuiri", "Selection_atribuiri", "Insertion_atribuiri");
        p.createGroup("MediuStatistic_nr_atribuiri_selection ( nu se observa mai sus)","Selection_atribuiri");
        p.createGroup("MediuStatistic_nr_comparari", "Bubble_comparari", "Selection_comparari", "Insertion_comparari");
        p.createGroup("MediuStatistic_nr_comparari_insertion ( nu se observa mai sus)", "Insertion_comparari");
        p.createGroup("MediuStatistic_nr_total", "Bubble_final", "Selection_final", "Insertion_final");
        p.createGroup("MediuStatistic_nr_total_selection", "Selection_final");
        p.createGroup("MediuStatistic_nr_total_insertion", "Insertion_final");
        p.createGroup("MediuStatistic_nr_total_bubble", "Bubble_final");

        p.showReport();

    }
    else
    {
        //DEMO BUBBLE SORT
        int a[100];
        int n;
        std::cout << "BubbleSort\n";
        std::cout << "n=";
        std::cin >> n;
        for (int i = 0; i < n; i++)
        {
            std::cout << "a[" << i << "]=";
            std::cin >> a[i];
        }

        bubble_sort(a, n);
        for (int i = 0; i < n; i++)
        {
            std::cout << a[i] << " ";
        }

        //DEMO SELECTION

        std::cout << "\nSelectionSort\n";
        std::cout << "n=";
        std::cin >> n;
        for (int i = 0; i < n; i++)
        {
            std::cout << "a[" << i << "]=";
            std::cin >> a[i];
        }
        selection_sort(a, n);
        for (int i = 0; i < n; i++)
        {
            std::cout << a[i] << " ";
        }

        //DEMO INSERTION

        std::cout << "\nInsertionSort\n";
        std::cout << "n=";
        std::cin >> n;
        for (int i = 0; i < n; i++)
        {
            std::cout << "a[" << i << "]=";
            std::cin >> a[i];
        }
        insertion_sort(a, n);
        for (int i = 0; i < n; i++)
        {
            std::cout << a[i] << " ";
        }

    }
}

