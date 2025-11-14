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

const int N = 10;

vertex *root1 = NULL;
vertex *root2 = NULL;
vertex *root3 = NULL;

int c = 0;
int *mas, *W;
int AW[N + 1][N + 1];
int AP[N + 1][N + 1], AR[N + 1][N + 1];

void AW_count() {
	for (int i = 0; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
			AW[i][j] = AW[i][j - 1] + W[j - 1];
}

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

void add(vertex *&p, int x, int w) {
	if (p == NULL)
	{
		p = new vertex;
		p->data = x;
		p->w = w;
		p->h = 0;
		p->left = NULL;
		p->right = NULL;
	}
	else
		if (x < p->data) {
			add(p->left, x, w);
		}
		else {
			add(p->right, x, w);
		}
}

void create_tree(int L, int R) {
	if (L >= R) return;
	int k = AR[L][R];
	add(root1, k, W[k - 1]);
	create_tree(L, k - 1);
	create_tree(k, R);
}

void A2(int L, int R) {
	if (L > R) return;
	int wes = 0;
	for (int i = L; i <= R; i++) wes += W[i];
	int sum = 0;
	int i;
	for (i = L; i <= R; i++) {
		if (sum < wes / 2 && sum + W[i] >= wes / 2) break;
		sum += W[i];
	}
	add(root3, mas[i], W[i]);
	A2(L, i - 1);
	A2(i + 1, R);
}

void QuickSort(int left, int right) {
	if (left >= right) return;

	int i = left, j = right;
	int pivotW = W[(left + right) / 2];

	while (i <= j) {
		while (W[i] > pivotW) i++;
		while (W[j] < pivotW) j--;

		if (i <= j) {
			int tempW = W[i];
			W[i] = W[j];
			W[j] = tempW;

			int tempMas = mas[i];
			mas[i] = mas[j];
			mas[j] = tempMas;

			i++;
			j--;
		}
	}

	if (left < j) QuickSort(left, j);
	if (i < right) QuickSort(i, right);
}

void LRprint(vertex *&x) {
	if (x == NULL) return;
	LRprint(x->left);
	cout << " " << x->data << " (" << x->w << ", h=" << x->h << ")";
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
	if (root1) root1->h = 1;
	seth(root1);

	A2(0, N - 1);
	if (root3) root3->h = 1;
	seth(root3);

	QuickSort(0, N - 1);
	for (int i = 0; i < N; i++) {
		add(root2, mas[i], W[i]);
	}
	if (root2) root2->h = 1;
	seth(root2);

	cout << "\nДерево оптимального поиска (DP):" << endl;
	LRprint(root1); cout << endl;

	cout << "\nДерево A1 (вставка по убыванию веса):" << endl;
	LRprint(root2); cout << endl;

	cout << "\nДерево A2 (рекурсивное разделение):" << endl;
	LRprint(root3); cout << endl;

	int WW = AW[0][N];

	c = 0;
	midh(root1);
	double avg_opt = (double)c / WW;

	c = 0;
	midh(root2);
	double avg_A1 = (double)c / WW;

	c = 0;
	midh(root3);
	double avg_A2 = (double)c / WW;

	cout << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	cout << "| Метод |  Размер  | Сумма узлов  | Ср. взвеш. высота   |" << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;
	cout << "|  DP   |" << setw(10) << size(root1) << "|" << setw(14) << summ(root1) << "|" << setw(21) << fixed << setprecision(3) << avg_opt << "|" << endl;
	cout << "|  A1   |" << setw(10) << size(root2) << "|" << setw(14) << summ(root2) << "|" << setw(21) << avg_A1 << "|" << endl;
	cout << "|  A2   |" << setw(10) << size(root3) << "|" << setw(14) << summ(root3) << "|" << setw(21) << avg_A2 << "|" << endl;
	cout << "+-------+----------+--------------+---------------------+" << endl;

	delete[] mas;
	delete[] W;

	return 0;
}