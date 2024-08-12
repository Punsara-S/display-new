#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <queue>

using namespace std;

class Details {
public:
    string name, gender;
    int cId;
    int phoneNo;
    int age;
    string add;

    void information() {
        cout << "\n Enter the customer ID: ";
        cin >> cId;

        cout << "\n Enter the name: ";
        cin >> name;

        cout << "\n Enter the age: ";
        cin >> age;

        cout << "\n Address: ";
        cin.ignore();
        getline(cin, add);

        cout << "\n Gender: ";
        cin >> gender;
        cout << "Your details are saved with us \n" << endl;
    }
};

class Registration {
public:
    int choice;
    int choice1;
    float charges;

    virtual void flights() {
        string flightN[] = {"Dubai", "Canada", "UK", "USA", "Australia", "Europe"};

        for (int a = 0; a < 6; a++) {
            cout << (a + 1) << ". flight to " << flightN[a] << endl;
        }

        cout << "\n Welcome to the Airlines!" << endl;
        cout << "Press the number of the country of which you want to book the flight: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookFlight("Dubai", 15000, 20000, 18000);
                break;
            case 2:
                bookFlight("Canada", 30000, 28000, 25000);
                break;
            case 3:
                bookFlight("UK", 44000, 22000, 24000);
                break;
            case 4:
                bookFlight("USA", 37000, 39000, 42000);
                break;
            case 5:
                bookFlight("Australia", 44000, 34000, 48000);
                break;
            case 6:
                bookFlight("Europe", 36000, 37000, 42000);
                break;
            default:
                cout << "Invalid input, shifting to the main menu!" << endl;
                break;
        }
    }

    void bookFlight(string destination, float charge1, float charge2, float charge3) {
        cout << "..........................Welcome to " << destination << " Airlines....................\n" << endl;
        cout << "Your comfort is our priority. Enjoy the journey!" << endl;
        cout << "Following are the flights\n" << endl;
        cout << "1. " << destination.substr(0, 3) << " - 498 " << endl;
        cout << "\t 08-12-2024 8.00AM 10 hrs Rs." << charge1 << endl;
        cout << "2. " << destination.substr(0, 3) << " - 658 " << endl;
        cout << "\t 09-12-2024 4.00AM 12 hrs Rs." << charge2 << endl;
        cout << "3. " << destination.substr(0, 3) << " - 798 " << endl;
        cout << "\t 10-12-2024 11.00AM 11 hrs Rs." << charge3 << endl;
        cout << "\n Select the flight you want to book: ";
        cin >> choice1;

        if (choice1 == 1) {
            charges = charge1;
            cout << "\n You have successfully booked the flight " << destination.substr(0, 3) << " - 498" << endl;
        } else if (choice1 == 2) {
            charges = charge2;
            cout << "\n You have successfully booked the flight " << destination.substr(0, 3) << " - 658" << endl;
        } else if (choice1 == 3) {
            charges = charge3;
            cout << "\n You have successfully booked the flight " << destination.substr(0, 3) << " - 798" << endl;
        } else {
            cout << "Invalid input, shifting to the previous menu" << endl;
            flights();
        }
        cout << "You can go back to menu and take the ticket" << endl;
    }

    virtual void Bill(queue<Details>& customerQueue) = 0;
};

class Ticket : public Registration {
public:
    void Bill(queue<Details>& customerQueue) override {
        string destination = "";
        Details currentCustomer = customerQueue.front();
        customerQueue.pop();

        ofstream outf("records.txt");

        outf << "S&S Airlines" << endl;
        outf << "Ticket" << endl;
        outf << "_" << endl;

        outf << "Customer ID: " << currentCustomer.cId << endl;
        outf << "Customer Name: " << currentCustomer.name << endl;
        outf << "Customer Gender: " << currentCustomer.gender << endl;
        outf << "\t Description" << endl << endl;

        if (choice == 1) {
            destination = "Dubai";
        } else if (choice == 2) {
            destination = "Canada";
        } else if (choice == 3) {
            destination = "UK";
        } else if (choice == 4) {
            destination = "USA";
        } else if (choice == 5) {
            destination = "Australia";
        } else if (choice == 6) {
            destination = "Europe";
        }

        outf << "Destination\t\t" << destination << endl;
        outf << "Flight cost: \t\t" << charges << endl;
        outf << "_" << endl;
        outf << "Thank You" << endl;
        outf.close();
    }

    void dispBill() {
        ifstream ifs("records.txt");
        if (!ifs) {
            cout << "File error!" << endl;
        }

        while (!ifs.eof()) {
            char arr[100];
            ifs.getline(arr, 100);
            cout << arr << endl;
        }
        ifs.close();
    }
};

class PriorityTicket : public Ticket {
public:
    void Bill(queue<Details>& customerQueue) override {
        string destination = "";
        Details currentCustomer = customerQueue.front();
        customerQueue.pop();

        ofstream outf("priority_records.txt");

        outf << "S&S Airlines" << endl;
        outf << "Priority Ticket" << endl;
        outf << "_" << endl;

        outf << "Customer ID: " << currentCustomer.cId << endl;
        outf << "Customer Name: " << currentCustomer.name << endl;
        outf << "Customer Gender: " << currentCustomer.gender << endl;
        outf << "\t Description" << endl << endl;


        if (choice == 1) {
            destination = "Dubai";
        } else if (choice == 2) {
            destination = "Canada";
        } else if (choice == 3) {
            destination = "UK";
        } else if (choice == 4) {
            destination = "USA";
        } else if (choice == 5) {
            destination = "Australia";
        } else if (choice == 6) {
            destination = "Europe";
        }

        outf << "Destination\t\t" << destination << endl;
        outf << "Flight cost: \t\t" << charges << endl;
        outf << "Priority Service: Included" << endl;
        outf << "_" << endl;
        outf << "Thank You" << endl;
        outf.close();
    }
};

class Management {
private:
    queue<Details> customerQueue;

public:
    Management() {
        mainMenu();
    }

    void mainMenu() {
        int lchoice;
        int schoice;
        int back;

        Details d;
        Ticket t;
        PriorityTicket pt;

        cout << "\t                 S&S Airlines \n" << endl;
        cout << "\t_Main Menu" << endl;
        cout << "\t_" << endl;
        cout << "\t|\t\t\t\t\t|" << endl;
        cout << "\t|\t Customer Management -> 1\t|" << endl;
        cout << "\t|\t Flight Registration -> 2\t|" << endl;
        cout << "\t|\t Ticket and Charges -> 3\t|" << endl;
        cout << "\t|\t Exit -> 4\t\t\t|" << endl;
        cout << "\t|\t\t\t\t\t|" << endl;
        cout << "\t_" << endl;

        cout << "\nEnter the choice: ";
        cin >> lchoice;

        switch (lchoice) {
            case 1:
                cout << "Customers\n" << endl;
                cout << "1. Enter Customer Details\n" << endl;
                cout << "2. Display Customer Details\n" << endl;

                cout << "\nEnter the choice: ";
                cin >> schoice;

                if (schoice == 1) {
                    d.information();
                    customerQueue.push(d);
                    cout << "Press any key to go back to main menu: ";
                    cin >> back;
                    mainMenu();
                } else if (schoice == 2) {
                    if (!customerQueue.empty()) {
                        Details frontCustomer = customerQueue.front();
                        cout << "Customer ID: " << frontCustomer.cId << endl;
                        cout << "Name: " << frontCustomer.name << endl;
                        cout << "Age: " << frontCustomer.age << endl;
                        cout << "Address: " << frontCustomer.add << endl;
                        cout << "Gender: " << frontCustomer.gender << endl;
                    } else {
                        cout << "No customer details available!" << endl;
                    }
                    cout << "Press any key to go back to main menu: ";
                    cin >> back;
                    mainMenu();
                } else {
                    cout << "Invalid input, shifting to main menu" << endl;
                    mainMenu();
                }
                break;
            case 2:
                t.flights();
                cout << "Flight registration completed. You can now proceed to ticketing." << endl;
                cout << "Press any key to go back to main menu: ";
                cin >> back;
                mainMenu();
                break;
            case 3:
                cout << "1. Normal Ticket\n" << endl;
                cout << "2. Priority Ticket\n" << endl;
                cout << "\nEnter the choice: ";
                cin >> schoice;

                if (schoice == 1) {
                    t.Bill(customerQueue);
                    t.dispBill();
                } else if (schoice == 2) {
                    pt.Bill(customerQueue);
                    pt.dispBill();
                } else {
                    cout << "Invalid input, shifting to main menu" << endl;
                    mainMenu();
                }
                break;
            case 4:
                cout << "Thank you" << endl;
                break;
            default:
                cout << "Invalid input, please try again!" << endl;
                mainMenu();
                break;
        }
    }
};

int main() {
    Management Mobj;
    return 0;
}
