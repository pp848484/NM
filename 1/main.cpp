#include "matrix.h"
#include "vector.h"

double findDeltasist(MyVector<double> f,MyVector<double> x)
{
	int size = f.getSize();
	double q = 0.1;
	double res;
	MyVector<double> delta(size);
	for (int i = 0; i < size; i++)
	{
		if (abs(x[i]) > q)
			delta[i] = abs((f[i] - x[i]) / x[i]);
		else
			delta[i] = abs(f[i] - x[i]);
	}
	return delta.norm();
}
double testSize(int size) {
	Matrix<double> matrix(size, 1 + rand() % (size - 1));
	matrix.fillRandom(size);
	return findDeltasist(matrix.algo(), matrix.getX());
}
double testCondition(int size) {
	Matrix<double> matrix(size, 1 + rand() % (size - 1));
	matrix.fillBadCond(size);
	return findDeltasist(matrix.algo(), matrix.getX());
}
double testRange(double range) {
	Matrix<double> matrix(10, 5);
	matrix.fillRandom(range);
	return findDeltasist(matrix.algo(), matrix.getX());
}
int main() {
    setlocale(LC_ALL, "Russian");
    Matrix<double> matrix(5, 3);
	matrix.fillRandom(10);
    cout << matrix << endl<<endl;
	MyVector<double> result = matrix.algo();
	cout << endl<<"Матрица после решения:" << endl;
    cout << matrix << endl<<endl;
	cout << "Начальный x: " << matrix.getX()<<endl;
	cout << "Полученный newX: " << result << endl;
	cout << "Погрешность: " << scientific << findDeltasist(result, matrix.getX()) << fixed << endl;
}