#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>

#define YES true
#define NO false

using namespace std;

struct vertex {
    int data;
    int bal;
    vertex* left;
    vertex* right;
};

bool up = NO;
bool um = NO;
vertex* q = nullptr;

void ll(vertex*& point) {
    vertex* current = point->left;
    point->bal = 0;
    current->bal = 0;
    point->left = current->right;
    current->right = point;
    point = current;
}

void rr(vertex*& point) {
    vertex* current = point->right;
    point->bal = 0;
    current->bal = 0;
    point->right = current->left;
    current->left = point;
    point = current;
}

void lr(vertex*& point) {
    vertex* current = point->left;
    vertex* reva = current->right;

    if (reva->bal < 0) {
        point->bal = 1;
    } else {
        point->bal = 0;
    }

    if (reva->bal > 0) {
        current->bal = -1;
    } else {
        current->bal = 0;
    }
    reva->bal = 0;
    current->right = reva->left;
    point->left = reva->right;
    reva->left = current;
    reva->right = point;
    point = reva;
}

void rl(vertex*& point) {
    vertex* current = point->right;
    vertex* reva = current->left;

    if (reva->bal < 0) {
        point->bal = 1;
    } else {
        point->bal = 0;
    }

    if (reva->bal > 0) {
        current->bal = -1;
    } else {
        current->bal = 0;
    }
    
    reva->bal = 0;
    current->left = reva->right;
    point->right = reva->left;
    reva->right = current;
    reva->left = point;
    point = reva;
}

void addAVL(int data, vertex*& point) {
    if (point == nullptr) {
        point = new vertex;
        point->data = data;
        point->bal = 0;
        point->left = nullptr;
        point->right = nullptr;
        up = YES;
    } else if (point->data > data) {
        addAVL(data, point->left);
        if (up == YES) {
            if (point->bal > 0) {
                point->bal = 0;
                up = NO;
            } else if (point->bal == 0) {
                point->bal = -1;
                up = YES;
            } else {
                if (point->left->bal < 0) {
                    ll(point);
                } else {
                    lr(point);
                }
                up = NO;
            }
        }
    } else if (point->data < data) {
        addAVL(data, point->right);
        if (up == YES) {
            if (point->bal < 0) {
                point->bal = 0;
                up = NO;
            } else if (point->bal == 0) {
                point->bal = 1;
                up = YES;
            } else {
                if (point->right->bal > 0) {
                    rr(point);
                } else {
                    rl(point);
                }
                up = NO;
            }
        }
    } else {
        cout << "Data in tree ! \n";
        up = NO;
    }
}

void LL1(vertex*& p) {
    vertex* q_node = p->left;
    if (q_node->bal == 0) {
        q_node->bal = 1;
        p->bal = -1;
        um = NO;
    } else {
        q_node->bal = 0;
        p->bal = 0;
    }
    p->left = q_node->right;
    q_node->right = p;
    p = q_node;
}

void RR1(vertex*& p) {
    vertex* q_node = p->right;
    if (q_node->bal == 0) {
        q_node->bal = -1;
        p->bal = 1;
        um = NO;
    } else {
        q_node->bal = 0;
        p->bal = 0;
    }
    p->right = q_node->left;
    q_node->left = p;
    p = q_node;
}

void BL(vertex*& p) {
    if (p->bal == -1) {
        p->bal = 0;
        um = YES;
    } else if (p->bal == 0) {
        p->bal = 1;
        um = NO;
    } else if (p->bal == 1) {
        if (p->right->bal >= 0) {
            RR1(p);
        } else {
            rl(p);
        }
    }
}

void BR(vertex*& p) {
    if (p->bal == 1) {
        p->bal = 0;
        um = YES;
    } else if (p->bal == 0) {
        p->bal = -1;
        um = NO;
    } else if (p->bal == -1) {
        if (p->left->bal <= 0) {
            LL1(p);
        } else {
            lr(p);
        }
    }
}

void del(vertex*& r) {
    if (r->right != nullptr) {
        del(r->right);
        if (um == YES) {
            BR(r);
        }
    } else {
        q->data = r->data;
        q = r;
        r = r->left;
        um = YES;
    }
}

void DeleteAVL(int x, vertex*& p) {
    if (p == nullptr) {
        cout << "Element not found!" << endl;
        return;
    }

    if (x < p->data) {
        DeleteAVL(x, p->left);
        if (um == YES) {
            BL(p);
        }
    } else if (x > p->data) {
        DeleteAVL(x, p->right);
        if (um == YES) {
            BR(p);
        }
    } else {
        q = p;
        if (q->left == nullptr) {
            p = q->right;
            um = YES;
        } else if (q->right == nullptr) {
            p = q->left;
            um = YES;
        } else {
            del(q->left);
            if (um == YES) {
                BL(p);
            }
        }
        delete q;
    }
}

void LR(vertex* x) {
    if (x == nullptr) return;
    LR(x->left);
    cout << x->data << ' ';
    LR(x->right);
}

int TreeSize(vertex* p) {
    if (p == nullptr) return 0;
    return 1 + TreeSize(p->left) + TreeSize(p->right);
}

int Max(int x, int y) {
    return (x > y) ? x : y;
}

int TreeHeight(vertex* x) {
    if (x == nullptr) return 0;
    return 1 + Max(TreeHeight(x->left), TreeHeight(x->right));
}

int SumDlinPutey(vertex* x, int l) {
    if (x == nullptr) return 0;
    return l + SumDlinPutey(x->left, l + 1) + SumDlinPutey(x->right, l + 1);
}

int Sum(vertex* x) {
    if (x == nullptr) return 0;
    return x->data + Sum(x->left) + Sum(x->right);
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "rus");

    const int COUNT = 10;
    int* m = new int[COUNT];

    bool used[101] = {false};
    int generated = 0;
    while (generated < COUNT) {
        int num = rand() % 100 + 1;
        if (!used[num]) {
            used[num] = true;
            m[generated] = num;
            generated++;
        }
    }

    cout << "Сгенерированные числа: ";
    for (int i = 0; i < COUNT; i++) {
        cout << m[i] << " ";
    }
    cout << "\n\n";

    vertex* rootAVL = nullptr;

    for (int i = 0; i < COUNT; i++) {
        addAVL(m[i], rootAVL);
    }

    cout << "Дерево после вставки:\n";
    LR(rootAVL);
    cout << "\n---\n";

    cout << "\nТеперь удаляйте элементы по одному.\n";
    while (TreeSize(rootAVL) > 0) {
        cout << "\nТекущее дерево: ";
        LR(rootAVL);
        cout << "\nВведите число для удаления: ";

        int value;
        cin >> value;

        um = NO;
        DeleteAVL(value, rootAVL);

        if (TreeSize(rootAVL) == 0) {
            cout << "\nДерево стало пустым. Завершение.\n";
            break;
        }
    }

    delete[] m;
    return 0;
}