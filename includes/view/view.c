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

void loading(int start, char *message, int intervals){
    if(start){Sleep(1000);}
    printf("%s", message);
    for(int i = 0; i < intervals; i++){
        Sleep(500);
        printf(".");
    }
    Sleep(500);
}


/* UI */
void landing_page(){

printf("Welcome to BudgetC!\n");
printf("    This app serves as a mini-budgeting tool where users can keep track of their\n budget and expenses through the command line.\n\n");
}

void menu(){
printf("Welcome to BudgetC!\n\n");
int balance = get_balance();
printf("Current Balance: %dPHP\n\n", balance);
printf("1. Update Balance\n");
printf("2. View History\n");
printf("3. Logout\n");
printf("What would you like to do?: ");

}


void update_balance_menu(){
    printf("\nUpdate Balance\n");
    printf("1. Add\n2. Spend\n3. Go Back\n");
    printf("What would you like to do?: ");
}

void add_menu(){
    printf("Add Balance\n\n");
    printf("How much would you like to add?: ");
}

void spend_menu(){
    printf("Spend Balance\n\n");
    printf("How much did you spend?: ");
}

void logout(){
    clear();
    printf("Thank you for using BudgetC!");
}

/* error handlers */

void invalid_choice(int limit){
    printf("Invalid input. Please choose from 1 - %d\n\n", limit);
}

void invalid_balance_update(char *mode){
    if(strcmp(mode, "string") == 0){
        printf("Invalid input. Please enter a valid number.\n");
    }
    else if(strcmp(mode, "negative") == 0){
        printf("Invalid input. Please enter a non-negative number.\n");
    }
    else if(strcmp(mode, "zero") == 0){
        printf("You can't add nothing. Try again.\n" );
    }
    else{
        printf("invalid add mode bro.\n");
    }
}

void invalid_input(){
    printf("Invalid input. Try again.\n\n");
}