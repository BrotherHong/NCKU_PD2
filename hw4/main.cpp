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

typedef struct result_s {
    int id;
    int consicutive;
    Date start;
    Date end;

    result_s(int id) 
        : id(id), consicutive(0) {}
} Result;

void readRecords(vector<SignRecord> &arr, ifstream&);
void categorizeById(vector<SignRecord> &arr, map<int, vector<Date>> &mp);
void uniqueDate(vector<Date> &arr);
void calculateResult(map<int, vector<Date>> &mp, vector<Result> &results);
bool cmpResult(const Result &r1, const Result &r2);


int main(int argc, char **argv) {

    ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        cerr << "Fail to load file " << argv[1] << endl;
        return 1;
    }

    vector<SignRecord> records;
    readRecords(records, inFile);

    sort(records.begin(), records.end());

    map<int, vector<Date>> catDate;
    categorizeById(records, catDate);

    vector<Result> results;
    calculateResult(catDate, results);

    sort(results.begin(), results.end(), cmpResult);

    for (int i = 0;i < 3;i++) {
        Result &r = results[i];
        cout << r.id << ',' << r.consicutive << ',' << r.start << ',' << r.end << '\n';
    }

    return 0;
}

void readRecords(vector<SignRecord> &arr, ifstream &inFile) {
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

        arr.push_back(SignRecord(id, type, stamp));
    }
}

void categorizeById(vector<SignRecord> &arr, map<int, vector<Date>> &mp) {
    for (auto &r : arr) {
        int id = r.getID();
        mp[id].push_back(r.getDate());
    }
}

void uniqueDate(vector<Date> &arr) {
    auto it = unique(arr.begin(), arr.end(), isSameDate);
    arr.erase(it, arr.end());
}

void calculateResult(map<int, vector<Date>> &mp, vector<Result> &results) {
    for (auto &p : mp) {

        int id = p.first;
        vector<Date> &v = p.second;
        uniqueDate(v);
        v.push_back(Date::fromString("999901010000"));

        Result result(id);
        int start = 0;
        for (int i = 1;i < v.size();i++) {
            if (!isConsecutiveDate(v[i-1], v[i])) {
                int consicutive = i-start;
                if (consicutive >= result.consicutive) {
                    result.consicutive = consicutive;
                    result.start = v[start];
                    result.end = v[i-1];
                }
                start = i;
            }
        }

        results.push_back(result);
    }
}

bool cmpResult(const Result &r1, const Result &r2) {
    if (r1.consicutive != r2.consicutive) {
        return r1.consicutive > r2.consicutive;
    }
    return r1.id < r2.id;
}
