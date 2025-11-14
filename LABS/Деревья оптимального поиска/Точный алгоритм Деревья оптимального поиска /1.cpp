#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <iomanip>
#include <ctime>

#define YES true
#define NO false
using namespace std;

struct vertex {
	int data;
	int h;
	int w;
	vertex *left;
	vertex *right;
};

const int N = 4;

vertex *root;
int c = 0;
int *mas, *W;
int *h;
int AW[N + 1][N + 1];
int AP[N + 1][N + 1], AR[N + 1][N + 1];

/*Матрица весов*/
void AW_count() {
	for (int i = 0; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
			AW[i][j] = AW[i][j - 1] + W[j - 1];
}

/*Взвешенная матрица весов AP и итоговая матрица AR*/
void AP_AR_count() {
	int min, m, x, j;
	
	for (int i = 0; i < N; i++) {
		j = i + 1;
		AP[i][j] = AW[i][j];
		AR[i][j] = j;
	}
	
	for (int H = 2; H <= N; H++) {
		for (int i = 0; i <= N - H; i++) {
			j = i + H;
			m = AR[i][j - 1];
			min = AP[i][m - 1] + AP[m][j];
			for (int k = m + 1; k <= AR[i + 1][j]; k++) {
				x = AP[i][k - 1] + AP[k][j];
				if (x < min) {
					m = k;
					min = x;
				}
			}
			AP[i][j] = min + AW[i][j];
			AR[i][j] = m;
		}
	}
}

/*Функция добавления в дерево - обычное sdp*/
void add(vertex *&p, int x, int w) {
	if (p == NULL)
	{
		p = new vertex;
		p->data = mas[x - 1];
		p->w = w;
		p->left = NULL;
		p->right = NULL;
	}
	else
		if (x < p->data) {
			add(p->left, x, w);
		}
		else
			if (x >= p->data) {
				add(p->right, x, w);
			}
}

/*Создание вершины*/
void create_tree(int L, int R) {
	int k;
	if (L < R) {
		k = AR[L][R];
		add(root, k, W[k - 1]);
		create_tree(L, k - 1);
		create_tree(k, R);
	}
}


void LRprint(vertex *&x) {
	if (x == NULL) return;
	LRprint(x->left);
	cout << x->data << ' ' << x->w << " " << x->h << endl;
	LRprint(x->right);
}

int size(vertex *p)
{
	if (p == NULL)
		return 0;
	return 1 + size(p->left) + size(p->right);
}

long summ(vertex *p)
{
	if (p == NULL)
		return 0;
	return p->data + summ(p->left) + summ(p->right);
}

void seth(vertex *p)
{
	if (p) {
		if (p->left) {
			p->left->h = p->h + 1;
		}
		if (p->right) {
			p->right->h = p->h + 1;
		}
		seth(p->left);
		seth(p->right);
	}
}

void midh(vertex *p)
{
	if (p) {
		c += p->w * p->h;
		midh(p->left);
		midh(p->right);
	}
}


int main() {
	setlocale(0, "rus");
	srand(time(NULL));

	mas = new int[N];
	for (int i = 0; i < N; i++) {
		mas[i] = i + 1;
		cout << setw(3) << mas[i] << " ";
	}
	cout << " // Исходный массив" << endl;

	W = new int[N];
	for (int i = 0; i < N; i++) {
		W[i] = rand() % 99 + 1;
		cout << setw(3) << W[i] << " ";
	}
	cout << " // Случайные веса" << endl << endl;

	cout << "\nМатрица весов: " << endl;
	AW_count();
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			cout << setw(4) << AW[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	AP_AR_count();

	cout << "\nМатрица взвешенных высот: " << endl;
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			cout << setw(4) << AP[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "\nМатрица  итоговая: " << endl;
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++) {
			cout << setw(4) << AR[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;


	create_tree(0, N);
	
	int WW = AW[0][N];

	cout << endl;

	cout << "Дерево:" << endl;
	
	root->h = 1;
	seth(root);
	midh(root);
	LRprint(root);

	cout << endl << (double)AP[0][N] / AW[0][N] << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	cout << "| n=4   |  Узлы    | Сумм. веса   | Средневзвеш. высота |" << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	cout << "|  Итог |" << setw(10) << size(root) << "|" << setw(14) << summ(root) << "|" << setw(21) << c / (double)WW << "|" << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	return 0;
}