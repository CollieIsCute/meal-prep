#include "CSV-header/csv.h"
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

class Calendar {
	std::map<date, people> datesPeople;
	std::map<person, dates> peopleDates;
	std::string removeCharEverywhere(std::string s, char target);
	std::string makeMonthAndDateTwoDigits(std::string date);
	void writeMap(std::string filename,
				  const std::map<std::string, std::vector<std::string>>& datesPeopleOrPeopleDates);

public:
	Calendar() = default;
	Calendar(const Calendar& _cal) = default;
	Calendar(Calendar&& _cal) = delete;
	void updatePeopleDates(const std::string& name, std::string rawDates);
	void updateDatesPeopleFromPeopleDates();
	void updatePeopleDatesFromDatesPeople();
	void reducePeopleToLimit();
	int getSomeoneDatesNum(std::string name);
	int getSomedatePersonNum(std::string date);
	void writeFiles(std::string filename1, std::string filename2);
};

int prompForInputInt(std::string msg);
std::string prompForInputString(std::string msg);

const int DAILY_WORKING_PEOPLE = prompForInputInt("請輸入每日值日生數量： ");
const int NAME = prompForInputInt("請輸入姓名所在的欄數（從最左欄訂為0開始數）： ");
const int DATE = prompForInputInt("請輸入日期所在的欄數（從最左欄訂為0開始數）： ");

// TODO 可能是讀 csv 檔頭的問題
// TODO 移除重複填寫的資料
int main() {
	CSVReader reader(prompForInputString("請輸入檔案名稱： "));
	Calendar attendCal;
	std::string tempDate;

	for(int i = 1; i < reader.getRowNum(); i++)
		attendCal.updatePeopleDates(reader.getCell(i, NAME), reader.getCell(i, DATE));
	attendCal.updateDatesPeopleFromPeopleDates();

	Calendar workCal(attendCal);
	workCal.reducePeopleToLimit();

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

void Calendar::reducePeopleToLimit() {
	std::random_device rd;
	std::mt19937 gen(rd());
	for(auto& element : datesPeople) {
		people& people = element.second;
		while(people.size() > DAILY_WORKING_PEOPLE) {
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

int prompForInputInt(std::string msg) {
	int ret;
	std::cout << msg;
	std::cin >> ret;
	return ret;
}

std::string prompForInputString(std::string msg) {
	std::string ret;
	std::cout << msg;
	std::cin >> ret;
	return ret;
}