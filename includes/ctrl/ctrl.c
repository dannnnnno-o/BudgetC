#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>
#include <stddef.h>

#include "ctrl.h"
#include "../view/view.h"


void flush(){
int flush_buffer;
while ((flush_buffer = getchar()) != '\n' && flush_buffer != EOF);
}

void strip(size_t len, char *comment_buffer){
    if(len > 0 && comment_buffer[len - 1] == '\n'){
        comment_buffer[len - 1] = '\0';
    }
}


int login(){
    char p[5] = "0000";
    char pin[255];
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


int get_choice(char *mode){
int choice = 0;    

/* landing page */
if(strcmp(mode, "landing_page") == 0){
    while(1){
        if(scanf("%d", &choice) != 1){
            clear();
            invalid_choice(5);
            menu();
            flush();
            continue;    
        }
        if(choice <= 0 || choice > 5){
            clear();
            invalid_choice(5);
            menu();
            flush();
            continue;
        }
        else{
            getchar();
            break;
        }
    }
}

/* update balance */
if(strcmp(mode, "update_balance") == 0){
        while(1){
        if((scanf("%d", &choice) != 1) || (choice <= 0 || choice > 3)){
        clear();
        invalid_choice(3);
        update_balance_menu();
        flush();
        continue;
        }
        else{
            getchar();
            break;
        }
    }
}

/* comment choice */
if(strcmp(mode, "comment") == 0){
char c;
while(1){
    printf("Would you like to add a comment? (y/n): ");

    if(scanf(" %c", &c) != 1){
        flush();
        clear();
        invalid_input();
        continue;
    }

    else if(c == 'y' || c == 'Y'){
        choice = 1;
        break;
    }

    else if(c == 'n' || c == 'N'){break;} // choice is 0 by default
    else{
        clear();
        invalid_input();
        continue;
    }
}
}

/* confirm update */
if(strcmp(mode, "confirm_update") == 0){
char c;
while(1){
    printf("Would you like to add a comment? (y/n): ");

    if(scanf(" %c", &c) != 1){
        flush();
        clear();
        invalid_input();
        continue;
    }

    else if(c == 'y' || c == 'Y'){choice = 1; getchar(); break;}

    else if(c == 'n' || c == 'N'){getchar(); break;} // choice is 0 by default
    else{
        clear();
        invalid_input();
        continue;
    }
}
}

/* history */
if(strcmp(mode, "history") == 0){
while(1){
    if(scanf("%d", &choice) != 1 || (choice <= 0 || choice > 4)){
        clear();
        invalid_choice(4);
        history_menu();
        flush();
        continue;
    }
    else{
        getchar();
        break;
    }
}
}

/* goal menu */
if(strcmp(mode, "goal") == 0){
    while(1){
        printf("What would you like to do?: ");
        if((scanf("%d", &choice) != 1) || (choice <= 0 || choice > 5)){
            clear();
            invalid_choice(5);
            //men
            flush();
            continue;
        }
        else{
            getchar();
            break;
        }
    }
}
if(strcmp(mode, "no_goal") == 0){
    while(1){
        printf("What would you like to do?: ");
        if((scanf("%d", &choice) != 1) || (choice <= 0 || choice > 2)){
            clear();
            invalid_choice(2);
            flush();
            continue;
        }
        else{
            getchar();
            break;
        }
    }
}

/* end of goal menu */

return choice;
}

int get_update_value(){
int value = 0;
while(1){
    if(scanf("%d", &value) != 1){
        clear();
        invalid_balance_update("string");
        flush();
        add_menu();
        continue;
    }
    else if(value < 0){
        clear();
        invalid_balance_update("negative");
        flush();
        add_menu();
        continue;
    }
    else if(value == 0){
        clear();
        invalid_balance_update("zero");
        flush();
        add_menu();
        continue;
    }
    else{
        break;
    }
}
return value;
}


int confirm(char mode, int bal_buffer, int comment, char *comment_buffer){
printf("\n");
int choice = 0;
char c;
if(comment){
while(1){
    if(mode == '+'){
        printf("Add: %d\n", bal_buffer);
    }
    else{
        printf("Spend: %d\n", bal_buffer);
    }
    printf("Comment: %s\n\n", comment_buffer);
    printf("Are you sure you want to update your balance? (y/n): ");

    if(scanf(" %c", &c) != 1){
        flush();
        clear();
        invalid_input();
        continue;
    }

    else if(c == 'y' || c == 'Y'){choice = 1; break;}

    else if(c == 'n' || c == 'N'){break;} // choice is 0 by default
    else{
        clear();
        invalid_input();
        continue;
    }
}
}

else if(!comment){
while(1){
    printf("Add: %d\n", bal_buffer);
    printf("Comment: no comment.\n\n");
    printf("Are you sure you want to update your balance? (y/n): ");

    if(scanf(" %c", &c) != 1){
        flush();
        clear();
        invalid_input();
        continue;
    }

    else if(c == 'y' || c == 'Y'){choice = 1; break;}

    else if(c == 'n' || c == 'N'){break;} // choice is 0 by default
    else{
        clear();
        invalid_input();
        continue;
    }
}
}


return choice;
}


char *get_comment(){
    printf("Comment: ");
    char *comment = malloc(255);
    flush();
    fgets(comment, 255, stdin);
    char *comment_dup = strdup(comment);
    free(comment);
    
    strip(strlen(comment_dup), comment_dup);
    return comment_dup;
}

void wait_for_enter(){
    while(getchar() != '\n');
}

char *get_date(){
    char date[32];

    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);

    int day =  local_time->tm_mday;
    int month = local_time->tm_mon + 1;
    int year = local_time->tm_year - 100;
    
    sprintf(date, "%d-%d-%d", month, day, year);
    return strdup(date);
}

Goal get_goal(char *path){
    FILE *file = fopen(path, "r");
    char buffer[255];
    Goal goal = {NULL, 0, NULL, 0}; // initialize all to null for error handling
    for(int i = 0; i < 4; i++){
        if(fgets(buffer, sizeof(buffer), file) == NULL){break;}
        switch(i){
            case 0: goal.name = strdup(buffer); break;
            case 1: goal.amount = atoi(strdup(buffer)); break;
            case 2: goal.date = strdup(buffer); break;
            case 3: goal.investment = atoi(strdup(buffer)); break;
        }
    }
    fclose(file);
    return goal;
}

char *get_goal_name(){
    char *name = malloc(255);
    while(1){
        printf("What are you saving for?: ");
        fgets(name, 255, stdin);
        strip(strlen(name), name);
        return name;
    }
}

int get_goal_amount(){
int amount;
while(1){
    printf("What is your target amount?: ");
    if(scanf("%d", &amount) != 1){
        clear();
        invalid_goal_input("amount");
        flush();
        title("Set Goal");
        continue;
    }
    else{
        getchar();
        break;
    }
    break;
}
return amount;
}

char *get_goal_date(){
    char *date = malloc(255);
    printf("Enter your target date: ");
    fgets(date, 255, stdin);
    strip(strlen(date), date);
    return date;
}
float get_goal_progress(int investment, int amount){
    if(!investment){
        return 0;
    }
    float progress = ((investment/amount) * 100);
    return progress;
}

int confirm_goal_removal(Goal goal){
    int choice = 0;
    char c;
    while(1){
        printf("Are you sure you want to remove your goal? (y/n): ");
        if(scanf(" %c", &c) != 1){
            flush();
            clear();
            invalid_input();
            title("Remove Goal");
            print_goal(goal);
            continue;
        }
        else if(c == 'n' || c == 'N'){break;}
        else if(c == 'y' || c == 'Y'){choice = 1; break;}
        else{
            clear();
            invalid_input();
            title("Remove Goal");
            print_goal(goal);
            continue;
        }
    }
    getchar();
    return choice;
}


