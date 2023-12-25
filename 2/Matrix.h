#pragma once
#include "Vector.h"

class Matrix {
	void correct() {
		int gr = 1;
		for (int j = 1; j < L; j++) {
			for (int i = N; i > N - gr; i--)
				P[j][i] = 0;
			gr++;
		}
	}
public:
	int N, L;
	Vector* P;
	
	Matrix(){
		P = nullptr;
		L = 0;
		N = 0;
	}
	Matrix(int n, int l) {
		N = n;
		L = l;
		P = new Vector[l];
		for (int i = 0; i < l; i++) P[i].setSize(n);
	}
	Matrix(const Matrix& obj) {
		P = obj.P;
		N = obj.N;
		L = obj.L;
	}
	Matrix(int l, Vector t[]) {
		P = new Vector[l];
		for (int i = 0; i < l; i++) P[i] = t[i];
		L = l;
		N = P[0].size();
		correct();
	}
	~Matrix() {
		for (int i = 0; i < L; i++) P[i].clean();
		delete[] P;
	}

	double& operator() (int i, int j) {
		if (i >= L + j || j >= L + i) return P[L-1][N];
		else {
			int ni = i;
			int nj = j - i + 1;
			return P[nj - 1][ni];
		}
	}
	friend ostream& operator<< (ostream& out, Matrix& A) {
		for (int i = 1; i <= A.N; i++) {
			for (int j = 1; j <= A.N; j++)
				if (j >= i) out << setprecision(3)  << A(i, j)<<"\t";
				else out << setprecision(3) << A(j, i)<<"\t";
			out <<endl;
		}
		return out;
	}

	int getN() {
		return N;
	}
	int getL() {
		return L;
	}
	void matRandGenerate(int n = 10, int l = 1,double min=-10, double max=10) {
		for (int i = 0; i < L; i++) P[i].clean();
		if (P != nullptr) delete[] P;
		N=n,L=l;
		P = new Vector[L];
		for (int i = 0; i < L; i++) P[i].vecRandGenerate(N, min, max);
		correct();
	}
	void matRandGenerateBC(int n = 10, int l = 1, double min = -10, double max = 10,int k=1) {
		for (int i = 0; i < L; i++) P[i].clean();
		if (P != nullptr) delete[] P;
		N = n, L = l;
		P = new Vector[L];
		for (int i = 0; i < L; i++) {
			P[i].vecRandGenerate(N, min, max);
			for (int j = 1; j <= N; j++)
				if (i == 0) P[i][j] /= pow(10, k);
				else P[i][j] *= pow(10, k);
		}
		
		correct();
	}

	Matrix operator- (const Matrix& M) {
		Matrix ans(N, L);
		for (int i = 0; i < L; i++) ans.P[i] = P[i] - M.P[i];
		return ans;
	}
	Matrix operator+ (const Matrix& M) {
		Matrix ans(N, L);
		for (int i = 0; i < L; i++) ans.P[i] = P[i] + M.P[i];
		return ans;
	}
	Matrix operator* (double k) {
		Matrix ans(L, P);
		for (int i = 0; i < L; i++) ans.P[i] = ans.P[i] * k;
		return ans;
	}
	Vector operator* (Vector& x){
		Vector ans(N);

		for (int i = 1; i <= N; i++) {
			double S = 0.0;
			int m = i <= L ? 1 : i - L + 1;
			int M = i + L - 1 < N ? i + L - 1 : N;
			for (int j = m; j <= M; j++)
				if (j >= i)
					S += (*this)(i, j) * x[j];
				else
					S += (*this)(j, i) * x[j];
			ans[i] = S;
		}

		return ans;
	}
	Matrix operator= (const Matrix M) {
		if (this != &M) {
			P = M.P;
			N = M.N;
			L = M.L;
		}
		return *this;
	}

	void print() {
		for (int i = 1; i <= N; i++) {
			int KNI = min(i + L - 1, N);
			int k = L;
			for (int j = i; j <= KNI; j++) {
				k--;
				cout << setprecision(3)<<(*this)(i, j) << "\t";
			}
			if (k > 0) for (int j = 1; j <=k; j++) cout << setprecision(3) << 0 << "\t";
			cout <<endl;
		}
	}
};