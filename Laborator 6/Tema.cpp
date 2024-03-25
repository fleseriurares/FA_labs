// Tema.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

typedef struct node
{
    int key;
    int status;
    char name[30];
} NodeT;

enum {FREE,OCCUPIED};


int h_prim(int k,int n)
{
    return k % n;
}

int quad_probing(int k, int n, int i)
{
    return (h_prim(k, n) + i + i * i) % n;  
}

int insert(NodeT *hT[],int val,int n)
{
    int i = 0;
    do {
        int index = quad_probing(val, n, i);
        if (hT[index]->status == FREE)
        {
            hT[index]->key = val;
            hT[index]->status = OCCUPIED;
            return index;
        }
        else i++;
    } while (i != n);
    std::cout << "Tabela este plina";
}

void reset_table(NodeT* hTable[],int n)
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
            std::cout << hTable[i]->key << '\n';
        }
        else
        {
            std::cout <<'-' << '\n';
        }
    }
}
int main()
{
    int n;
    char c;
    std::cout << "Numarul de elemente:";
    std::cin >> n;

    NodeT** hTable = (NodeT**)malloc(n * sizeof(NodeT*));
    
    for (int i = 0; i < n; i++)
    {
        hTable[i] = (NodeT*)malloc(sizeof(NodeT));
    }

    reset_table(hTable,n);

    insert(hTable, 10, n);
    insert(hTable, 15, n);
    insert(hTable, 24, n);
    insert(hTable, 3, n);

    afisare_tabela(hTable, n);

    std::cin >> c;
}

