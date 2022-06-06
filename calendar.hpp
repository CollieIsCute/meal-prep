#ifndef __CALENDAR_H__
#define __CALENDAR_H__

#include <map>
#include <string>
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
	void reducePeopleToLimit(const int daily_working_people);
	int getSomeoneDatesNum(std::string name);
	int getSomedatePersonNum(std::string date);
	void writeFiles(std::string filename1, std::string filename2);
};

#endif