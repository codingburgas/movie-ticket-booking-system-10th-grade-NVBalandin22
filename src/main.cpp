#include<iostream>
using namespace std;
void signIn() {
    cout << "You're singned in" << endl;
}
void addfilm() {
    cout << "Added" << endl;
}
void removefilm() {
    cout << "Removed" << endl;
}
void signUp() {
    // << "Your username is: "
    cout << "You're singned up" << endl;
}
void start(){
    cout << "Who are you?" << endl << "1.user" << endl << "2.admin" << endl;
    int fchoice, schoice;
    cin >> fchoice;
    cout << "1.Sign in" << endl << "2.Sign up" << endl;
    cin >> schoice;
    if (schoice == 1){
        signIn();
    }
    else{
        signUp();
    }


    if (fchoice == 2) {
        system("cls");
        cout << "What are you going to do?" << endl << "1.add film" << endl << "2.remove film" << endl << "3.book ticket" << endl << "4. view activity" << endl;
        cin >> fchoice;
        switch(fchoice){
            case 1:
                addfilm();
                break;
            case 2:
                removefilm();
                break;

        }
    }
    else {
        system("cls");
        cout << "What are you going to do?" << endl << "1.book ticket" << endl << "2.check actual films" << endl;
        cin >> fchoice;
    }

}

int main() {
    start();
}