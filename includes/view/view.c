#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "view.h"
#include "../ctrl/ctrl.h"
#include "../model/model.h"

void clear(){
    system("clear");
}

/* loading pages */

void loading(int start, char *message, int intervals){
    if(start){sleep(1);}
    printf("%s", message);
    for(int i = 0; i < intervals; i++){
        sleep(1);
        printf(".");
    }
    sleep(1);
}


/* UI */
void title(char *title){

    int limit = strlen(title) + 6;
    for(int i = 0; i < limit; i++){
        printf("-");
    }
    printf("\n");

    printf("|| %s ||\n", title);

    for(int i = 0; i < limit; i++){
        printf("-");
    }
    printf("\n");
}

void landing_page(){

printf("Welcome to BudgetC!\n");
printf("    This app serves as a mini-budgeting tool where users can keep track of their\n budget and expenses through the command line.\n\n");
}

void menu(){
int balance = get_balance();
title("Welcome to BudgetC!");
printf("Current Balance: %dPHP\n\n", balance);
printf("[1]. Update Balance\n");
printf("[2]. View History\n");
printf("[3]. Logout\n");
printf("What would you like to do?: ");

}

void update_balance_menu(){
    title("UPDATE BALANCE");
    printf("[1]. Add\n");
    printf("[2]. Spend\n");
    printf("[3]. Go Back\n");
    printf("What would you like to do?: ");
}

void add_menu(){
    title("ADD BALANCE");
    printf("How much would you like to add?: ");
}

void spend_menu(){
    title("SPEND BALANCE");
    printf("How much did you spend?: ");
}

void logout(){
    clear();
    printf("Thank you for using BudgetC!\n");
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

void history_menu(){
    title("HISTORY");
    printf("[1]. All\n");
    printf("[2]. Added\n");
    printf("[3]. Spent\n");
    printf("[4]. Go Back\n");
    printf("What transactions would you like to see?: ");
}
