/*---------------------------------------
creater: Meng-Shr,Tsai (46)
date:2020/7/9
anyone can copy and modify this.
---------------------------------------*/
#include<iostream>
#include<stdio.h>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#define People 3// number of people of preparing meals
using namespace std;

class aRow{
public:
    vector<string> date;
    vector<string> preDate;//the date of preparing meal
    string name;
    string others;
    aRow(string name, string others):name(name), others(others){}
    void addDate(string );
    void setDateVector();
    void showRow(){// only for debugging
        for(int i = 0; i < date.size(); i++){
            cout<<date[i]<<" ";
        }
        cout<<endl;
    }
    bool attend(string date);
};

void setData(vector< aRow>&, vector<string>&);
void writeOut(vector< aRow>& data, vector<string>& allDay);

int main(){
    srand(time(NULL));
    vector< aRow> data;
    vector<string> allDay;
    setData(data, allDay);
    writeOut(data, allDay);
}

void aRow::addDate(string newDate){
    (*this).date.push_back(newDate);
}

void aRow::setDateVector(){
    size_t now = 0;
    while(now<others.size()){
        if(others.find_first_of(" ,\t", now)-now == 0){
            now++;
            continue;
        }
        size_t next = others.find_first_of(" ,\t", now);
        string temp;
        temp = others.substr(now, next-now);
        addDate(temp);
        now = next;
    }
}

bool aRow::attend(string d){
    bool flag = false;
    for(int i = 0; i < date.size(); i++){
        if(d == date[i]) flag = true;
    }
    return flag;
}

void setData(vector< aRow>& data, vector<string>& allDay){
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
        data.push_back(aRow(line.substr(0,pos-0), line.substr(pos)));
    }
    file.close();

    for(int i = 0; i < data.size(); i++){
        data[i].setDateVector();
    }
    for(int i = 0; i < data[0].date.size(); i++){
        allDay.push_back(data[0].date[i]);
    }
    data.erase(data.begin());
}

void writeOut(vector< aRow>& data, vector<string>& allDay){
    cout<<"寫檔案中..."<<endl;
    ofstream out1, out2;
    out1.open("打飯表1.txt");
    out2.open("打飯表2.txt");
    vector< vector<string> > table;
    for(int i = 0; i < allDay.size(); i++){
        table.push_back(vector<string>());
        for(int j = 0; j < data.size(); j++){
            if(data[j].attend(allDay[i])){
                 table[i].push_back(data[j].name);
            }
        }
        while(table[i].size() > People){
            //cout<<"table[i] size is "<<table[i].size()<<endl;
            int temp = rand()%(table[i].size());
            //cout<<temp<<endl;
            table[i].erase( table[i].begin()+ temp );
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
        for(int j = 0; j < People; j++){
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
