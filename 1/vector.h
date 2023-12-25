#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime> 

using namespace std;

template<typename T>
class MyVector {
	T* arr;
	int size;
public:

	MyVector(int size) :size(size) {
		arr = new T[size];
	}

	~MyVector() { delete[] arr; }

	MyVector(const MyVector& other) : size(other.size) {
		arr = new T[size];
		for (int i = 0; i < size; ++i) {
			arr[i] = other.arr[i];
		}
	}

	MyVector& operator=(MyVector&& other) noexcept {
		if (this != &other) {
			delete[] arr;
			size = other.size;
			arr = new T[size];
			for (int i = 0; i < size; ++i) {
				arr[i] = other.arr[i];
			}
		}
		return *this;
	}

	int getSize() { return size; }
	void setSize(int size) { this->size = size; }

	T* getArr() {
		return arr;
	}

	void fillRandom(T rnd) {
		int	min = -rnd, max = rnd;
		static const double fraction = 1.0 / (static_cast<T>(RAND_MAX) + 1.0);
		for (int i = 0; i < size; i++)
		{
			arr[i] = (static_cast<T>(rand() * fraction * (max - min + 1) + min));
		}
	}

	void fill(MyVector vec) {
		vec.setSize(size);
		for (int i = 0; i < size; i++)
			arr[i] = vec[i];
	}

	T norm() {
		T maxComponent = abs(arr[0]);
		for (int i = 1; i < size; ++i) {
			T absValue = abs(arr[i]);
			if (absValue > maxComponent) {
				maxComponent = absValue;
			}
		}
		return maxComponent;
	}

	void readFromFile(const string filename) {
		ifstream input(filename);
		if (!input.is_open()) throw runtime_error("Не удалось открыть файл для чтения.");
		for (int i = 0; i < size; ++i) {
			input >> arr[i];
		}
		input.close();
	}

	void writeToFile(const string filename) {
		ofstream output(filename);
		if (!output.is_open()) throw runtime_error("Не удалось открыть файл для записи.");
		for (int i = 0; i < size; ++i) {
			output << arr[i] << " ";
		}
		output.close();
	}

	T& operator[](int index) {
		return arr[index];
	}


	MyVector<T> operator+(MyVector<T>& other) {
		MyVector<T> result(size);
		for (int i = 0; i < size; ++i) {
			result.arr[i] = arr[i] + other.arr[i];
		}
		result.size = size;
		return result;
	}

	MyVector<T> operator-(MyVector<T>& other) {
		MyVector<T> result(size);
		for (int i = 0; i < size; ++i) {
			result.arr[i] = arr[i] - other.arr[i];
		}
		result.size = size;
		return result;
	}

	T operator*(MyVector<T>& other) {
		T result = 0;
		for (int i = 0; i < size; ++i) {
			result += arr[i] * other.arr[i];
		}
		return result;
	}

	friend ostream& operator<<(ostream& os, const MyVector<T>& vec) {
		for (int i = 0; i < vec.size; ++i) {
			os << fixed << vec.arr[i] << " ";
		}
		return os;
	}
};
