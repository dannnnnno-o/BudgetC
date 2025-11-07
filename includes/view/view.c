#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>
#include "view.h"
#include "../ctrl/ctrl.h"

void clear(){
    system("cls");
}

void landingPage(){
printf("Welcome to budgetC!\n");
printf("    This app serves as a mini-budgeting tool where users can keep track of their\n budget and expenses through the command line.\n\n");
Sleep(1000);
printf("Loading");
Sleep(500);
printf(".");
Sleep(500);
printf(".");
Sleep(500);
printf(".\n");
Sleep(500);
}

int login(){
    char p[5] = "0000";
    char pin[5];
    while(1){

    printf("Login ka muna.\n");
    
    printf("Enter Pin: ");
    fgets(pin, sizeof(pin), stdin);
    pin[strcspn(pin, "\n")] = '\0'; // accesses the "\n" in username and assigns a null terminator instead 

    if(strcmp(p, pin) == 0){
        return 1;
    }
    else{
        clear();
        printf("Mali pin mo tol, ulit ka.\n");
        continue;
    }

    
    }
}