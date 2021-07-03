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

using person = std::string;
using people = std::vector< person >;
using date = std::string;
using dates = std::vector< date >;
const int DAILY_WORKING_PEOPLE = 3;
const int NAME = 1, DATE = 7;

class Calendar {
	std::map< date, people > datesPeople;
	std::map< person, dates > peopleDates;

public:
	Calendar() = default;
	Calendar( Calendar&& _cal ) = default;
	void erase( const date& d );
};

int main() {
	CSVReader reader( "input.csv" );
	Calendar workCal, attendCal;
	
}

void Calendar::erase( const date& d ) {
	datesPeople.erase( d );
}