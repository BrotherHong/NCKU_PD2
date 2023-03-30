#include <iostream>
#include <fstream>

#include <string>
#include <sstream>

#include <vector>
#include <map>
#include <algorithm>

#include "date.h"
#include "sign_record.h"

#define OVERLOAD_HR 8

using namespace std;

int main(int argc, char **argv) {

    ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        cerr << "Fail to load file " << argv[1] << endl;
        return 1;
    }

    vector<SignRecord> records;

    string line;
    while (getline(inFile, line)) {

        vector<string> data;
        stringstream ss(line);
        string sub;
        
        while (getline(ss, sub, ',')) {
            data.push_back(sub);
        }

        int id = stoi(data[0]);
        SignType type = (data[1].size() == 7 ? IN : OUT);
        Date stamp = fromString(data[2]);

        records.push_back(SignRecord(id, type, stamp));
    }

    sort(records.begin(), records.end());

    map<int, vector<SignRecord>> personalRecord;
    for (auto &record : records) {
        int id = record.getID();
        personalRecord[id].push_back(record);
    }

    for (auto recordPair : personalRecord) {
        int id = recordPair.first;

        int overload = 0;
        int forget = 0;

        SignRecord *lastRecord = nullptr;

        for (auto &record : recordPair.second) {

            if (record.getType() == IN) {

                if (lastRecord && lastRecord->getType() == IN) {
                    forget++;
                }
                
            } else if (record.getType() == OUT) {

                if (!lastRecord || lastRecord->getType() == OUT) {
                    forget++;
                } else { 
                    // last record is check IN
                    Date lastTime = lastRecord->getTimestamp();
                    Date currTime = record.getTimestamp();

                    if (isSameDay(lastTime, currTime)) {
                        if (currTime - lastTime > OVERLOAD_HR*60) {
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