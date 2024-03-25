#include <iostream>

using namespace std;

typedef struct _NodeT
{
    int key;
    int size;
    struct _NodeT *left;
    struct _NodeT *right;
} NodeT;

NodeT *newnode(int val,int dim)
{
    NodeT *p=(NodeT *)malloc(sizeof(NodeT));
    p->key=val;
    p->size=dim;
    p->left=NULL;
    p->right=NULL;
    return p;
}

NodeT *BUILD_TREE(int st,int dr)
{
    if(st>dr)
        return NULL;
    NodeT *Tree=newnode((st+dr)/2,dr-st+1);
    Tree->left=BUILD_TREE(st,(st+dr)/2-1);
    Tree->right=BUILD_TREE((st+dr)/2+1,dr);
    return Tree;
}

void pretty_print(NodeT *T,int ct)
{
    if(T!=NULL)
    {
        std::cout<<endl;
        for(int i=0; i<ct; i++)
        {
            std::cout<<"  ";
        }
        std::cout<<T->key<<" size:"<<T->size;
        pretty_print(T->left,ct+1);
        pretty_print(T->right,ct+1);

    }
}

NodeT *OS_Select(NodeT *T,int i)
{
    int poz;
    if(T->left!=NULL)
        poz=T->left->size+1;
    else
        poz=1;
    if(poz==i)
    {
        return T;
    }
    else if(i<poz)
    {
        return OS_Select(T->left,i);
    }
    else return OS_Select(T->right,i-poz);
}

OS_Delete

int main()
{
    NodeT *Tree=BUILD_TREE(1,11);
    NodeT *p=OS_Select(Tree,7);
    //pretty_print(Tree,0);
        std::cout<<p->key;
    // pretty_print(Tree,0);
    return 0;
}
