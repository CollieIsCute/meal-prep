/*---------------------------------------
Maker: Meng-Shr,Tsai (46)
date:2020/7/9
---------------------------------------*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <list>
 
using PersonName = std::string;
using Today = std::string;
using attendDates = std::vector<std::string>;
using workingDates = std::vector<std::string>;
using PeopleAndAttends = std::map<PersonName, attendDates>;
using PeopleAndWorks = std::map<PersonName, workingDates>;
using DatesAndWorkingPeople = std::map<Today, class Group>;
const int DAILY_WORKING_PEOPLE = 3; // number of people of preparing meals

class Group
{
private:
    std::list<PersonName> people;

public:
    Group() = default;
    void add(PersonName name);
    void del(PersonName name);
};

class Calendar
{
private:
    DatesAndWorkingPeople datesPeople;

public:
    Calendar() = default;
    Calendar(std::ifstream ifs);
    Calendar(Calendar &&_cal);
    Calendar(std::string_view filename);
    void erase(const Today &today);
    Group &operator[](const Today &today);
    const Group &operator[](const Today &today) const;
};

int main()
{
    Calendar cal("input.csv");
}

Calendar::Calendar(std::ifstream ifs) {
    if(!ifs.is_open())
        throw std::runtime_error("File could not open!");
    
    // Do what you want.
    // Parse the csv?
}

Calendar::Calendar(std::string_view filename) : Calendar(std::ifstream(filename.data(), std::ifstream::in)) {
    std::cout << "input file '" << filename << "' opened.\n";
}

Calendar::Calendar(Calendar && _cal){
    datesPeople.swap(_cal.datesPeople);
}

void Calendar::erase(const Today &today) {
    datesPeople.erase(today);
}

Group &Calendar::operator[](const Today& today){
    return datesPeople[today];
}

const Group &Calendar::operator[](const Today &today) const{
    return datesPeople.at(today);
}

void Group::add(PersonName name)
{
    if (std::find(people.begin(), people.end(), name) == people.end())
        people.push_back(name);
}

void Group::del(PersonName name)
{
    auto index = std::find(people.begin(), people.end(), name);
    if (index != people.end())
        people.erase(index);
}