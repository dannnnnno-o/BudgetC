#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>
#include <stddef.h> // for size_t

#include "includes/model/model.h"
#include "includes/ctrl/ctrl.h"
#include "includes/view/view.h"

#define BAL_PATH "includes/db/balance.txt"
#define HISTORY_PATH "includes/db/history.txt"
#define COMMENT_SIZE 256

int main(){
landing_page();
clear();
int current_balance;
int is_logged_in = login();

while(is_logged_in){
current_balance = get_balance();
clear();
menu();

int choice = get_choice("landing_page");
switch(choice){
case 1: // update balance 
int update; // what to update
int bal_buffer = 0; // assign to zero for later checks 
int comment_choice;
int add_check; // checked for add_balance();
char *comment_buffer = malloc(COMMENT_SIZE); 
int confirm_add;
int confirm_update_balance;
char update_mode;

while(1){
    clear();
    update_balance_menu();
    int update_balance_choice = get_choice("update_balance");

    switch(update_balance_choice){
        case 1: // Add
            clear();
            add_menu();
            update_mode = '+';
            bal_buffer = get_update_value();
            clear();
            comment_choice = get_choice("comment");
            if(comment_choice){
                comment_buffer = get_comment();
            }
            else{
                comment_buffer = "n";
            }
            break;

        case 2: // Spend
            clear();
            spend_menu();
            update_mode = '-';
            bal_buffer = get_update_value();
            clear();
            comment_choice = get_choice("comment");
            if(comment_choice){
                comment_buffer = get_comment();
            }
            else{
                comment_buffer = "n";
            }
            break;

        case 3: break;

        default: invalid_input(); break;
    }
    
    if(bal_buffer){
        if(confirm(update_mode, bal_buffer, comment_choice, comment_buffer)){
        load_add_bal();
        update_account(update_mode, current_balance, bal_buffer, comment_buffer, BAL_PATH, HISTORY_PATH);
        }
        else{
        clear();
        printf("Process canceled.\n");
        }
    }
    break;
}

break;

case 2: printf("History"); break;

case 3: logout(); exit(0);
}
continue;
}
return 0;
}