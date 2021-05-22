#include "csv.h"
#include <iostream>
#include <string_view>

CSVReader::CSVReader() = default;
CSVReader::CSVReader( std::string filename ) : fin( filename ) {
	std::string test;
	while ( !fin.eof() ) {
		std::getline( fin, test );
		std::cout << test << std::endl;
	}
}

CSVReader::getParsedLine(){
	std::string_view test;
	getline(fin, test);
}