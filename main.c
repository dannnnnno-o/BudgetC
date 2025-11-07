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
landingPage();
int is_logged_in = login();

while(is_logged_in){
    printf("What would you like to do?: ");
    printf("1. Add Balance\n");
    printf("2. Spend \n");
    printf("3. View Statistics\n");
    printf("4. Logout\n");
}


    return 0;
}