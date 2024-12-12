#include <iostream>
#include "Bin.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	Bin x;
	int a;
	cout << "Номера заданий:\n1 2 3 4 5 6\nВыберите номер задания:";
	cin >> a;
	switch (a)
	{
	case 1:
	{
		x.Rfile("x.bin", 10, 0, 10);
		x.Rfile1("x.bin", "y.txt");
		break;
	}
	case 2:
	{
		cout << "Введите размерность матрицы (n):" << endl;
		int n;
		cin >> n;
		x.Rfile("x.bin", 100, 0, 100);
		x.copyToMatrix("x.bin", n);
		break;
	}
	case 3:
	{
		x.Toys("x.bin");
		x.Toys1("x.bin");
		break;
	}
	case 4:
	{
		x.MinMax("xy.txt", 10, 0, 100);
		x.MinMax1("xy.txt");
		break;
	}
	case 5:
	{
		x.ChetEl("xy.txt", 2, 7, 5, 1, 10);
		x.ChetEl1("xy.txt");
		break;
	}
	case 6:
	{
		x.LatLine("xyz.txt", "y.txt");
		break;
	}
	default:
	{
		cout << "Неверное действие." << endl;
		break;
	}
	}
}