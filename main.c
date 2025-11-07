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
int is_logged_in = login();

while(is_logged_in){
/* printf("1. Add Balance\n");
printf("2. Spend \n");
printf("3. View Statistics\n");
printf("4. Logout\n");
printf("What would you like to do?: ");

int choice = get_choice("landing_page");
switch(choice){
case 1: get_balance();

case 4: printf("Thank you for using BudgetC!"); exit(0);
}
} */

printf("%d", get_balance());
return 0;
}
}