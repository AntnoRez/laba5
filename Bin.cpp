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
		cerr << "Ошибка открытия файла для записи: " << filename << endl;
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
	cout << "Файл " << filename << " успешно записан." << endl;
}

void Bin::Rfile1(const string& inputFile, const string& outputFile)
{
	ifstream inFile(inputFile, ios::binary);
	if (!inFile)
	{
		cerr << "Ошибка открытия входного файла: " << inputFile << endl;
		return;
	}

	int count = 0;
	int num;
	cout << "Чтение из файла сгенерированных значений: ";
	while (inFile.read(reinterpret_cast<char*>(&num), sizeof(num)))
	{
		cout << " " << num;
		double x = sqrt(num);
		if (x - round(x) == 0) // Провоерка на квадрат 
		{
			if ((int)x % 2 != 0) // Проверка на отрицалельное число
			{
				count++;
			}
		}
	}
	cout << endl << "Количество квадратов нечетных чисел:" << count << endl;
	inFile.close();
}

void Bin::copyToMatrix(const string& inputFile, int n)
{
	ifstream inFile(inputFile, ios::binary); // Открываем файл для чтения в бинарном режиме
	if (!inFile) { // Проверяем, удалось ли открыть файл
		cerr << "Ошибка открытия файла: " << inputFile << endl;
		return;
	}

	vector<vector<int>> matrix(n, vector<int>(n, 0)); // Создаем матрицу n x n, заполненную нулями
	int number;
	int index = 0; // Индекс для заполнения матрицы

	// Читаем числа из файла и заполняем матрицу
	while (inFile.read(reinterpret_cast<char*>(&number), sizeof(number)) && index < n * n)
	{
		matrix[index / n][index % n] = number; // Заполняем матрицу значениями из файла
		index++;
	}

	int count = 0;
	int max = 0;
	int c;
	cout << "Матрица:" << endl;
	for (int i = 0; i < n; i++)// Проход по строкам
	{
		for (int j = 0; j < n; j++) // Проход по элементам строки
		{
			if (i + j != 0)
			{
				if (matrix[i][j] % (i + j) == 0)
				{
					count += 1;
					cout << "!";
				}
			}
			cout << matrix[i][j] << " ";// Вывод элемента
		}
		cout << endl << endl;
		if (count > max)
		{
			max = count;
			c = i + 1;
		}
		count = 0;
	}
	cout << "Номер строки с наибольшим кол-ом подходящих элементов: " << c << endl;
}

void Bin::Toys(const string& filename)
{
	ofstream file(filename, ios::binary);
	if (!file) {
		cerr << "Не удалось открыть файл для записи." << endl;
		return;
	}

	// Пример игрушек
	Toy toys[] = {
		{"Кубики", 500.0, 1, 3},
		{"Конструктор", 1500.0, 2, 5},
		{"Мягкая игрушка", 700.0, 0, 4},
		{"Машинка", 1200.0, 2, 8},
		{"Кукла", 1300.0, 0, 8},
		{"LEGO", 2500.0, 4, 10}
	};

	for (const auto& toy : toys) {
		cout << "Название: " << toy.name << ", Цена: " << toy.price << ", Возраст: " << toy.age_from << "-" << toy.age_to << endl;
		file.write(reinterpret_cast<const char*>(&toy), sizeof(Toy));
	}

	file.close();
}

void Bin::Toys1(const string& filename)
{
	ifstream file(filename, ios::binary);
	if (!file)
	{
		cerr << "Не удалось открыть файл для чтения." << endl;
		return;
	}

	Toy x;
	Toy y;
	x.price = 0;

	while (file.read(reinterpret_cast<char*>(&y), sizeof(Toy)))
	{
		// Проверяем возрастные границы
		if (y.age_to < 4)
		{ // Если игрушка предназначена для детей до 4 лет
			// Сравниваем цены
			if (y.price > x.price)
			{
				x = y;
			}
		}
	}

	if (x.price > 0)
	{
		cout << "Самая дорогая игрушка для детей до четырех лет: " << x.name << " Цена: " << x.price << " рублей" << endl;
	}
	else
	{
		cout << "Нет игрушек для детей до четырех лет." << endl;
	}
	file.close();
}

void Bin::MinMax(const string& filename, size_t size, int minValue, int maxValue)
{
	ofstream outFile(filename); // Текстовый режим по умолчанию
	if (!outFile)
	{
		cerr << "Ошибка: невозможно открыть файл " << filename << endl;
		return;
	}

	srand(static_cast<unsigned>(time(nullptr))); // Инициализация генератора случайных чисел

	for (size_t i = 0; i < size; ++i)
	{
		int value = minValue + rand() % (maxValue - minValue + 1);
		outFile << value << "\n"; // Записываем число в текстовом формате, добавляя символ новой строки
	}

	outFile.close();
	cout << "Файл " << filename << " заполнен " << size << " случайными числами.\n";
}

void Bin::MinMax1(const string& filename)
{
	ifstream inFile(filename); // Текстовый режим по умолчанию
	if (!inFile)
	{
		cerr << "Ошибка: невозможно открыть файл " << filename << endl;
		return;
	}

	vector<int> values;
	int value;
	while (inFile >> value)
	{ // Чтение числа из текстового файла
		values.push_back(value);
	}

	inFile.close();

	// Вывод данных
	cout << "Чтение из файла:" << endl;
	for (size_t i = 0; i < values.size(); ++i)
	{
		cout << values[i] << " ";
	}
	cout << endl;

	float MinMax = (*min_element(begin(values), end(values)) + *max_element(begin(values), end(values))) / 2.;

	cout << "Минимальный элемент: " << *min_element(begin(values), end(values)) << endl;
	cout << "Максимальный элемент: " << *max_element(begin(values), end(values)) << endl;
	cout << "Среднее арифметичсекое:" << MinMax << endl;
}

void Bin::ChetEl(const string& filename, size_t minCols, size_t maxCols, size_t rows, int minValue, int maxValue)
{
	ofstream outFile(filename);
	if (!outFile)
	{
		cerr << "Ошибка: невозможно открыть файл " << filename << endl;
		return;
	}

	srand(static_cast<unsigned>(time(nullptr))); // Инициализация генератора случайных чисел

	for (size_t i = 0; i < rows; ++i)
	{
		size_t cols = minCols + rand() % (maxCols - minCols + 1); // Случайное количество чисел в строке
		for (size_t j = 0; j < cols; ++j)
		{
			int value = minValue + rand() % (maxValue - minValue + 1); // Случайное число
			outFile << value;
			if (j < cols - 1)
			{
				outFile << " "; // Разделитель между числами
			}
		}
		outFile << endl; // Переход на новую строку
	}

	outFile.close();
	cout << "Файл " << filename << " успешно заполнен случайными числами с переменным количеством столбцов.\n";
}

void Bin::ChetEl1(const string& filename)
{

	ifstream inFile(filename);
	if (!inFile)
	{
		cerr << "Ошибка: не удалось открыть файл " << filename << endl;
		return;
	}

	long long p = 1; // Начальное значение для произведения
	bool hasMultiples = false; // Флаг наличия элементов, кратных k

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
		cout << "Произведение ЧЕТНЫХ элементов: " << p << endl;
	}
	else
	{
		cout << "Нет ЧЕТНЫХ элементов в файле." << endl;
	}
}

bool Bin::LatLine1(const string& str)
{
	for (char ch : str)
	{
		// Проверяем, является ли символ латинской буквой
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		{
			return true;  // Если хотя бы одна латинсккая буква
		}
	}
	return false;  // Если нет латинских букв
}

// Функция для обработки файла
void Bin::LatLine(const string& inputFilename, const string& outputFilename)
{
	// Открываем исходный файл
	ifstream inFile(inputFilename);
	if (!inFile)
	{
		cerr << "Ошибка: невозможно открыть файл " << inputFilename << endl;
		return;
	}

	// Открываем выходной файл для записи
	ofstream outFile(outputFilename);
	if (!outFile)
	{
		cerr << "Ошибка: невозможно открыть файл " << outputFilename << endl;
		return;
	}

	string line;
	while (getline(inFile, line))
	{
		// Если строка не содержит латинских букв, записываем её в новый файл
		if (!LatLine1(line))
		{
			outFile << line << endl;  // Записываем строку в новый файл
		}
	}

	inFile.close();  // Закрываем входной файл
	outFile.close();  // Закрываем выходной файл
	cout << "Строки без латинских букв переписаны в файл " << outputFilename << endl;
}
