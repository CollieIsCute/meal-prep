#ifndef CSV_H
#define CSV_H
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class CSVReader {
	std::vector<std::vector<std::string>> table;
	std::ifstream fin;
	std::vector<std::string> getParsedLine();

public:
	CSVReader() = delete;
	CSVReader(const std::string filename);
	std::vector<std::string> getRow(int rowNum);
	std::vector<std::string> getCol(int colNum);
	std::string getCell(int rowNum, int colNum);
	int getRowNum();
	int getColNum(int rowNum);
};

class CSVWriter {
	std::vector<std::vector<std::string>> table;
	std::ofstream fout;
	std::string produceLine(const std::vector<std::string>& row);

public:
	CSVWriter() = delete;
	CSVWriter(const std::string& filename);
	void setRow(const int& rowNum,
				const std::vector<std::string>& row);  // setting functions only modify table, not write files.
	void setCol(const int& colNum, const std::vector<std::string>& col);
	void setCell(const int& rowNum, const int& colNum, const std::string& content);
	void writeFile();
};

#endif