#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stddef.h>

#include "../includes/ctrl/ctrl.h"
#include "../includes/view/view.h"
#include "../includes/model/model.h"
#include "../includes/goal.h"

#define GOAL_PATH "../goal.h"




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
            invalid_choice(4);
            menu();
            flush();
            continue;    
        }
        if(choice <= 0 || choice > 4){
            clear();
            invalid_choice(4);
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
        if((scanf("%d", &choice) != 1) || (choice <= 0 || choice > 4)){
            clear();
            invalid_choice(4);
            //men
            flush();
            goal_menu();
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
            goal_menu();
            continue;
        }
        else{
            getchar();
            break;
        }
    }
}

return choice;
}

/* end of goal menu */



int get_update_value(char mode){
int value = 0;
while(1){
    if(scanf("%d", &value) != 1){
        clear();
        invalid_balance_update("string");
        flush();
    }
    else if(value < 0){
        clear();
        invalid_balance_update("negative");
        flush();
    }
    else if(value == 0){
        clear();
        invalid_balance_update("zero");
        flush();
    }
    else{
        break;
    }
    if(mode == '+'){
        add_menu();
    }
    else if(mode == '-'){
        spend_menu();
    }
    continue;
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
    if(mode == '+'){
        printf("Add: %d\n", bal_buffer);
    }
    else if(mode == '-'){
        printf("Spend %d\n", bal_buffer);
    }
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

getchar();
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
    char date[255];

    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);

    int day =  local_time->tm_mday;
    int month = local_time->tm_mon + 1;
    int year = local_time->tm_year - 100;
    
    snprintf(date, sizeof(date), "%02d-%02d-%d", month, day, year);

    return strdup(date);
}

char *get_transact_date(char *transaction){
    char date[9];
    return strdup(strncpy(date, transaction, 8));
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

int confirm_set_goal(Goal goal){
    int choice = 0;
    char c;
    while(1){
        clear();
        title("SET GOAL");
        print_goal_buffer(goal);
        printf("Are you sure you want to set this goal? (y/n): ");
        if(scanf(" %c", &c) != 1){
            flush();
            invalid_input();
            clear();
            continue;
        }

        else if(c == 'n' || c == 'N'){break;}
        else if(c == 'y' || c == 'Y'){choice = 1; break;}
        else{
            clear();
            invalid_input();
            print_goal();
            continue;
        }
    }
getchar();
return choice;
}


float get_goal_progress(int investment, int amount){
    if(!investment){
        return 0;
    }
    float progress = (((float)investment/(float)amount) * 100);
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
            print_goal();
            continue;
        }
        else if(c == 'n' || c == 'N'){break;}
        else if(c == 'y' || c == 'Y'){choice = 1; break;}
        else{
            clear();
            invalid_input();
            title("Remove Goal");
            print_goal();
            continue;
        }
    }
    getchar();
    return choice;
}

int invest(int bal, int curr_invest, int target){
int investment = 0;
int max_invest;
if(curr_invest){
    max_invest = target - curr_invest;
}
else{
    max_invest = target;
}

title("Invest Money");
if(!bal){
    printf("You don't have any balance to invest.\n\n");
    printf("Press enter to go back.\n");
    wait_for_enter();
    return 0;
}
while(1){
    printf("How much would you like to invest?: ");
    if(scanf("%d", &investment) != 1){
        flush();
        clear();
        title("Invest Money");
        invalid_invest("invalid");
        continue;
    }
    else if(investment < 0){
        clear();
        title("Invest Money");
        invalid_invest("negative");
        continue;
    }

    else if(investment == 0){
        clear();
        title("Invest Money");
        invalid_invest("zero");
        continue;
    }

    else if(investment > bal){
        clear();
        title("Invest Money");
        invalid_invest("insufficient_bal");
        continue;
    }
    else if(investment > max_invest){
        clear();
        title("Invest Money");
        invalid_invest("exceeds_goal");
        continue;
    }
    break;
}
return investment;
}

int confirm_investment(int investment){
    int choice = 0;
    char c;
    while(1){
        printf("\nAre you sure you want to invest %dPHP?\nThis will be deducted to your current balance. (y/n): ", investment);
        if(scanf(" %c", &c) != 1){
            flush();
            clear();
            invalid_input();
        }

        else if(c == 'y' || c == 'Y'){choice = 1; break;}

        else if(c == 'n' || c == 'N'){break;}

        else{
            clear();
            invalid_input();
        }

        title("Invest Money");
        printf("How much would you like to invest?: %d", investment);
        continue;
    }
    getchar();
return choice; 
}

int take_investment(int goal_investment){
clear();
int to_take;
while(1){
    title("TAKE INVESTMENT");
    print_goal();
    printf("How much would you like to take?: ");

    if(scanf("%d", &to_take) != 1){
        clear();
        invalid_take_investment("invalid");
        flush();
        continue;
    }
    else if(to_take < 0){
        clear();
        invalid_take_investment("negative");
        flush();
        continue;
    }
    else if(to_take == 0){
        clear();
        invalid_take_investment("zero");
        flush();
        continue;
    }
    else if(to_take > goal_investment){
        clear();
        invalid_take_investment("insufficient_investment");
        flush();
        continue;
    }
    else{
        getchar();
        return to_take;
    }
}
}

int confirm_take_investment(int to_take){
    int choice = 0;
    char c;
    while(1){
        title("TAKE INVESTMENT");
        print_goal();
        printf("You're about to take %dPHP from your investments.\n", to_take);
        printf("Are you sure? (y/n): ");

        if(scanf(" %c", &c) != 1){
            clear();
            invalid_input();
            flush();
            continue;
        }

        else if(c == 'y' || c == 'Y'){
            choice = 1;
            break;
        }
        
        else if(c == 'n' || c == 'N'){
            break;
        }
        else{
            clear();
            invalid_input();
            continue;
        }
    }
getchar();
return choice;
}

int confirm_goal_completion(Goal goal){
    int choice = 0;
    char c;
    while(1){
        clear();
        title("GOAL COMPLETION");
        print_goal();
        printf("\nAre you sure you want to mark this goal as complete? (y/n): ");

        if(scanf(" %c", &c) != 1){
            flush();
            clear();
            invalid_input();
        }

        else if(c == 'y' || c == 'Y'){
            choice = 1;
            break;
        }

        else if(c == 'n' || c == 'N'){
            break;
        }

        else{
            flush();
            clear();
            invalid_input();
        }
        continue;
    }
    getchar();
    return choice;
}
