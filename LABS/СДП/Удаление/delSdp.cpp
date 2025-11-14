#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

const int N = 10;
int *a;

struct vertex
{
    vertex *left;
    vertex *right;
    int data;
};



vertex *root = NULL;



void SDP(int data, vertex*& p);
int TreeSize(vertex* p);
int TreeHeight(vertex* p);
int Max(int l, int r);
int SumDlinPutey(vertex*, int L);
long Sum(vertex* p);
void PrintLR(vertex* x);
void delSDP(vertex *&Root, int point);





int main()
{
    int i, x;
    srand(time(NULL));
    a = new int[N];
    
    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }
    for (i = 0; i < N; i++) {
        SDP(a[i], root);
    }    
    
    while (1) {    
        for (i = 0; i < N; i++) {
            cout << a[i] << " ";
        }
        cout << "- initial array" << endl << "---" << endl;
    
        PrintLR(root);
        cout << "- binary search tree (in-order)" << endl << "---" << endl;
        
        cout << "Enter value to delete: ";
        cin >> x;

        delSDP(root, x);
        
        int found = 0;
        for (int i = 0; i < N; i++) {
            if (a[i] == x) {
                found = 1;
                break;
            }
        }
        
        if (found) {
            cout << "Value '" << x << endl;
        } else {
            cout << "Value not found in original array (but may have been inserted before)." << endl;
        }

        cout << endl;
        // === Вывод характеристик дерева после удаления ===
        cout << "Tree size: " << TreeSize(root) << endl;
        cout << "Sum of all nodes: " << Sum(root) << endl;
        cout << "Tree height: " << TreeHeight(root) << endl;
        cout << "Sum of path lengths: " << SumDlinPutey(root, 0) << endl;
        // ================================================

        PrintLR(root);
                
        cout << endl << endl << "Continue? (1 = yes, 0 = no): ";
        cin >> i;
        system("clear");
        if (i == 0) break;
    }
    
    delete[] a;
    return 0;	   
}




/*=================Функция для работы с сдп==============*/
void SDP(int data, vertex* &p)
{
    if (!p) {
        p = new vertex;
        p->data = data;
        p->left = NULL;
        p->right = NULL;
    } 
    else if (data < p->data) {
        SDP(data, p->left);
    }
    else if (data > p->data) {
        SDP(data, p->right);
    }
    else {
        return;
    }
}

void delSDP(vertex *&Root, int point)
{
    vertex **p = &Root;
    vertex *S;
    vertex *r;

    while ((*p) != NULL) {
        if (point < ((*p)->data)) {
            p = &((*p)->left);
        } else if (point > ((*p)->data)) {
            p = &((*p)->right);
        } else {
            break;
        }
    }

    if ((*p) != NULL) {
        vertex *q = (*p);
        if (q->left == NULL) {
            (*p) = q->right;
        } else if (q->right == NULL) {
            (*p) = q->left;
        } else {
            r = q->left;
            S = q;

            if (r->right == NULL) {
                r->right = q->right;
                (*p) = r;
            } else {
                while (r->right != NULL) {
                    S = r;
                    r = r->right;
                }
                
                S->right = r->left;
                
                r->left = q->left;
                r->right = q->right;
                (*p) = r;
            }
        }
        delete q;
    }
}


/*============Оставшиеся функции===============*/
void PrintLR(vertex *x)
{ 
    if (x == NULL) return;
    PrintLR(x->left);
    cout << x->data << ' ';
    PrintLR(x->right);
}

int TreeSize(vertex *p)
{
    if (p == NULL) return 0;
    return 1 + TreeSize(p->left) + TreeSize(p->right);
}

long Sum(vertex *p)
{
    if (p == NULL) return 0;
    return p->data + Sum(p->left) + Sum(p->right);
}

int Max(int l, int r)
{
    return (l > r) ? l : r;
}

int TreeHeight(vertex *p)
{
    if (p == NULL) return 0;
    return 1 + Max(TreeHeight(p->left), TreeHeight(p->right));
}

int SumDlinPutey(vertex *x, int L)
{
    if (x == NULL) {
        return 0;
    } else {
        return L + SumDlinPutey(x->left, L + 1) + SumDlinPutey(x->right, L + 1);
    }
}
