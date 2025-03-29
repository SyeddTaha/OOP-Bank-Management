#include "registration.h"

bool isValidEmail(const string &email) {
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

void registration() {
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

    cout << "\n\nRegistration Successful!";
}