#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <windows.h>

using namespace std;

class Bank{
    public:
        void menu();
        void bank_management();
        void atm_management();
    void menu(){
        start:
        system("cls");
        cout << "\nWelcome to Nexus Bank!";
        cout << "\n1. Nexus ATM";
        cout << "\n2. Nexus Bank";
        cout << "\n3. Exit";
        cout << "\nENTER YOUR CHOICE: ";
        int choice;
        cin >> choice;
        switch (choice){
            case 1:
                atm_management();
                break;
            case 2:
                bank_management();
                break;
            case 3:
                cout << "\nExiting...\n Have a great day!";
                exit(0);
                break;
            default:
                cout << "\nOops! Invalid option selected!. Kindly try again";   
        }
        getch();
        goto start;
    }
};

int main() {
    
    return 0;
}