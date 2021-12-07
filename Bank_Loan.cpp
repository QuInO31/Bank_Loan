/*
    Authorship
    Group 5 : Project 2 << Bank Loan
    Members:
    First name  |   Last name
    ------------|--------------
    Bhavin      |   Patel
    Kieran      |   Primeau
    Ivan        |   Kepseu
    Yug falgun  |   Shah

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <limits>
#include <string>
#include "Customer.hpp"
#include "PriorityQueue.hpp"

using namespace std;
void inputOperation(double& in, string s);

int main(int argc, char** argv)
{
    srand((int)time(0));
    double option = -1;
    string id, sex, region, married, car, saveAct, currentAct, mortgage;
    int age = 0;
    int children = 0;
    double income = 0;
    int approved = 0, denied = 0;
    PriorityQueue<Customer>allCustomerQueue;
    PriorityQueue<Customer>customerRiskQueue;
    PriorityQueue<Customer>approvedCustomerQueue;
    PriorityQueue<Customer>deniedCustomerQueue;

    while (option != 0)
    {
        cout << "\n--------------------------------------------" << endl;
        cout << "Welcome to Group Five's Bank Loan System" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "" << endl;
        cout << "Please make a selection then press enter:" << endl;
        cout << "1. Load RAW customer data from csv file." << endl;
        cout << "2. Determine if the customers will have access to a loan or NOT." << endl;
        cout << "3. Display Approved Customers Queue" << endl;
        cout << "4. Display Denied Customers Queue" << endl;
        cout << "5. Save Approved and Denied Customer Queues to An External csv File" << endl;
        cout << "0. Exit" << endl;
        cout << "\nChoice: ";
        inputOperation(option, "option");
        cout << endl;

        if (option == 1)
        {
            int insertCustomer = 0;
            int dataCount = 0;
            ifstream inputFile;
            string filename;
            cout << " Enter a path to a csv file containing a list of patients: ";
            cin >> filename;

            inputFile.open(filename);
            if (!inputFile.good())
            {
                cout << "Invalid file entry" << endl;
                continue;
            }
            else
            {
                while (inputFile.good())
                {
                    string line, data;
                    getline(inputFile, line);
                    stringstream ss(line);
                    while (getline(ss, data, ','))
                    {
                        if(insertCustomer != 0)
                        //cout << data << ", ";
                        switch (dataCount)
                        {
                        case 0:
                            id = data;
                            break;
                        case 1:
                            age = stoi(data);
                            break;
                        case 2:
                            sex = data;
                            break;
                        case 3:
                            region = data;
                            break;
                        case 4:
                            income = stod(data);
                            break;
                        case 5:
                            married = data;
                            break;
                        case 6:
                            children = stoi(data);
                            break;
                        case 7:
                            car = data;
                            break;
                        case 8:
                            saveAct = data;
                            break;
                        case 9:
                            currentAct = data;
                            break;
                        case 10:
                            mortgage = data;
                            break;
                        default:
                            break;
                        }
                        dataCount++;
                    }
                    dataCount = 0;
                    if (insertCustomer > 0 && !ss.str().empty())
                    {
                        try
                        {
                            allCustomerQueue.insert_with_priority(Customer(id, age, sex, region, income, married, children, car, saveAct, currentAct, mortgage));
                        }
                        catch (exception e)
                        {
                            cout << "Error in file :" << e.what();
                        }
                        //cout << endl;
                    }
                    insertCustomer++;
                }
            }
            //allCustomerQueue.print();
            cout << "\n...Data loaded ..." << endl;
            system("pause");
        }
        if (option == 2)
        {
            while (allCustomerQueue.size() > 0)
            {
                Customer cust = allCustomerQueue.pull_highest_priority_element();
                cust.ageRisk_ = (double)(rand() % 10) + 1;
                cust.sexRisk_ = (double)(rand() % 10) + 1;
                cust.regionRisk_ = (double)(rand() % 10) + 1;
                cust.incomeRisk_ = (double)(rand() % 10) + 1;
                cust.marriedRisk_ = (double)(rand() % 10) + 1;
                cust.childrenRisk_ = (double)(rand() % 10) + 1;
                cust.carRisk_ = (double)(rand() % 10) + 1;
                cust.save_actRisk_ = (double)(rand() % 10) + 1;
                cust.current_actRisk_ = (double)(rand() % 10) + 1;
                cust.mortgageRisk_ = (double)(rand() % 10) + 1;

                double sumRisk = cust.ageRisk_ + cust.sexRisk_ + cust.regionRisk_ + cust.incomeRisk_ + cust.marriedRisk_ + 
                    cust.childrenRisk_ + cust.carRisk_ + cust.save_actRisk_ + cust.current_actRisk_ + cust.mortgageRisk_ ;
                cust.totalRisk = sumRisk / 10.0;
                if (cust.totalRisk < 5)
                {
                    approved++;
                    cust.isApproved = true;
                    approvedCustomerQueue.insert_with_priority(cust);
                }
                else
                {
                    denied++;
                    cust.isApproved = false;
                    deniedCustomerQueue.insert_with_priority(cust);
                }
                customerRiskQueue.insert_with_priority(cust);
            }
            while (customerRiskQueue.size() > 0)
            {
                allCustomerQueue.insert_with_priority(customerRiskQueue.pull_highest_priority_element());
            }
            cout << "\t...Data sorted out..." << endl;
            cout << "\t" << approved <<" Customers approved for a loan." << endl;
            cout << "\t" << denied << " Customers denied a loan." << endl;
            system("pause");
        }
        if (option == 3)
        {
            cout << "Approved Customers Queue\n" << endl;
            approvedCustomerQueue.print();
        }
        if (option == 4)
        {
            cout << "Denied Customers Queue\n" << endl;
            deniedCustomerQueue.print();
        }
        if (option == 5)
        {
            cout << " Saving the approved queue to an approved.csv file and the denied queue to a denied.csv file\n";

            ofstream outputFile;
            ofstream ootFile;
            outputFile.open("Approved.csv");

            outputFile << "Id,Age,Sex,Region,Income,Married,Children,Car,Save_act,Current_act,Mortgage,Total Risk,Is Approved\n";
            approvedCustomerQueue.printToFile(outputFile);

            cout << "\t\t...Saving approved queue...\n";
            outputFile.close();

            ootFile.open("Denied.csv");

            ootFile << "Id,Age,Sex,Region,Income,Married,Children,Car,Save_act,Current_act,Mortgage,Total Risk,Is Approved\n";
            deniedCustomerQueue.printToFile(ootFile);
            
            cout << "\t\t...Saving denied queue...\n";
            ootFile.close();
            system("pause");
        }

    }

    return EXIT_SUCCESS;
}

void inputOperation(double& in, string s)
{
    do
    {
        cin >> in;
        if (cin.good())
        {
            in = floor(in);
            if (s == "option")
            {
                while (in < 0 || in > 5)
                {
                    cout << "*Invalid choice level * " << endl;
                    cout << "Enter your choice(0-5): ";
                    cin >> in;
                    if (!cin.good())
                    {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                    }
                }
            }
            break;
        }
        else
        {
            cout << "\n*Invalid " << s << " input*" << endl;
            if (s == "option")
                cout << "Enter your choice(0-5): ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (true);
}