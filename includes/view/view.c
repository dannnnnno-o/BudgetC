#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>
#include "view.h"
#include "../ctrl/ctrl.h"
#include "../model/model.h"

void clear(){
    system("cls");
}

/* loading pages */
void load_add_bal(){
    printf("Adding balance");
    Sleep(250);
    printf(".");
    Sleep(250);
    printf(".");
    Sleep(250);
    printf(".");
    Sleep(250);
    printf("\n");
}

/* UI */
void landing_page(){

printf("Welcome to BudgetC!\n");
printf("    This app serves as a mini-budgeting tool where users can keep track of their\n budget and expenses through the command line.\n\n");
Sleep(1000);
printf("Loading");
Sleep(500);
printf(".");
Sleep(500);
printf(".");
Sleep(500);
printf(".");
Sleep(500);
}

int login(){
    clear();
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


void menu(){

int balance = get_balance();
printf("Current Balance: %d\n\n", balance);
printf("1. Add Balance\n");
printf("2. Spend \n");
printf("3. View Statistics\n");
printf("4. Logout\n");
printf("What would you like to do?: ");

}


