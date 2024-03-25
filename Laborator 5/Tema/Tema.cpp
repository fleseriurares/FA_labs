// Tema.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
*@author Fleseriu Ioan-Rares
*
*Grupa 30225
*
*   Pentru generarea a k liste crescatoare, de lungimi diferite am gandit un astfel de algoritm:
* 
*       In functie de numarul de elemente generez un sir "a", cu n elemente random, in ordine crescatoare.
*   Prima data pun cate un element, in ordinea in care apar a, in fiecare sir(de la sirul 1 pana la sirul k), pentru a ma asigura ca in final toate dintre cele k
*   siruri va avea cel putin un element.
*   Apoi, folosesc o variabila x, care ia un numar random de la 1 la k, si in functie de acel numar, o sa pun urmatorul element din a in lista x.
*   Astfel, dupa acest algoritm, voi avea k siruri de lungimi aleatoare, fiecare avand elemente aleatoare, in ordine crescatoare.
*   
    
    Analiza mediu statistic k=5/10/100; "n" este variabil:
* 
*       La început am analizat cum creste numarul de operatii facute de algoritm pentru 3 valori ale lui k(numar de liste) in conditiile in care n era constant.
*   Dupa cum se observa si din grafic, se observa ca atunci cand avem un numar constant de liste graficul functiei progreseaza intr-o commplexitate de O(n*logk)
*   Desi nu este o diferenta foarte mare, putem observa ca, atunci cand am ales valori mai mari pentru k, numarul de operatii este mai mare decat atunci cand avem valori
*   mai mici(mai putine liste), ceea ce este si de asteptat.
*       In ceea ce priveste atribuirile si comparatiile acestea avanseaza la un raport relativ egal, intre cele 3 valori ale lui k.
*   
* 
*  Analiza mediu statistic n este constant(n=10000) si k variabil:
* 
*       Cu toate acestea, este interesant de observat cum arata graficul functiei atunci cand n este constant(n=10000 in cazul nostru) si variaza numarul de 
*   liste(k). Se observa astfel din grafic, in urma a 5 masuratori(cazul mediu statistic), ca pe masura ce k creste, numarul de operatii are valori din ce
*   in ce mai apropiate. Astfel, se observa clar cum domina cresterea logaritmica(la n=10000, teoretic complexitatea este 100000 * logk, coeficientul influenteaza
    din ce in ce mai putin graficul, pe masura ce k creste la valori mari).

        
        
        Complexitate KwayMerge: O(nlogk).
* 
*/
#include <iostream>
#include "Profiler.h"
#include <stdlib.h>
#include <time.h>

Profiler p("Mediu_Statistic_3k");

typedef struct node {
    int key;
    struct node* next;
}nodeT;

nodeT* newnode(int val)
{
    nodeT* p = (nodeT*)malloc(sizeof(nodeT));
    p->next = NULL;
    p->key = val;
    return p;
}

void insert_last(nodeT** first, int val)
{

    nodeT* p = newnode(val);
    nodeT* aux = *first;
    if (*first == NULL)
    {
        *first = p;
    }
    else
    {
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = p;
    }
}

void afisare(nodeT* first)
{
    while (first != NULL)
    {
        std::cout << first->key << ' ';
        first = first->next;
    }

}

int find_right(int i)
{
    return 2 * i + 2; // deoarece sirul incepe cu iteratia 0
}

int find_left(int i)
{

    return 2 * i + 1; // deoarece sirul incepe cu iteratia 0
}


void Heapify(nodeT* a[], int i, int n, int nr, Operation atribuiri, Operation comparari)
{
  //  Operation atribuiri = p.createOperation("atribuiri", nr);
  //  Operation comparari = p.createOperation("comparari", nr);
    int left = find_left(i);
    int right = find_right(i);
    int minim;

    if (left < n)
    {
        comparari.count();
        if (a[left]->key < a[i]->key)
            minim = left;
        else
            minim = i;
    }
    else
    {
        minim = i;
    }
    if (right < n)
    {
        comparari.count();
        if (a[right]->key < a[minim]->key)
        {
            minim = right;
        }
    }

    if (minim != i)
    {
        atribuiri.count(3);
        nodeT* aux = a[i];
        a[i] = a[minim];
        a[minim] = aux;

        Heapify(a, minim, n, nr,atribuiri, comparari);
    }

}


//void Heapify(nodeT* a[], int i, int n, int nr)
//{
//    Operation atribuiri = p.createOperation("atribuiri", n);
//    Operation comparari = p.createOperation("comparari", n);
//    int left = find_left(i);
//    int right = find_right(i);
//    int minim;
//
//    if (left < n && a[left]->key < a[i]->key)
//    {
//            minim = left;
//    }
//    else
//    {
//        minim = i;
//    }
//    if (right < n && a[right]->key < a[minim]->key)
//    {
//            minim = right;  
//    }
//    if (minim != i)
//    {
//        atribuiri.count(3);
//        nodeT* aux = a[i];
//        a[i] = a[minim];
//        a[minim] = aux;
//
//        Heapify(a, minim, n, nr);
//    }
//
//}


void Build_min_heap(nodeT* sir[], int k, int n,Operation atribuiri, Operation comparari)
{
    for (int i = k / 2; i >= 0; i--)
    {
        Heapify(sir, i, k, n,atribuiri,comparari);
    }
}

void random_insert(nodeT* sir[], int a[], int k, int n)
{

    int j = 0;
    for (int i = k - 1; i >= 0; i--)
    {
        insert_last(&sir[i], a[j]);
        j++;
        n--;
    }
    srand(time(NULL));

    while (n > 0)
    {
        int x = rand() % k;
        insert_last(&sir[x], a[j]);
        j++;
        n--;
    }
}

void reset_lists(nodeT* s[], int n)
{
    for (int i = 0; i <= n; i++)
    {
        s[i] = NULL;
    }
}

void KwayMerge(nodeT* a[], int k, int n, Operation atribuiri, Operation comparari)
{
  //  Operation atribuiri = p.createOperation("atribuiri", n);
   // Operation comparari = p.createOperation("comparari", n);
    int heapsize = k, minim;
    Build_min_heap(a, k, n,atribuiri,comparari);

    while (heapsize > 0)
    {
        atribuiri.count();
        atribuiri.count();
        minim = a[0]->key;
        a[0] = a[0]->next;
        insert_last(&a[k], minim);
      // comparari.count();
        if (a[0] == NULL)
        {
            atribuiri.count();
            a[0] = a[heapsize - 1];
            heapsize--;
        }

        Heapify(a, 0, heapsize, n,atribuiri,comparari);
    }
   // p.addSeries("Total_operatii", "atribuiri", "comparari");
}

int main()
{
    int  n, x;
    char c;
    int k;
    std::cout << "Alege (G/T):";
    std::cin >> c;
    int a[10001];
    nodeT* sir[10000] = {};
   
    if (c == 'T') // nodeT* p[100] = {};
    { 
        Operation atribuirii = p.createOperation("atribuirii", 100);
    Operation compararii = p.createOperation("compararii", 100);
        std::cout << "n=";
        std::cin >> n;
        int m = n;
        std::cout << "k=";
        std::cin >> k;

        FillRandomArray(a, n, 0, 1000, false, 1);
        random_insert(sir, a, k, n);
        for (int i = 0; i < k;i++)
        {
            afisare(sir[i]);
        std::cout << '\n';
        }

    std:: cout << "\nSirul interclasat este :\n";
    KwayMerge(sir, k, n, atribuirii, compararii);
    afisare(sir[k]);  
    std::cout << "\nTastati 'ok' pentru final ";
    std::cin >> c;

    }
    else 
    {
        for (int l = 0; l < 10; l++)
        {
           // std::cout << l<<' ';
            for (int n = 100; n <= 10000; n = n + 100)
            {

                Operation atribuiri_k1 = p.createOperation("atribuiri", n);
                Operation comparari_k1 = p.createOperation("comparari", n);
                k = 5;
                FillRandomArray(a, n, 0, 100000, false, 1);
                random_insert(sir, a, k, n);
                KwayMerge(sir, k, n, atribuiri_k1, comparari_k1);
                reset_lists(sir, k);
                p.addSeries("Operatii k=5", "atribuiri", "comparari");
            }

            for (int n = 100; n <= 10000; n = n + 100)
            {
                Operation atribuiri_k2 = p.createOperation("atribuiri2", n);
                Operation comparari_k2 = p.createOperation("comparari2", n);


                k = 10;
                FillRandomArray(a, n, 0, 100000, false, 1);
                random_insert(sir, a, k, n);
                KwayMerge(sir, k, n, atribuiri_k2, comparari_k2);
                reset_lists(sir, k);
                p.addSeries("Operatii k=10", "atribuiri2", "comparari2");

            }

            for (int n = 100; n <= 10000; n = n + 100)
            {
                Operation atribuiri_k3 = p.createOperation("atribuiri3", n);
                Operation comparari_k3 = p.createOperation("comparari3", n);


                k = 100;
                FillRandomArray(a, n, 0, 100000, false, 1);
                random_insert(sir, a, k, n);
                KwayMerge(sir, k, n, atribuiri_k3, comparari_k3);
                reset_lists(sir, k);
                p.addSeries("Operatii k=100", "atribuiri3", "comparari3");
            }
        }
        p.divideValues("Operatii k=100", 10);
        p.divideValues("Operatii k=10", 10);
        p.divideValues("Operatii k=5", 10);
        p.divideValues("atribuiri3", 10);
        p.divideValues("atribuiri2", 10);
        p.divideValues("atribuiri", 10);
        p.divideValues("comparari", 10);
        p.divideValues("comparari2", 10);
        p.divideValues("comparari3", 10);
        p.createGroup("Operatii_final", "Operatii k=100", "Operatii k=10", "Operatii k=5");
        p.createGroup("Atribuiri_final", "atribuiri3", "atribuiri2", "atribuiri");
        p.createGroup("Comparatii_final", "comparari3", "comparari2", "comparari");
        p.reset("N_variabil");
        n = 10000;
        for (int j = 0; j < 5; j++)
        {
            std::cout << j << ' ';
            for (int k = 10; k < 500; k = k + 10)
            {
                Operation atribuiri = p.createOperation("atribuiri", k);
                 Operation comparari = p.createOperation("comparari", k);
                 if (k % 100 == 0)
                std::cout << k << ' ';
                FillRandomArray(a, n, 0, 100000, false, 1);
                 random_insert(sir, a, k, n);
                 KwayMerge(sir, k, n, atribuiri, comparari);
               reset_lists(sir, k);
                p.addSeries("Operatii k=var", "atribuiri", "comparari");
            }
         }

         p.divideValues("Operatii k=var", 5);
        p.divideValues("atribuiri", 5);
        p.divideValues("comparari", 5);

        p.showReport();
        std::cout << "\nTastati 'ok' pentru final ";
        std::cin >> c;
    }
}

