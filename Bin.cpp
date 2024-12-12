#include "Bin.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <fstream>
#include <random>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

void Bin::Rfile(const std::string& filename, size_t count, int min, int max)
{
	ofstream outFile(filename, ios::binary);
	if (!outFile)
	{
		cerr << "������ �������� ����� ��� ������: " << filename << endl;
		return;
	}
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(min, max);

	for (size_t i = 0; i < count; ++i)
	{
		int num = dis(gen);
		outFile.write(reinterpret_cast<char*>(&num), sizeof(num));
	}
	cout << endl;
	outFile.close();
	cout << "���� " << filename << " ������� �������." << endl;
}

void Bin::Rfile1(const string& inputFile, const string& outputFile)
{
	ifstream inFile(inputFile, ios::binary);
	if (!inFile)
	{
		cerr << "������ �������� �������� �����: " << inputFile << endl;
		return;
	}

	int count = 0;
	int num;
	cout << "������ �� ����� ��������������� ��������: ";
	while (inFile.read(reinterpret_cast<char*>(&num), sizeof(num)))
	{
		cout << " " << num;
		double x = sqrt(num);
		if (x - round(x) == 0) // ��������� �� ������� 
		{
			if ((int)x % 2 != 0) // �������� �� ������������� �����
			{
				count++;
			}
		}
	}
	cout << endl << "���������� ��������� �������� �����:" << count << endl;
	inFile.close();
}

void Bin::copyToMatrix(const string& inputFile, int n)
{
	ifstream inFile(inputFile, ios::binary); // ��������� ���� ��� ������ � �������� ������
	if (!inFile) { // ���������, ������� �� ������� ����
		cerr << "������ �������� �����: " << inputFile << endl;
		return;
	}

	vector<vector<int>> matrix(n, vector<int>(n, 0)); // ������� ������� n x n, ����������� ������
	int number;
	int index = 0; // ������ ��� ���������� �������

	// ������ ����� �� ����� � ��������� �������
	while (inFile.read(reinterpret_cast<char*>(&number), sizeof(number)) && index < n * n)
	{
		matrix[index / n][index % n] = number; // ��������� ������� ���������� �� �����
		index++;
	}

	int count = 0;
	int max = 0;
	int c;
	cout << "�������:" << endl;
	for (int i = 0; i < n; i++)// ������ �� �������
	{
		for (int j = 0; j < n; j++) // ������ �� ��������� ������
		{
			if (i + j != 0)
			{
				if (matrix[i][j] % (i + j) == 0)
				{
					count += 1;
					cout << "!";
				}
			}
			cout << matrix[i][j] << " ";// ����� ��������
		}
		cout << endl << endl;
		if (count > max)
		{
			max = count;
			c = i + 1;
		}
		count = 0;
	}
	cout << "����� ������ � ���������� ���-�� ���������� ���������: " << c << endl;
}

void Bin::Toys(const string& filename)
{
	ofstream file(filename, ios::binary);
	if (!file) {
		cerr << "�� ������� ������� ���� ��� ������." << endl;
		return;
	}

	// ������ �������
	Toy toys[] = {
		{"������", 500.0, 1, 3},
		{"�����������", 1500.0, 2, 5},
		{"������ �������", 700.0, 0, 4},
		{"�������", 1200.0, 2, 8},
		{"�����", 1300.0, 0, 8},
		{"LEGO", 2500.0, 4, 10}
	};

	for (const auto& toy : toys) {
		cout << "��������: " << toy.name << ", ����: " << toy.price << ", �������: " << toy.age_from << "-" << toy.age_to << endl;
		file.write(reinterpret_cast<const char*>(&toy), sizeof(Toy));
	}

	file.close();
}

void Bin::Toys1(const string& filename)
{
	ifstream file(filename, ios::binary);
	if (!file)
	{
		cerr << "�� ������� ������� ���� ��� ������." << endl;
		return;
	}

	Toy x;
	Toy y;
	x.price = 0;

	while (file.read(reinterpret_cast<char*>(&y), sizeof(Toy)))
	{
		// ��������� ���������� �������
		if (y.age_to < 4)
		{ // ���� ������� ������������� ��� ����� �� 4 ���
			// ���������� ����
			if (y.price > x.price)
			{
				x = y;
			}
		}
	}

	if (x.price > 0)
	{
		cout << "����� ������� ������� ��� ����� �� ������� ���: " << x.name << " ����: " << x.price << " ������" << endl;
	}
	else
	{
		cout << "��� ������� ��� ����� �� ������� ���." << endl;
	}
	file.close();
}

void Bin::MinMax(const string& filename, size_t size, int minValue, int maxValue)
{
	ofstream outFile(filename); // ��������� ����� �� ���������
	if (!outFile)
	{
		cerr << "������: ���������� ������� ���� " << filename << endl;
		return;
	}

	srand(static_cast<unsigned>(time(nullptr))); // ������������� ���������� ��������� �����

	for (size_t i = 0; i < size; ++i)
	{
		int value = minValue + rand() % (maxValue - minValue + 1);
		outFile << value << "\n"; // ���������� ����� � ��������� �������, �������� ������ ����� ������
	}

	outFile.close();
	cout << "���� " << filename << " �������� " << size << " ���������� �������.\n";
}

void Bin::MinMax1(const string& filename)
{
	ifstream inFile(filename); // ��������� ����� �� ���������
	if (!inFile)
	{
		cerr << "������: ���������� ������� ���� " << filename << endl;
		return;
	}

	vector<int> values;
	int value;
	while (inFile >> value)
	{ // ������ ����� �� ���������� �����
		values.push_back(value);
	}

	inFile.close();

	// ����� ������
	cout << "������ �� �����:" << endl;
	for (size_t i = 0; i < values.size(); ++i)
	{
		cout << values[i] << " ";
	}
	cout << endl;

	float MinMax = (*min_element(begin(values), end(values)) + *max_element(begin(values), end(values))) / 2.;

	cout << "����������� �������: " << *min_element(begin(values), end(values)) << endl;
	cout << "������������ �������: " << *max_element(begin(values), end(values)) << endl;
	cout << "������� ��������������:" << MinMax << endl;
}

void Bin::ChetEl(const string& filename, size_t minCols, size_t maxCols, size_t rows, int minValue, int maxValue)
{
	ofstream outFile(filename);
	if (!outFile)
	{
		cerr << "������: ���������� ������� ���� " << filename << endl;
		return;
	}

	srand(static_cast<unsigned>(time(nullptr))); // ������������� ���������� ��������� �����

	for (size_t i = 0; i < rows; ++i)
	{
		size_t cols = minCols + rand() % (maxCols - minCols + 1); // ��������� ���������� ����� � ������
		for (size_t j = 0; j < cols; ++j)
		{
			int value = minValue + rand() % (maxValue - minValue + 1); // ��������� �����
			outFile << value;
			if (j < cols - 1)
			{
				outFile << " "; // ����������� ����� �������
			}
		}
		outFile << endl; // ������� �� ����� ������
	}

	outFile.close();
	cout << "���� " << filename << " ������� �������� ���������� ������� � ���������� ����������� ��������.\n";
}

void Bin::ChetEl1(const string& filename)
{

	ifstream inFile(filename);
	if (!inFile)
	{
		cerr << "������: �� ������� ������� ���� " << filename << endl;
		return;
	}

	long long p = 1; // ��������� �������� ��� ������������
	bool hasMultiples = false; // ���� ������� ���������, ������� k

	string line;
	while (getline(inFile, line))
	{
		stringstream ss(line);
		int value;
		while (ss >> value)
		{
			cout << value << " ";
			if (value % 2 == 0)
			{
				p *= value;
				hasMultiples = true;
			}
		}
		cout << endl;
	}

	inFile.close();

	if (hasMultiples)
	{
		cout << "������������ ������ ���������: " << p << endl;
	}
	else
	{
		cout << "��� ������ ��������� � �����." << endl;
	}
}

bool Bin::LatLine1(const string& str)
{
	for (char ch : str)
	{
		// ���������, �������� �� ������ ��������� ������
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		{
			return true;  // ���� ���� �� ���� ���������� �����
		}
	}
	return false;  // ���� ��� ��������� ����
}

// ������� ��� ��������� �����
void Bin::LatLine(const string& inputFilename, const string& outputFilename)
{
	// ��������� �������� ����
	ifstream inFile(inputFilename);
	if (!inFile)
	{
		cerr << "������: ���������� ������� ���� " << inputFilename << endl;
		return;
	}

	// ��������� �������� ���� ��� ������
	ofstream outFile(outputFilename);
	if (!outFile)
	{
		cerr << "������: ���������� ������� ���� " << outputFilename << endl;
		return;
	}

	string line;
	while (getline(inFile, line))
	{
		// ���� ������ �� �������� ��������� ����, ���������� � � ����� ����
		if (!LatLine1(line))
		{
			outFile << line << endl;  // ���������� ������ � ����� ����
		}
	}

	inFile.close();  // ��������� ������� ����
	outFile.close();  // ��������� �������� ����
	cout << "������ ��� ��������� ���� ���������� � ���� " << outputFilename << endl;
}
