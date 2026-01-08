#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

//Structure of employee to store information

struct Employee{
    int empID;
    string name;
    float baseSalary;
    float HRA;
    float DA;
    float grossSalary;
    float tax;
};

//fuction to calculate salary 

void calculateSalary(Employee &e){

    e.HRA = 0.20 * e.baseSalary;
    e.DA = 0.10 * e.baseSalary;

    e.grossSalary = e.baseSalary + e.HRA + e.DA ;

    e.tax = 0.05 * e.grossSalary;

}

// function to add new record of employee

void addEmployee(){
    Employee e;

    ofstream file;
    file.open("employee.txt", ios::app); //opening file and if it does not exist it will create a new file

    cout<<"Enter employee ID: "<<endl;
    cin>>e.empID;

    cout<<"Enter the name of employee: "<<endl;
    getline(cin, e.name);

    cout<<"Enter the base salary: "<<endl;
    cin>>e.baseSalary;

    calculateSalary(e);

    //writing data into file

    file << e.empID <<" | " << e.name << " | " <<e.baseSalary << " | " << e.HRA << " | " <<e.DA << " | " << e.grossSalary << " | " <<e.tax <<endl;

    file.close();
    cout<<"Employee added successfully" <<endl;
     
}

//search any employee by ID

void searchEmployee(){

    Employee e;
    int id;
    bool found = false;

    cout << "Enter Employee's ID you want to search: ";
    cin >> id;

    ifstream file("employee.txt"); //reading data from file

    while (file >> e.empID >> e.name >> e.baseSalary >> e.HRA >> e.DA >> e.grossSalary >> e.tax) {
        if (e.empID == id) {
            cout << "Employee Found!";
            cout << "ID: " << e.empID << endl;
            cout << "Name: " << e.name << endl;
            cout << "Base Salary: " << e.baseSalary << endl;

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Employee not found!"<<endl;

}

void showSalarySlip() {
    Employee e;
    int id;
    bool found = false;

    cout << "Enter Employee ID: ";
    cin >> id;

    ifstream file("employee.txt");

    while (file >> e.empID >> e.name >> e.baseSalary >> e.HRA >> e.DA >> e.grossSalary >> e.tax) {
        if (e.empID == id) {
            cout << "------------- Salary Slip ------------";
            cout << fixed << setprecision(2);
            cout << "Employee ID   : " << e.empID << endl;
            cout << "Name          : " << e.name << endl;
            cout << "Base Salary  : " << e.baseSalary << endl;
            cout << "HRA (20%)     : " << e.HRA << endl;
            cout << "DA (10%)      : " << e.DA << endl;
            cout << "Gross Salary  : " << e.grossSalary << endl;
            cout << "Tax (5%)      : " << e.tax << endl;
            cout << "Net Salary    : " << e.grossSalary - e.tax << endl;
        
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Employee not found!";
}

int main(){

}
