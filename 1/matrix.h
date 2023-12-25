#pragma once

#include "vector.h"
#include <iomanip>


template<typename T>
class Matrix
{
	MyVector<T> b;
	MyVector<T> c;
	MyVector<T> a;
	MyVector<T> p;
	MyVector<T> f;
	MyVector<T> x;
	int size;
	int k;

public:
	Matrix(int size, int k) : b(size), c(size), a(size), p(size), f(size), x(size), size(size) {
		if (k > 0) this->k=k;
		else throw runtime_error("k < 1");
	};
	
	Matrix() : b(10), c(10), a(10), p(10), f(10), x(10), size(10) {
		k = 1 + rand() % (size - 1);
	};

	MyVector<T> getB() { return b; }
	MyVector<T> getC() { return c; }
	MyVector<T> getA() { return a; }
	MyVector<T> getP() { return p; }
	MyVector<T> getF() { return f; }
	MyVector<T> getX() { return x; }
	int getK() { return k; }
	int getSize() { return size; }
	void setSize(int size) { this->size = size; }
	void setF(MyVector<T> vec) { f = vec; }
	void setX(MyVector<T> x) {
		this->x = x;
		f = *this * x;
	}

	void fillRandom(T rnd) {
		b.fillRandom(rnd);
		c.fillRandom(rnd);
		a.fillRandom(rnd);
		p.fillRandom(rnd);
		x.fillRandom(rnd);
		/*p[k - 2] = c[k - 2];
		p[k - 1] = b[k - 1];
		p[k] = a[k];*/
		a[0] = 0;
		c[size - 1] = 0;
		refresh();
		f = *this * x;
	}
	void fillBadCond(T rnd) {

		b.fillRandom(rnd / 250);
		c.fillRandom(rnd * 300);
		a.fillRandom(rnd * 300);
		p.fillRandom(rnd);
		x.fillRandom(rnd);
		a[0] = 0;
		c[size - 1] = 0;
		p[k - 1]= b[k - 1];
		p[k]= a[k];
		p[k - 2]= c[k - 2];
		f = *this * x;
	}
	void check() {
		if (p[k - 1] == b[k - 1] &&
			p[k] == a[k] &&
			p[k - 2] == c[k - 2]) cout << "true" << endl;
		else cout << "false" << endl;
	}
	void refresh() {
		b[k - 1] = p[k - 1];
		a[k] = p[k];
		c[k - 2] = p[k - 2];
	}

	void writeToFile(string filename) {
		ofstream output(filename);
		if (!output.is_open()) throw runtime_error("Не удалось открыть файл для записи.");
		output << *this;
		output.close();
	}
	void readFromFile(string filename) {
		ifstream input(filename);
		if (!input.is_open()) throw runtime_error("Не удалось открыть файл для чтения.");
		T z;
		int count;
		for (int i = 0; i < size; i++)
		{
			if (i == 0) {
				input >> b[i] >> c[i];
				count = 2;
				while (count < k - 1) {
					input >> z;
					count++;
				}
				input >> p[i];
				count++;
				while (count < size - 1) {
					input >> z;
					count++;
				}
			}
			else if (i == size - 1) {
				count = 0;
				while (count < k - 1) {
					input >> z;
					count++;
				}
				input >> p[i];
				count++;
				while (count < size - 2) {
					input >> z;
					count++;
				}
				input >> a[i] >> b[i];
			}
			else {
				count = 0;
				while (count < i-1) {
					input >> z;
					count++;
				}
				input >> a[i] >> b[i] >> c[i];
				count += 3;
				while (count < k - 1) {
					input >> z;
					count++;
				}
				input >> p[i];
				count++;
				while (count < size - 1) {
					input >> z;
					count++;
				}
			}
		}
	}

	void print() {
		cout << "c:" << c << endl<<"b:" << b << endl << "a:" << a << endl << "p:" << p << endl;
	}

	MyVector<T> operator*(MyVector<T> vec) {
		MyVector<T> res(size);
		for (int i = 0; i < size; i++) res[i] = 0;
		if (size != vec.getSize())throw runtime_error("Невозможно умножить матрицу на вектор");
		res[0] = b[0] * x[0] + c[0] * x[1];
		if (k>2) res[0] += p[0] * x[k - 1];
		for (int i = 1; i < size-1; i++)
		{
			res[i] = a[i] * x[i - 1] + b[i] * x[i] + c[i] * x[i + 1];
			if (i != k - 2 && i != k - 1 && i != k)	res[i] += p[i] * x[k - 1];	
		}
		res[size - 1] = a[size - 1] * x[size - 2] + b[size - 1] * x[size - 1] ;
		if (size - 2 != k - 1 && size - 1 != k - 1) res[size - 1] += p[size - 1] * x[k - 1];
		return res;
	}
	Matrix<T> operator+(Matrix<T>& other) {
		Matrix<T> res(size);
		if (size != other.getSize())throw runtime_error("Невозможно сложить матрицы");
		else
		{
			for (int i = 0; i < size; i++)
			{
				res.getB()[i] = b[i] + other.getB()[i];
				res.getA()[i] = a[i] + other.getA()[i];
				res.getP()[i] = p[i] + other.getP()[i];
				res.getC()[i] = c[i] + other.getC()[i];
				res.setSize(size);
			}
		}
	}
	Matrix<T> operator-(Matrix<T>& other) {
		Matrix<T> res(size);
		if (size != other.getSize())throw runtime_error("Невозможно вычесть матрицы");
		else
		{
			for (int i = 0; i < size; i++)
			{
				res.getB()[i] = b[i] - other.getB()[i];
				res.getA()[i] = a[i] - other.getA()[i];
				res.getP()[i] = p[i] - other.getP()[i];
				res.getC()[i] = c[i] - other.getC()[i];
				res.setSize(size);
			}
		}
		return res;
	}
	friend ostream& operator<<(ostream& os, Matrix<T>& vec) {
		int size = vec.getSize();
		for (int i = 0; i < size; i++)
		{
			os << "|";
			for (int j = 0; j < size; j++) {
				 if (j == vec.getK()-1)
					os << setprecision(2) << vec.getP()[i] << "\t";
				else if (i == j)
					os << setprecision(2) << vec.getB()[i] << "\t";
				else if (j == i + 1 && i < size)
					os << setprecision(2) << vec.getC()[i] << "\t";
				else if (i == j + 1 && i > 0)
					os << setprecision(2) << vec.getA()[i] << "\t";
				
				else
					os << setprecision(2) << 0 << "\t";

			}
			
			os << "||" << "\t" <<fixed<< setprecision(10) << vec.getX()[i];
			os << "||" << "\t" <<fixed<< setprecision(10) << vec.getF()[i] << endl;
		}
		return os;
	}

	MyVector<T> algo() {
		double R;
		MyVector<T> newF(size);
		MyVector<T> diff(size);
		for (int i = 0; i < size; i++) newF[i] = f[i];
		//cout << "Прямой ход:" << endl<<endl;
		for (int i = 0; i < k - 1; i++)
		{
			R = 1.0 / b[i];
			b[i] = 1;
			c[i] *= R;
			p[i] *= R;
			f[i] *= R;

			R = a[i + 1];
			a[i + 1] = 0;
			b[i + 1] -= R * c[i];
			p[i + 1] -= R * p[i];
			f[i + 1] -= R * f[i];
			refresh();
			newF = *this * x;
			diff = newF - f;
			//cout << "max|A'x-f|: "<<scientific<< diff.norm()<<fixed << endl;
		}
		for (int i = size - 1; i > k - 1; i--) {
			R = 1 / b[i];
			b[i] = 1;
			a[i] *= R;
			p[i] *= R;
			f[i] *= R;

			R = c[i - 1];
			c[i - 1] = 0;
			b[i - 1] -= R * a[i];
			p[i - 1] -= R * p[i];
			f[i - 1] -= R * f[i];
			refresh();
			newF = *this * x;
			diff = newF - f;
			//cout << "max|A'x-f|: " << scientific<<diff.norm() << fixed << endl;
		}
		//cout <<endl <<"Обратный ход: " <<endl<< endl;
		MyVector<T> newX = MyVector<T>(size);
		for (int i = 0; i < size; i++) newX[i] = 0;
		R = p[k - 1];
		p[k - 1] /= R;
		b[k - 1] /= R;
		f[k - 1] /= R;
		newX[k - 1] = f[k - 1];

		newF = *this * x;
		diff = newF - f;
		//cout << "max|A'x-f|: " << scientific <<diff.norm()<<fixed<< endl;
		for (int i = k - 2; i >= 0; i--) {
			if (i == k - 2)
				newX[i] = f[i] - p[i] * newX[k - 1];
			else
				newX[i] = f[i] - c[i] * newX[i + 1] - p[i] * newX[k - 1];
		}
		for (int i = k; i < size; i++) {
			if (i == k)
				newX[i] = f[i] - p[i] * newX[k - 1];
			else
				newX[i] = f[i] - a[i] * newX[i - 1] - p[i] * newX[k - 1];
		}

		return newX;
	}

	
};
