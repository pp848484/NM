#pragma once
#include "Vector.h"

class Matrix {
	int N;
	Vector* A;
public:
	
	Matrix(){
		A = nullptr;
		N = 0;
	}
	Matrix(int n,char E) {
		N = n;
		A = new Vector[N];
		for (int i = 0; i < N; i++) {
			A[i] = Vector(N);
			for (int j = 0; j < N; j++) {
				if (i == j) A[i][j] = 1;
				else A[i][j] = 0;
			}
		}
	}
	Matrix(int n) {
		N = n;
		A = new Vector [N];
		for (int i = 0; i < N; i++) {
			A[i] = Vector(N);
			for (int j = 0; j < N; j++) A[i][j] = 0;
		}
	}
	Matrix(const Matrix& obj) {
		N = obj.N;
		A = new Vector[N];
		for (int i = 0; i < N; i++) {
			A[i] = obj.A[i];
		}
	}
	Matrix(int N, Vector* t) {
		this->N = N;
		A = new Vector[N];
		for (int i = 0; i < N; i++) {
			A[i] = Vector(N);
			for (int j = 0; j < N; j++) {
				A[i][j] = t[i][j];
			}
		}
	}
	Matrix(int N, Vector t) {
		this->N = N;
		A = new Vector  [N];
		for (int i = 0; i < N; i++) {
			A[i] = Vector(N);
			for (int j = 0; j < N; j++) {
				if (i == j) A[i][j] = t[j];
				else A[i][j] = 0;
			}
		}
	}
	~Matrix() {
		delete[] A;
		A = nullptr;
	}

	Vector& operator[] (int i) {
		return A[i];
	}
	friend ostream& operator<< (ostream& out, const Matrix& matr) {
		for (int i = 0; i < matr.N; i++)
			out << matr.A[i] << endl;
		return out;
	}

	int getN() {
		return N;
	}
	void matRandGenerate(double min = -10, double max = 10) {
		for (int i = 0; i < N; i++) A[i].vecRandGenerate(min, max);
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < N; j++) A[i][j] = A[j][i];

	}

	Matrix operator- (const Matrix& M) {
		Matrix ans(N);
		for (int i = 0; i < N; i++)
			for(int j = 0 ;j<N;j++)
				ans[i][j] = A[i][j] - M.A[i][j];
		return ans;
	}
	Matrix operator+ (const Matrix& M) {
		Matrix ans(N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				ans[i][j] = A[i][j] + M.A[i][j];
		return ans;
	}
	Matrix operator* (double k) {
		Matrix ans(N);
		for (int i = 0; i < N; i++)
			for(int j = 0 ; j < N;j++)
				ans[i][j] = A[i][j] * k;
		return ans;
	}
	Vector operator* (Vector& x){
		Vector ans(N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				ans[i] += A[i][j]*x[j];
			}
		}
		return ans;
	}
	Matrix operator* (Matrix& x) {
		Matrix ans(N);
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < N; j++) 
				for (int k = 0; k < N; k++) 
					ans[i][j] += A[i][k] * x.A[k][j];
		return ans;
	}
	Matrix& operator= (const Matrix& M) {
		if (this != &M) {
			delete[] A;
			N = M.N;
			A = new Vector[N];
			for (int i = 0; i < N; i++) {
				A[i] = M.A[i]; 
			}
		}
		return *this;
	}

};