#include "calendar.hpp"
#include "CSV-header/csv.h"

#include <sstream>
#include <random>
#include <iomanip>

namespace{
std::string two_digits(const int number);
}

void Calendar::updatePeopleDates(const std::string& name, std::string rawDates) {
	dates dates;
	std::istringstream datesWithSpace(removeCharEverywhere(rawDates, ','));
	std::string temp;
	while(!datesWithSpace.eof()) {
		datesWithSpace >> temp;
		temp = makeMonthAndDateTwoDigits(temp);
		dates.push_back(temp);
	}

	peopleDates[name] = dates;
}

std::string Calendar::removeCharEverywhere(std::string s, char target) {
	std::string ret = "";
	for(char it : s)
		if(it != target)
			ret += it;
	return ret;
}

// expect MM/DDXXX format, which MM and DD can be one or two digits, and XXX can be zero or more non-digit charactors. ex. 11/17(三) or 9/9
std::string Calendar::makeMonthAndDateTwoDigits(std::string date) {
	std::istringstream d(date);
	int MM, DD;
	char split;
	std::string remain;
	d >> MM >> split >> DD;
	std::getline(d, remain);
	std::string ret = ::two_digits(MM) + split + ::two_digits(DD) + remain;
	return ret;
}

namespace{
std::string two_digits(const int number) {
	std::stringstream ss;
	ss << std::setw(2) << std::setfill('0') << number;
    return ss.str();
}
}

void Calendar::updateDatesPeopleFromPeopleDates() {
	datesPeople.clear();
	for(const auto& element : peopleDates)
		for(const auto& date : element.second)
			datesPeople[date].push_back(element.first);
}

void Calendar::updatePeopleDatesFromDatesPeople() {
	peopleDates.clear();
	for(const auto& element : datesPeople)
		for(const auto& name : element.second)
			peopleDates[name].push_back(element.first);
}

void Calendar::reducePeopleToLimit(const int daily_working_people) {
	std::random_device rd;
	std::mt19937 gen(rd());
	for(auto& element : datesPeople) {
		people& people = element.second;
		while(people.size() > daily_working_people) {
			int delIndex = gen() % people.size();
			for(int i = 0; i < people.size(); i++)
				if(getSomeoneDatesNum(people.at(i)) > getSomeoneDatesNum(people.at(delIndex)))
					delIndex = i;
			people.erase(people.begin() + delIndex);
			updatePeopleDatesFromDatesPeople();
		}
	}
}

int Calendar::getSomeoneDatesNum(std::string name) {
	for(const auto& elem : peopleDates)
		if(elem.first == name)
			return elem.second.size();
	throw std::overflow_error("not find in peopleDates!");
}

int Calendar::getSomedatePersonNum(std::string date) {
	for(const auto& elem : datesPeople)
		if(elem.first == date)
			return elem.second.size();
	throw std::overflow_error("not find in datesPeople!");
}

void Calendar::writeFiles(std::string filename1, std::string filename2) {
	writeMap(filename1, datesPeople);
	writeMap(filename2, peopleDates);
}

void Calendar::writeMap(std::string filename,
						const std::map<std::string, std::vector<std::string>>& datesPeopleOrPeopleDates) {
	CSVWriter fileWriter(filename);
	auto& table = datesPeopleOrPeopleDates;

	for(const auto& row : table) {
		std::vector<std::string> rowForWrite;
		rowForWrite.push_back(row.first);
		for(const auto& value : row.second)
			rowForWrite.push_back(value);
		fileWriter.pushRow(rowForWrite);
	}
	fileWriter.writeFile();
}