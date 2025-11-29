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
#include "includes/goal.h"

#define BAL_PATH "includes/db/balance.txt"
#define HISTORY_PATH "includes/db/history.txt"
#define GOAL_PATH "includes/db/goal.txt"
#define COMMENT_SIZE 256

int main(){
clear();
landing_page();
loading(1, "Loading", 3);
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
            loading(0, "Updating your balance", 3);
            update_account(update_mode, current_balance, bal_buffer, comment_buffer, BAL_PATH, HISTORY_PATH);
            clear();
            printf("Balance updated!\n\n");
        }
        else{
        clear();
        loading(0, "Cancelling process", 3);
        clear();
        printf("Process Cancelled.\n\n");
        }
        loading(0, "Redirecting", 3);
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
        loading(0, "Loading transactions", 2);
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
    loading(0, "Redirecting", 2);
    clear();
    continue;
}
break;

case 3: //GOAL
Goal goal = get_goal(GOAL_PATH);
int goal_choice;
Goal goal_buf = {NULL, 0, NULL};
clear();
goal_menu(goal);
if(goal.amount){
    goal_choice = get_choice("goal");
    switch(goal_choice){
        case 1: //invest money
        case 2: //take money
        case 3: 
        clear();
        title("Remove Goal");
        print_goal(goal);
        int goal_removal = confirm_goal_removal(goal);
        if(goal_removal){
            remove_goal(GOAL_PATH);
            clear();
            loading(0, "Removing goal", 3);
            clear();
            printf("Goal removed.\n\n");
            printf("Press enter to continue.\n");
            wait_for_enter();
            clear();
            home = 'y'; 
            break;
        }
        else if(!goal_removal){
            clear();
            loading(0, "Cancelling process", 3);
            clear();
            printf("Process cancelled.\n\n");
            printf("Press enter to continue.\n");
            wait_for_enter();
            clear();
            home = 'y'; break;
        }

        break;
       
        case 4: home = 'y'; break;
    }
}
    if(home == 'y'){clear();break;}

    if(!goal.amount){

    goal_choice = get_choice("no_goal");
    clear();

    if(goal_choice == 2){   // return home
        break;
    }

    title("Set Goal");
    goal_buf.name = get_goal_name();           //get goal details
    goal_buf.amount = get_goal_amount();
    goal_buf.date = get_goal_date();
}
    if(update_goal(GOAL_PATH, goal_buf)){
        printf("Can't update goal\n");
    }
    printf("\n");
    loading(0, "Updating goal", 3);
    clear();
    title("GOAL UPDATED!");
    printf("Press enter to return.\n");
    wait_for_enter();
    break;

break;

case 4:
    clear();
    loading(0, "Logging you out", 3);
    // could ask for confirmation here
    logout(); 
    exit(0);
}
continue;
}
return 0;
}