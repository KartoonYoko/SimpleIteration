// SimpleIterartion.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;



void outm(vector<vector<double>> matrix, int n) {
	cout.setf(ios::fixed);
	const unsigned accuracy = 2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n + 1; j++) {
			if (j == n)
				cout << " |  " << setprecision(accuracy) << matrix[i][j] << endl;
			else
				if (matrix[i][j] < 0)
					cout << "  " << setprecision(accuracy) << matrix[i][j];
				else
					cout << "   " << setprecision(accuracy) << matrix[i][j];
		}
	}
	cout << "-------------------------------------" << endl;
	cout.unsetf(ios::fixed);
}

bool CompareTwoVectors(const vector<double>& vec1, const vector<double>& vec2, const int& size, const double& accuracy) {
	bool answer = false;
	for (int i = 0; i < size; i++) {
		if (abs(vec1[i] - vec2[i]) < accuracy) {
			answer = true;
		}
		else
		{
			answer = false;
			break;
		}
	}
	return answer;
}

vector<double> MethodOfIteration(const vector<vector<double>>& matrix, const int& n) {
	vector<double> recAns(n, 0);
	vector<double> prevAns(n, 0);
	vector <vector<double>> bufMat(n, vector<double>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j)
				bufMat[i][j] = -matrix[i][j] / matrix[i][i];
			else
				bufMat[i][j] = matrix[i][n] / matrix[i][i];
		}
	}
	do {
		prevAns = recAns;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				double sum = 0;
				if (i != j) {
					recAns[i] += prevAns[j] * bufMat[i][j];
				}
				else {
					recAns[i] += bufMat[i][j];
				}
			}
		}
	} while (CompareTwoVectors(recAns, prevAns, n, 0.001));
	return recAns;
}


int main()
{
	matrix[0][1] = -0.66;
	matrix[1][1] = -0.59;
	matrix[2][1] = -0.8;
	matrix[3][1] = -0.97;
	matrix[4][1] = 0.33;
	matrix[0][2] = 0.46;
	matrix[1][2] = -0.46;
	matrix[2][2] = -0.24;
	matrix[3][2] = -0.46;
	matrix[4][2] = -0.28;
	matrix[0][3] = 0.62;
	matrix[1][3] = 0.63;
	matrix[2][3] = -0.51;
	matrix[3][3] = 0.27;
	matrix[4][3] = -0.94;
	matrix[0][4] = 0.83;
	matrix[1][4] = -0.68;
	matrix[2][4] = 0.98;
	matrix[3][4] = -0.45;
	matrix[4][4] = -0.92;
	matrix[0][0] = -0.02;
	matrix[1][0] = 0.52;
	matrix[2][0] = 0.28;
	matrix[3][0] = 0.38;
	matrix[4][0] = 0.17;

	matrix[0][5] = 0.24;
	matrix[1][5] = -0.98;
	matrix[2][5] = -0.94;
	matrix[3][5] = -0.84;
	matrix[4][5] = -0.79;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
