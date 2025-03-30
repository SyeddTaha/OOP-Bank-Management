#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <sstream> 
#include <windows.h>

using namespace std;

// Function prototypes
void registration();
void login();
bool isValidEmail(const string &email);
void displayMenu();
bool loadFromCSV(const string &email, const string &password);
void saveToCSV(const string &firstName, const string &lastName, const string &email, const string &password);

void displayMenu(){
    cout << "\n\nWelcome to NEXUS Banking System\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Admin Panel\n";
    cout << "4. Exit\n";
    cout << "Please select an option: ";
    int choice;
    cin >> choice;
    cin.ignore();
    switch (choice) {
        case 1:
            login();
            break;
        case 2:
            registration();
            break;
        case 3:
            cout << "\nAdmin Panel\n";
            login();
            break;
        case 4:
            cout << "\nExiting... Thank you for using NEXUS bank!\n";
            exit(0);
        default:
            cout << "\nInvalid choice. Kindly retry choosing correct option.\n";
            displayMenu();
    }
}

void saveToCSV(const string &firstName, const string &lastName, const string &email, const string &password){
    ofstream file("users.csv", ios::app);
    if (file.is_open()) {
        file << firstName << "," << lastName << "," << email << "," << password << "\n";
        file.close();
        // cout << "\nUser data saved successfully in users.csv!\n";
        cout << "\n\nRegistration Successful!";
    } else {
        cout << "\nError: Unable to open file for saving.\n";
    }
}

bool loadFromCSV(const string &email, const string &password) {
    ifstream file("users.csv");
    if (!file.is_open()) {
        cout << "\nError: Could not open users.csv file!\n";
        return false;
    }

    string line, firstName, lastName, storedEmail, storedPassword;
    while (getline(file, line)) {  // Read each line from the CSV
        stringstream ss(line);  // Use stringstream to parse CSV line

        // Read values separated by commas
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, storedEmail, ',');
        getline(ss, storedPassword, ',');

        if (storedEmail == email && storedPassword == password) {
            file.close();
            return true;  // Credentials Matched
        }
    }

    file.close();
    return false;  // No Match Found
}

bool isValidEmail(const string &email){
    if (email.empty()) return false;
    size_t atPos = email.find('@');
    size_t dotPos = email.rfind('.');

    if (atPos == string::npos || dotPos == string::npos) return false; // Must contain '@' and '.'
    if (atPos == 0 || dotPos == email.length() - 1) return false; // '@' not at start, '.' not at end
    if (email.find('@', atPos + 1) != string::npos) return false; // Only one '@'
    if (dotPos < atPos + 2) return false; // '.' must be at least 2 positions after '@'
    if (email.find("..") != string::npos) return false; // Prevents ".." in email
    if (email.find(' ') != string::npos) return false; // No spaces in email
    if (email[atPos - 1] == '.') return false; // Prevents '.' before '@'
    if (email[atPos + 1] == '.') return false; // Prevents '@' right before '.'

    return true;
}

void login(){
    cout << "\nLogin";
    
    string email;
    do{
        cout << "\nEmail: ";
        getline(cin, email);
        
        if(!isValidEmail(email)){
            cout << "\nInvalid Email\nPlease enter a valid email address.\n";
        }

    }while(!isValidEmail(email)); // Loop until a valid email is entered

    cout << "\nPassword: ";
    string password;
    
    char ch;
    while ((ch = getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << "*";
        }
    }
    if (loadFromCSV(email, password)) {
        cout << "\n\nLogin Successful!\n";
    } else {
        cout << "\n\nInvalid Email or Password. Try Again!\n";
    }
}

void registration(){
    cout << "\nRegister a new account\n";
    
    string email;
    do {
        cout << "\nEmail: ";
        getline(cin, email);
        
        if (!isValidEmail(email)) {
            cout << "\nInvalid Email\nPlease enter a valid email address.\n";
        }

    } while (!isValidEmail(email));
    string password, confirmPassword;
    do {
        cout << "\nPassword: ";
        password.clear();
        char ch;
        while ((ch = getch()) != '\r') {
            if (ch == '\b') {
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            } else {
                password += ch;
                cout << "*";
            }
        }

        cout << "\nConfirm Password: ";
        confirmPassword.clear();
        while ((ch = getch()) != '\r') {
            if (ch == '\b') {
                if (!confirmPassword.empty()) {
                    confirmPassword.pop_back();
                    cout << "\b \b";
                }
            } else {
                confirmPassword += ch;
                cout << "*";
            }
        }

        if (password != confirmPassword) {
            cout << "\n\nPasswords do not match! Please try again.\n";
        }
    } while (password != confirmPassword);

    cout << "\nFirst Name: ";
    string firstName;
    getline(cin, firstName);
    
    cout << "\nLast Name: ";
    string lastName;
    getline(cin, lastName);

    saveToCSV(firstName, lastName, email, password);
}

int main() {
    // registration();
    login();
    return 0;
}