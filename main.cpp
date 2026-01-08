#include<iostream>
#include<fstream>
#include<string>

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
    file.open("employee.txt", ios::app);

    cout<<"Enter employee ID: "<<endl;
    cin>>e.empID;

    cout<<"Enter the name of employee: "<<endl;
    cin>>e.name;

    cout<<"Enter the base salary: "<<endl;
    cin>>e.baseSalary;

    calculateSalary(e);
     
}

int main(){

}
