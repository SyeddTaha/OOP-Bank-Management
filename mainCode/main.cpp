#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <algorithm>

using namespace std;

void keyEncryption(string &password);
void toLowerCase(string &str);
void registration(string person);
void login(string person);
bool isValidEmail(const string &email);
void displayMenu();
bool loadFromCSV(const string &email, const string &password, string filename);
void saveToCSV(const string &firstName, const string &lastName, const string &email, const string &password, string filename);

void keyEncryption(string &password) {
    password.clear();  // Clear previous password
    char ch;
    while ((ch = getch()) != '\r') {  // Read until Enter key
        if (ch == '\b') {  // Handle backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << "*";
        }
    }
}

void toLowerCase(string &str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void displayMenu() {
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
            login("user");
            break;
        case 2:
            registration("user");
            break;
        case 3:
            cout << "\nAdmin Panel\n";
            cout << "1. Login\n";
            cout << "2. Register\n";
            cout << "Please select an option: ";
    
            int choice1;
            cin >> choice1;
            cin.ignore();
            switch(choice1) {
                case 1:
                    login("admin");
                    break;
                case 2:
                    registration("admin");
                    break;
                default:
                    cout << "\nInvalid choice. Kindly retry choosing the correct option.\n";
                    displayMenu();
            }
            break;
        case 4:
            cout << "\nExiting... Thank you for using NEXUS bank!\n";
            exit(0);
        default:
            cout << "\nInvalid choice. Kindly retry choosing the correct option.\n";
            displayMenu();
    }
}

void saveToCSV(const string &firstName, const string &lastName, const string &email, const string &password, string filename) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << firstName << "," << lastName << "," << email << "," << password << "\n";
        file.close();
        cout << "\n\nRegistration Successful!";
    } else {
        cout << "\nError: Unable to open file for saving.\n";
    }
}

bool loadFromCSV(const string &email, const string &password, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\nError: Could not open " << filename << " file!\n";
        return false;
    }

    string line, firstName, lastName, storedEmail, storedPassword;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, storedEmail, ',');
        getline(ss, storedPassword, ',');

        string emailCopy = email;
        toLowerCase(storedEmail);
        toLowerCase(emailCopy);

        if (storedEmail == emailCopy && storedPassword == password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool isValidEmail(const string &email) {
    if (email.empty()) return false;
    size_t atPos = email.find('@');
    size_t dotPos = email.rfind('.');

    if (atPos == string::npos || dotPos == string::npos) return false;
    if (atPos == 0 || dotPos == email.length() - 1) return false;
    if (email.find('@', atPos + 1) != string::npos) return false;
    if (dotPos < atPos + 2) return false;
    if (email.find("..") != string::npos) return false;
    if (email.find(' ') != string::npos) return false;
    if (email[atPos - 1] == '.' || email[atPos + 1] == '.') return false;

    return true;
}

void login(string person) {
    string filename;
    cout << "\n\nWelcome to NEXUS Banking System\n";
    if (person == "admin") {
        cout << "\n\nAdmin Login\n";
        filename = "admin.csv";
    } else {
        cout << "\n\nUser Login\n";
        filename = "users.csv";
    }

    string email;
    do {
        cout << "\nEmail: ";
        getline(cin, email);
        if (!isValidEmail(email)) {
            cout << "\nInvalid Email\nPlease enter a valid email address.\n";
        }
    } while (!isValidEmail(email));

    cout << "\nPassword: ";
    string password;
    keyEncryption(password);

    if (loadFromCSV(email, password, filename)) {
        cout << "\n\nLogin Successful!\n";
    } else {
        cout << "\n\nInvalid Email or Password. Try Again!\n";
    }
}

void registration(string person) {
    string filename;
    cout << "\n\nWelcome to NEXUS Banking System\n";
    if (person == "admin") {
        cout << "Enter pin to access admin panel: ";
        string pin;
        keyEncryption(pin);
        if (pin != "1234") {
            cout << "\n\nInvalid pin! Access denied.\n";
            return;
        }
        cout << "\n\nAccess granted!\nAdmin Registration\n";
        filename = "admin.csv";
    } else {
        cout << "\n\nUser Registration\n";
        filename = "users.csv";
    }

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
        keyEncryption(password);
        cout << "\nConfirm Password: ";
        keyEncryption(confirmPassword);
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

    saveToCSV(firstName, lastName, email, password, filename);
}

int main() {
    do{
    displayMenu();  // Start by displaying the main menu
    }while(true);  // Loop until the user chooses to exit
    return 0;
}
