// Tema.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string.h>
#include "Profiler.h"

Profiler p("Verificare numar operatii");

/**
@30225
@author Fleseriu Ioan-Rares

    Am creat un tabel, conform cerintei, in care am analizat cum variaza numarul de operatii pentru diferiti factori de inserare,
cand avem selectie uniforma, sau neuniforma(0.95). Mai apoi am analizat cum variaza numarul de opreatii daca facem o serie de
setergeri in tabela.

    Dupa cum era de asteptat, atunci cand avem o selectie non-uniforma, numarul mediu al operatiilor pentru elementele gasite este
1, deoarece selectia fiind non-uniforma, elementele cautate au fost primele inserate, iar astfel numarul de suprapuneri este foarte redus.

    In ceea ce priveste analiza cautarii atunci cand elementele de cautat au fost alese prin selectie uniforma observam ca, cu cat factorul
de inserare creste(se apropie de 1) cu atat numerele de operatii pentru toate cazurile( coloanele) cresc.
Efortul mediu creste mai llent, insa efortul maxim atat pentru cele gasite cat si oentru cele negasite creste mai mult.
    Cu toate acesetea, desi ar parea ca ar fi o crestere relativ proportionala la inceput, observam ca daca ne apropiem foarte tare de alfa=1,
    (0.95,0.99) eforturile cresc mult mai mult, mai ales pentru elementele negasite, deoarece spatiile libere din tabela sunt mult mai putine( avand
in vedere caatunci cand se intalneste o celula cu statusul "FREE" se opreste cautarea, deoarece nu mai exista posibilitatea de gasire a elementului).

    In ceea ce priveste stergerea, putem observa ca atunci cand stergem aprox 19% dintre elemente(0.99->0.80) avem un numar destul de mare de operatii,
semanator cu cazul in care avem factorul de umplere 0.99. Acest lucru se explica prin faptul ca, desi un element a fost sters si a eliberat o pozitie, pozitia
va fi marcata cu "DELETED" si nu cu "FREE", deoarece este nevoie sa se continue cautarea. Valorile numarului de operatii in acest caz depind totusi de cele generate
aleator, cat si de functia de hashing.

*/

typedef struct node
{
    int id;
    int status;
    char name[30];
} NodeT;

enum { FREE, OCCUPIED, DELETED };


int h_prim(int k, int n)
{
    return k % n;
}

int random_h_prim(int k, int n, int i)
{
    return (k + i) % n;
}

int quad_probing(int k, int n, int i)
{
    return (h_prim(k, n) + i + i * i) % n;
}



void insertTable(NodeT* hT[], int val, char string[30], int n)
{

    int i = 0;
    do
    {
        int index = quad_probing(val, n, i);
        if (hT[index]->status == FREE || hT[index]->status == DELETED)
        {
            hT[index]->id = val;
            strcpy_s(hT[index]->name, string);
            hT[index]->status = OCCUPIED;
            return;
        }
        else i++;
    } while (i != n);

    std::cout << "Tabela este plina, nu se poate insera " << val << '\n';
}

int StringNull(char nume[])
{
    if (nume == NULL)
        return 1;
    return 0;
}


int SearchInTable(NodeT* hT[], int val, int n, int* nr_op)
{
    // Operation op = p.createOperation("operatii", n);
    int i = 0;
    // std::cout<<"-----------------------------------------------------------\n";
    int index;
    do
    {
        // std::cout<<n<<' '<<i<<'\n';;
        index = quad_probing(val, n, i);
        (*nr_op)++;
        if (hT[index]->status == OCCUPIED)
        {
            if (hT[index]->id == val)
            {
                return index;
            }
        }

        i++;
    } while (i <= n && hT[index]->status != FREE);
    // std::cout << "Nu exista elementul "<<val<<" in tabela!";
    return -1;
}

int SearchInTablewChar(NodeT* hT[], int val, char nume[], int n)
{
    int i = 0;
    int index;
    do
    {

        index = quad_probing(val, n, i);
        if (hT[index]->status == OCCUPIED)
        {
            if (hT[index]->id == val && StringNull(nume) != 1 && strcmp(hT[index]->name, nume) == 0)
            {
                return index;
            }
        }

        i++;
    } while (i != n && hT[index]->status != FREE);
    std::cout << "Nu exista elementul " << val << " cu numele " << nume << "  in tabela!";
    return -1;
}

void copyarray(int c[], int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        c[i] = a[i];
    }
}

int getRandomEl(int c[], int N)
{

    int i = rand() % N;

    if (c[i] != -1)
    {
        int a = c[i];
        c[i] = -1;
        return a;
    }
    else return getRandomEl(c, N);///pentru a nu se selecta un duplicat, vom cauta un nou element(va fi altul datorita lui "rand()"


}

void insert_randomIndex(int b[], int val, int n)
{
    int i = 0;
    do
    {
        int index = random_h_prim(val, n, i);
        if (b[index] == -1)
        {
            // std::cout<<"ok\n";
            b[index] = val;
            return;
        }
        else i++;
    } while (i != n);
}

void setArray(int b[], int n)
{
    for (int i = 0; i < n; i++)
    {
        b[i] = -1;
    }
}


void insertRandomFromAtoA(int a[], int b[], int N, int n)
{
    int c[20000], m = n;
    setArray(b, n);
    copyarray(c, a, N);

    srand(time(NULL));
    while (n > 0)
    {
        insert_randomIndex(b, getRandomEl(c, N), m);
        n--;
    }
}

void deleteKey(NodeT* hT[], int val, int n, int* nr_op)
{
    //std::cout<<val<<"<-val\n";
    int index = SearchInTable(hT, val, n, nr_op);
    //std::cout<<val<<"<-val\n";
    if (index < 0)
    {
        return;
    }
    hT[index]->status = DELETED;   // std::cout<<val<<"<-val\n";
}

void deleteKeywChar(NodeT* hT[], int val, char nume[], int n, int* nr_op)
{
    //std::cout<<val<<"<-val\n";
    int index = SearchInTablewChar(hT, val, nume, n);
    //std::cout<<val<<"<-val\n";
    if (index < 0)
    {
        return;
    }
    hT[index]->status = DELETED;  //  std::cout<<val<<"<-val\n";
}


void formare(int b[], int n)     ///formarea elementelor ce nu vor fi gasite
{
    for (int i = n; i < n * 2; i++)
    {
        b[i] = b[i - n] + 100001; ///pentru a ne asigura ca nu il vom gasi in tabela
    }
    for (int i = 1; i < n * 2 - 5; i = i + 2)
    {
        std::swap(b[i], b[n * 2 - i]); ///pentru a ne asigura ca nu sunt toate el de gasit la inceput
    }
}



void reset_table(NodeT* hTable[], int n)
{
    for (int i = 0; i < n; i++)
    {
        hTable[i]->status = FREE;
    }
}

void afisare_tabela(NodeT* hTable[], int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << "hTable[" << i << "]= ";
        if (hTable[i]->status == OCCUPIED)
        {
            std::cout << hTable[i]->id << "  " << hTable[i]->name << '\n';
        }
        else
        {
            std::cout << '-' << '\n';
        }
    }
}

void keepMax(int* a, int b)
{
    if (b > *a)
        *a = b;
}

int get_random(int n)
{
    //   srand(time(NULL));
    return rand() % n;
}

int main()
{
    int n;
    char c;
    char string[30];
    std::cout << "Alege (T/G): ";
    std::cin >> c;

    if (c == 'T')
    {

        std::cout << "Numarul de celule ale tabelei: ";
        std::cin >> n;
        NodeT** hTable = (NodeT**)malloc(n * sizeof(NodeT*));

        for (int i = 0; i < n; i++)
        {
            hTable[i] = (NodeT*)malloc(sizeof(NodeT));
        }

        reset_table(hTable, n);

        int m;
        std::cout << "Numarul de elemente pe care doriti sa le cititi: ";
        std::cin >> m;
        int x;
        char NUME[30];
        for (int i = 0; i < m; i++)
        {
            std::cout << "id= ";
            std::cin >> x;
            std::cout << "name= ";
            std::cin >> NUME;
            insertTable(hTable, x, NUME, n);

        }

        std::cout << '\n';
        afisare_tabela(hTable, n);
        std::cout << "Ce id/nume doriti sa cautati?";
        std::cout << "id=";
        std::cin >> x;
        std::cout << "nume=";
        std::cin >> NUME;
        std::cout << SearchInTablewChar(hTable, x, NUME, n);
        std::cout << '\n';
        std::cout << "Ce element id/nume ati dori sa stergeti?";
        std::cout << "id=";
        std::cin >> x;
        std::cout << "nume=";
        std::cin >> NUME;
        int op = 0;
        deleteKeywChar(hTable, x, NUME, n, &op);
        std::cout << '\n';
        afisare_tabela(hTable, n);

        //        deleteKey(hTable,24,n,&op);
        //        afisare_tabela(hTable, n);
        //        deleteKey(hTable,24,n,&op);
        //        deleteKey(hTable,24,n,&op);
        //        deleteKey(hTable,24,n,&op);

        //        std :: cout<<'\n';
        //        afisare_tabela(hTable, n);
                // deleteKey(hTable,24,n);
                //deleteKey(hTable,24,n);
                //   std :: cout<<'\n';
                // std :: cout<<SearchInTablewChar(hTable, 10, "ok", n);

                //  std :: cin >> c;
    }
    else
    {



        int N = 9973;
        int a[20000], b[40000];

        NodeT** hTable = (NodeT**)malloc(N * sizeof(NodeT*));

        for (int i = 0; i < N; i++)
        {
            hTable[i] = (NodeT*)malloc(sizeof(NodeT));
        }

        //        reset_table(hTable,N);
        //
        //     ///   afisare_tabela(hTable,N);
        //
        //
        //        FillRandomArray(a, n, 0, 100000, false, 0);
        //        insertRandomFromAtoA(a,b,n,1500);
        //
        //        for(int i=0;i<n;i++)
        //        {
        //            insertTable(hTable,a[i],NULL,N);
        //        }
        //        formare(b,1500);

                ///SELECTIE NON-UNIFORMA alfa=0.95:


        n = 9973 * 0.95;
        int mgnonunif = 0;
        int mnnonunif = 0;
        int nr_nonunif = 0, g_nonunif = 0, n_nonunif = 0;
        reset_table(hTable, N);
        //std::cout<<g_op80<< ' ';
        FillRandomArray(a, n, 0, 100000, false, 0);
        insertRandomFromAtoA(a, b, n, 1500);

        for (int i = 0; i < n; i++)
        {
            insertTable(hTable, a[i], NULL, N);
        }

        for (int j = 0; j < 5; j++)
        {
            reset_table(hTable, N);

            FillRandomArray(a, n, 0, 100000, false, 0);
            //insertRandomFromAtoA(a,b,n,1500);

            for (int i = 0; i < n; i++)
            {
                insertTable(hTable, a[i], NULL, N);
            }
            copyarray(b, a, 1500);
            formare(b, 1500);
            for (int i = 0; i < 3000; i++)
            {
                nr_nonunif = 0;
                if (SearchInTable(hTable, b[i], N, &nr_nonunif) != -1)
                {
                    g_nonunif = g_nonunif + nr_nonunif;
                    keepMax(&mgnonunif, nr_nonunif);
                }
                else
                {
                    n_nonunif = n_nonunif + nr_nonunif;
                    keepMax(&mnnonunif, nr_nonunif);
                }

            }
        }

        nr_nonunif = nr_nonunif / 5;
        g_nonunif = g_nonunif / 5;
        n_nonunif = n_nonunif / 5;



        ///factorul alfa=80%
        n = 9973 * 0.8;
        int mg80 = 0;
        int mn80 = 0;
        int mg85 = 0;
        int mn85 = 0;
        int mg90 = 0;
        int mn90 = 0;
        int mg95 = 0;
        int mn95 = 0;
        int mg99 = 0;
        int mn99 = 0;
        int nr_op80 = 0, g_op80 = 0, n_op80 = 0;
        for (int j = 0; j < 5; j++)
        {
            reset_table(hTable, N);
            /// std::cout<<g_op80<< ' ';
            FillRandomArray(a, n, 0, 100000, false, 0);
            insertRandomFromAtoA(a, b, n, 1500);

            for (int i = n; i >= 0; i--)
            {
                insertTable(hTable, a[i], NULL, N);
            }
            formare(b, 1500);
            for (int i = 0; i < 3000; i++)
            {
                nr_op80 = 0;
                if (SearchInTable(hTable, b[i], N, &nr_op80) != -1)
                {
                    g_op80 = g_op80 + nr_op80;
                    keepMax(&mg80, nr_op80);
                }
                else
                {
                    n_op80 = n_op80 + nr_op80;
                    keepMax(&mn80, nr_op80);
                }

            }
        }

        nr_op80 = nr_op80 / 5;
        g_op80 = g_op80 / 5;
        n_op80 = n_op80 / 5;
        ///   std::cout<<g_op80<<' '<<n_op80<<"   ";



        ///factorul alfa=85%
        n = 9973.0 * 0.85;
        int nr_op85 = 0, g_op85 = 0, n_op85 = 0;
        for (int j = 0; j < 5; j++)
        {
            reset_table(hTable, N);

            FillRandomArray(a, n, 0, 100000, false, 0);
            insertRandomFromAtoA(a, b, n, 1500);

            for (int i = n; i >= 0; i--)
            {
                insertTable(hTable, a[i], NULL, N);
            }
            formare(b, 1500);
            for (int i = 0; i < 3000; i++)
            {
                nr_op85 = 0;
                if (SearchInTable(hTable, b[i], N, &nr_op85) != -1)
                {
                    g_op85 = g_op85 + nr_op85;
                    keepMax(&mg85, nr_op85);
                }
                else
                {
                    n_op85 = n_op85 + nr_op85;
                    keepMax(&mn85, nr_op85);
                }
            }
        }
        nr_op85 = nr_op85 / 5;
        g_op85 = g_op85 / 5;
        n_op85 = n_op85 / 5;
        ///   std::cout<<g_op85<<' '<<n_op85<<"   ";


        ///factorul alfa=90%
        n = 9973 * 0.9;
        int nr_op90 = 0, g_op90 = 0, n_op90 = 0;
        for (int j = 0; j < 5; j++)
        {
            reset_table(hTable, N);

            FillRandomArray(a, n, 0, 100000, false, 0);
            insertRandomFromAtoA(a, b, n, 1500);

            for (int i = n; i >= 0; i--)
            {
                insertTable(hTable, a[i], NULL, N);
            }
            formare(b, 1500);
            for (int i = 0; i < 3000; i++)
            {
                nr_op90 = 0;
                if (SearchInTable(hTable, b[i], N, &nr_op90) != -1)
                {
                    g_op90 = g_op90 + nr_op90;
                    keepMax(&mg90, nr_op90);
                }
                else
                {
                    n_op90 = n_op90 + nr_op90;
                    keepMax(&mn90, nr_op90);
                }

            }
        }
        nr_op90 = nr_op90 / 5;
        g_op90 = g_op90 / 5;
        n_op90 = n_op90 / 5;
        ///   std::cout<<g_op90<<' '<<n_op90<<"   ";



        ///factorul alfa=95%
        n = 9973 * 0.95;
        int nr_op95 = 0, g_op95 = 0, n_op95 = 0;
        for (int j = 0; j < 5; j++)
        {
            reset_table(hTable, N);

            FillRandomArray(a, n, 0, 100000, false, 0);
            insertRandomFromAtoA(a, b, n, 1500);

            for (int i = n; i >= 0; i--)
            {
                insertTable(hTable, a[i], NULL, N);
            }
            formare(b, 1500);
            for (int i = 0; i < 3000; i++)
            {
                nr_op95 = 0;
                if (SearchInTable(hTable, b[i], N, &nr_op95) != -1)
                {
                    g_op95 = g_op95 + nr_op95;
                    keepMax(&mg95, nr_op95);
                }
                else
                {
                    n_op95 = n_op95 + nr_op95;
                    keepMax(&mn95, nr_op95);
                }

            }
        }
        nr_op95 = nr_op95 / 5;
        g_op95 = g_op95 / 5;
        n_op95 = n_op95 / 5;
        ///    std::cout<<g_op95<<' '<<n_op95<<"   ";


        n = 9973 * 0.99;

        ///factorul alfa=99%
        int nr_op99 = 0, g_op99 = 0, n_op99 = 0;
        for (int j = 0; j < 5; j++)
        {
            reset_table(hTable, N);

            FillRandomArray(a, n, 0, 100000, false, 0);
            insertRandomFromAtoA(a, b, n, 1500);
            for (int i = n; i >= 0; i--)
            {
                insertTable(hTable, a[i], NULL, N);
            }
            formare(b, 1500);
            for (int i = 0; i < 3000; i++)
            {
                nr_op99 = 0;
                if (SearchInTable(hTable, b[i], N, &nr_op99) != -1)
                {
                    g_op99 = g_op99 + nr_op99;
                    //  std::cout<<g_op99<<' ';
                    keepMax(&mg99, nr_op99);
                }
                else
                {
                    n_op99 = n_op99 + nr_op99;
                    keepMax(&mn99, nr_op99);
                }

            }
        }
        nr_op99 = nr_op99 / 5;
        g_op99 = g_op99 / 5;
        n_op99 = n_op99 / 5;
        ///  std::cout<<g_op99<<' '<<n_op99<<"   ";

        ///Generare tabel
        std::cout << '\n';
        std::cout << "Factor de umplere" << " | " << "Efort mediu gasite" << " | " << "Efort maxim gasite" << " | " << "Efort mediu negasite" << " | " << "Efort maxim negasite";
        std::cout << '\n';
        n = 9973 * 0.95;
        std::cout << "----------------------------------------------------------------------------------------------------------" << '\n';
        std::cout << "Non-uniforma 0.85 " << " | " << "     " << g_nonunif / (1500) << "     " << " | " << "       " << mgnonunif << "       " << " | " << "       " << n_nonunif / (1500) << "      " << " | " << "      " << mnnonunif;
        std::cout << '\n';
        n = 9973 * 0.8;
        std::cout << "----------------------------------------------------------------------------------------------------------" << '\n';
        std::cout << "      0.80       " << " | " << "     " << g_op80 / (1500) << "     " << " | " << "       " << mg80 << "       " << " | " << "       " << n_op80 / (1500) << "      " << " | " << "      " << mn80;
        std::cout << '\n';
        n = N * 0.85;
        std::cout << "----------------------------------------------------------------------------------------------------------" << '\n';
        std::cout << "      0.85       " << " | " << "     " << g_op85 / (1500) << "     " << " | " << "       " << mg85 << "       " << " | " << "       " << n_op85 / (1500) << "      " << " | " << "      " << mn85;
        std::cout << '\n';
        std::cout << "----------------------------------------------------------------------------------------------------------" << '\n';
        n = N * 0.9;
        std::cout << "      0.90       " << " | " << "     " << g_op90 / (1500) << "     " << " | " << "       " << mg90 << "       " << " | " << "       " << n_op90 / (1500) << "      " << " | " << "      " << mn90;
        std::cout << '\n';
        std::cout << "----------------------------------------------------------------------------------------------------------" << '\n';
        n = N * 0.95;
        std::cout << "      0.95       " << " | " << "     " << g_op95 / (1500) << "     " << " | " << "       " << mg95 << "       " << " | " << "       " << n_op95 / (1500) << "      " << " | " << "      " << mn95;
        std::cout << '\n';
        std::cout << "----------------------------------------------------------------------------------------------------------" << '\n';
        n = N * 0.99;
        std::cout << "      0.99       " << " | " << "     " << g_op99 / (1500) << "     " << " | " << "       " << mg99 << "       " << " | " << "       " << n_op99 / (1500) << "      " << " | " << "      " << mn99;


        ///   SearchInTable(hTable,200,N,&nr_op99);

        n = 9973 * 0.8;
        int x;
        srand(time(NULL));
        nr_op99 = 0;
        nr_op80 = 0;
        g_op80 = 0;
        n_op80 = 0;
        int mgs = 0;
        int mns = 0;
        for (int j = 0; j < 5; j++)
        {
            reset_table(hTable, N);
            int n1 = 9973 * 0.99;
            n = 9973 * 0.8;
            FillRandomArray(a, n1, 0, 100000, false, 0);
            insertRandomFromAtoA(a, b, n1, 1500);

            for (int i = 0; i < n1; i++)
            {
                insertTable(hTable, a[i], NULL, N);
            }


            while (n1 > n)
            {
                int ind = 0;

                // std::cout<<x<<' ';
                while (ind == 0)
                {
                    x = rand() % n;
                    if (a[x] != -1)
                    {
                        deleteKey(hTable, a[x], N, &nr_op99);
                        ind = 1;
                        // std::cout<<a[x]<<' ';
                        a[x] = -1;
                    }
                }

                n1--;

            }

            formare(b, 1500);
            for (int i = 0; i < 3000; i++)
            {
                nr_op80 = 0;
                if (SearchInTable(hTable, b[i], N, &nr_op80) != -1)
                {
                    g_op80 = g_op80 + nr_op80;
                    keepMax(&mgs, nr_op80);
                }
                else
                {
                    n_op80 = n_op80 + nr_op80;
                    keepMax(&mns, nr_op80);;
                }

            }
        }
        nr_op80 = nr_op80 / 5;
        g_op80 = g_op80 / 5;
        n_op80 = n_op80 / 5;

        std::cout << '\n';
        std::cout << "----------------------------------------------------------------------------------------------------------" << '\n';
        std::cout << " Stergere 0.99->0.8  " << " | " << "     " << g_op80 / (1500) << "     " << " | " << "       " << mgs << "       " << " | " << "       " << n_op80 / (1500) << "      " << " | " << "      " << mns;
    }

}

