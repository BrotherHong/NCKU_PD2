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

vector<SignRecord> records;

void readRecords();

int main(int argc, char **argv) {

    ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        cerr << "Fail to load file " << argv[1] << endl;
        return 1;
    }

    readRecords(inFile);

    sort(records.begin(), records.end());

    

    return 0;
}

void readRecords(ifstream &inFile) {
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
        Date stamp = Date::fromString(data[2]);

        records.push_back(SignRecord(id, type, stamp));
    }
}