#pragma once
#define BIN_H
#include <string>

using namespace std;

struct Toy
{
	string name;
	double price;
	int age_from;
	int age_to;
};

class Bin
{
public:
	static void Rfile(const std::string& filename, size_t count, int min, int max);
	
	static void Rfile1(const string& inputFile, const string& outputFile);
	
	static void copyToMatrix(const string& inputFile, int n);

	static void Toys(const string& filename);

	static void Toys1(const string& filename);
	
	static void MinMax(const string& filename, size_t size, int minValue, int maxValue);

	static void MinMax1(const string& filename);

	static void ChetEl(const string& filename, size_t minCols, size_t maxCols, size_t rows, int minValue, int maxValue);

	static void ChetEl1(const string& filename);

	static bool LatLine1(const string& str);

	static void LatLine(const string& inputFilename, const string& outputFilename);
};

