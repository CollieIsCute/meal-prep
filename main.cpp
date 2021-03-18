/*---------------------------------------
Maker: Meng-Shr,Tsai (46)
date:2020/7/9
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
    vector<NameOfPerson> people;
    int nameToGroupIndex(NameOfPerson name);
    bool alreadyHas(NameOfPerson name);
public:
    Group(){}
    void addPerson(NameOfPerson name);
    void delPerson(NameOfPerson name);
};

class Calendar{
private:
    DatesAndWorkingPeople datesPeople;
public:
    Calendar(){}
    void addDateAndGroup(Today today, Group &group);
    void delDateAndGroup(Today today, Group &group);
    Group getGroupOfToday(Today today);
    bool DateExisted(Today today);
};

void readFileAndSetCalendar(Calendar &calendar);
void setCalendar(ifstream &inputFile, Calendar &calendar);

int main(){
    Calendar cal;
    readFileAndSetCalendar(cal);
}

void readFileAndSetCalendar(Calendar &calendar){
    ifstream inputfile;
    string filename;
    cout<<"Please input the file name:\n";
    //cin>>filename;
    filename="input.csv";
    inputfile.open(filename);
    if(inputfile.is_open())
        cout<<"input file '"<<filename<<"' opened.\n";
    else{
        cout<<"input file '"<<filename<<"' open failed.\n";
        exit(0);
    }
    setCalendar(inputfile, calendar);
}

void setCalendar(ifstream &inputfile, Calendar &Calendar){
    cout<<"goto setCalendar\n";
    string test;
    ofstream outputFile;
    outputFile.open("output.csv");
    while(!inputfile.eof()){
        inputfile>>test;
        outputFile<<test<<",";
        cout<<test<<",";
    }
}

void Group::addPerson(NameOfPerson name){
    if(!alreadyHas(name))
        people.push_back(name);
}

void Group::delPerson(NameOfPerson name){
    if(alreadyHas(name)){
        int del = nameToGroupIndex(name);
        people.erase(people.begin()+del);
    }
}

int Group::nameToGroupIndex(NameOfPerson name){
    if(!alreadyHas(name)) return -1;
    for(int i = 0; i < people.size(); i++)
        if(people[i] == name) return i;
}

bool Group::alreadyHas(NameOfPerson name){
    for(int i = 0; i < people.size(); i++)
        if(people[i] == name) return true;
    return false;
}