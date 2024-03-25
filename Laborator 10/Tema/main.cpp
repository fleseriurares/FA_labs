#include <iostream>

using namespace std;

typedef struct _NodeT
{
    int key;
    struct _NodeT *p; //parinte
    int rank;
} NodeT;

typedef struct _Graf
{
    int n;
    int **mat;
}Graf;



typedef struct _Muchie
{
    Graf *p1;
    Graf *p2;
    int pondere;
}Muchie;

NodeT *newnode(int val)
{
    NodeT *x=(NodeT *)malloc(sizeof(NodeT));
    x->key=val;
    x->rank=0;
    x->p=NULL;
    return x;
}

void Make_Set(NodeT *x)
{
    x->p=x;
    x->rank=0;
}

void Link_Sets(NodeT *x, NodeT *y)
{
    if(x->rank>y->rank)
    {
        y->p=x;
    }
    else
    {
        x->p=y;
    }
    if(x->rank==y->rank)
    {
        (y->rank)++;
    }
}

NodeT *Find_Set(NodeT *x)
{
    if(x->p!=x)
        x->p=Find_Set(x->p);
    return x->p;
}

void Union(NodeT *x,NodeT *y)
{
    Link_Sets(Find_Set(x),Find_Set(y));
}


Graf *newNodeAux(int val)
{
    Graf *p=(Graf*)malloc(sizeof(Graf));
    p->next=NULL;
    p->key=val;
}

Graf **newGraf(int n)
{
    Graf **G=(Graf**)malloc(n*sizeof(Graf*));
    for(int i=0;i<n;i++)
    {
        G[i]=(Graf*)malloc(sizeof(Graf));
      G[i]->key=i+1;
        G[i]->next=NULL;
        G[i]->last=G[i];
    }

    return G;
}


void addMuchie(Graf **G,int a,int b,int pond,Muchie **M,int i)
{
    Graf *aux=G[a];
    while(aux->next!=NULL)
    {
        aux=aux->next;
    }
    aux->next=newNodeAux(b);
    M[i]->p1=G[a];
    M[i]->p2=G[b];
    M[i]->pondere=pond;
}



int main()
{
    NodeT *T1=newnode(2);
    NodeT *T2=newnode(3);
    NodeT *T3=newnode(4);
    Make_Set(T1);
    Make_Set(T2);
    Make_Set(T3);
    Link_Sets(T1,T2);
    Link_Sets(T3,T2);
   /// std::cout<<Find_Set(T1)->key;
    Graf **G=newGraf(10);

    for(int i=0;i<10;i++)
    {
        std::cout<<G[i]->key<<' ';
    }
    int a,b;
    std::cout<<"Scrieti muchiile ( cand vreti sa va opriti introduceti:0 0) ";
    std::cin>>a;
    std::cin>>b;

    while(a!=0 && b!=0)
    {
        addMuchie(G,a,b,10,M,i);
    }

    return 0;
}
