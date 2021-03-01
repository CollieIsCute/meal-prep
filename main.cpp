/*---------------------------------------
Maker: Meng-Shr,Tsai (46)
date:2020/7/9
modified date:2021/2/8
---------------------------------------*/
#include<iostream>
#include<stdio.h>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#define DAILY_WORKING_PEOPLE 3// number of people of preparing meals
using namespace std;

class Person{
public:
    vector<string> attendDates;
    int workingDaysAmount;
    string name;
    string exceptName;
    Person(string name, string others):name(name), exceptName(others){
        workingDaysAmount = 0;
    }
    void addAttendDate(string );
    void buildAttendDates();
    void showDetails(){// only for debugging
        for(int i = 0; i < attendDates.size(); i++){
            cout<<attendDates[i]<<" ";
        }
        cout<<endl;
    }
    bool isAttended(string date);
    void setNumDate(int num) {workingDaysAmount += num;}
};

void setData(vector< Person>&, vector<string>&);
int nameForIndex(string, vector<Person>);
void writeOut(vector< Person>& data, vector<string>& allDay);

int main(){
    srand(time(NULL));
    vector< Person> allPeople;
    vector<string> wholeCampDates;
    setData(allPeople, wholeCampDates);
    writeOut(allPeople, wholeCampDates);
    allPeople.clear();
    wholeCampDates.clear();
}

void Person::addAttendDate(string newDate){
    (*this).attendDates.push_back(newDate);
}

void Person::buildAttendDates(){
    size_t now = 0;
    while(now<exceptName.size()){
        if(exceptName.find_first_of(" ,\t", now)-now == 0){
            now++;
            continue;
        }
        size_t next = exceptName.find_first_of(" ,\t", now);
        string temp;
        temp = exceptName.substr(now, next-now);
        addAttendDate(temp);
        now = next;
    }
}

bool Person::isAttended(string d){
    bool flag = false;
    for(int i = 0; i < attendDates.size(); i++){
        if(d == attendDates[i]) flag = true;
    }
    return flag;
}

void setData(vector< Person>& allPeople, vector<string>& allDay){
    ifstream file;
    ofstream out1, out2;
    char filename[100];
    string line, temp;
    cout<<"請輸入檔案名稱(含副檔名:.txt) : ";
    cin>>filename;
    file.open(filename, ifstream::in);
    out1.open("打飯表1.txt");
    out2.open("打飯表2.txt");
    if(file.is_open()){
        cout<<"Access to data...";
        cout<<endl;
    }
    else{
        cout<<"Failed to get data QQ";
        cout<<endl;
        exit(123456789);
    }
    while(!(file.eof())){
        getline(file, line);
        int pos = 0;
        pos = line.find_first_of(" \t", pos);
        allPeople.push_back(Person(line.substr(0,pos-0), line.substr(pos)));
    }
    file.close();

    for(int i = 0; i < allPeople.size(); i++){
        allPeople[i].buildAttendDates();
    }
    for(int i = 0; i < allPeople[0].attendDates.size(); i++){
        allDay.push_back(allPeople[0].attendDates[i]);
    }
    allPeople.erase(allPeople.begin());
}

int nameForIndex(string name, vector<Person> data){
    for(int i = 0; i < data.size(); i++){
        if(name == data[i].name) return i;
    }
    return -1;
}

void writeOut(vector< Person>& data, vector<string>& allDay){
    cout<<"寫檔案中..."<<endl;
    ofstream out1, out2;
    out1.open("打飯表1.txt");
    out2.open("打飯表2.txt");
    vector< vector<string> > table;
    for(int i = 0; i < allDay.size(); i++){ //put all present people in list
        table.push_back(vector<string>());
        for(int j = 0; j < data.size(); j++){
            if(data[j].isAttended(allDay[i])){
                 table[i].push_back(data[j].name);
                 data[j].setNumDate(1);
            }
        }
        while(table[i].size() > DAILY_WORKING_PEOPLE){    // if size()> People(const), then do deleting loop
            int maxdays = 0;
            int maxindex = 0;
            for(int j = 0; j < table[i].size(); j++){
                for(int k = 0; k < data.size(); k++){
                    if(data[k].name == table[i][j] && data[k].workingDaysAmount>maxdays){
                        maxindex = j;
                        maxdays = data[k].workingDaysAmount;
                    }
                }
            }
            int tempind = nameForIndex(table[i][maxindex], data);
            data[tempind].setNumDate(-1);
            table[i].erase( table[i].begin()+ maxindex );
        }
    }

    /*for(int i = 0; i < table.size(); i++){
        for(int j = 0; j < table[i].size(); j++){
            out1<<table[i][j]<<" ";
        }
        out1<<endl;
    }*/

    for(int i = 0; i < allDay.size(); i++){
        out1<<allDay[i]<<"\t";
        for(int j = 0; j < DAILY_WORKING_PEOPLE; j++){
            out1<<table[i][j]<<" ";
        }
        out1<<endl;
    }

    for(int i = 0; i < data.size(); i++){
        out2<<data[i].name<<"\t";
        int sum = 0;
        for(int j = 0; j < allDay.size(); j++){
            bool doWork = false;
            for(int k = 0; k < table[j].size(); k++){
                if(data[i].name == table[j][k]) doWork = true;
            }
            out2<<doWork<<" ";
            sum += doWork;
        }
        out2<<"sum: "<<sum<<endl;
    }

    out1.close();
    out2.close();
    cout<<"寫檔完成!!!"<<endl;
    system("Pause");
}
