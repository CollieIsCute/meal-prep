#include "csv.h"

CSVReader::CSVReader() = default;
CSVReader::CSVReader( std::string filename ) : fin( filename ) {
	while ( !fin.eof() )
		table.push_back( getParsedLine() );
}

std::vector< std::string > CSVReader::getParsedLine() {
	std::string plainLine;
	getline( fin, plainLine );
	std::istringstream lineStream( plainLine );
	std::vector< std::string > ret;
	std::string cell;
	while ( lineStream ) {
		if ( lineStream.peek() == '"' ) {
			char trash;
			lineStream >> trash;
			getline( lineStream, cell, '"' );
		}
		else {
			getline( lineStream, cell, ',' );
		}
		std::cout << cell << "- -";
		ret.push_back( cell );
	}
	return ret;
}

std::vector< std::string > CSVReader::getRow( int rowNum ) {
	return table.at( rowNum );
}

std::string CSVReader::getCell( int rowNum, int colNum ) {
	return table.at( rowNum ).at( colNum );
}