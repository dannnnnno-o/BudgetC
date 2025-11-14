#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>
#include <stddef.h>

#include "ctrl.h"
#include "../view/view.h"


void flush(){
int flush_buffer;
while ((flush_buffer = getchar()) != '\n' && flush_buffer != EOF);
}

void strip(size_t len, char *comment_buffer){
    if(len > 0 && comment_buffer[len - 1] == '\n'){
        comment_buffer[len - 1] = '\0';
    }
}



int get_choice(char *mode){
int choice = 0;    

/* landing page */
if(strcmp(mode, "landing_page") == 0){
    while(1){
        if(scanf("%d", &choice) != 1){
            clear();
            invalid_choice(5);
            menu();
            flush();
            continue;    
        }
        if(choice <= 0 || choice > 5){
            clear();
            invalid_choice(5);
            menu();
            flush();
            continue;
        }
        else{
            getchar();
            break;
        }
    }
}

/* update balance */
if(strcmp(mode, "update_balance") == 0){
        while(1){
        if(scanf("%d", &choice) != 1){
        clear();
        invalid_choice(3);
        update_balance_menu();
        flush();
        continue;
        }
        if(choice <= 0 || choice > 3){
        clear();
        invalid_choice(3);
        update_balance_menu();
        flush();
        continue;
        }
        else{
            getchar();
            break;
        }
    }
}

/* comment choice */
if(strcmp(mode, "comment") == 0){
char c;
while(1){
    printf("Would you like to add a comment? (y/n): ");

    if(scanf(" %c", &c) != 1){
        flush();
        clear();
        invalid_input();
        continue;
    }

    else if(c == 'y' || c == 'Y'){choice = 1; break;}

    else if(c == 'n' || c == 'N'){break;} // choice is 0 by default
    else{
        clear();
        invalid_input();
        continue;
    }
}
}

/* confirm update */
if(strcmp(mode, "confirm_update") == 0){
char c;
while(1){
    printf("Would you like to add a comment? (y/n): ");

    if(scanf(" %c", &c) != 1){
        flush();
        clear();
        invalid_input();
        continue;
    }

    else if(c == 'y' || c == 'Y'){choice = 1; break;}

    else if(c == 'n' || c == 'N'){break;} // choice is 0 by default
    else{
        clear();
        invalid_input();
        continue;
    }
}
}

return choice;
}

int get_update_value(char *mode){
int value = 0;
/* add */
if(strcmp(mode, "add") == 0){
    while(1){
    
    if(scanf("%d", &value) != 1){
        clear();
        invalid_balance_update("string");
        flush();
        add_menu();
        continue;
    }
    else if(value <= 0){
        clear();
        invalid_balance_update("negative");
        flush();
        add_menu();
        continue;
    }
    else{
        break;
    }

    }
}

/* spend */


return value;
}


int confirm(int bal_buffer, char *comment_buffer){
int choice = 0;
char c;
while(1){
    printf("Add: %d\n", bal_buffer);
    printf("Comment: %s\n", comment_buffer);
    printf("Are you sure you want to update your balance? (y/n): ");

    if(scanf(" %c", &c) != 1){
        flush();
        clear();
        invalid_input();
        continue;
    }

    else if(c == 'y' || c == 'Y'){choice = 1; break;}

    else if(c == 'n' || c == 'N'){break;} // choice is 0 by default
    else{
        clear();
        invalid_input();
        continue;
    }
}
return choice;
}