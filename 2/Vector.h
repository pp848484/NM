#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

class Vector {
	vector<double> a;

public:
	Vector() {}
	Vector(vector<double> a) {
		this->a = a;
	}
	Vector(int size) {
		for (int i = 0; i < size; i++)
			a.push_back(0.0);
	}
	Vector(const Vector& original) {
		this->a = original.a;
	}
	~Vector() {
		clean();
	}
		
	int size() {
		return a.size();
	}
	void setSize(int newSize) {
		a.clear();
		for (int i = 0; i < newSize; i++) a.push_back(0.0);
	}
	void setVec(int n) {
		a.clear();

		for (int i = 0; i < n; i++) {
			double x;
			cin >> x;
			a.push_back(x);
		}
	}
	void vecRandGenerate(int n, double min = -10, double max = 10) {
		a.clear();
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		for (int i = 0; i < n; i++) {
			double x = (rand() * fraction * (max - min + 1) + min);
			a.push_back(x);
		}
	}
	vector<double> get() {
		return this->a;
	}
	void clean() {
		a.clear();
	}

	double& operator[] (size_t i) {
		return a[i - 1];
	}
	friend ostream& operator<< (ostream& out, Vector& v) {
		int size = v.size();
		for (int i = 0; i < size; i++) out << v.a[i]<<" ";
		return out;
	}
	Vector operator- (const Vector& v) {
		int size = v.a.size();
		Vector ans(size);
		for (int i = 0; i < size; i++) ans[i + 1] = a[i] - v.a[i];
		return ans;
	}
	Vector operator+ (const Vector& v) {
		int size = v.a.size();
		Vector ans(size);
		for (int i = 0; i < size; i++) ans[i + 1] = a[i] + v.a[i];
		return ans;
	}
	Vector operator* (double k) {
		Vector ans(a.size());
		for (int i = 0; i < a.size(); i++) ans[i + 1] = a[i] * k;
		return ans;
	}
	Vector operator/ (double k) {
		Vector ans(a.size());
		for (int i = 0; i < a.size(); i++) ans[i + 1] = a[i] / k;
		return ans;
	}
	Vector operator= (const Vector v) {
		if (this != &v) {
			a.clear();
			a = v.a;
		}
		return *this;
	}
};