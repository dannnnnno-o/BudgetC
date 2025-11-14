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
#define ADD_HISTORY_PATH "includes/db/add_history.txt"
#define COMMENT_SIZE 256

int main(){
landing_page();
int current_balance;
int is_logged_in = login();

while(is_logged_in){
current_balance = get_balance();
menu();

int choice = get_choice("landing_page");
switch(choice){
case 1: // update balance 
int update; // what to update
int bal_buffer; 
int comment_choice;
int add_check; // checked for add_balance();
char *comment_buffer = malloc(COMMENT_SIZE); 
int confirm_add;
int confirm_update_balance;

while(1){
    update_balance_menu();
    int update_balance_choice = get_choice("update_balance");

    switch(update_balance_choice){
        case 1: // Add
            clear();
            add_menu();
            bal_buffer = get_update_value("add");

        case 2: // Spend
            clear();
            add_menu();

        case 3: break;
    }

    if(bal_buffer == 0){ //breaks out of loop if bal_buffer is untouched.
        break;
    }

    // at this point, we assume that the bal_buffer has a valid data.
    // and start the loop point for comment check
    clear();
    comment_choice = get_choice("comment");
    confirm_update_balance = confirm(bal_buffer, comment_buffer);
    if(confirm_update_balance == 0){
        printf("test.\n");
        break;
    }

    break;
}

break;

case 3: exit(0);
}

return 0;
}
}