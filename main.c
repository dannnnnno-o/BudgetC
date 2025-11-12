#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>
#include "includes/model/model.h"
#include "includes/ctrl/ctrl.h"
#include "includes/view/view.h"

#define BAL_PATH "includes/db/balance.txt"

int main(){
landing_page();
int current_balance;
int is_logged_in = login();

while(is_logged_in){
current_balance = get_balance();
menu();

int choice = get_choice("landing_page");
switch(choice){
case 1: // add balance 
int bal_buffer;
char comment;
while(1){
    printf("Add Balance\n\n");
    printf("How much would you like to add?: ");
    if(scanf("%d", &bal_buffer) == 1){
        while(1){
            printf("Would you like to add a comment? (y/n): ");
            if(scanf(" %c", &comment) != 1){
                break;
            } 
            else if(comment == 'n' || comment == 'N'){
                int add_check = add_balance(current_balance, bal_buffer, "n", BAL_PATH);
                if(add_check == 1){
                    exit(0);
                }
                
                load_add_bal();
                clear();
                printf("Balance updated!\n");
                break;
            }
/*             else if(comment == 'y' || comment == 'Y'){
                char *comment_buf;
                getchar();
                printf("What would you like to say?: ");
                scanf("%s", comment_buf);
                int check_add = add_balance(bal_buffer, comment_buf);
                load_add_bal();
                if(check_add == 1){
                    printf("Balance updated!\n");
                    return_home();
                } */
                else{
                    printf("Process failed. Please try again.\n");
                    break;
                }
            break;
            }
        }
    else{
        printf("Process failed.\n");
        continue;
    }
    break;
}
break;


case 4: printf("Thank you for using BudgetC!"); exit(0);
}
continue;  
}

return 0;
}