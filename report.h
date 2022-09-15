//
// Created by pilavov on 15.09.2022.
//

#ifndef TEST2222_REPORT_H
#define TEST2222_REPORT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <future>

using namespace std;

class Report {
private:
    map<string,string> months = {
            {"01", "January"},
            {"02", "February"},
            {"03", "March"},
            {"04", "April"},
            {"05", "May"},
            {"06", "June"},
            {"07", "July"},
            {"08", "August"},
            {"09", "September"},
            {"10", "October"},
            {"11", "November"},
            {"12", "December"}

    };
    ifstream file;
    char delimiter ;
    int namePos, emailPos, datePos, logHoursPos ;
    vector<string> checked;
    vector<future<string>> fut_vec;
    string corporateEmail = "@company.com";
    string file_loc;

public:
    Report()=delete;
    explicit Report(const string& loc);

    void getReport();
    string timeTracker(const string& name, const string& email);

};


#endif //TEST2222_REPORT_H
