#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

class Vector {
	double* a;
	int size;

public:
	Vector() {
		a = nullptr;
		size = 0;
	}
	Vector(double *a, int size) {
		this->size = size;
		this->a = new double[size];
		for (int i = 0; i < size; i++) this->a[i] = a[i];

	}
	Vector(int size) {
		this->size = size;
		a = new double[size];
		for (int i = 0; i < size; i++) this->a[i] = 0;
	}
	Vector(const Vector& o) {
		this->size = o.size;
		this->a = new double[this->size];
		for (int i = 0; i < this->size; i++) this->a[i] = o.a[i];
	}
	~Vector() {
		delete[] a;
		a = nullptr;
		size = 0;
	}
	double norma() {
		double norm = 0;
		for (int i = 0; i < size; i++) norm += a[i] * a[i];
		return sqrt(norm);
	}
	Vector normalization() {
		double norm = norma();
		*this = *this / norm;
		return *this;
	}
	
	int getSize() {
		return size;
	}
	void setVec(int n) {
		delete[] a;
		a = new double[n];
		this->size = n;
		for (int i = 0; i < n; i++) cin >> a[i];
	}
	void vecRandGenerate(double min = -10, double max = 10) {
		for (int i = 0; i < size; i++)
			a[i] = min +(max-min)*(rand()/(RAND_MAX+1.0));
	}

	double& operator[] (size_t i) {
		return a[i];
	}
	friend ostream& operator<< (ostream& out, const Vector& v) {
		for (int i = 0; i < v.size; i++)
			out <<setprecision(2)<< v.a[i] << "\t";
		return out;
	}

	Vector operator- (const Vector& v) {
		int size = v.size;
		Vector ans(size);
		for (int i = 0; i < size; i++) ans[i] = a[i] - v.a[i];
		return ans;
	}
	Vector operator+ (const Vector& v) {
		int size = v.size;
		Vector ans(size);
		for (int i = 0; i < size; i++) ans[i] = a[i] + v.a[i];
		return ans;
	}
	Vector operator* (double k) {
		Vector ans(size);
		for (int i = 0; i <size; i++) ans[i] = a[i] * k;
		return ans;
	}
	Vector operator/ (double k) {
		Vector ans(size);
		for (int i = 0; i < size; i++) ans[i] = a[i] / k;
		return ans;
	}
	Vector& operator= (const Vector& v) {
		if (this != &v) {
			delete[] a;
			size = v.size;
			a = new double[size];
			for (int i = 0; i < size; i++) {
				a[i] = v.a[i];
			}
		}
		return *this;
	}
	double mult (Vector& o) {
		double result = 0.00;
		for (int i = 0; i < size; i++) {
			result += a[i] * o.a[i];
		}
		return result;
	}
	Vector* multT(Vector& o) {
		Vector* result = new Vector[size];
		for (int i = 0; i < size; i++) {
			result[i] = Vector(o.size);
			for (int j = 0; j < size; j++) result[i][j] = a[i] * o.a[j];
		}
		return result;
	}
};