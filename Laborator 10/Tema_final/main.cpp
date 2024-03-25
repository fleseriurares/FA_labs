#include <iostream>
#include "Profiler.h"
#include <time.h>

/**
Grupa 30225
Autor: Fleseriu Ioan-Rares

Operatiile pe multimi disjuncte:
    Am implementat cele 3 operatii(4 cu LINK_SETS), conform pseudocodului din Cormen. Folosim Make_Set pentru a creea o multime noua care contine elemntul x,
FIND_SET pentru a gasi reprezentantul unei multimi, avansand in arbore prin legatura cu parintele, iar UNION pentru a reuni 2 multimi(Vom lega cei 2 arbori).

    Datorita faptului ca folosim operatia de reuniune cu rancul(UNION by rank) eficienta algoriitmului se imbunatateeste, intrucat evitam cazurile de formare
a arborilor degenerati.
    Operatia de FIND_SET ne ajuta sa ajungem la radacina(reprezentantul multimii) arborelui, iar, dupa cum am mentionat si anterior,datorita uniunii in functiie
    de rank, aceasta operatie prezinta o eficienta sporita.

    Folosirea tuturor operatiilor in implementarea algoritmului lui Kruskal prezinta o crestere liniara, odata
cu cresterea numarului de varfuri ale grafului. Acest fapt este datorat unei cresteri lente al functiei, dupa cum complexitatea  este exprimata cu ajutorul
inversei funtiei lui Ackermann(functia alfa). Asadar, FIND_SET si UNION prezinta o complexitate  egala cu inversa functiei lui Ackermann: alfa(V)
(V-numarul de noduri al grafului).

    Bineinteles, functia MAKE_SET are o complexitate constanta pentru fiecare element, liniara pentru toate nodurile( O(n) pentru crearea celor n noduri).
Dupa cum se poate observa si pe grafic,atunci cand masuram operatiile pe multimi disjuncte folosind algoritmul lui Kruskal, acestea vor prezenta o
crestere relativ liniara( O(V+E*alfa(V)), unde alfa=inversa functiei lui Ackermann, V-nr. varfuri si E-nr. muchii).Complexitatea respecitva se deduce din
faptul  ca vom trece prin fiecare muchie din graf(E muchii) pentru care vom face operatiile necesare(alfa(V))=>E*alfa(V).De asemenea folosind functia
MAKE_SET initial, pentru fiecare nod, complexitatea va ajunge chiar la cea mentionata mai sus:O(V+E*alfa(V).

    Pentru numararea operatiilor, am numarat operatiile de atribuire si comparare ale fiecare functii pe multimi disjunte.



*/

Profiler p("Laborator_Tema");

using namespace std;

typedef struct _NodeT
{
    int key;
    struct _NodeT *p; //parinte
    int rank;
} NodeT;

typedef struct _Graf
{
    int key;
    struct _Graf *next;
} Graf;



typedef struct _Muchie
{
    Graf *p1;
    Graf *p2;
    int pondere;
} Muchie;

NodeT *newnode(int val)
{
    NodeT *x=(NodeT *)malloc(sizeof(NodeT));
    x->key=val;
    x->rank=0;
    x->p=NULL;
    return x;
}

int variabila=100;

void Make_Set(NodeT *x)
{
    x->p=x;
    x->rank=0;
}


void Make_Set2(NodeT *x)
{   Operation op= p.createOperation("Make_Set", variabila);
Operation Top= p.createOperation("Total_op", variabila);
    op.count(2);
    Top.count(2);
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

void Link_Sets2(NodeT *x, NodeT *y)
{
     Operation op= p.createOperation("Link_Sets", variabila);
     Operation Top= p.createOperation("Total_op", variabila);
    op.count();
    Top.count();
    if(x->rank>y->rank)
    { op.count();
    Top.count();
        y->p=x;
    }
    else
    { op.count();
    Top.count();
        x->p=y;
    }
     op.count();
     Top.count();
    if(x->rank==y->rank)
    {
         op.count();
         Top.count();

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

NodeT *Find_Set2(NodeT *x)
{
    Operation op= p.createOperation("Find_Set", variabila);
    Operation Top= p.createOperation("Total_op", variabila);
    op.count();
    Top.count();
    if(x->p!=x)
        {x->p=Find_Set2(x->p);
     op.count();
     Top.count();}return x->p;
}

void Union2(NodeT *x,NodeT *y)
{

    Link_Sets2(Find_Set2(x),Find_Set2(y));
}

Graf *newNodeAux(int val)
{
    Graf *p=(Graf*)malloc(sizeof(Graf));
    p->next=NULL;
    p->key=val;
    return p;
}

Graf **newGraf(int n)
{
    Graf **G=(Graf**)malloc((1+n)*sizeof(Graf*));
    for(int i=1; i<=n; i++)
    {
        G[i]=(Graf*)malloc(sizeof(Graf));
        G[i]->key=i;
        G[i]->next=NULL;
    }

    return G;
}

Graf **newGrafDemo(int a[],int n)
{
    Graf **G=(Graf**)malloc((1+n)*sizeof(Graf*));
    for(int i=1; i<=n; i++)
    {
        G[i]=(Graf*)malloc(sizeof(Graf));
        G[i]->key=a[i];
        G[i]->next=NULL;
    }

    return G;
}

Muchie **newMuchie(int n)
{
    Muchie **m=(Muchie **)malloc((n*5)*sizeof(Muchie*));
    for(int i=1; i<=n*5; i++)
    {
        m[i]=(Muchie *)malloc(sizeof(Muchie));
    }
    return m;
}

bool connection_exists(Graf **G,int a,int b)
{
    Graf *aux=G[a];

    while(aux!=NULL && aux->key!=b)
    {
        aux=aux->next;
    }
    if(aux==NULL || aux->key!=b)
        return 0;
    else
        return 1;
}

bool connection_existsDemo(Graf **G,int a,int b)
{
    Graf *aux=G[a];

    while(aux!=NULL && aux->key!=G[b]->key)
    {
        aux=aux->next;
    }
    if(aux==NULL)
        return 0;
    else
        return 1;
}

Graf *list_insert(Graf *lista,int val)
{
    if(lista==NULL)
    {
        return lista=newNodeAux(val);
    }
    else
    {
        Graf *aux=lista;
        while(aux->next!=NULL)
        {
            aux=aux->next;
        }
        aux->next=newNodeAux(val);
    }
    return lista;
}


int addMuchie(Graf **G,int a,int b,int pond,Muchie **M,int i)
{

    if(connection_exists(G,a,b)==0)
    {
        Graf *aux=G[a]->next;
        if(aux==NULL)
        {
            aux=newNodeAux(b);
            G[a]->next=aux;
        }
        else
        {
            while(aux->next!=NULL)
            {
                aux=aux->next;
            }
            aux->next=newNodeAux(b);
        }
        aux=G[b]->next;
        if(aux==NULL)
        {
            aux=newNodeAux(a);
            G[b]->next=aux;
        }
        else
        {
            while(aux->next!=NULL)
            {
                aux=aux->next;
            }
            aux->next=newNodeAux(a);
        }


        M[i]->p1=G[a];
        M[i]->p2=G[b];
        M[i]->pondere=pond;
        return 1;
    }
    return 0;
}



int addMuchieDemo(Graf **G,int a,int b,int pond,Muchie **M,int i)
{

    if(connection_existsDemo(G,a,b)==0)
    {
        Graf *aux=G[a]->next;
        if(aux==NULL)
        {
            aux=newNodeAux(G[b]->key);
            G[a]->next=aux;
        }
        else
        {
            while(aux->next!=NULL)
            {
                aux=aux->next;
            }
            aux->next=newNodeAux(G[b]->key);
        }
        aux=G[b]->next;
        if(aux==NULL)
        {
            aux=newNodeAux(G[a]->key);
            G[b]->next=aux;
        }
        else
        {
            while(aux->next!=NULL)
            {
                aux=aux->next;
            }
            aux->next=newNodeAux(G[a]->key);
        }


        M[i]->p1=newNodeAux(a);
        M[i]->p2=newNodeAux(b);
        M[i]->pondere=pond;
        return 1;
    }
    return 0;
}

Graf **newGrafR(int n, Muchie **M)
{
    Graf **G=NULL;
    G=(Graf**)malloc((1+n)*sizeof(Graf*));
    for(int i=1; i<=n; i++)
    {
        G[i]=(Graf*)malloc(sizeof(Graf));
        G[i]->key=i;
        G[i]->next=NULL;
        int pond=rand()%1000+1;
        if(i>1)
        {
            addMuchie(G,i,i-1,pond,M,i-1);
        }
    }
    return G;
}


void print_list(Graf *G)
{
    Graf *aux=G;
    while(aux!=NULL)
    {
        std::cout<<aux->key;

        if(aux->next!=NULL)
            std::cout<<" -> ";
        aux=aux->next;
    }
}


void SortByWeight(Muchie **M,int n)
{
    int i,j;
    Muchie *k;
    for(int i=2; i<=n; i++)
    {
        k=M[i];
        j=i-1;

        while(j>=1 && M[j]->pondere>k->pondere)
        {
            M[j+1]=M[j];
            j--;
        }
        M[j+1]=k;
    }
}

int verif_exist(int a[],int *n, int k)
{

    for(int i=1; i<=*n; i++)
    {
        if(a[i]==k)
        {
            return i;
        }
    }
    a[*n]=k;
    (*n)++;
    return (*n)-1;
}


void afisare_multimi(NodeT **T,int n)
{

    Graf **afis=NULL; ///folosim structura de la graf intrucat ea reprezinta de fapt o lista de adiacenta
    afis=(Graf **)malloc((n+5) * sizeof(Graf*));
    for(int i=0; i<=n; i++)
    {
        afis[i]=NULL;
        ///afis[i]=(Graf *)malloc(sizeof(Graf));

    }
    int k=1;
    int *a=(int *)calloc(100,sizeof(int));
    for(int i=1; i<=n; i++)
    {
        int x=verif_exist(a,&k,Find_Set(T[i])->key);
        ///std::cout<<x<<" ";
        afis[x]=list_insert(afis[x],T[i]->key);
    }

    std::cout<<endl;

    for(int i=1; i<k; i++)
    {
        print_list(afis[i]);
        std::cout<<endl;
    }
}


void addMuchieK(Graf **G,int a,int b,int pond,Muchie **M,int i)
{

    M[i]->p1=G[a];
    M[i]->p2=G[b];
    M[i]->pondere=pond;

}

void addMuchieKDemo(Graf **G,int a,int b,int pond,Muchie **M,int i)
{

    M[i]->p1=newNodeAux(a);
    M[i]->p2=newNodeAux(b);
    M[i]->pondere=pond;

}

Muchie **Kruskal(Graf **G,int n,Muchie **M,int nr_m)
{

    Muchie **A=newMuchie(n);

    Graf **G2=newGraf(n);
    NodeT **G_aux=(NodeT **)malloc((n+2)*sizeof(NodeT*));

    for(int i=1; i<=n; i++)
    {///std::cout<<"ok";
        G_aux[i]=(NodeT *)malloc(sizeof(NodeT));
        G_aux[i]=NULL;
    }
    for(int i=1; i<=n; i++)
    {
        G_aux[i]=newnode(G[i]->key);
        Make_Set2(G_aux[i]);
    }

    SortByWeight(M,nr_m);
    int k=1;
    for(int i=1; i<=nr_m; i++)
    {
        if(Find_Set2(G_aux[M[i]->p1->key])!=Find_Set2(G_aux[M[i]->p2->key]))
        {
            addMuchieK(G,M[i]->p1->key,M[i]->p2->key,M[i]->pondere,A,k);
           /// std::cout<<i<<" :)"<<endl;

            Union2(G_aux[M[i]->p1->key],G_aux[M[i]->p2->key]);
            k++;

        }
    }
    return A;
}


Muchie **KruskalDemo(Graf **G,int n,Muchie **M,int nr_m)
{

    Muchie **A=newMuchie(n);


    NodeT **G_aux=(NodeT **)malloc((n+1)*sizeof(NodeT*));
    for(int i=1; i<=n; i++)
    {
        G_aux[i]=(NodeT *)malloc(sizeof(NodeT));
        G_aux[i]=NULL;
    }
    for(int i=1; i<=n; i++)
    {
        G_aux[i]=newnode(G[i]->key);
        Make_Set(G_aux[i]);
    }

    SortByWeight(M,nr_m);
    int k=1;
    for(int i=1; i<=nr_m; i++)
    {
        if(Find_Set(G_aux[M[i]->p1->key])!=Find_Set(G_aux[M[i]->p2->key]))
        {
            addMuchieKDemo(G,M[i]->p1->key,M[i]->p2->key,M[i]->pondere,A,k);
            Union(G_aux[M[i]->p1->key],G_aux[M[i]->p2->key]);
            k++;

        }
    }
    return A;
}


Graf **GenerateRandomGraph(int n,Muchie ***M,int *nr_m)
{

    Graf **G = NULL;
    *M=NULL;
    *M=newMuchie(n);
    G=newGrafR(n,*M);


    *nr_m=n-1;

    int x1=rand()%(n)+1;
    int x2=rand()%(n)+1;

    //  std::cout<<x1<<' '<<x2;
    int p=rand()%(1000)+1;
    int k=0;
    int nr;
    if(n<10)
        nr=n+1;
    else
        nr=n*4;
    while(*nr_m<=nr)
    {
        if(x1!=x2 && addMuchie(G,x1,x2,p,*M,*nr_m)==1)
        {
            (*nr_m)++;
        }
        x1=rand()%(n)+1;
        x2=rand()%(n)+1;
        p=rand()%(1000)+1;

        k++;
    }
    (*nr_m)--;
    return G;

}

int main()
{

    char c;
    std::cout<<"(T/G): ";
    std::cin>>c;
    if(c=='T')
    {
        std::cout<<"Multimi disjuncte: "<<endl;
        int n,x;
        int sir[100];
        std::cout<<"n= ";
        std::cin>>n;
        NodeT **T=(NodeT **)malloc(n*sizeof(NodeT *));
        std::cout<<"Cititi multimile: "<<endl;
        for(int i=1; i<=n; i++)
        {
            std::cin>>x;
            sir[i]=x;
            T[i]=newnode(x);
            Make_Set(T[i]);
        }
        afisare_multimi(T,n);
        int y;
        std::cout<<"y =  -1=>stop, 0=>UNION, 1=>Find_Set";
        std::cout<<endl<<"y= ";
        std::cin>>y;
        int a,b;
        while(y!=-1)
        {

            if(y==0)
            {
                std::cout<<"Ce elemente(dupa index) ai dori sa le unesti?: ";
                for(int i=1; i<=n; i++)
                {
                    std::cout<<sir[i]<<' ';
                }
                std::cout<<endl;
                std::cout<<"a= ";
                std::cin>>a;
                std::cout<<"b= ";
                std::cin>>b;
                Union(T[a],T[b]);
                std::cout<<endl;
                afisare_multimi(T,n);
            }
            if(y==1)
            {
                std::cout<<"Radacina carei chei(index) ati dori sa o afisati?: ";
                std::cin>>a;
                std::cout<<"Radacina arborelui(multimii) care contine acel nod este: "<<Find_Set(T[a])->key;
                std::cout<<endl;
            }
            std::cin>>y;
        }


        std::cout<<endl;
        std::cout<<"Grafuri: "<<endl;

        int m,sir2[100];
        std::cout<<"nr. de elemente= ";
        std::cin>>m;
        std::cout<<"Cititi elementele din graf: "<<endl;
        for(int i=1;i<=m;i++)
        {
            std::cin>>sir2[i];
        }
        Graf **G=newGrafDemo(sir2,m);
        Muchie **M=newMuchie(m);
        for(int i=1;i<=m;i++)
        {
            std::cout<<i<<": "<<sir2[i]<<endl;
        }

        int p;
        int m_ct=0;
        std::cout<<endl;
        std::cout<<"Scrieti muchiile (indexul nodurilor) ( cand vreti sa va opriti introduceti:0 0 0) "<<endl;
        std::cout<<"nod1= ";
        std::cin>>a;
        std::cout<<"nod2= ";
        std::cin>>b;
        std::cout<<"ponderea= ";
        std::cin>>p;
        std::cout<<endl;


        while(a!=0 && b!=0)
        {
            m_ct++;
            int x=addMuchieDemo(G,a,b,p,M,m_ct);
            std::cout<<"(1/0): "<<x<<endl;
            if(x==0)
            {
                m_ct--;
            }
            std::cout<<"nod1= ";
            std::cin>>a;
            std::cout<<"nod2= ";
            std::cin>>b;
            std::cout<<"ponderea= ";
            std::cin>>p;
        }

            std::cout<<"Afisare muchii: "<<endl;
            for(int i=1; i<=m_ct; i++)
            {
                std::cout<<G[M[i]->p1->key]->key<<' '<<G[M[i]->p2->key]->key<<' '<<M[i]->pondere;
                std::cout<<endl;
            }

            std::cout<<"Algoritmul lui Kruskal: "<<endl;

            Muchie **M4=KruskalDemo(G,m,M,m_ct);
            std::cout<<endl;
                for(int i=1; i<=m-1; i++)
                {

                    std::cout<<G[M4[i]->p1->key]->key<<' '<<G[M4[i]->p2->key]->key<<' '<<M4[i]->pondere;
                    std::cout<<endl;
                }
    }
    else
    {

        Muchie **M;
        Graf **G;
        int nr_m=0;
        for(int i=100;i<=10000;i=i+100)
        {variabila=i;
            std::cout<<i<<" ";

            M=NULL;
            G=NULL;
            nr_m=0;
            M=newMuchie(i);
            G=GenerateRandomGraph(i,&M,&nr_m);
            Kruskal(G,i,M,nr_m);
        }
       // p.addSeries("Total_Op","Union","Link_Sets","Find_Set");
        p.createGroup("Operatii Kruskal","Make_Set","Link_Sets","Find_Set");

        p.showReport();
    }

    return 0;
}

