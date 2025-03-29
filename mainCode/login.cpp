#include "Login.h"
#include <conio.h>
#include <string>

void login(){
    cout << "\nLogin";
    cout << "\nUsername: ";
    
    string username;
    getline(cin, username);
    
    cout << "\nPassword: ";
    string password;
    
    char ch;
    while((ch = getch()) != '\r'){
        if(ch == '\b'){
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }else{
            password += ch;
            cout << "*";
        }
    }
    cout << "\n\nLogin Successful!";
}
