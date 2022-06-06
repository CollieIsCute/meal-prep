#if defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows
#elif defined(_WIN64)
    #define PLATFORM_NAME "windows" // Windows
#endif

#include "CSV-header/csv.h"
#include "calendar.hpp"

#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

static int prompForInputInt(std::string msg);
static std::string produceNewInputFile();
static std::string prompForInputString(std::string msg);

// TODO 移除重複填寫的資料
int main() {
	const int daily_working_people = prompForInputInt("請輸入每日值日生數量： ");
	const int name = prompForInputInt("請輸入姓名所在的欄數（從最左欄訂為0開始數）： ");
	const int date = prompForInputInt("請輸入日期所在的欄數（從最左欄訂為0開始數）： ");
	CSVReader reader(produceNewInputFile());
	Calendar attendCal;
	for(int i = 1; i < reader.getRowNum(); i++)
		attendCal.updatePeopleDates(reader.getCell(i, name), reader.getCell(i, date));
	attendCal.updateDatesPeopleFromPeopleDates();

	Calendar workCal(attendCal);
	workCal.reducePeopleToLimit(daily_working_people);
	workCal.writeFiles("work1.csv", "work2.csv");
	attendCal.writeFiles("attend1.csv", "attend2.csv");
	std::cout << "檔案已建立" << std::endl;
}

static int prompForInputInt(std::string msg) {
	int ret;
	std::cout << msg;
	std::cin >> ret;
	return ret;
}

static std::string produceNewInputFile(){
	const std::string origin_file = prompForInputString("請輸入檔案名稱(檔名不可有空白)： ");
	const std::string return_file = (PLATFORM_NAME == "windows") ? "_" + origin_file : origin_file;
	if(PLATFORM_NAME == "windows") {
		const std::string unix2dos("\" ((Get-Content -Encoding utf8 \""
								   + origin_file + "\") | Set-Content -Encoding utf8 \"" + return_file + "\")\"");
		std::system(("powershell -command "+ unix2dos).c_str());
	}
	return return_file;
}

static std::string prompForInputString(std::string msg) {
	std::string ret;
	std::cout << msg;
	std::cin >> ret;
	return ret;
}
