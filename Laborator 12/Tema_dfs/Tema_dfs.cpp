#include <iostream>

using namespace std;

enum {
    WHITE = 0,
    GRAY,
    BLACK
};


typedef struct _Node {

    int key;
    int size;
    int d;
    int f;
    struct _Node** lista;
    int color;
    struct _Node* parent;
}NodeT;


typedef struct {
    int nrNodes;
    NodeT** v;
}Graph;

NodeT* newNode(int key, int n)
{
    NodeT* p = (NodeT*)malloc(sizeof(NodeT));
    p->key = key;
    p->color = WHITE;
    p->d = 0;
    p->f = 0;
    p->size = 0;
    p->parent = NULL;
    p->lista = (NodeT**)malloc(n * sizeof(NodeT*));
    for (int i = 0; i < n; i++)
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
        graf->v[i] = (NodeT*)malloc(sizeof(NodeT));
    }
    graf->nrNodes = n;
    return graf;
}
void DFS(Graph* graf, int* time)
{
    for (int i = 0; i < graf->nrNodes; i++)
    {
        graf->v[i]->color = WHITE;
        graf->v[i]->parent = NULL;
    }
    *time = 0;
    for (int i = 0; i < graf->nrNodes; i++)
    {
        if (graf->v[i]->color == WHITE)
        {
            DFS_VISIT(graf, graf->v[i], time);
        }
    }
}

void DFS_VISIT(Graph* graf, NodeT* u, int* time)
{
    (*time)++;
    u->d = *time;
    u->color = GRAY;
    for (int i = 0; i < u->size; i++)
    {
        NodeT* v = u->lista[i];
        if (v->color == WHITE)
        {
            v->parent = u;
            DFS_VISIT(graf, v, time);
        }
        v->color = BLACK;
        (*time)++;
        v->f = *time;
    }
}

int main()
{
    int n;
    printf("n= ");
    scanf("%d", &n);
    Graph* graf = newGraf(n);

    printf("Cititi valorile nodurilor:");
    for (int i = 0; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        graf->v[i] = newNode(x, n);
    }
}

