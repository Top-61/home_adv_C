/*В программе описана структура для хранения двоичного дерева:
typedef struct tree {
    datatype key;
    struct tree *left, *right;
} tree;

Необходимо реализовать функцию, которая печатает вид дерева сверху.
Функция должна строго соответствовать прототипу: void btUpView(tree *root)

В качестве ответа загрузите только одну функцию void btUpView(tree *root)
Пример №1
Данные на входе:

       10
      /   \
     5     15
    / \   /  \
   3   7 13   18
  /   /
 1   6

Данные на выходе:   1 3 5 10 15 18
 */


#include "stdio.h"
#include "stdlib.h"

typedef struct tree
{
    int key;
    struct tree *left, *right;
} tree;


tree* insert(tree *p, int k)
{
    if( p==NULL )
    {
        p=malloc(sizeof(tree));
        p->key=k;
        p->left = p->right=NULL;
        return p;
    }
    if( k < p->key)
        p->left = insert( p->left,k);
    else
        p->right = insert( p->right,k);
    return p;
}
void print_left(tree *p)
{
    int a = p->key;
    if(p->left)
    {
        p=p->left;
        print_left(p);
    }
    printf("%d ",a);
}

void print_right(tree *p)
{
    while(p)
    {
        printf("%d ",p->key);
        p=p->right;
    }
}

void btUpView(tree *root)
{
    print_left(root->left);
    printf("%d ", root->key);
    print_right(root->right);
}

int main(void)
{
    tree *a = insert(NULL,10);
    insert(a,5);
    insert(a,15);
    insert(a,3);
    insert(a,7);
    insert(a,1);
    insert(a,6);
    insert(a,13);
    insert(a,18);
    btUpView(a);
    return 0;
}
