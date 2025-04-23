#include<iostream>
#include "../include/functions.h"



void signIn() {
    std::cout << "You're singed in" << std::endl;
}

void addFilm() {
    std::cout << "Added" << std::endl;
}

void removeFilm() {
    std::cout << "Removed" << std::endl;
}

void signUp() {
    // << "Your username is: "
    std::cout << "You're singed up" << std::endl;
}


void start(){
    std::cout << "Who are you?" << std::endl << "1.user" << std::endl << "2.admin" << std::endl;
    int fChoice, sChoice;
    std::cin >> fChoice;
    std::cout << "1.Sign in" << std::endl << "2.Sign up" << std::endl;
    std::cin >> sChoice;
    if (sChoice == 1){
        signIn();
    }
    else{
        signUp();
    }


    if (fChoice == 2) {
        system("cls");
        std::cout << "What are you going to do?" << std::endl << "1.add film" << std::endl << "2.remove film" << std::endl << "3.book ticket" << std::endl << "4. view activity" << std::endl;
        std::cin >> fChoice;
        switch(fChoice){
            case 1:
                addFilm();
            break;
            case 2:
                removeFilm();
            break;
            default:
                std::cout << "Incorrect input!";
        }
    }
    else {
        system("cls");
        std::cout << "What are you going to do?" << std::endl << "1.book ticket" << std::endl << "2.check actual films" << std::endl;
        std::cin >> fChoice;
    }

}