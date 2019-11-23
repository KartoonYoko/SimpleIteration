#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include "../../oop/Classes/tryToMatrix.h"
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

//сравнивает два вектора. Size - размер векторов. Accuracy - допустимая точность для совпадения векторов.
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
			recAns[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i != j) {
					recAns[i] += prevAns[j] * bufMat[i][j];
				}
				else {
					recAns[i] += bufMat[i][j];
				}
			}
		}
	} while (!CompareTwoVectors(recAns, prevAns, n, 0.001));
	return recAns;
}



vector<double> MethodOfZeidel(const vector<vector<double>>& matrix, const int& n) {
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
			recAns[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i != j) {
					if (i > j) recAns[i] += recAns[j] * bufMat[i][j];
					else recAns[i] += prevAns[j] * bufMat[i][j];
				}
				else {
					recAns[i] += bufMat[i][j];
				}
			}
		}
		
	} while (!CompareTwoVectors(recAns, prevAns, n, 0.001));
	return recAns;
}



	void methodOfBlocking(const MyMatrix& matrix) {
		MyMatrix result(matrix.getRowCount(), matrix.getColCount());
		MyMatrix m(2, 2), n(2, 2), p(2, 2), q(2, 2);
		MyMatrix x(2, 2), v(2, 2), u(2, 2), y(2, 2);
		int i1 = 0, j1 = 0;

		for(int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++) {
				m(i, j) = matrix.getItem(i, j);
			}
		for (int i = 0; i < 2; i++)
			for (int j = 2; j < 4; j++) {
				n(i1, j1) = matrix.getItem(i, j);
				if (j1 == 1) {
					j1 = 0;
					if (i1 == 1) i1 = 0; else i1++;
				}
				else j1++;
			}
		i1 = 0; j1 = 0;
		for (int i = 2; i < 4; i++)
			for (int j = 0; j < 2; j++) {
				p(i1, j1) = matrix.getItem(i, j);
				if (j1 == 1) {
					j1 = 0;
					if (i1 == 1) i1 = 0; else i1++;
				}
				else j1++;
			}
		i1 = 0; j1 = 0;
		for (int i = 2; i < 4; i++)
			for (int j = 2; j < 4; j++) {
				q(i1, j1) = matrix.getItem(i, j);
				if (j1 == 1) {
					j1 = 0;
					if (i1 == 1) i1 = 0; else i1++;
				}
				else j1++;
			}
		
		
		x = (m - n * (q.invertMatrix()) * p);
		x = x.invertMatrix();
		
		v = (q - (p * m.invertMatrix()) * n);
		v = v.invertMatrix();
		
		u = (v * -1) * p * m.invertMatrix();
		
		y = (x * -1) * n * q.invertMatrix();
		
		cout << "X:" << endl;
		x.outputConsole();
		cout << endl;

		cout << "Y:" << endl;
		y.outputConsole();
		cout << endl;

		cout << "U:" << endl;
		u.outputConsole();
		cout << endl;

		cout << "V:" << endl;
		v.outputConsole();
		cout << endl;
		
		
	}

int main()
{

	const int n = 5;
	vector <vector<double>> matrix(n, vector<double>(n + 1, 1));
	vector <vector<double>> nevyaz(n, vector<double>(n + 1, 1));
	vector<double> answer(n);
	double buf, buf2;
	double eps = 1 * pow(10, -2);



	//Описание матрицы
	{
		matrix[0][1] = 6;
		matrix[1][1] = 25;
		matrix[2][1] = -1;
		matrix[3][1] = 5;
		matrix[4][1] = 8;
		matrix[0][2] = 5;
		matrix[1][2] = -9;
		matrix[2][2] = 24;
		matrix[3][2] = -6;
		matrix[4][2] = -7;
		matrix[0][3] = 1;
		matrix[1][3] = -6;
		matrix[2][3] = 4;
		matrix[3][3] = 33;
		matrix[4][3] = 8;
		matrix[0][4] = -2;
		matrix[1][4] = 0;
		matrix[2][4] = -9;
		matrix[3][4] = 9;
		matrix[4][4] = 38;
		matrix[0][0] = 25;
		matrix[1][0] = 3;
		matrix[2][0] = -2;
		matrix[3][0] = 2;
		matrix[4][0] = -5;

		matrix[0][5] = 35;
		matrix[1][5] = 26;
		matrix[2][5] = 48;
		matrix[3][5] = 86;
		matrix[4][5] = 42;
	}

	outm(matrix, n);

	cout << "________________________Methof of iteration_________________________" << endl;
	{
		answer = MethodOfIteration(matrix, n);
		cout << endl << answer[0] << " " << answer[1] << " " << answer[2] << " " << answer[3] << " " << answer[4] << endl;

		nevyaz = matrix;
		for (int i = 0; i < n; i++) {
			buf = 0;
			for (int j = 0; j < n; j++) {
				buf += nevyaz[i][j] * answer[j];
			}
			if (abs(nevyaz[i][n] - buf) > eps) cout << "Not required accuracy in line " << i << endl;
			else cout << "There is required accuracy in line " << i << endl;
		}

	}
	

	cout << "________________________Methof of Zeidel_________________________" << endl;
	{
		answer = MethodOfZeidel(matrix, n);
		cout << endl << answer[0] << " " << answer[1] << " " << answer[2] << " " << answer[3] << " " << answer[4] << endl;

		nevyaz = matrix;
		for (int i = 0; i < n; i++) {
			buf = 0;
			for (int j = 0; j < n; j++) {
				buf += nevyaz[i][j] * answer[j];
			}
			if (abs(nevyaz[i][n] - buf) > eps) cout << "Not required accuracy in line " << i << endl;
			else cout << "There is required accuracy in line " << i << endl;
		}

	}


	cout << "________________________Methof of blocking_________________________" << endl;
	{
		MyMatrix a(4, 4);

		//Описание матрицы
		{
			a[0] = { -1,  2,  2, -1 };
			a[1] = { -2,  3,  4, -3 };
			a[2] = {  2, -3, -3,  5 };
			a[3] = { -2,  2,  4, -3 };
			/*
			a(0, 0) = -1;	a(0, 1) = 2;	a(0, 2) = 2;	a(0, 3) = -1;
			a(1, 0) = -2;	a(1, 1) = 3;	a(1, 2) = 4;	a(1, 3) = -3;
			a(2, 0) = 2;	a(2, 1) = -3;	a(2, 2) = -3;	a(2, 3) = 5;
			a(3, 0) = -2;	a(3, 1) = 2;	a(3, 2) = 4;	a(3, 3) = -3;
			*/
		}

		
		cout << "Matrix A: " << endl;
		a.outputConsole();
		cout << endl;


		MyMatrix invert(4, 4);
		invert = a.invertMatrix();
		cout << "Invert: " << endl;
		invert.outputConsole();
		cout << endl;

		methodOfBlocking(a);
		
	
	}
}
