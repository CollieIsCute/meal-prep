#ifndef CSV_H
#define CSV_H
#include <fstream>
#include <string>
#include <vector>

class CSVReader {
	std::vector< std::vector< std::string > > table;
	std::ifstream fin;
	std::vector< std::string > getParsedLine();
public:
	CSVReader();
	CSVReader( std::string filename );
	std::vector< std::string > getRow( int rowNum );
	std::string getCell( int rowNum, int ColNum );
};

#endif