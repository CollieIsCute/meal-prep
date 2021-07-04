#include "csv.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

using person = std::string;
using people = std::vector<person>;
using date = std::string;
using dates = std::vector<date>;
const int DAILY_WORKING_PEOPLE = 3;
const int NAME = 1, DATE = 6;

class Calendar {
	std::map<date, people> datesPeople;
	std::map<person, dates> peopleDates;
	std::string removeCharEverywhere(std::string s, char target);

public:
	Calendar() = default;
	Calendar(Calendar&& _cal) = default;
	void addNameDates(const std::string name, std::string rawDates);
};

int main() {
	CSVReader reader("input.csv");
	Calendar workCal, attendCal;

	for(int i = 1; i < reader.getRowNum(); i++) {
		std::cout << reader.getCell(i, NAME) << "\t" << reader.getCell(i, DATE) << std::endl;
		attendCal.addNameDates(reader.getCell(i, NAME), reader.getCell(i, DATE));
	}

	// TODO: and update datesPeople in attendCal
	// TODO: make workCal (select people or sth)
	// TODO: write workCal into output file
}

void Calendar::addNameDates(const std::string name, std::string rawDates) {
	dates dates;
	std::istringstream datesWithSpace(removeCharEverywhere(rawDates, ','));
	std::string temp;

	while(!datesWithSpace.eof()) {
		datesWithSpace >> temp;
		dates.push_back(temp);
	}

	peopleDates[name] = dates;
}

std::string Calendar::removeCharEverywhere(std::string s, char target) {
	while(find(s.begin(), s.end(), target) != s.end())
		s.erase(find(s.begin(), s.end(), target));
	return s;
}