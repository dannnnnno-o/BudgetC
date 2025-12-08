#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../includes/view/view.h"
#include "../includes/ctrl/ctrl.h"
#include "../includes/model/model.h"
#include "../includes/goal.h"

#define LIMIT 40

void clear(){
    system("cls");
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
printf("[3]. Goal\n");
printf("[4]. Logout\n");
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

void history_menu(){
    title("HISTORY");
    printf("[1]. All\n");
    printf("[2]. Added\n");
    printf("[3]. Spent\n");
    printf("[4]. Go Back\n");
    printf("What transactions would you like to see?: ");
}


void print_transact_date(char *date){
    printf("\n\n");
    printf("--------------\n");
    printf("|| %s ||\n", date);
    printf("--------------\n");
}

/* start of goal */

void format_goal(Goal goal){
    strip(strlen(goal.name), goal.name);
    strip(strlen(goal.date), goal.date);

    char amount[256];   
    sprintf(amount, "%d", goal.amount);
    int name_amount_length = strlen(goal.name) + strlen(amount) + 5; // 5 for ": " and for PHP

    printf("%s: %sPHP", goal.name, amount);
    for(int i = name_amount_length; i < LIMIT; i++){
        printf(" ");
    }
    printf("Invested amount: %dPHP\n", goal.investment);
    
    printf("Target Date: %s", goal.date);
    int date_length = strlen(goal.date) + 13;
    for(int i = date_length; i < LIMIT; i++){
        printf(" ");
    }
    printf("Progress: %.2f%%\n\n", get_goal_progress(goal.investment, goal.amount));
}

void print_goal(){
    Goal goal = get_goal();
    printf("Current Balance: %dPHP\n\n", get_balance());
    format_goal(goal);
}

void print_goal_buffer(Goal goal){
    format_goal(goal);
}

void goal_menu(){
    int target_complete = 0;
    Goal goal = get_goal();

    if(goal.investment == goal.amount && goal.name){
        target_complete = 1;
    }

    title("GOAL");
    if(!goal.name){
        printf("Goal isn't set yet.\n\n");
        
        printf("[1]. Set Goal\n");
        printf("[2]. Go Back\n");
    }
    if(!target_complete && goal.name){
        print_goal();
        printf("[1]. Invest Money\n");
        printf("[2]. Take Investment\n");
        printf("[3]. Remove Goal\n");
        printf("[4]. Go Back\n\n");
    }

    else if(target_complete){
        printf("NOTICE: Target amount has been reached.\n");
        printf("NOTICE: You can now mark the goal as complete.\n\n");
        print_goal();
        printf("[1]. Complete Goal\n");
        printf("[2]. Take Investment\n");
        printf("[3]. Remove Goal\n");
        printf("[4]. Go Back\n\n");
    }

}

/* end of goal */

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



void invalid_goal_input(char *mode){
    if(strcmp(mode, "amount") == 0){
        printf("Invalid target amount.\nPlease enter a valid target amount.\n");
    }
    else if(strcmp(mode, "date") == 0){
        printf("Invalid target date.\nPlease enter a valid target date\n");
    }
    
    else{
        printf("Invalid goal input mode\n");
    }
}

void invalid_invest(char *mode){
    if(strcmp(mode, "invalid") == 0){
        printf("Please enter a valid amount.\n");
    }
    else if(strcmp(mode, "negative") == 0){
        printf("You can't invest a negative amount.\n");
    }
    else if(strcmp(mode, "zero") == 0){
        printf("You can't invest nothing.\n");
    }
    else if(strcmp(mode, "exceeds_goal") == 0){
        printf("That exceeds the target amount.\n");
    }
    else if(strcmp(mode, "insufficient_bal") == 0){
        printf("You don't have enough balance to invest that amount.\n");
    }
    else{
        printf("Invalid investment mode");
    }
}

void invalid_take_investment(char *mode){
    if(strcmp(mode, "invalid") == 0){
        printf("Please enter a valid number.\n");
    }
    else if(strcmp(mode, "negative") == 0){
        printf("You can't take a negative amount.\n");
    }
    else if(strcmp(mode, "zero") == 0){
        printf("Please can't take nothing.\n");
    }
    else if(strcmp(mode, "insufficient_investment") == 0){
        printf("You don't have enough investment for that amount.\n");
    }
    else{
        printf("Invalid investment take mode.\n");
    }
}

