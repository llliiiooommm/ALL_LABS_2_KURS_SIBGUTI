#include <iostream>
#include <cstdlib>
#include <locale>

#define YES true
#define NO false

using namespace std;

const int N = 100;
bool up = NO;

struct vertex {
    int data;
    int bal;
    vertex* left;
    vertex* right;
};

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
    } else if (point->data < data){
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

vertex* ISDP(int l, int r, int* m) {
    if (l > r) return nullptr;
    int k = (l + r) / 2;
    vertex* p = new vertex;
    p->data = m[k];
    p->left = ISDP(l, k - 1, m);
    p->right = ISDP(k + 1, r, m);
    return p;
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

    int* m = new int[N];

    bool used[101] = {false};
    int count = 0;
    while (count < N) {
        int num = rand() % 100 + 1;
        if (!used[num]) {
            used[num] = true;
            m[count] = num;
            count++;
        }
    }

    cout << "\t\t\t\t\tORIG: " << endl;
    for (int i = 0; i < N; i++) {
        cout << m[i] << " ";
    }
    cout << endl << endl;

    vertex* rootAVL = nullptr;
    vertex* rootISDP = nullptr;

    for (int i = 0; i < N; i++) {
        addAVL(m[i], rootAVL);
    }

    for (int i = 0; i < N; i++) {
        m[i] = i + 1;
    }
    rootISDP = ISDP(0, N - 1, m);

    cout << "\t\t\t\t\tAVL: " << endl;
    LR(rootAVL);
    cout << endl << "---" << endl;

    cout << "\t\t\t\t\tISDP: " << endl;
    LR(rootISDP);
    cout << endl << "---" << endl;

    printf("\t+------+----------+----------------+----------+----------------+\n");
    printf("\t|%6d|  Размер  |      Сумма     |  Высота  | Средняя высота |\n", N);
    printf("\t+------+----------+----------------+----------+----------------+\n");
    printf("\t|  AVL |%10d|%16d|%10d|%16.2f|\n",
        TreeSize(rootAVL), Sum(rootAVL), TreeHeight(rootAVL),
        (double)SumDlinPutey(rootAVL, 1) / TreeSize(rootAVL));
    printf("\t| ISDP |%10d|%16d|%10d|%16.2f|\n",
        TreeSize(rootISDP), Sum(rootISDP), TreeHeight(rootISDP),
        (double)SumDlinPutey(rootISDP, 1) / TreeSize(rootISDP));
    printf("\t+------+----------+----------------+----------+----------------+\n");

    delete[] m;
    return 0;
}
