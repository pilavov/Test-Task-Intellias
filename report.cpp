//
// Created by pilavov on 15.09.2022.
//

#include "report.h"

Report::Report(const string& loc) {
    vector<string> row;
    string line, word;
    file_loc = loc;

    file.open(loc);
    if (file.is_open())
    {
        getline(file, line);
        row.clear();

        stringstream str(line);

        //Handling different CSV separators.
        string tm = (line.substr(line.find("email") + 5, 1));
        delimiter =  *(tm.data());

        while (getline(str, word, delimiter))
            row.push_back(word);

        //3. Assumed that in future we can change position of columns , change their names etc. So program looks at first string of input csv and datects position of columns with which we work in the project
        namePos = std::find(row.begin(), row.end(), "Name") - row.begin();
        emailPos = std::find(row.begin(), row.end(), "email") - row.begin();
        datePos = std::find(row.begin(), row.end(), "date") - row.begin();
        logHoursPos = std::find(row.begin(), row.end(), "logged hours") - row.begin();
    } else
        cout << "Unable to open file." << endl;

}



void Report::getReport() {
    vector<string> row;
    string line, word;

    while (getline(file, line)) {
        row.clear();

        stringstream str(line);

        while (getline(str, word, delimiter))
            row.push_back(word);

        //Considered and noted only if worker inputed corporate domain not gmail.com etc. else Error message will be sent to standard output and this hours will not be calculated
        if (row[emailPos].substr(row[emailPos].find('@'), row[emailPos].length() - row[emailPos].find('@')) !=
            corporateEmail) {
            cerr << row[namePos] << " is using not corporation email adress on "  << row[datePos] << endl;
        } else {
            if (find(checked.begin(), checked.end(), row[emailPos]) == checked.end()) {
                //Async parsing (-40% of program duration in result)
                fut_vec.push_back(async(launch::async, &Report::timeTracker, this, row[namePos], row[emailPos]));
                checked.push_back(row[emailPos]);
            }
        }
    }

    ofstream res_file("../output.csv");
    for(auto & i : fut_vec){
        res_file << i.get();
    }

    res_file.close();
    file.close();
}


string Report::timeTracker(const string &name, const string &email) {
    vector<string> row;
    string line, word;
    string date ;
    string result ;

    map<string, int> record ;
    map<string, int>::iterator it;

    ifstream file_newly_opened;
    file_newly_opened.open(file_loc);

    while (getline(file_newly_opened, line)) {
        row.clear();
        stringstream str(line);

        while (getline(str, word, delimiter))
            row.push_back(word);
        if (row[emailPos] == email) {
            date = row[datePos];
            date = date.substr(0,7);
            it = record.find(date);
            if ( it == record.end()){
                record.insert(make_pair(date, stoi(row[logHoursPos])));
            }
            else
                it -> second += stoi(row[logHoursPos]);
        }
    }

    file_newly_opened.close();
    string  year, month ;

    for(const auto& elem : record)
    {
        year = elem.first.substr(0, 4);
        month = months.find(elem.first.substr(5,2))->second;
        result += (name + ";" + month + " " + year + ";" + to_string(elem.second) + "\n");
    }
    return result;
}
