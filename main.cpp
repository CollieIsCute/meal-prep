/*---------------------------------------
Maker: Meng-Shr,Tsai (46)
date:2020/7/9
---------------------------------------*/
#include "csv.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <string_view>
#include <vector>

using worker = std::string;
using workers = std::vector< std::string >;
using date = std::string;
using dates = std::vector< std::string >;
const int DAILY_WORKING_PEOPLE = 3;

class Group {
private:
	std::list< worker > people;

public:
	Group() = default;
	void add( worker name );
	void del( worker name );
};

class Calendar {
private:
	std::map< date, class Group > datesPeople;

public:
	Calendar() = default;
	Calendar( Calendar&& _cal );
	Calendar( std::string_view filename );
	void erase( const date& d );
	Group& operator[]( const date& d );
	const Group& operator[]( const date& d ) const;
};

int main() {
	CSVReader c( "input.csv" );
}

Calendar::Calendar( std::string_view filename ) {
	CSVReader r;
}

Calendar::Calendar( Calendar&& _cal ) {
	datesPeople.swap( _cal.datesPeople );
}

void Calendar::erase( const date& d ) {
	datesPeople.erase( d );
}

Group& Calendar::operator[]( const date& d ) {
	return datesPeople.at( d );
}

const Group& Calendar::operator[]( const date& d ) const {
	return datesPeople.at( d );
}

void Group::add( worker name ) {
	if ( std::find( people.begin(), people.end(), name ) == people.end() )
		people.push_back( name );
}

void Group::del( worker name ) {
	auto index = std::find( people.begin(), people.end(), name );
	if ( index != people.end() )
		people.erase( index );
}