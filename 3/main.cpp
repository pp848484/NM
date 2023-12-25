#include "Matrix.h"
#include <Windows.h>
#include <cmath>
#define M_PI 3.14159265358979323846
using namespace std;

Vector solveMethodKholetskiy(Matrix& A, Vector& f) {
	int N = A.getN();
	int Nf = f.getSize();
	Vector y(N);
	Vector x(N);
	Matrix B(N);

	bool flag = true;
	for (int i = 0; i < N&&flag; i++)
	{
		for (int j = i; j < N; j++) {
			double S = 0.0;
			for (int k = 0; k < i; k++)
				if (B[k][k] == 0) flag = false;
				else S += B[k][i] * B[k][j] / B[k][k];
			B[i][j] = A[i][j] - S;
			B[j][i] = B[i][j];
			
		}
	}
	
	
	if (!flag) {
		cout << "Деление на 0!"<<endl;
		return Vector(N);
	}
	for (int i = 0; i < N; i++) {
		double S = 0.0;
		for (int j = 0; j < i; j++)
			S += B[j][i] * y[j];
		y[i] = (f[i] - S) / B[i][i];
	}
	for (int i = N-1; i >= 0; i--) {
		double S = 0.0;
		for (int k = i + 1; k <N; k++)
			S += B[i][k] * x[k];
		x[i] = y[i] - S / B[i][i];
	}


	return x;
}
double accurency(Vector a, Vector b) {
	Vector d = a - b;
	double min = d[0];
	for (int i = 1; i < d.getSize(); i++)
		if (abs(d[i]) < min) 
			min = abs(d[i]);
	return min;
}
int findFirstMin(Vector v) {
	double min = abs(v[0]);
	int minInd = 0;
	for (int i = 1; i < v.getSize(); i++) {
		if (abs(v[i]) < min) {
			min = abs(v[i]);
			minInd = i;
		}
	}
	return minInd;
}
int findSecondMin(Vector v, int fmin) {
	double min = DBL_MAX;
	int minIndex = -1;
	for (int i = 0; i < v.getSize(); i++) {
		if (abs(v[i]) < min && i != fmin) {
			min = abs(v[i]);
			minIndex = i;
		}
	}
	return minIndex;
}
double absAngle(Vector a, Vector b) {
	return abs(acos(abs(a.mult(b) / (a.norma() * b.norma()))) * 180.0 / M_PI);
}
struct Pair {
	int numberOfIteration;
	double lambda;
	Vector x;
};

Pair iterationMethod(Matrix A, int N, double l1, Vector x1, double el, double eg, int M) {
	int k = 0;
	Matrix B = (Matrix(N, 'E') - Matrix(N, x1.multT(x1)));

	Vector x(N);
	x.vecRandGenerate();
	Vector v(N);
	v.vecRandGenerate();

	double alpha = 0.00001;
	double prevAlpha = 0.00002;
	Vector Bv;
	while (k < M && abs(1 / alpha - 1/prevAlpha) > el && absAngle(v, x) > eg) {
		v = x.normalization();
		x = solveMethodKholetskiy(A, Bv=B * v);
		prevAlpha=alpha;
		alpha = v.mult(x);
		k++;
	}
	x.normalization();
	Pair p{ k,1 / alpha,x };
	return p;
}
void test() {
	int size[] = { 10,30,50 };
	double lValues[] = { 2,10 };
	double eValues[] = { 1e-5,1e-8,1e-15 };
	double avarageL =0, avarageX = 0,avarageR =0, avarageK = 0;
	int test = 1;
	int maxNumberIteration = 1000000;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 3; k++) {
				Vector lambda(size[i]);
				lambda.vecRandGenerate(-lValues[j], lValues[j]);
				Matrix L(size[i], lambda);

				Vector w(size[i]);
				w.vecRandGenerate();
				w.normalization();

				Matrix H = Matrix(size[i], 'E') - Matrix(size[i], w.multT(w)) * 2;
				Matrix A = H * L * H;

				int index = findFirstMin(lambda);
				int secondIndex = findSecondMin(lambda, index);
				
				
				Pair result = iterationMethod(A, size[i], lambda[index], H[index], eValues[k], eValues[k], maxNumberIteration);
				
				double l = abs(result.lambda - lambda[secondIndex]);
				double x = accurency(result.x, H[secondIndex]);
				double r = accurency(A * result.x - result.x * result.lambda, Vector(size[i]));
				double K = result.numberOfIteration;
				avarageL += l;
				avarageX += x;
				avarageR += r;
				avarageK += K;
				cout << "Тест№" << test << "\t| N = " << size[i] << "| l = [" << -lValues[j] << "," << lValues[j] << "]\t| e = " << eValues[k] << "\t| accL2 = " << l << "\t| accX = " << x << "\t| accR = " << r << "\t| k = " << K << endl;
				test++;
			}
		}
	}
	cout<<endl<< "lAvg=" << avarageL / test << " xAvg=" << avarageX / test << " rAvg=" << avarageR / test << " kAvg=" << avarageK / test << endl;
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int N=8;
	//Генерация А
	Vector lambda(N);
	lambda.vecRandGenerate();
	Matrix Lambda(N, lambda);

	Vector w(N);
	w.vecRandGenerate();
	w.normalization();
	
	Matrix H = Matrix(N, 'E') - Matrix(N, w.multT(w)) * 2;
	Matrix A = H * Lambda * H;
	//Метод итераций
	int first = findFirstMin(lambda);
	int second = findSecondMin(lambda, first);
	cout << "lambda: " << lambda << endl;
	cout << "H: \n" << H << endl;
	cout << "A: \n" << A << endl;
	cout << "lambda[" << first << "]=>lambda[" << second << "]" << endl;
	Pair result =iterationMethod(A, N, lambda[first], H[first], 1e-15,1e-15, 100000);
	cout << "l["<< second <<"]: " << lambda[second] << " result : " << result.lambda << endl;
	cout << "H["<<second<<"]: " << H[second] << endl <<"result : " << result.x << endl;
	double r = accurency(A * result.x - result.x * result.lambda,Vector(N));//r = Ax-lx-O 
	cout <<"r=" << r <<endl;
}