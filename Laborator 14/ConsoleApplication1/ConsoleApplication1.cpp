#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
#include <time.h>


/*
Group:30225
Fleseriu Ioan-Rares

    Algoritmul DFS:
    DFS este compus din 2 functii, DFS care asigura ca fiecare nod sa fie vizitat, chiar daca face parte dintr-un graf care nu e conex si
DFS_visit care face parcurgerea pentru fiecare componenta(conexa). In functia DFS am initializat fiecare nod cu valorile corespunzatoare(O(v)), am
setat timpul la 0 si am inceput parcurgerea.
    In functia DFS_visit am marcat nodul curent(O(1)), continuam vizitarea nodurilor adiacente care nu au fost vizitate pana cand toate nodurile la
  care se poate ajunge din nodul curent au fost vizitate(O(E) dupa parcurgerea fiecarei muchii). La fiecare nod vizitat vom seta timpul de descoperire
  si timpul de finalizare(O(1)). Astfel, complexitatea algoritmului DFS va fi O(V+E), astfel incat fiecare nod si fiecare muchie va fi vizitata o singura data.

  Sortare topologica:
  Dupa cum stim, conditiile de existenta ale unei sortari topologice sunt: ca graful sa fie orientat si aciclic. Asadar, atunci cand fac parcurgerea DFS verific
 posibila existenta a ciclurilor. Daca graful nu are cicluri, in timpul DFS-ului, adaug fiecare nod care devine negru la inceputul listei de noduri(lista cu sortarea)
 Acest algoritm are o complexitate do O(V+E), intrucat e DFS cu o adaugare de O(1).

 Algoritmul lui tarjan:
 Acest algritm este de asemenea compus din 2 functii(Tarjan si Strong-Connect) si se bazeaza pe 2 stive. Asemeni DFS-ului, la inceput initializam fiecare nod
corespunzator, iar apoi, pentru fiecare nod nevizitat aplicam Strong-Connect. Pe parcursul algoritmului, fiecare nod isi va gasi componenta conexa, folosind index, si vom avea
si numarul de componente conexe. Complexitatea acestui algoritm este de asemenea O(V+E), intrucat fiecare nod si fiecare muchie va fi viziitata o singura data.

  In urma realizarii graficelor, putem observa faptul ca ambele au o crestere liniara, crescand raportat la numarul de muchii/varfuri. Dupa cum era de asteptat, atunci cand
variem numarul de varfuri, numarul de operatii este mai mare, atat in ceeea ce priveste atribuirile cat si comparatiile. Individual, numarul de atribuiri este putin mai mare
decat numarul de comparatii in ambele cazuri.
*/

Profiler p("DFS");

enum
{
    WHITE = 0,
    GRAY,
    BLACK
};


typedef struct _Node
{

    int key;
    int size;
    int d;
    int f;
    int index;
    int indexT;
    int lowLink;
    int onStack;
    int comp;
    struct _Node** lista;
    int color;
    struct _Node* parent;
    struct _Node* next;
} NodeT;


typedef struct
{
    int nrNodes;
    NodeT** v;
} Graph;

void push(NodeT** S, NodeT* p)
{
    if (*S == NULL)
    {

        *S = p;
    }
    else
    {
        p->next = *S;
        *S = p;
    }
}

NodeT* pop(NodeT** S)
{
    if (*S == NULL)
    {
        return 0;
    }
    NodeT* aux = *S;
    *S = (*S)->next;
    return aux;
}

NodeT* newNode(int key, int n)
{
    NodeT* p = (NodeT*)malloc(sizeof(NodeT));
    p->key = key;
    p->color = WHITE;
    p->d = 0;
    p->f = 0;
    p->size = 0;
    p->parent = NULL;
    p->next = NULL;
    p->lista = (NodeT**)malloc((n + 1) * sizeof(NodeT*));
    for (int i = 0; i <= n; i++)
    {
        p->lista[i] = (NodeT*)malloc(sizeof(NodeT));
    }
    return p;
}

Graph* newGraf(int n)
{
    Graph* graf = (Graph*)malloc(sizeof(Graph));
    graf->v = (NodeT**)malloc((n + 1) * sizeof(NodeT*));
    for (int i = 0; i <= n; i++)
    {
        graf->v[i] = newNode(i,n);
    }
    graf->nrNodes = n;
    return graf;
}


void DFS_VISIT(Graph* graf, NodeT* u, int* time, Operation atr, Operation comp)
{
    (*time)++;
    u->d = *time;
    u->color = GRAY;
    atr.count(2);
    for (int i = 1; i <= u->size; i++)
    {
        NodeT* v = u->lista[i];
        atr.count();
        comp.count();
        if (v->color == WHITE)
        {
            //a[v->index]=u->index;
       //     printf("v-i=%d  u-i=%d", v->index, u->index);
            atr.count();
            v->parent = u;
            DFS_VISIT(graf, v, time,atr,comp);
        }
    }
    atr.count(2);
    u->color = BLACK;
    (*time)++;
    u->f = *time;
}
void DFS(Graph* graf, int* time,Operation atr,Operation comp)
{
    
    for (int i = 1; i <= graf->nrNodes; i++)
    {
        atr.count(2);
        graf->v[i]->color = WHITE;
        graf->v[i]->parent = NULL;
    }
    *time = 0;
    for (int i = 1; i <= graf->nrNodes; i++)
    {
        comp.count();
        if (graf->v[i]->color == WHITE)
        {
            DFS_VISIT(graf, graf->v[i], time,atr,comp);
        }
    }
}




void DFS_VISIT2(Graph* graf, NodeT* u, int* time, NodeT* sort_vector)
{
    (*time)++;
    u->d = *time;
    u->color = GRAY;
    for (int i = 1; i <= u->size; i++)
    {
        NodeT* v = u->lista[i];
        if (v->color == WHITE)
        {
            v->parent = u;
            DFS_VISIT2(graf, v, time, sort_vector);
        }
        if (v->color == GRAY)
        {
            sort_vector->lista[0]= newNode(-1, graf->nrNodes);
        }
    }
    u->color = BLACK;
    (*time)++;
    u->f = *time;
    
    sort_vector->lista[sort_vector->size] = u;
    sort_vector->size--;
}
void DFS2(Graph* graf, int* time, NodeT* sort_vector)
{
    for (int i = 1; i <= graf->nrNodes; i++)
    {
        graf->v[i]->color = WHITE;
        graf->v[i]->parent = NULL;
    }
    *time = 0;
    for (int i = 1; i <= graf->nrNodes; i++)
    {
        if (graf->v[i]->color == WHITE)
        {
            graf->v[i]->index = -1;
            DFS_VISIT2(graf, graf->v[i], time, sort_vector);
        }
    }
}
void adaugare_muchii(Graph* graf, int a, int b)
{
    graf->v[a]->size++;
    graf->v[a]->lista[graf->v[a]->size] = graf->v[b];

}

void print_list(NodeT* sort_vector)
{
    for (int i = 1; i <= sort_vector->size; i++)
    {
        printf("%d\n", sort_vector->lista[i]->key);
    }
}

void print_list2(NodeT* sort_vector)
{
    for (int i = 1; i <= sort_vector->size; i++)
    {
        printf("%d  t.i=%d   t.f=%d\n", sort_vector->lista[i]->key, sort_vector->lista[i]->d, sort_vector->lista[i]->f);
    }
}


void print_graph(Graph* graf)
{
    for (int i = 1; i <= graf->nrNodes; i++)
    {
        printf("%d: ", graf->v[i]->key);
        for (int j = 1; j <= graf->v[i]->size; j++)
        {
            printf("%d ", graf->v[i]->lista[j]->key);
        }
        printf("\n");
    }
}

void afisare_dfs(Graph* graf)
{
    Graph* aux = graf;
    for (int i = 2; i <= aux->nrNodes; i++)
    {
        NodeT* x = aux->v[i];
        int j = i - 1;
        while (j >= 1 && aux->v[j]->d > x->d)
        {
            aux->v[j + 1] = aux->v[j];
            j--;
        }
        aux->v[j + 1] = x;
    }
    printf("cheie  t.d  t.f\n");
    for (int i = 1; i <= aux->nrNodes; i++)
    {
        printf(" %d     %d   %d\n", aux->v[i]->key, aux->v[i]->d, aux->v[i]->f);
    }
}



void sortare_topologica2(Graph* graf, NodeT* sort_vector)
{
    int time;
    sort_vector->lista[0]->key = 1;
    sort_vector->size = graf->nrNodes;

    DFS2(graf, &time, sort_vector);
    if (sort_vector->lista[0] ->key== -1)
    {
        printf("Nu se poate face sortarea topologica(graful are cicluri).\n");

    }
    else
    {
        //printf("ok");       
        sort_vector->size = graf->nrNodes;
        print_list2(sort_vector);
    }

}

void parent_form(Graph* g, int a[100])
{
    // int a[100];
    for (int i = 1; i <= g->nrNodes; i++)
    {
        if (g->v[i]->parent != NULL)
            a[i] = g->v[i]->parent->index;
        else
        {
            a[i] = -1;
        }
    }
    //  return a;
}

void pretty_print(Graph* graf, int a[100], int rad, int ct)
{
    for (int i = 1; i <= graf->nrNodes; i++)
    {
        if (a[i] == rad)
        {
            for (int i = 0; i < ct; i++)
                printf(" ");
            printf("%d\n", graf->v[i]->key);
            pretty_print(graf, a, i, ct + 1);

        }
    }

}

int index = 0;
NodeT* S;
int nrComponents = 0;

int minim(int a, int b)
{
    if (a <= b)
        return a;
    return b;
}



void Strong_Connect(Graph* graf, NodeT* u)
{
    u->indexT = index;
    u->lowLink = index;
    index++;
    push(&S, u);
    u->onStack = 1;
    for (int i = 1; i <= u->size; i++)
    {
        NodeT* v = u->lista[i];
        if (v->indexT == -1)
        {
            Strong_Connect(graf, v);
            u->lowLink = minim(u->lowLink, v->lowLink);
        }
        else if (v->onStack)
        {
            u->lowLink = minim(u->lowLink, v->indexT);
        }
    }
    if (u->lowLink == u->indexT)
    {
        nrComponents++;

        NodeT* v;
        do
        {
            v = pop(&S);
            //printf("%d ",v->index);
            v->onStack = 0;
            v->comp = nrComponents;
        } while (v != u);
    }
}

void Tarjan(Graph* graf)
{
    S = NULL;

    for (int i = 1; i <= graf->nrNodes; i++)
    {
        graf->v[i]->indexT = -1;
        graf->v[i]->lowLink = -1;
        graf->v[i]->onStack = 0;
        graf->v[i]->comp = 0;
    }

    for (int i = 1; i <= graf->nrNodes; i++)
    {
        if (graf->v[i]->indexT == -1)
        {
            Strong_Connect(graf, graf->v[i]);
        }
    }
}

int main()
{
    char c;
    printf("Alegeti (G/T): ");
    scanf("%c", &c);
    if (c == 'T')
    {
        Operation aux=p.createOperation("aux", 10);
        int n;
        printf("Cate noduri are graful:\n");
        printf("n= ");
        scanf("%d", &n);
        Graph* graf = newGraf(n);

        printf("Cititi valorile nodurilor:\n");
        for (int i = 1; i <= n; i++)
        {
            int x;
            scanf_s("%d", &x);
            graf->v[i] = newNode(x, n);
            graf->v[i]->index = i;
        }

        printf("Cititi indexurile muchiilor: (pentru a va opri din cititi introduceti : 0 0)\n");
        for (int i = 1; i <= n; i++)
        {
            printf("%d:  %d\n", i, graf->v[i]->key);
        }
        int x, y;
        printf("x=");
        scanf("%d", &x);
        printf("y=");
        scanf("%d", &y);
        while (x != 0 && y != 0)
        {
            adaugare_muchii(graf, x, y);
            printf("x=");
            scanf("%d", &x);
            printf("y=");
            scanf("%d", &y);
        }
        /* adaugare_muchii(graf,1,2);
         adaugare_muchii(graf,1,3);
         adaugare_muchii(graf,2,4);
         // adaugare_muchii(graf,4,1);
         adaugare_muchii(graf,3,4);
         //  adaugare_muchii(graf,3,5);
        adaugare_muchii(graf, 1, 3);
        adaugare_muchii(graf, 2, 1);
        adaugare_muchii(graf, 2, 4);
        adaugare_muchii(graf, 3, 2);
        adaugare_muchii(graf, 3, 4);
        adaugare_muchii(graf, 3, 5);
        adaugare_muchii(graf, 4, 6);
        adaugare_muchii(graf, 5, 6);
        adaugare_muchii(graf, 5, 7);
        adaugare_muchii(graf, 6, 4);
        adaugare_muchii(graf, 6, 8);
        adaugare_muchii(graf, 7, 5);
        adaugare_muchii(graf, 7, 8);
        */
        int time;
        int ind_sort = 1;
        printf("Lista de adiacenta:\n");
        print_graph(graf);
        printf("\nDemo:\n");
        NodeT* sort_top_vector = newNode(1, graf->nrNodes);
        DFS(graf, &time,aux,aux);
        printf("\n");
        int a[100];
        parent_form(graf, a);
        printf("\n Sortare topologica:\n ");
        sortare_topologica2(graf, sort_top_vector);
        printf("\n");
      /*  for (int i = 1; i <= graf->nrNodes; i++)
        {
            printf("%d ", a[i]);
        }
        printf("\n");
        */
        printf("Afisarea arborelui DFS:\n");
        pretty_print(graf, a, -1, 0);
        printf("\n Tarjan:\n");
        Tarjan(graf);
        printf("Nr componente conexe=%d\n", nrComponents);
        for (int i = 1; i <= graf->nrNodes; i++)
        {
            printf("Nodul:%d se afla in componenta %d\n", graf->v[i]->key, graf->v[i]->comp);
        }
        int** mat_comp = (int**)malloc((nrComponents + 1) * sizeof(int*));
        for (int i = 0; i <= nrComponents+1; i++)
        {
            mat_comp[i] = (int*)malloc((graf->nrNodes + 1) * sizeof(int));
        }
        for (int i = 0; i <= nrComponents+1; i++)
        {
            for (int j = 0; j <= graf->nrNodes +1; j++)
            {
                mat_comp[i][j] = -1;
            }
        }

        for (int i = 1; i <= graf->nrNodes; i++)
        {
            int k = 1;
            while (mat_comp[graf->v[i]->comp][k] != -1)
            {
                k++;
            }
            mat_comp[graf->v[i]->comp][k] = graf->v[i]->key;
           // printf("%d -> %d\n", graf->v[i]->key, graf->v[i]->comp);
        }
        
        for (int i = 1; i <= nrComponents; i++)
        {
           int  k = 1;
           printf("Componenta %d: ",i);
            while (mat_comp[i][k] != -1)
            {
                printf("%d ", mat_comp[i][k]);
                k++;
            }
            printf("\n");
        }
        
        //afisare_dfs(graf);
        //printf("\n");
        //sortare_topologica2(graf,sort_top_vector);
    }
    else
    {
        int time = 0;
        for (int n = 1000; n <= 4500; n += 100) {
            Graph* graf=newGraf(100);
           // graf->nrNodes = 100;
            int mat[101][101];
            //facem o matrice ca sa verifice daca dintr-un varf au plecat muchii random
            for (int i = 0; i < 101; i++)
            {
                for (int j = 0; j < 101; j++)
                {
                    mat[i][j] = 0;
                }
            } 
            //srand(Time(NULL));
           //graf = newGraf(100);
            int m_ramase = n;
            while (m_ramase > 0)
            {
                int a = rand() % 100+1;
                int b = rand() % 100+1;
                if (mat[a][b] == 0)
                {
                    graf->v[a]->lista[graf->v[a]->size] = graf->v[b];
                    
                    (graf->v[a]->size)++;
                    mat[a][b] = 1;
                    m_ramase--;
                }
            }
            Operation atr = p.createOperation("atribuiri", n);
            Operation comp = p.createOperation("comparatii", n);
            DFS(graf, &time, atr, comp);
        }
        p.addSeries("Op_total_Variem_E", "atribuiri", "comparatii");
        p.createGroup("Variem_E", "atribuiri", "comparatii");

        for (int n = 100; n <= 200; n += 10) {
            Operation atr2 = p.createOperation("atribuiri2", n);
            Operation comp2 = p.createOperation("comparatii2", n);
            Graph* graf = newGraf(n);
     
            int mat[201][201];
            //facem o matrice ca sa verifice daca dintr-un varf au plecat muchii random
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    mat[i][j] = 0;
                }
            }
            //srand(Time(NULL));
           //graf = newGraf(100);
            int m_ramase = 4500;
            while (m_ramase > 0)
            {
                int a = rand() % n + 1;
                int b = rand() % n + 1;
                if (mat[a][b] == 0)
                {
                    graf->v[a]->lista[graf->v[a]->size] = graf->v[b];

                    (graf->v[a]->size)++;
                    mat[a][b] = 1;
                    m_ramase--;
                }
            } 
            DFS(graf, &time, atr2, comp2);
        }

        p.addSeries("Op_total_Variem_V", "atribuiri2", "comparatii2");
        p.createGroup("Variem_V", "atribuiri2", "comparatii2");
        p.showReport();
    }
}

