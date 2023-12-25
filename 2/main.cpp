#include "Matrix.h"
#include <Windows.h>
using namespace std;

Vector solveMethodKholetskiy(Matrix& A, Vector& f) {
	int N = A.getN();
	int L = A.getL();
	int Nf = f.size();
	Vector y(N);
	Vector x(N);
	Matrix B(N, L);

	if (N != Nf) {
		cout << "\n Матрица и вектор имеют разный размер!";
		return x;
	}

	bool flag = true;
	for (int i= 1; i <= N; i++) {
		for (int j = i; j <= min(i + L - 1, N); j++) {
			double S = 0.0;
			for (int k = max(1, j - L + 1); k <= i - 1; k++)
				if (B(k, k) == 0) flag = false;
				else S += B(k, i) * B(k, j) / B(k, k);
			B(i, j) = A(i, j) - S;
		}
	}
	//cout << endl<<"Матрица B в результате разложения матрицы А:" << endl;
	//cout << B << endl;
	if (!flag) {
		cout << "Деление на 0!";
		x.setSize(N);
		return x;
	}
	for (int i = 1; i <= N; i++) {
		double S = 0.0;
		for (int j = max(1, i - L + 1); j <= i; j++)
			S += B(j, i) * y[j];
		y[i] = (f[i] - S) / B(i, i);
	}
	//cout << "y: " << y << endl;
	for (int i = N; i >= 1; i--) {
		double S = 0.0;
		for (int k = i + 1; k <= min(i + L - 1, N); k++)
			S += B(i, k) * x[k];
		x[i] = y[i] - S / B(i, i);
	}


	return x;
}
double accurancy(Vector a, Vector b) {
	Vector d = a - b;
	double res;
	int s = d.size();
	res = abs(d[1]);
	for (int i = 2; i <= s; i++)
		if (abs(d[i]) > res)
			res = abs(d[i]);
	return res;
}

void test1() {
	Matrix A;
	Vector x, f;
	for (int i = 25; i <= 1000; i *= 2) {
		x.vecRandGenerate(i);
		A.matRandGenerate(i, i / 10);
		f = A * x;
		cout << "N=" << i << " L=" << i / 10 << " accurancy=" << scientific<<accurancy(solveMethodKholetskiy(A, f), x)<<fixed<<endl;
	}
}
void test2() {
	Matrix A;
	Vector x, f;
	for (int i = 10; i <= 1000; i *= 10) {
		for (int j = i / 10; j < i; j *= 2) {
			x.vecRandGenerate(i);
			A.matRandGenerate(i, j);
			f = A * x;
			cout << "N=" << i << " L=" << j << " accurancy=" << scientific << accurancy(solveMethodKholetskiy(A, f), x) << fixed << endl;
		}
		cout << endl;
	}
}
void test3() {
	Matrix A;
	Vector x, f;
	for (int i = 25; i <= 1000; i *= 2) {
		x.vecRandGenerate(i);
		A.matRandGenerateBC(i, i / 10, -10, 10, 3);
		f = A * x;
		cout << "N=" << i << " L=" << i / 10 << " k=3 accurancy=" << scientific << accurancy(solveMethodKholetskiy(A, f), x) << fixed << endl;
	}
	cout << endl;
	for (int i = 25; i <= 1000; i *= 2) {
		x.vecRandGenerate(i);
		A.matRandGenerateBC(i, i / 10, -10, 10, 4);
		f = A * x;
		cout << "N=" << i << " L=" << i / 10 << " k=4 accurancy=" << scientific << accurancy(solveMethodKholetskiy(A, f), x) << fixed << endl;
	}
	cout << endl;
	for (int i = 25; i <= 1000; i *= 2) {
		x.vecRandGenerate(i);
		A.matRandGenerateBC(i, i / 10, -10, 10, 6);
		f = A * x;
		cout << "N=" << i << " L=" << i / 10 << " k=6 accurancy=" << scientific << accurancy(solveMethodKholetskiy(A, f), x) << fixed << endl;
	}
}
void test4() {
	Matrix A;
	Vector x, f;
	int N = 1000;
	x.vecRandGenerate(N);
	for (int j = 1; j <= N; j *= 2) {
		A.matRandGenerate(N, j);
		f = A * x;
		cout << "N=" << N << " L=" << j << " accurancy=" << scientific << accurancy(solveMethodKholetskiy(A, f), x) << fixed << endl;
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	test4();
}