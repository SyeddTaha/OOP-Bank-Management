#include <iostream>
#include <conio.h>

using namespace std;

int main() {
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
    return 0;
}
