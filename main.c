#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stddef.h> // for size_t

#include "includes/model/model.h"
#include "includes/ctrl/ctrl.h"
#include "includes/view/view.h"

#define BAL_PATH "includes/db/balance.txt"
#define HISTORY_PATH "includes/db/history.txt"
#define COMMENT_SIZE 256

int main(){
clear();
landing_page();
clear();

int current_balance;
int is_logged_in = login();


char home;
while(is_logged_in){
home = 'n';
current_balance = get_balance();

clear();
menu();
int choice = get_choice("landing_page");

switch(choice){
case 1: // update balance 
int bal_buffer = 0; // assign to zero for later checks 
int comment_choice;
char *comment_buffer = malloc(COMMENT_SIZE); 
char update_mode;
int history;

while(1){
    clear();
    update_balance_menu();
    int update_balance_choice = get_choice("update_balance");

    switch(update_balance_choice){
        case 1: // Add
            clear();
            add_menu();
            update_mode = '+';
            break;

        case 2: // Spend
            clear();
            spend_menu();
            update_mode = '-';
            break;

        case 3: home = 'y'; break;
    }
    if(home == 'y'){break;}; 

    bal_buffer = get_update_value();
    clear();

    comment_choice = get_choice("comment");
    if(comment_choice){
        comment_buffer = get_comment();
    }
    else{
        comment_buffer = "n";
    }
    
    if(bal_buffer){
        if(confirm(update_mode, bal_buffer, comment_choice, comment_buffer)){
            clear();
            update_account(update_mode, current_balance, bal_buffer, comment_buffer, BAL_PATH, HISTORY_PATH);
            clear();
            printf("Balance updated!\n\n");
        }
        else{
        clear();
        printf("Process Cancelled.\n\n");
        }
    }
    break;
}

break;

case 2: 
while(1){

    clear();
    history_menu();
    history = get_choice("history");
    clear();
    if(history != 4){
        clear();
    }
    switch(history){
        case 1:
            title("ALL TRANSACTIONS"); 
            view_transactions("all", HISTORY_PATH); 
            break;
        case 2: 
            title("ADDED BALANCE");
            view_transactions("add", HISTORY_PATH);
            break;
        case 3: 
            title("SPENT BALANCE");
            view_transactions("spent", HISTORY_PATH); 
            break;
        case 4: home = 'y'; break;
    }

    if(home == 'y'){
        clear();
        break;
    }

    printf("\n\nPress Enter to go back.\n");
    wait_for_enter();
    clear();
    continue;
}
break;

case 3:
    clear();
    // could ask for confirmation here
    logout(); 
    exit(0);
}
continue;
}
return 0;
}
