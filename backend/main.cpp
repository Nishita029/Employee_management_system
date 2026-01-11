#define CPPHTTPLIB_NO_MMAP
#include "httplib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace httplib;
using namespace std;

//Structure of Employee data
struct Employee {
    int id;
    string name;
    double basic;
    double hra;
    double da;
    double gross;
    double tax;
};

//CORS
void enableCORS(Response &res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

//Salary Calculation
void calculateSalary(Employee &e) {
    e.hra = e.basic * 0.20;
    e.da = e.basic * 0.10;
    e.gross = e.basic + e.hra + e.da;
    e.tax = e.gross * 0.10;
}

//File functions
bool findEmployee(int id, Employee &emp) {
    ifstream file("backend/employees.txt");
    if (!file) return false;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;

        getline(ss, temp, ','); emp.id = stoi(temp);
        getline(ss, emp.name, ',');
        getline(ss, temp, ','); emp.basic = stod(temp);
        getline(ss, temp, ','); emp.hra = stod(temp);
        getline(ss, temp, ','); emp.da = stod(temp);
        getline(ss, temp, ','); emp.gross = stod(temp);
        getline(ss, temp, ','); emp.tax = stod(temp);

        if (emp.id == id) return true;
    }
    return false;
}

//check duplicates
bool employeeExists(int id) {
    Employee emp;
    return findEmployee(id, emp);
}

void addEmployee(const Employee &emp) {
    ofstream file("backend/employees.txt", ios::app);
    file << emp.id << ","
         << emp.name << ","
         << emp.basic << ","
         << emp.hra << ","
         << emp.da << ","
         << emp.gross << ","
         << emp.tax << "\n";
}

bool updateEmployee(const Employee &emp) {
    ifstream fin("backend/employees.txt");
    ofstream fout("backend/temp.txt");

    bool found = false;
    string line;

    while (getline(fin, line)) {
        int id = stoi(line.substr(0, line.find(',')));

        if (id == emp.id) {
            fout << emp.id << ","
                 << emp.name << ","
                 << emp.basic << ","
                 << emp.hra << ","
                 << emp.da << ","
                 << emp.gross << ","
                 << emp.tax << "\n";
            found = true;
        } else {
            fout << line << "\n";
        }
    }

    fin.close();
    fout.close();
    remove("backend/employees.txt");
    rename("backend/temp.txt", "backend/employees.txt");

    return found;
}

bool deleteEmployee(int id) {
    ifstream fin("backend/employees.txt");
    ofstream fout("backend/temp.txt");

    bool found = false;
    string line;

    while (getline(fin, line)) {
        int curId = stoi(line.substr(0, line.find(',')));
        if (curId == id) {
            found = true;
            continue;
        }
        fout << line << "\n";
    }

    fin.close();
    fout.close();
    remove("backend/employees.txt");
    rename("backend/temp.txt", "backend/employees.txt");

    return found;
}


int main() {
    Server server;

    server.Options(R"(.*)", [](const Request&, Response &res) {
        enableCORS(res);
        res.status = 204;
    });

    //Add no duplicates
    server.Post("/add", [](const Request &req, Response &res) {
        enableCORS(res);

        int id = stoi(req.get_param_value("id"));

        // Duplicate ID check
        if (employeeExists(id)) {
            res.set_content("ERROR: Employee ID already exists", "text/plain");
            return;
        }

        Employee emp;
        emp.id = id;
        emp.name = req.get_param_value("name");
        emp.basic = stod(req.get_param_value("salary"));

        calculateSalary(emp);
        addEmployee(emp);

        res.set_content("SUCCESS: Employee added successfully", "text/plain");
    });

    //Update
    server.Post("/update", [](const Request &req, Response &res) {
        enableCORS(res);

        Employee emp;
        emp.id = stoi(req.get_param_value("id"));
        emp.name = req.get_param_value("name");
        emp.basic = stod(req.get_param_value("salary"));

        calculateSalary(emp);

        if (updateEmployee(emp))
            res.set_content("SUCCESS: Employee updated successfully", "text/plain");
        else
            res.set_content("ERROR: Employee not found", "text/plain");
    });

    //Delete
    server.Post("/delete", [](const Request &req, Response &res) {
        enableCORS(res);

        int id = stoi(req.get_param_value("id"));

        if (deleteEmployee(id))
            res.set_content("SUCCESS: Employee deleted successfully", "text/plain");
        else
            res.set_content("ERROR: Employee not found", "text/plain");
    });

    //Search
    server.Get("/search", [](const Request &req, Response &res) {
        enableCORS(res);

        int id = stoi(req.get_param_value("id"));
        Employee emp;

        if (findEmployee(id, emp)) {
            res.set_content(
                "ID: " + to_string(emp.id) +
                "\nName: " + emp.name +
                "\nBasic Salary: " + to_string(emp.basic),
                "text/plain"
            );
        } else {
            res.set_content("ERROR: Employee not found", "text/plain");
        }
    });

    //Salary slip
    server.Get("/salary", [](const Request &req, Response &res) {
        enableCORS(res);

        int id = stoi(req.get_param_value("id"));
        Employee emp;

        if (!findEmployee(id, emp)) {
            res.set_content("ERROR: Employee not found", "text/plain");
            return;
        }

        res.set_content(
            "SALARY SLIP\n"
            "------------------\n"
            "ID: " + to_string(emp.id) +
            "\nName: " + emp.name +
            "\nBasic Salary: " + to_string(emp.basic) +
            "\nHRA: " + to_string(emp.hra) +
            "\nDA: " + to_string(emp.da) +
            "\nGross Salary: " + to_string(emp.gross) +
            "\nTax: " + to_string(emp.tax) +
            "\nNet Salary: " + to_string(emp.gross - emp.tax),
            "text/plain"
        );
    });

    cout << "Server running on http://localhost:18080\n";
    server.listen("0.0.0.0", 18080);
}
