#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"
#include <time.h>


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

void push(NodeT **S,NodeT *p)
{
    if(*S==NULL)
    {

        *S=p;
    }
    else
    {
        p->next=*S;
        *S=p;
    }
}

NodeT *pop(NodeT **S)
{
    if(*S==NULL)
    {
        return 0;
    }
    NodeT *aux=*S;
    *S=(*S)->next;
    return aux;
}

NodeT *newNode(int key,int n)
{
    NodeT* p = (NodeT*)malloc(sizeof(NodeT));
    p->key = key;
    p->color = WHITE;
    p->d = 0;
    p->f = 0;
    p->size = 0;
    p->parent = NULL;
    p->next=NULL;
    p->lista = (NodeT**)malloc((n+1)* sizeof(NodeT*));
    for (int i = 0; i <= n; i++)
    {
        p->lista[i] = (NodeT*)malloc(sizeof(NodeT));
    }
    return p;
}

Graph *newGraf(int n)
{
    Graph* graf = (Graph*)malloc(sizeof(Graph));
    graf->v = (NodeT **)malloc((n + 1) * sizeof(NodeT*));
    for (int i = 0; i <= n; i++)
    {
        graf->v[i]= (NodeT*)malloc( sizeof(NodeT));
    }
    graf->nrNodes = n;
    return graf;
}

void DFS(Graph* graf,int *time)
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

            DFS_VISIT(graf, graf->v[i],time);
        }
    }
}

void DFS_VISIT(Graph* graf, NodeT* u, int *time)
{
    (*time)++;
    u->d = *time;
    u->color = GRAY;
    for (int i = 1; i <= u->size; i++)
    {
        NodeT* v = u->lista[i];
        if (v->color == WHITE)
        {
            //a[v->index]=u->index;
            printf("v-i=%d  u-i=%d",v->index,u->index);
            v->parent = u;
            DFS_VISIT(graf, v, time);
        }
    }
    u->color = BLACK;
    (*time)++;
    u->f = *time;
}

void DFS2(Graph* graf,int *time,NodeT *sort_vector)
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
            graf->v[i]->index=-1;
            DFS_VISIT2(graf, graf->v[i],time,sort_vector);
        }
    }
}

void DFS_VISIT2(Graph* graf, NodeT* u, int *time,NodeT *sort_vector)
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
            DFS_VISIT2(graf, v, time,sort_vector);
        }
        if (v->color == GRAY)
        {
            sort_vector->lista[0]->key=newNode(-1,graf->nrNodes);
        }
    }
    u->color = BLACK;
    (*time)++;
    u->f = *time;
    sort_vector->size++;
    sort_vector->lista[sort_vector->size]=u;
}

void adaugare_muchii(Graph *graf, int a,int b)
{
    graf->v[a]->size++;
    graf->v[a]->lista[graf->v[a]->size]=graf->v[b];

}

void print_graph(Graph *graf)
{
    for(int i=1; i<=graf->nrNodes; i++)
    {
        printf("%d: ",graf->v[i]->key);
        for(int j=1; j<=graf->v[i]->size; j++)
        {
            printf("%d ",graf->v[i]->lista[j]->key);
        }
        printf("\n");
    }
}

void afisare_dfs(Graph *graf)
{
    Graph *aux=graf;
    for(int i=2; i<=aux->nrNodes; i++)
    {
        NodeT *x=aux->v[i];
        int j=i-1;
        while(j>=1 && aux->v[j]->d > x->d)
        {
            aux->v[j+1]=aux->v[j];
            j--;
        }
        aux->v[j+1]=x;
    }
    printf("cheie  t.d  t.f\n");
    for(int i=1; i<=aux->nrNodes; i++)
    {
        printf(" %d     %d   %d\n",aux->v[i]->key,aux->v[i]->d,aux->v[i]->f);
    }
}



void sortare_topologica2(Graph *graf, NodeT *sort_vector)
{
    int *time;
    sort_vector->lista[0]->key=1;


    DFS2(graf,&time,sort_vector);
    if(sort_vector->lista[0]==-1)
    {
        printf("Nu se poate face sortarea topologica(graful are cicluri).");
    }
    else
    {
        printf("ok");
        print_list(sort_vector);
    }

}

void print_list(NodeT *sort_vector)
{
    for(int i=1; i<=sort_vector->size; i++)
    {
        printf("%d\n",sort_vector->lista[i]->key);
    }
}

void parent_form(Graph *g,int a[100])
{
    // int a[100];
    for(int i=1; i<=g->nrNodes; i++)
    {
        if(g->v[i]->parent!=NULL)
            a[i]=g->v[i]->parent->index;
        else
        {
            a[i]=-1;
        }
    }
    //  return a;
}

void pretty_print(Graph *graf,int a[100],int rad,int ct)
{
    for(int i=1; i<=graf->nrNodes; i++)
    {
        if(a[i]==rad)
        {
            for(int i=0; i<ct; i++)
                printf(" ");
            printf("%d\n",graf->v[i]->key);
            pretty_print(graf,a,i,ct+1);

        }
    }

}

int index=0;
NodeT *S;
int nrComponents=0;

int minim(int a,int b)
{
    if(a<=b)
        return a;
    return b;
}

void Tarjan(Graph *graf)
{
    S=NULL;

    for(int i=1; i<=graf->nrNodes; i++)
    {
        graf->v[i]->indexT=-1;
        graf->v[i]->lowLink=-1;
        graf->v[i]->onStack=0;
        graf->v[i]->comp=0;
    }

    for(int i=1; i<=graf->nrNodes; i++)
    {
        if(graf->v[i]->indexT==-1)
        {
            Strong_Connect(graf,graf->v[i]);
        }
    }
}

void Strong_Connect(Graph *graf,NodeT *u)
{
    u->indexT=index;
    u->lowLink=index;
    index++;
    push(&S,u);
    u->onStack=1;
    for(int i=1; i<=u->size; i++)
    {
        NodeT *v=u->lista[i];
        if(v->indexT == -1)
        {
            Strong_Connect(graf,v);
            u->lowLink=minim(u->lowLink,v->lowLink);
        }
        else if(v->onStack)
        {
            u->lowLink=minim(u->lowLink,v->indexT);
        }
    }
    if(u->lowLink == u->indexT)
    {
        nrComponents++;

        NodeT *v;
        do
        {
            v=pop(&S);
            //printf("%d ",v->index);
            v->onStack=0;
            v->comp=nrComponents;
        }
        while(v!=u);
    }
}

int main()
{
    char c;
    printf("Alegeti (G/T): ");
    scanf("%c",&c);
    if(c=='T')
    {
        int n;
        printf("n= ");
        scanf("%d", &n);
        Graph *graf = newGraf(n);

        printf("Cititi valorile nodurilor:\n");
        for (int i = 1; i <= n; i++)
        {
            int x;
            scanf("%d", &x);
            graf->v[i] = newNode(x, n);
            graf->v[i]->index=i;
        }
        /* adaugare_muchii(graf,1,2);
         adaugare_muchii(graf,1,3);
         adaugare_muchii(graf,2,4);
         // adaugare_muchii(graf,4,1);
         adaugare_muchii(graf,3,4);
         //  adaugare_muchii(graf,3,5);*/
        adaugare_muchii(graf,1,3);
        adaugare_muchii(graf,2,1);
        adaugare_muchii(graf,2,4);
        adaugare_muchii(graf,3,2);
        adaugare_muchii(graf,3,4);
        adaugare_muchii(graf,3,5);
        adaugare_muchii(graf,4,6);
        adaugare_muchii(graf,5,6);
        adaugare_muchii(graf,5,7);
        adaugare_muchii(graf,6,4);
        adaugare_muchii(graf,6,8);
        adaugare_muchii(graf,7,5);
        adaugare_muchii(graf,7,8);
        int time;
        int ind_sort=1;
        print_graph(graf);
        printf("\nDFS:\n");
        NodeT *sort_top_vector=newNode(1,graf->nrNodes);
        DFS(graf,&time);
        printf("\n");
        int a[100];
        parent_form(graf,a);

        for(int i=0; i<=graf->nrNodes; i++)
        {
            printf("%d ",a[i]);
        }
        printf("\n");

        pretty_print(graf,a,-1,0);
        Tarjan(graf);
        for(int i=1; i<5; i++)
        {
            printf("\n");
        }
        printf("Nr=%d\n",nrComponents);
        for(int i=1; i<=graf->nrNodes; i++)
        {
            printf("%d -> %d\n",graf->v[i]->key,graf->v[i]->comp);
        }
        //afisare_dfs(graf);
        //printf("\n");
        //sortare_topologica2(graf,sort_top_vector);
    }
    else
    {
        for(n=1000; n<=4500; n+=100){
        Graph graf;
        graf->nrNodes = 100;
        int mat[101][101];
        //facem o matrice ca sa verifice daca dintr-un varf au plecat muchii random
        for (int i = 0; i < 101; i++)
        {
            for (int j = 0; j < 101; j++)
            {
                mat[i][j] = 0;
            }
        }
        srand(Time(NULL));
        graf=newGraf(100);
        int m_ramase=n;
        while(m_ramase>0)
        {
            int a = rand() % 100;
            int b = rand() % 100;
            if (mat[a][b] == 0)
            {
                graph->v[a]->v[graph->v[a]->size] = graph->v[b];
                (graph->v[a]->size) ++;
                nr++;
                mat[a][b] == 1;
                m_ramase--;
            }
        }
    }
}

