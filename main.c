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
#define GOAL_HISTORY "includes/db/goal_history.txt"
#define COMMENT_SIZE 256

int main(){
clear();
// landing_page();
// loading(1, "Loading", 3);
// clear();

int current_balance;


char home;
while(1){
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

    bal_buffer = get_update_value(update_mode);
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

        printf("Press enter to proceed.\n\n");
        wait_for_enter();
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
    if(history != 5){
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

        case 4: title("GOAL HISTORY");
        view_goal_history(GOAL_HISTORY);
        break;

        case 5: home = 'y'; break;
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
Goal goal = get_goal();

int goal_choice;
Goal goal_buf = {NULL, 0, NULL, 0};

int investment = 0;
int invest_confirm = 0;
int take_invest = 0;
int confirm_take;
int goal_complete = 0;




while(1){


    clear();

    goal_menu();
    if(goal.name){
        goal_choice = get_choice("goal");
    }
    switch(goal_choice){
        case 1: //invest money || complete goal'
        goal = get_goal();
        if(goal.name && goal.amount == goal.investment){
            goal_complete = 1;
        }
        else{
            goal_complete = 0;
        }
            clear();
            if(goal_complete){
                int confirm_completion = confirm_goal_completion(goal);
                if(confirm_completion){
                    clear();
                    loading(0, "Updating goal", 3);
                    clear();
                    complete_goal(GOAL_PATH, GOAL_HISTORY, goal);
                    printf("Goal completed!\n\n");
                    printf("Press enter to proceed.\n\n");
                    goal_complete = 0;
                    goal = get_goal();
                    wait_for_enter();
                    clear();
                }
                else{
                    clear();
                    loading(0, "Cancelling Process", 3);
                    clear();
                    printf("Process cancelled.\n\n");
                    printf("Press enter to proceed.\n\n");
                    wait_for_enter();
                }
            }
            else if(!goal_complete){
                investment = invest(current_balance, goal.investment, goal.amount);
                if(!investment){break;}
                invest_confirm = confirm_investment(investment);
                if(invest_confirm){
                    clear();
                    loading(0, "Updating investment", 3);
                    clear();
                    update_investment(GOAL_PATH, goal, investment, BAL_PATH, HISTORY_PATH, GOAL_HISTORY, '+');
                    printf("\nInvestment Success!\n");
                }
            else if(!invest_confirm){
                clear();
                loading(0, "Cancelling process", 3);
                clear();
                printf("Process cancelled.\n\n");
            }
            printf("Press enter to proceed. \n\n");
            wait_for_enter();
            break; // end of invest money
        }
       
        break;

            case 2: //take money
            clear();
            title("TAKE INVESTMENT");
            print_goal(); // causing an error
            if(!goal.investment){
                printf("You have no investment to take back.\n\n");
            }
            else{
                printf("How much would you like to take?: ");
                take_invest = take_investment(goal.investment);
                clear();
                confirm_take = confirm_take_investment(take_invest);
                if(confirm_take){
                    clear();
                    loading(0, "Updating goal", 3);
                    clear();
                    update_investment(GOAL_PATH, goal, take_invest, BAL_PATH, HISTORY_PATH, GOAL_HISTORY, '-');
                    printf("\n%d was added to your balance.\n", take_invest);    
                }
                else{
                    clear();
                    loading(0, "Cancelling process", 3);
                    clear();
                    printf("Process cancelled.\n\n");
                }
                
            }
            printf("Press enter to continue. ");
            wait_for_enter();
            break;
            

        case 3: // remove goal
            clear();
            title("Remove Goal");
            print_goal();
            int goal_removal = confirm_goal_removal(goal);
            if(goal_removal){
                remove_goal(GOAL_PATH, GOAL_HISTORY);
                clear();
                loading(0, "Removing goal", 3);
                clear();
                printf("Goal removed.\n\n");
                printf("Press enter to continue.\n");
                wait_for_enter();
                clear();
                goal = get_goal();
            }
            else if(!goal_removal){
                clear();
                loading(0, "Cancelling process", 3);
                clear();
                printf("Process cancelled.\n\n");
                printf("Press enter to continue.\n");
                wait_for_enter();
                clear();
            }

        break;
       
        case 4: goal_choice = 0; home = 'y'; break;
    }
    goal_choice = 0;
    if(home == 'y'){clear(); break;}

    if(!goal.name){
        clear();
        goal_menu();
        goal_choice = get_choice("no_goal");
        clear();
        if(goal_choice == 1){
            title("Set Goal");
            goal_buf.name = get_goal_name();           //get goal details
            goal_buf.amount = get_goal_amount();
            goal_buf.date = get_goal_date();

            int set_goal_confirmed = confirm_set_goal(goal_buf);

            
            if(set_goal_confirmed){
                if(update_goal(GOAL_PATH, GOAL_HISTORY, goal_buf)){
                    printf("Can't update goal\n");
                }
                clear();
                loading(0, "Updating goal", 3);
                clear();
                title("GOAL UPDATED!");
                printf("Press enter to return.\n");
                wait_for_enter();
                goal_choice = 0;
                goal = get_goal();
                continue;
            }
            else{
                clear();
                loading(0, "Cancelling process", 3);
                clear();
                printf("Process cancelled.\n\n");
                printf("Press enter to return.\n");
                wait_for_enter();
                goal_choice = 0;
                continue;
            }

        }
        else if(goal_choice == 2){   // return home
            goal_choice = 0;
            break;
        }
    }
    continue;
}
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