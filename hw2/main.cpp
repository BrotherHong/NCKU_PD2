#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<fstream>
using namespace std;

class Employee {
    private:
        int id;
        int age;
        char gender;
        int salary;
    public:
        Employee(int id, int age, char gender, int salary) {
            this->id = id;
            this->age = age;
            this->gender = gender;
            this->salary = salary;
        }

        bool operator < (const Employee &e) {
            if (salary != e.salary) {
                return salary < e.salary;
            }
            if (age != e.age) {
                return age < e.age;
            }
            if (gender != e.gender) {
                return gender == 'f';
            }
            return id < e.id;
        }

        int getID() {
            return id;
        }

        int getSalary() {
            return salary;
        }

};

int main(int argc, char **argv) {

    ifstream input = ifstream(argv[1]);
    if (!input.is_open()) {
        cerr << "Failed to open " << argv[1] << endl;
        return 1;
    }

    vector<Employee> employees;

    string line;
    while (getline(input, line)) {

        vector<string> data;
        stringstream ss(line);
        string sub;

        while (getline(ss, sub, ',')) {
            data.push_back(sub);
        }

        int id = stoi(data[0]);
        int age = stoi(data[1]);
        char gender = data[2][0];
        int salary = stoi(data[3]);

        employees.push_back(Employee(id, age, gender, salary));        
    }

    input.close();

    sort(employees.begin(), employees.end());

    int currSalary = employees[0].getSalary();
    cout << currSalary;
    for (auto emp : employees) {
        if (emp.getSalary() != currSalary) {
            cout << endl;
            currSalary = emp.getSalary();
            cout << currSalary;
        }
        cout << "," << emp.getID();
    }

    cout << endl;
    return 0;
}