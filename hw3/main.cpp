#include <iostream>
#include <fstream>

#include <string>
#include <sstream>

#include <vector>
#include <map>
#include <algorithm>

#include "mytime.h"
#include "check_record.h"

#define OVERLOAD_HR 8

using namespace std;

int main(int argc, char **argv) {

    ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        cerr << "Fail to load file " << argv[1] << endl;
        return 1;
    }

    vector<CheckRecord> records;

    string line;
    while (getline(inFile, line)) {

        vector<string> data;
        stringstream ss(line);
        string sub;
        
        while (getline(ss, sub, ',')) {
            data.push_back(sub);
        }

        int id = stoi(data[0]);
        CheckType type = (data[1].size() == 7 ? IN : OUT);
        MyTime stamp = fromYYYYMMDDhhmm(data[2]);

        records.push_back(CheckRecord(id, type, stamp));
    }

    sort(records.begin(), records.end());

    map<int, vector<CheckRecord>> personalRecord;
    for (auto &record : records) {
        int id = record.getID();
        personalRecord[id].push_back(record);
    }

    for (auto recordPair : personalRecord) {
        int id = recordPair.first;

        int overload = 0;
        int forget = 0;

        CheckRecord *lastRecord = nullptr;

        for (auto &record : recordPair.second) {
            if (record.getType() == IN) {
                if (lastRecord && lastRecord->getType() == IN) {
                    forget++;
                }
            } else if (record.getType() == OUT) {
                if (!lastRecord || lastRecord->getType() == OUT) {
                    forget++;
                } else { // last record is check IN
                    MyTime last = lastRecord->getTimestamp();
                    MyTime curr = record.getTimestamp();

                    if (isSameDate(last, curr)) {
                        if (curr - last > OVERLOAD_HR*60) {
                            overload++;
                        }
                    } else {
                        forget++;
                    }
                }
            }
            lastRecord = &record;
        }

        if (lastRecord && lastRecord->getType() == IN) {
            forget++;
        }

        cout << id << "," << overload << "," << forget << endl;
    }

    return 0;
}