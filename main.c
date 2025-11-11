#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>
#include "includes/model/model.h"
#include "includes/ctrl/ctrl.h"
#include "includes/view/view.h"

int main(){
landing_page();
int balance;

int is_logged_in = login();



while(is_logged_in){
menu();

int choice = get_choice("landing_page");
switch(choice){
case 1: balance = get_balance();

case 4: printf("Thank you for using BudgetC!"); exit(0);
}

printf("%d", get_balance());
return 0;
}
}