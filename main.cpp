#include "report.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*
 *Done in project :
 * 1. Basic task
 * 2. Assumed that we can have workers with equivalent name and surname, so email was taken like primary key
 * 3. Assumed that in future we can change position of columns , change their names etc. So program looks at first string of input csv and datects position of columns with which we work in the project
 * 4. Was tested to distinguish situation when we have different year but the same month
 * 5. Considered and noted only if worker inputed corporate domain not gmail.com etc. else Error message will be sent to standard output and this hours will not be calculated
 * 6. Handling different CSV separators.
 * 7. Async parsing (-40% of program duration in result)
 * 8. Measuring parsing time.
 * 9. Logging class with output to separate file.
 */


int main() {
    //Measuring parsing time.
    auto start = high_resolution_clock::now();


    Report obj("../data.csv");
    obj.getReport();


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
    return 0;
}