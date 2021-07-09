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
	std::string makeMonthAndDateTwoDigits(std::string date);

public:
	Calendar() = default;
	Calendar(const Calendar& _cal) = default;
	Calendar(Calendar&& _cal) = delete;
	void updatePeopleDates(const std::string& name, std::string rawDates);
	void updateDatesPeopleFromPeopleDates();
	void updatePeopleDatesFromDatesPeople();
	void reducePeopleToLimit(const int limit);
	void writeFiles(std::string filename1, std::string filename2);
	void print();
};

int main() {
	CSVReader reader("input.csv");
	Calendar attendCal;
	std::string tempDate;

	for(int i = 1; i < reader.getRowNum(); i++)
		attendCal.updatePeopleDates(reader.getCell(i, NAME), reader.getCell(i, DATE));
	attendCal.updateDatesPeopleFromPeopleDates();

	Calendar workCal(attendCal);
	workCal.reducePeopleToLimit(DAILY_WORKING_PEOPLE);

	workCal.writeFiles("work1.csv", "work2.csv");
	attendCal.writeFiles("attend1.csv", "attend2.csv");
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

std::string Calendar::makeMonthAndDateTwoDigits(std::string date) {
	std::istringstream d(date);
	std::string ret = "", temp;

	std::getline(d, temp, '/');
	ret += temp.size() == 2 ? temp : "0" + temp;
	ret += "/";
	std::getline(d, temp, '/');
	ret += temp.size() == 2 ? temp : "0" + temp;
	return ret;
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

void Calendar::reducePeopleToLimit(const int limit) {
	// TODO 儘量讓每個人工作的天數一樣多
	std::random_device rd;
	std::mt19937 gen(rd());
	for(auto& element : datesPeople) {
		dates& dates = element.second;
		while(dates.size() > limit) {
			dates.erase(dates.begin() + gen() % dates.size());
		}
	}
	updatePeopleDatesFromDatesPeople();
}

void Calendar::writeFiles(std::string filename1, std::string filename2) {
	CSVWriter nameAndDates(filename1), dateAndNames(filename2);
	// TODO :拆分兩個for loop 為 function "gen_peopleDates()" 之類的，或用 lamda
	for(auto& row : peopleDates) {
		std::vector<std::string> rowForWrite;
		rowForWrite.push_back(row.first);
		for(auto& date : row.second)
			rowForWrite.push_back(date);
		nameAndDates.pushRow(rowForWrite);
	}
	nameAndDates.writeFile();

	for(auto& row : datesPeople) {
		std::vector<std::string> rowForWrite;
		rowForWrite.push_back(row.first);
		for(auto& date : row.second)
			rowForWrite.push_back(date);
		dateAndNames.pushRow(rowForWrite);
	}
	dateAndNames.writeFile();
}

void Calendar::print() {

	// for debugging

	/*for(auto& element : peopleDates) { //uncomment, and It can be called to show peopleDates
		std::cout << element.first << " ";
		for(auto& date : element.second) {
			std::cout << date << " ";
		}
		std::cout << std::endl;
	}*/

	/*for(auto& element : datesPeople) { //uncomment, and It can be called to show datesPeople
		std::cout << element.first << " ";
		for(auto& name : element.second) {
			std::cout << name << " ";
		}
		std::cout << std::endl;
	}*/
}