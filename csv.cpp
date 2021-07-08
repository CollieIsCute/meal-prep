#include "csv.h"

CSVReader::CSVReader(const std::string filename) : fin(filename) {
	while(!fin.eof())
		table.push_back(getParsedLine());
}

std::vector<std::string> CSVReader::getParsedLine() {
	std::string plainLine;
	getline(fin >> std::ws, plainLine);
	std::istringstream lineStream(plainLine);
	std::vector<std::string> ret;

	while(!lineStream.eof()) {
		std::string cell;
		if(lineStream.peek() == '"') {
			char trash;
			std::string alsoTrash;
			getline(lineStream >> trash, cell, '"');
			getline(lineStream, alsoTrash, ',');
		}
		else {
			getline(lineStream >> std::ws, cell, ',');
		}
		if(find(cell.begin(), cell.end(), '\n') != cell.end())
			std::cout << "there is a '\n' \n";
		ret.push_back(cell);
	}
	return ret;
}

std::vector<std::string> CSVReader::getRow(int rowNum) {
	return table.at(rowNum);
}

std::vector<std::string> CSVReader::getCol(int colNum) {
	std::vector<std::string> ret;
	for(auto it : table)
		ret.push_back(it.at(colNum));
	return ret;
}

std::string CSVReader::getCell(int rowNum, int colNum) {
	return table.at(rowNum).at(colNum);
}

int CSVReader::getRowNum() {
	return table.size();
}

int CSVReader::getColNum(int rowNum) {
	return table.at(rowNum).size();
}

CSVWriter::CSVWriter(const std::string& filename) : fout(filename) {}

void CSVWriter::pushRow(const std::vector<std::string>& row) {
	table.push_back(std::vector<std::string>());
	std::vector<std::string>& thisRow = table.at(table.size() - 1);
	for(auto& content : row)
		thisRow.push_back(content);
}

void CSVWriter::setRow(const int rowNum, const std::vector<std::string>& row) {
	table.at(rowNum).clear();
	for(auto& it : row)
		table.at(rowNum).push_back(it);
}

void CSVWriter::setCol(const int colNum, const std::vector<std::string>& col) {
	if(col.size() != table.size())
		throw std::invalid_argument("CSVWriter: argument size is not equal to CSVWriter::table.");
	for(int i = 0; i < table.size(); i++) {
		table.at(i).at(colNum) = col.at(colNum);
	}
}

void CSVWriter::pushCell(const int rowNum, std::string content) {
	table.at(rowNum).push_back(content);
}

void CSVWriter::setCell(const int rowNum, const int colNum, const std::string content) {
	table.at(rowNum).at(colNum) = content;
}

void CSVWriter::writeFile() {
	std::string line;
	for(auto& row : table) {
		line = produceLine(row);
		fout << line << std::endl;
	}
}

std::string CSVWriter::produceLine(const std::vector<std::string>& row) {
	std::string rawLine = "";
	for(auto& it : row) {
		if(!rawLine.empty())
			rawLine += ",";
		if(it.find(',') != std::string::npos)
			rawLine = "\"" + it + "\"";
		else
			rawLine += it;
	}
	return rawLine;
}