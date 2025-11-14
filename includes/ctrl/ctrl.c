#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>
#include "ctrl.h"


void flush(){
int flush_buffer;
while ((flush_buffer = getchar()) != '\n' && flush_buffer != EOF);

}

int get_choice(char *mode){
int choice = 0;    
if(strcmp(mode, "landing_page") == 0){
    while(1){
    if(scanf("%d", &choice) != 1){
    printf("Invalid input. Please choose from 1-5.\n");
    }
    if(choice <= 0 || choice > 5){
        printf("Invalid input. Please choose from 1-5.\n");
    }
    getchar();
    break;
    }
}
return choice;
}