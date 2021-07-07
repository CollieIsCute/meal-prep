#include "csv.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <random>
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
	Calendar(Calendar& _cal);
	Calendar(Calendar&& _cal) = delete;
	void updatePeopleDates(const std::string name, std::string rawDates);
	void updateDatesPeopleFromPeopleDates();
	void updatePeopleDatesFromDatesPeople();
	void reducePeopleToLimit(const int limit);
	void print();
};

int main() {
	CSVReader reader("input.csv");
	Calendar attendCal;

	for(int i = 1; i < reader.getRowNum(); i++) {
		std::cout << reader.getCell(i, NAME) << "\t" << reader.getCell(i, DATE) << std::endl;
		attendCal.updatePeopleDates(reader.getCell(i, NAME), reader.getCell(i, DATE));
	}
	attendCal.updateDatesPeopleFromPeopleDates();

	Calendar workCal(attendCal);
	workCal.reducePeopleToLimit(DAILY_WORKING_PEOPLE);
	// workCal.print();	//just for debugging
	// TODO: check the output is correct
	// TODO: write workCal to file
}

Calendar::Calendar(Calendar& _cal) {
	datesPeople = std::map<date, people>(_cal.datesPeople);
	peopleDates = std::map<person, dates>(_cal.peopleDates);
}

void Calendar::updatePeopleDates(const std::string name, std::string rawDates) {
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

void Calendar::updateDatesPeopleFromPeopleDates() {
	datesPeople.clear();
	for(auto& element : peopleDates)
		for(auto date : element.second)
			datesPeople[date].push_back(element.first);
}

void Calendar::updatePeopleDatesFromDatesPeople() {
	peopleDates.clear();
	for(auto& element : datesPeople) {
		for(auto name : element.second) {
			peopleDates[name].push_back(element.first);
		}
	}
}

void Calendar::reducePeopleToLimit(const int limit) {
	std::random_device rd;
	std::mt19937 gen(rd());
	for(auto& element : datesPeople) {
		dates& dates = element.second;
		while(dates.size() > limit) {
			dates.erase(dates.begin() + gen() % dates.size());
		}
		std::cout << dates.size() << std::endl;
	}
	updatePeopleDatesFromDatesPeople();
}

void Calendar::print() {
	for(auto& element : peopleDates) {
		std::cout << element.first << " ";
		for(auto& date : element.second) {
			std::cout << date << " ";
		}
		std::cout << std::endl;
	}
}