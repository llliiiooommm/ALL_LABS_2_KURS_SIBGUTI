#include <iostream>
#include <iomanip>
#include <random>
#include <clocale>
#include <ctime>

#define YES true
#define NO false

using namespace std;

struct Vertex {
    int data;
    int bal;
    Vertex* left;
    Vertex* right;
};

bool up;

void ll(Vertex*& point) {
    Vertex* current = point->left;
    point->bal = 0;
    current->bal = 0;
    point->left = current->right;
    current->right = point;
    point = current;
}

void rr(Vertex*& point) {
    Vertex* current = point->right;
    point->bal = 0;
    current->bal = 0;
    point->right = current->left;
    current->left = point;
    point = current;
}

void lr(Vertex*& point) {
    Vertex* current = point->left;
    Vertex* reva = current->right;

    if (reva->bal < 0) point->bal = 1;
    else point->bal = 0;

    if (reva->bal > 0) current->bal = -1;
    else current->bal = 0;

    reva->bal = 0;
    current->right = reva->left;
    point->left = reva->right;
    reva->left = current;
    reva->right = point;
    point = reva;
}

void rl(Vertex*& point) {
    Vertex* current = point->right;
    Vertex* reva = current->left;

    if (reva->bal < 0) point->bal = 1;
    else point->bal = 0;

    if (reva->bal > 0) current->bal = -1;
    else current->bal = 0;

    reva->bal = 0;
    current->left = reva->right;
    point->right = reva->left;
    reva->right = current;
    reva->left = point;
    point = reva;
}


/* ------------------------------------------------------ */
void addAVL(int data, Vertex*& point) {
    if (point == nullptr) {
        point = new Vertex{data, 0, nullptr, nullptr};
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
                if (point->left->bal < 0) ll(point);
                else lr(point);
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
                if (point->right->bal > 0) rr(point);
                else rl(point);
                up = NO;
            }
        }
    } else {
        up = NO;
    }
}


/* ------------------------------------------------------ */
void B2INSERT(int D, Vertex*& p, int& VR, int& HR) {
    if (p == nullptr) {
        p = new Vertex{D, 0, nullptr, nullptr};
        VR = 1;
    }
    else if (p->data > D) {
        B2INSERT(D, p->left, VR, HR);
        if (VR == 1) {
            if (p->bal == 0) {
                Vertex* q = p->left;
                p->left = q->right;
                q->right = p;
                p = q;
                p->bal = 1;
                VR = 0;
                HR = 1;
            } else {
                p->bal = 0;
                VR = 1;
                HR = 0;
            }
        } else {
            HR = 0;
        }
    }
    else if (p->data < D) {
        B2INSERT(D, p->right, VR, HR);
        if (VR == 1) {
            p->bal = 1;
            HR = 1;
            VR = 0;
        }
        else if (HR == 1) {
            if (p->bal == 1) {
                Vertex* q = p->right;
                p->bal = 0;
                q->bal = 0;
                p->right = q->left;
                q->left = p;
                p = q;
                VR = 1;
                HR = 0;
            } else {
                HR = 0;
            }
        }
    }
}


/* ------------------------------------------------------ */
void LR(Vertex* x) {
    if (!x) return;
    LR(x->left);
    cout << x->data << ' ';
    LR(x->right);
}

int size(Vertex* x) {
    if (x == nullptr) {
        return 0;
    } else {
        int leftSize = size(x->left);
        int rightSize = size(x->right);
        return 1 + leftSize + rightSize;
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int height(Vertex* x) {
    if (x == nullptr) {
        return 0;
    } else {
        int leftHeight = height(x->left);
        int rightHeight = height(x->right);
        int maxHeight = max(leftHeight, rightHeight);
        return 1 + maxHeight;
    }
}

int sdp(Vertex* x, int level) {
    if (x == nullptr) {
        return 0;
    } else {
        int leftSum = sdp(x->left, level + 1);
        int rightSum = sdp(x->right, level + 1);
        return level + leftSum + rightSum;
    }
}

int summ(Vertex* x) {
    if (x == nullptr) {
        return 0;
    } else {
        int leftSum = summ(x->left);
        int rightSum = summ(x->right);
        return x->data + leftSum + rightSum;
    }
}

void printRow(const char* label, Vertex* tree) {
    int sz = size(tree);

    double avg;
    if (sz == 0) {
        avg = 0.0;
    } else {
        int totalDepth = sdp(tree, 1);
        avg = (double)totalDepth / (double)sz;
    }

    int totalSum = summ(tree);

    int treeHeight = height(tree);

    cout << "| ";
    cout << setw(4) << label;
    cout << " |";
    cout << setw(10) << sz;
    cout << "|";
    cout << setw(16) << totalSum;
    cout << "|";
    cout << setw(10) << treeHeight;
    cout << "|";
    cout << setw(16) << fixed << setprecision(2) << avg;
    cout << "|\n";
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));

    const int NUM = 100;
    bool used[101] = {false};
    int* vals = new int[NUM];
    int count = 0;
    while (count < NUM) {
        int v = rand() % 100 + 1;
        if (!used[v]) {
            used[v] = true;
            vals[count++] = v;
        }
    }

    Vertex* rootAVL = nullptr;
    Vertex* rootDBT = nullptr;

    for (int i = 0; i < NUM; ++i) {
        addAVL(vals[i], rootAVL);
    }

    for (int i = 0; i < NUM; ++i) {
        int VR = 0, HR = 0;
        B2INSERT(vals[i], rootDBT, VR, HR);
    }

    cout << "\t\t\t\t\tAVL: " << endl;
    LR(rootAVL);
    cout << endl << "---" << endl;

    cout << "\t\t\t\t\tDBD: " << endl;
    LR(rootDBT);
    cout << endl << "---" << endl;

    cout << "+------+----------+----------------+----------+----------------+\n";
    cout << "|      |  Дерево  |  Сумма узлов   |  Высота  |  Ср. глубина   |\n";
    cout << "+------+----------+----------------+----------+----------------+\n";
    printRow("AVL", rootAVL);
    printRow("DBD", rootDBT);
    cout << "+------+----------+----------------+----------+----------------+\n";

    delete[] vals;
    return 0;
}