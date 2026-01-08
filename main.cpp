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
    cin.ignore();
    getline(cin, e.name);

    cout<<"Enter the base salary: "<<endl;
    cin>>e.baseSalary;

    calculateSalary(e);

    //writing data into file

    file << e.empID << " "<< e.name << " "<< e.baseSalary << " "<< e.HRA << " "<< e.DA << " "<< e.grossSalary << " "<< e.tax << endl;

    file.close();
    cout<<"Employee added successfully" <<endl;
     
}

//search any employee by ID

void searchEmployee() {
    Employee e;
    int id;
    bool found = false;

    cout << "\nEnter Employee ID to search: ";
    cin >> id;

    ifstream file("employee.txt");

    while (file >> e.empID >> e.name >> e.baseSalary >> e.HRA >> e.DA >> e.grossSalary >> e.tax) {
        if (e.empID == id) {
            cout << "Employee Found!"<<endl;
            cout << "ID: " << e.empID << endl;
            cout << "Name: " << e.name << endl;
            cout << "Base Salary: " << e.baseSalary << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Employee not found!";
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
            cout << "------------- Salary Slip ------------"<<endl;
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
        cout << "Employee not found!"<<endl;
}

//update employee data using a temporary file 

void updateEmployee() {
    Employee e;
    int id;
    bool found = false;

    cout << "Enter Employee ID to update: ";
    cin >> id;

    ifstream file("employee.txt");
    ofstream temp("temp.txt");

    while (file >> e.empID >> e.name >> e.baseSalary >> e.HRA >> e.DA >> e.grossSalary >> e.tax) {
        if (e.empID == id) {
            cout << "Enter new name: ";
            cin >> e.name;

            cout << "Enter new basic salary: ";
            cin >> e.baseSalary;

            calculateSalary(e);
            found = true;
        }

        temp << e.empID << " "
             << e.name << " "
             << e.baseSalary << " "
             << e.HRA << " "
             << e.DA << " "
             << e.grossSalary << " "
             << e.tax << endl;
    }

    file.close();
    temp.close();

    remove("employee.txt");
    rename("temp.txt", "employee.txt");

    if (found)
        cout << "Employee updated successfully!"<<endl;
    else
        cout << "Employee not found!"<<endl;
}

void deleteEmployee() {
    Employee e;
    int id;
    bool found = false;

    cout << "Enter Employee ID to delete: ";
    cin >> id;

    ifstream file("employee.txt");
    ofstream temp("temp.txt");

    while (file >> e.empID >> e.name >> e.baseSalary >> e.HRA >> e.DA >> e.grossSalary >> e.tax) {
        if (e.empID != id) {
            temp << e.empID << " "
                 << e.name << " "
                 << e.baseSalary << " "
                 << e.HRA << " "
                 << e.DA << " "
                 << e.grossSalary << " "
                 << e.tax << endl;
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("employee.txt");
    rename("temp.txt", "employee.txt");

    if (found)
        cout << "Employee deleted successfully!"<<endl;
    else
        cout << "Employee not found!"<<endl;
}

int main(){

int choice;

    do {
        cout << "---------- Employee Salary Management System ----------"<<endl;
        cout << "1. Add Employee"<<endl;
        cout << "2. Search Employee"<<endl;
        cout << "3. Update Employee data"<<endl;
        cout << "4. Delete Employee"<<endl;
        cout << "5. Show Salary Slip"<<endl;
        cout << "6. Exit"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); 
            break;
            case 2: searchEmployee(); 
            break;
            case 3: updateEmployee(); 
            break;
            case 4: deleteEmployee(); 
            break;
            case 5: showSalarySlip(); 
            break;
            case 6: cout << "Exiting"; 
            break;
            default: cout << "Invalid choice!"<<endl;
        }
    } while (choice != 6);

    return 0;
}
