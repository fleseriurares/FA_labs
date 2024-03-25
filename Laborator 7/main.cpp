#include <iostream>

using namespace std;
typedef struct node
{
    int key;
    struct node *next;
} NodeT;

typedef struct _NodeR2
{
    int key;
    int nrC;
    struct _NodeR2 **kids;

} NodeR2;

typedef struct _NodeR3
{
    int key;
    struct _NodeR3 *children;
    struct _NodeR3 *sibling;

} NodeR3;

#define CAPACITY 100
typedef struct _queue
{
    int vec[CAPACITY];
    int size;
    int head, tail;
} Queue;

NodeR2 *newnodeR2(int val,int nr_children)
{
    NodeR2 *p=(NodeR2*)malloc(sizeof(NodeR2));
    p->key=val;
    p->nrC=nr_children;
    p->kids=(NodeR2**)malloc((nr_children+1)*sizeof(NodeR2*));
    return p;
}

NodeR3 *newnodeR3(int val)
{
    NodeR3 *p=(NodeR3*)malloc(sizeof(NodeR3));
    p->key=val;
    p->sibling=NULL;
    p->children=NULL;
    return p;
}

///ALOCARE COADA
Queue *newqueue()
{
    Queue *p=(Queue *)malloc(sizeof(Queue));
    return p;

}
void enqueue(Queue *q, int key)
{
    if(q->tail==q->head && q->size!=0)
    {
        printf("COADA ESTE PLINA!");
    }
    else
    {
        (q->size)++;
        q->vec[q->tail]=key;
        if(q->tail==CAPACITY-1)
            q->tail=0;
        else
            (q->tail)++;
    }
}

int dequeue(Queue *q)
{

    int x=q->vec[q->head];
    if(q->size==CAPACITY-1)
        q->head=0;
    else
        (q->head)++;
    (q->size)--;

    return x;
}



int form_vectorTati(int a[],int *nr)
{
    int x;
    Queue *coada=newqueue();
    coada->size=0;
    coada->head=0;
    coada->tail=0;
    std::cout<<"PENTRU CITIRE COPIL SCRIEM VALOARE, DACA NU MAI CITIM COPII SCRIEM '-1'\n";
    std::cout<<"Citeste radacina:";
    std::cin>>x;
    int rad=x;
    a[x]=-1;
    enqueue(coada,x);

    int y;
    (*nr)++;
    while(coada->size!=0)
    {
        x=dequeue(coada);
        std::cout<<"Citeste copii lui "<<x<<" : ";
        std::cin>>y;
        while(y!=-1)
        {
            (*nr)++;
            enqueue(coada,y);
            a[y]=x;
            std::cin>>y;
        }
    }
    return rad;
}

int find_root(int a[],int n)
{
    for(int i=1; i<=n; i++)
        if(a[i]==-1)
            return i;
}





NodeR2 *T1(int a[],int n)
{
    int *nr_children=(int*)calloc(n+1,sizeof(int));
    int *ct=(int *)calloc(100,sizeof(int));
    int root;
    NodeR2 **p=(NodeR2**)malloc(100*sizeof(NodeR2*));

    for(int i=1; i<=n; i++)
    {
        if(a[i]==-1)
        {
            root=i;
        }
        else
        {
            nr_children[a[i]]++;
            ct[a[i]]++;
        }
    }
    for(int i=1; i<=n; i++)
    {
        p[i]=newnodeR2(i,nr_children[i]);
    }
    for(int i=1; i<=n; i++)
    {

        if(a[i]!=-1 && ct[a[i]]>0)
        {
            p[a[i]]->kids[nr_children[a[i]]-ct[a[i]]+1]=p[i];
            ct[a[i]]--;
        }
    }
    // std::cout<<'\n'<<p[root]->key<<'\n';
    return p[root];
}

NodeR3 *T21(NodeR2 *R2)
{
    //  NodeR3 *r=newnodeR3(R2->key);
    NodeR3 *r=newnodeR3(R2->key);
//    NodeR3 *p=newnodeR3(R2->kids[1]->key);
//    r->children=p;
    //p->sibling=R2->kids[i+1];
//std::cout<<"ok";
    if(R2->nrC>0)
    {
        NodeR3 *p=newnodeR3(R2->kids[1]->key);
        r->children=p;
        for(int i=1; i<R2->nrC; i++)
        {
            p->sibling=T21(R2->kids[i+1]);
            if(R2->kids[i]->nrC>0)
                p->children=T21(R2->kids[i]->kids[1]);

        }
    }
    return r;
}

NodeR3 *T2(NodeR2 *R2,int ind)
{
    if(R2==NULL)
    {
        return 0;
    }
    NodeR3 *r=newnodeR3(R2->key);
    NodeR3 *p;
    if(R2->nrC>0)
    {
        p=newnodeR3(R2->kids[1]->key);
        r->children=p;
    }
    for(int i=1; i<=R2->nrC; i++)
    {
        if(i!=R2->nrC)
        p->sibling=newnodeR3(R2->kids[i+1]->key);
        p->children=T2(R2->kids[i],1);
        if(i!=R2->nrC)
        p=p->sibling;
    }
    if(ind==1)
    return r->children;
    return r;
}



void pretty_print1(int a[100],int n,int rad,int ct)
{

    for(int i=1; i<=n; i++)
    {
        if(a[i]==rad)
        {
            for(int i=0; i<ct; i++)
                std::cout<<' ';
            std::cout<<i<<'\n';
            pretty_print1(a,n,i,ct+1);

        }
    }

}

void pretty_print2(NodeR2 *R2,int ct)
{
    /// std::cout<<"ok";
    for(int i=0; i<ct; i++)
        std::cout<<' ';
    std::cout<<R2->key<<'\n';
    for(int i=1; i<=R2->nrC; i++)
    {
        pretty_print2(R2->kids[i],ct+1);
    }
}

void pretty_print3(NodeR3 *R3,int ct)
{
    if(R3!=NULL)
    {
        for(int i=0; i<ct; i++)
            std::cout<<' ';
        std::cout<<R3->key<<'\n';

        pretty_print3(R3->children,ct+1);
pretty_print3(R3->sibling,ct);
    }
}

int main()
{
    int a[100],n,x;
    int nr=0;
    int rad=form_vectorTati(a,&nr);
    std::cout<<endl;
    for(int i=1; i<=nr; i++)
    {
        std::cout<<a[i]<<' ';
    }
//   std::cout<<endl;
//   std::cout<<endl;
//   std::cout<<endl;
    // pretty_print1(a,nr,-1,0);
    std::cout<<endl;

    NodeR2 *R2=T1(a,nr);
    // std::cout<<R2->nrC;
// std::cout<<endl;
     pretty_print2(R2,0);
//    std::cout<<endl;
    NodeR3 *R3=T2(R2,0);
//    R3=R3->children->children;
//    while(R3!=NULL)
//    {
//        std::cout<<R3->key<<endl;
//        R3=R3->sibling;
//    }

    //  std::cout<<R3->children->children->key;
    //  std::cout<<'\n'<<'\n';
    pretty_print3(R3,0);
//


    return 0;
}
