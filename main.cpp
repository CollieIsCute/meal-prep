/*---------------------------------------
Maker: Meng-Shr,Tsai (46)
date:2020/7/9
modified date:2021/2/8
---------------------------------------*/
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<map>
#define DAILY_WORKING_PEOPLE 3// number of people of preparing meals
using namespace std;

typedef string NameOfPerson, Today;
typedef vector<string> attendDates, workingDates;
typedef map< NameOfPerson, attendDates> PeopleAndAttends;
typedef map< NameOfPerson, workingDates> PeopleAndWorks;
typedef map< Today, class Group> DatesAndWorkingPeople;

class Group{
private:
    vector<NameOfPerson> group;
public:
    Group(){}
    void addPerson(NameOfPerson name);
    void delPerson(NameOfPerson name);
    bool alreadyHas(NameOfPerson name);
};

class Calendar{
private:
    DatesAndWorkingPeople datesPeople;
public:
    Calendar(){}
    void addDateAndGroup(Today today, Group group);
    void delDateAndGroup(Today today, Group group);
    Group getGroupOfToday(Today today);
    bool DateExisted(Today today);
};

int main(){

}

void Group::addPerson(NameOfPerson name){
    if(!alreadyHas(name))
        group.push_back(name);
}