#include <iostream>
#include "Profiler.h"
#include <time.h>
/**
Grupa 30225
author Fleseriu Ioan-Rares

    Parcurgerea iterativa vs recursiva a unui arbore binar. Analiza QuickSort vs QuickSort hibridizat.

    Analiza comparativa a parcurgerii iterative vs recursive:

    Am ales sa implementez parcurgerea in preordine. Astfel, in ceea ce priveste parcurgerea recursiva,pentru un arbore binar
pe care il generez aleator, apelez functia de parcurgere incepand cu radacina, afisez nodul curent, apoi merg recursiv pe ramura stanga a
fiecarui nod apelat, apoi pe ramura dreapta. (RSD)
    Deoarece trec doar o data prin fiecare nod, complexitatea in timp a aceste parcurgeri va fi O(n), iar memoria aditionala e 0.
    Pentru parcurgerea iterativa am folosit algoritmul lui Morris, in care la fiecare parcurgere refac legaturile astfel incat sa nu fie nevoie
de alt element de memorie aditionala in afara de un nod auxiliar(complexitate aditionala constanta O(1)). Astfel, deoarece trec o data prin fiecare
nod, vom avea o complexitate liniara ( O(n)) si o memorie aditionala constanta, de O(1).
    Din grafic putem observa ca numarul de afisari ale cheii este identic, bineinteles. Din graficul ce compara numarul de operatii ale parcurgerilor,
    putem observa ca parcurgerea iterativa are nevoie de mult mai multe operatii, astfel fiind mai putin eficienta, din acest punct de vedere.

    Parcurgere recursiva: -complexitate timp O(n)
                          -memorie aditionala constanta (0...O(1))

    Parcurgere iterativa: -complexitate timp O(n)
                          -memorie aditionala constanta O(1)

    Am facut graficele atat pentru operatiile de afisare a cheii, cat si pentru operatiile folosite la implementare.

    Analiza QuickSort hibridizat si QuickSort hibridizat vs QuickSort:

    Am implementat QuickSortHibridizat astfel: pentru un numar de elemente ale sirului mai mici decat pragul se sirul respectiv se va sorta cu insertion sort,
altfel, sirul se va sorta cu quicksort. Aceasta varianta hibridizata a quicksortului este mai eficienta deoarece, pentru siruri de date mai mici, insertion sort
prezinta o performanta mai buna.Asadar, cand sirul mare va fi impartit conform partitiei quicksortului, si partitiile vor ajunge la dimensiuni mai mici decat pragul,
acele partitii vor fi sortate folosind insertion sort.

    Pentru AFLAREA PRAGULUI am folosit 2 metode: 1.prima data am comparat graficele de la quicksort si insertion sort, pentru a vedea cand incepe quicksort sa fie mai
eficient. In urma aceste analiza am vazut ca pragul este undeva in intervalul 7-13(in functie de rulare).
                                                 2.pentru a doua metoda, am luatun sir cu 10000 de elemente, asupra caruia am aplica quicksort hibridizat, variind pragul
de la 1 la 50. Asadar, am obtinut o grafic care are o valoare minima, care indica pragul optim. Acesta se arata a fi tot cuprins intre 7-13.

    Comparare QuickSortHibridizat vs QuickSort: pentru compararea celor 2 metode de sortare am facut grafice care le compara atatt din punct de vedere al operatiilor(atribuiri,
comparari si total), cat si din punct de vedere al timpului de rulare.  Am folosit un prag de 8.
    In urma graficelor, observa ca in ceea ce priveste numarul de atribuiri, quicksort hibridizat este mult mai eficient, iar in urma numarului de comparatii,quicksortul simplu
are putin mai putine operatii. Per total, se observa ca numarul de operatii al quicksortului hibridizat este mai mic decat numarul de operatii al quicksortului simplu, astfel do-
vedind eficienta acestuia.
    In ceea ce priveste timpul de rulare( am facut 100 de teste), se observa ca quicksort hibridizat are un timp mai bun de rulare, deci este mai eficient.


*/
Profiler p("Laborator8-9");

using namespace std;

typedef struct _NodeT
{
    int key;
    struct _NodeT *left;
    struct _NodeT *right;
} NodeT;

NodeT *newnode(int val)
{

    NodeT *p=(NodeT *)malloc(sizeof(NodeT));
    p->key=val;
    p->left=NULL;
    p->right=NULL;;
    return p;
}


int random_st_dr()
{
    return rand()%2;
}

NodeT *random_insert(NodeT* Tree,int val)
{

    if(Tree==NULL)
    {
        NodeT *p=newnode(val);
        Tree=p;
        return p;
    }
    int x=rand()%2;

    if(x==0)
    {
        Tree->left=random_insert(Tree->left,val);
    }
    else
    {
        Tree->right=random_insert(Tree->right,val);
    }
    return Tree;

}



void preordine_prettyprint(NodeT *Tree,int ct)
{
    if(Tree!=NULL)
    {
        for(int i=0; i<ct; i++)
        {
            std::cout<<"  ";
        }
        std::cout<<Tree->key<<endl;
        preordine_prettyprint(Tree->left,ct+1);
        preordine_prettyprint(Tree->right,ct+1);
    }
}

void preordine_recursiv(NodeT *Tree,int n)
{
    Operation operatii = p.createOperation("operatii_pre_rec2", n); ///numara operatiile totale
    Operation atribuiri = p.createOperation("atribuiri_pre_rec", n);
    operatii.count();
    if(Tree!=NULL)
    {
        atribuiri.count();
        /// std::cout<<Tree->key<<' ';
        preordine_recursiv(Tree->left,n);
        preordine_recursiv(Tree->right,n);
    }
}

void preordine_recursiv_demo(NodeT *Tree)
{

    if(Tree!=NULL)
    {
        std::cout<<Tree->key<<' ';
        preordine_recursiv_demo(Tree->left);
        preordine_recursiv_demo(Tree->right);
    }
}



void preordine_iterativ(NodeT* Tree,int n)
{
    Operation atribuiri = p.createOperation("atribuiri_pre_it", n); ///nnumara doar afisarile
    Operation operatii = p.createOperation("operatii_pre_it", n); ///numara operatiile


    while (Tree)
    {
        operatii.count();
        if (Tree->left == NULL)
        {
            atribuiri.count();
/// std::cout<<Tree->key<<' ';
            Tree = Tree->right;
        }
        else
        {
            operatii.count();
            NodeT* current = Tree->left;
            while (current->right && current->right != Tree)
            {   operatii.count(2);
            operatii.count();
                current = current->right;
            }

            operatii.count();
            if (current->right == Tree)
            {
                operatii.count(2);
                current->right = NULL;
                Tree = Tree->right;
            }

            else
            {
                operatii.count(2);
                atribuiri.count();
                /// std::cout<<Tree->key<<' ';
                current->right = Tree;
                Tree = Tree->left;
            }
        }
    }
}

void preordine_iterativ_demo(NodeT* Tree)
{
    while (Tree)
    {

        if (Tree->left == NULL)
        {
            std::cout<< Tree->key<<" ";
            Tree = Tree->right;
        }
        else
        {

            NodeT* current = Tree->left;
            while (current->right && current->right != Tree)
            {
                current = current->right;
            }

            if (current->right == Tree)
            {
                current->right = NULL;
                Tree = Tree->right;
            }

            else
            {

                std::cout<<Tree->key<<" ";
                current->right = Tree;
                Tree = Tree->left;
            }
        }
    }
}

NodeT *Build_BT(int a[20000],int n)
{
    FillRandomArray(a,n,1,n,true,0);
    NodeT *Tree=random_insert(Tree,a[0]);

    for(int i=1; i<n; i++)
    {
        /// std::cout<<endl<<a[i]<<"   ";
        random_insert(Tree,a[i]);

    }
    return Tree;
}

int Partition(int a[],int l,int  r,int n,Operation atribuiri,Operation comparari)
{

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
    ///p.addSeries("QuickSort_total", "QuickSort_atribuiri", "QuickSort_comparari");
    return i;
}

void QuickSort(int a[], int l, int r,int n,Operation atribuiri,Operation comparari)
{
    if (l < r)
    {
        int q = Partition(a, l, r,n,atribuiri,comparari);
        QuickSort(a, l, q - 1,n,atribuiri,comparari);
        QuickSort(a, q, r,n,atribuiri,comparari);
    }
}


void insertion_sort(int a[], int left,int right,int n,Operation atribuiri,Operation comparari) //Insertion sort cu inserare binara
{

    int val;
    for (int i =left+1; i < right; i++)
    {
        int dr = i - 1, st = left, mij, poz = -1;
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
    /// p.addSeries("Insertion_final", "Insertion_atribuiri", "Insertion_comparari");
}


void QuickSortHibridizat(int a[],int l,int r,int n,int prag,Operation atribuiri,Operation comparari)
{
    if(r-l+1>prag)
    {
        if(l < r)
        {
            int q = Partition(a, l, r,n,atribuiri,comparari);
            QuickSortHibridizat(a, l, q - 1,n,prag,atribuiri,comparari);
            QuickSortHibridizat(a, q, r,n,prag,atribuiri,comparari);
        }
    }
    else
    {
        if(l < r)
            insertion_sort(a,l,r+1,n,atribuiri,comparari);
    }
}

void copy_array(int a[], int b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        b[i] = a[i];
    }
}

int main()
{
    int n;
    int a[20000];
    char c;
    std::cout<<"Alege (T/G): ";
    std::cin>>c;

    if(c=='T')
    {
        Operation aux= p.createOperation("aux", 0);
        std::cout<<"n= ";
        std::cin>>n;
        NodeT *Tree=Build_BT(a,n);
        std::cout<<"Arborele arata asa: ";
        std::cout<<endl;
        preordine_prettyprint(Tree,0);
        std::cout<<endl;
        std::cout<<"Parcurgere recursiva(preordine): ";
        preordine_recursiv_demo(Tree);
        std::cout<<endl;
        std::cout<<"Parcurgere iterrativa(preordine): ";
        preordine_iterativ_demo(Tree);
        std::cout<<endl;
        std::cout<<"Testare QuickSortHibridizat: ";

        std::cout<<"n= ";
        std::cin>>n;

        int b[100];std::cout<<"Cititi elementele: ";
        for(int i=0; i<n; i++)
        {
            std::cin>>b[i];
        }

        QuickSortHibridizat(b,0,n-1,n,8,aux,aux);

        for(int i=0; i<n; i++)
        {
            std::cout<<b[i]<<' ';
        }
    }
    else
    {
        ///COMPARATIA ITERATIV VS RECURSIV



        for(int i=100; i<=10000; i=i+100)
        {
            NodeT *Tree=NULL;
            Tree=Build_BT(a,i);
            preordine_recursiv(Tree,i);
            preordine_iterativ(Tree,i);
        }
        p.createGroup("Numarare afisari iterativ","atribuiri_pre_it");
        p.createGroup("Numarare afisari recursiv","atribuiri_pre_rec");
        p.createGroup("Operatii","operatii_pre_rec2","operatii_pre_it");
        p.reset("Determinarea pragului");
///Determinarea pragului V1:

        int b[20000];
        for (int j = 1; j <= 5; j++)
        {
            for (int i = 1; i <= 100; i = i + 1)
            {
                FillRandomArray(a, i, 0, 100, true, 0);
                copy_array(a, b, i);
                Operation total_ins= p.createOperation("Insertion_final", i);

                Operation total_quick= p.createOperation("QuickSort_total", i);

                insertion_sort(a,0,i,i,total_ins,total_ins);
                QuickSort(b,0,i-1,i,total_quick,total_quick);
            }
        }

        p.divideValues("Insertion_final", 5);
        p.divideValues("QuickSort_total", 5);
        p.createGroup("Comparare_gasire_prag","QuickSort_total","Insertion_final");

        p.reset("Determinare prag 2");
///Determinare prag folosind variatia:

        FillRandomArray(a, 10000, 0, 10000, false, 0);
        for(int prag=1; prag<50; prag++)
        {
            Operation op_prag = p.createOperation("op_prag", prag);
            copy_array(a, b, 10000);
            QuickSortHibridizat(b,0,10000-1,10000,prag,op_prag,op_prag);
        }


        p.createGroup("Aflare prag v2","op_prag");

        p.reset("Quicksort vs Quicksort hibridizat");
        int c2[20000];

        int prag=8;

        for(int j=0; j<5; j++)
        {
            for(int i=100; i<=10000; i=i+100)
            {
                FillRandomArray(a, i, 100, 10000, false, 0);
                copy_array(a,b,i);


                Operation atribuiri_Q= p.createOperation("QuickS_atribuiri", i);
                Operation comparari_Q= p.createOperation("QuickS_comparari", i);
                QuickSort(c2,0,i-1,i,atribuiri_Q,comparari_Q);

                Operation atribuiri_QH= p.createOperation("QH_atribuiri", i);
                Operation comparari_QH= p.createOperation("QH_comparari", i);
                copy_array(a, b, i);
                QuickSortHibridizat(b,0,i-1,i,prag,atribuiri_QH,comparari_QH);
            }
        }

        for (int i = 100; i <= 10000; i=i+100)
        {
            if(i%1000==0)
            {
                std::cout<<i<<' ';
            }
            FillRandomArray(a, i, 100, 10000, false, 0);
            p.startTimer("QuickSort", i);
            for (int test = 0; test <100; ++test)
            {
                copy_array(a, c2, i);
                Operation atribuiri_Q= p.createOperation("QuickS_atribuiri", i);
                Operation comparari_Q= p.createOperation("QuickS_comparari", i);
                QuickSort(c2,0,i-1,i,atribuiri_Q,comparari_Q);

            }
            p.stopTimer("QuickSort", i);
            p.startTimer("QuickSort_hibridizat", i);

            for (int test = 0; test < 100; ++test)
            {
                Operation atribuiri_QH= p.createOperation("QH_atribuiri", i);
                Operation comparari_QH= p.createOperation("QH_comparari", i);
                copy_array(a, b, i);
                QuickSortHibridizat(b,0,i-1,i,prag,atribuiri_QH,comparari_QH);
            }
            p.stopTimer("QuickSort_hibridizat", i);

        }
        p.addSeries("QuickS_Total","QuickS_comparari","QuickS_atribuiri");
        p.addSeries("QuickSortHibridizat_Total","QH_atribuiri","QH_comparari");
        p.divideValues("QuickS_atribuiri",5);
        p.divideValues("QuickS_comparari",5);
        p.divideValues("QH_atribuiri",5);
        p.divideValues("QH_comparari",5);
        p.divideValues("QuickS_Total",5);
        p.divideValues("QuickSortHibridizat_Total",5);
        p.createGroup("Atribuiri_QvsQH","QuickS_atribuiri","QH_atribuiri");
        p.createGroup("Comparatii_QvsQH","QuickS_comparari","QH_comparari");
        p.createGroup("Total_QvsQH","QuickS_Total","QuickSortHibridizat_Total");
        p.createGroup("Comparare_timp","QuickSort","QuickSort_hibridizat");

        p.showReport();

    }

    return 0;
}
