#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>
#include "model.h"
#include "../ctrl/ctrl.h"
#include "../view/view.h"

int get_balance(){
    FILE *balance = fopen("includes/db/balance.txt", "r");
    int bal;
    fscanf(balance, "%d", &bal);
    fclose(balance);
    return bal;
}

void update_balance(char mode, int current_bal, int bal_buffer, char *bal_path){
    FILE *balance = fopen(bal_path, "w");
    int updated_bal;

    if(mode == '+'){
        updated_bal = current_bal + bal_buffer;
    }
    else{
        updated_bal = current_bal - bal_buffer;
    }
    fprintf(balance, "%d", updated_bal);
    fclose(balance);
}

void update_history(char mode, int bal_buffer, char *comment, char *history){
    char *date;
    date = get_date();
    if(strcmp(comment, "n") == 0){
        comment = "no comment.";
    }
    FILE *history_file = fopen(history, "a");
    if(mode == '+'){
        fprintf(history_file, "%s | + %d: %s\n", date, bal_buffer, comment);
    }
    else{
        fprintf(history_file, "%s | - %d: %s\n", date, bal_buffer, comment);
    }
    fclose(history_file);
}

int update_account(char mode, int current_balance, int bal_buffer, char *comment, char *balance_path, char *history_path){
    update_balance(mode, current_balance, bal_buffer, balance_path);
    update_history(mode, bal_buffer, comment, history_path);
    return 0;
}

void view_transactions(char *mode, char *history_path){
    FILE *file = fopen(history_path, "r");
    char buffer[256];
    char *curr_date;
    char *next_date;
    char *line;
    int i = 0;

    if(strcmp(mode, "all") == 0){
        line = fgets(buffer, sizeof(buffer), file);
        while(line != NULL){
            i++;
            curr_date = get_transact_date(buffer); // get curr_date
            line = fgets(buffer, sizeof(buffer), file); // get next_line
            next_date = get_transact_date(buffer); //get next_date
            if(strncmp(curr_date, next_date, 8) != 0){print_transact_date(next_date);} //print if curr != next
            if(line != NULL){printf("%s", line);} //print line if(line)
        }
        if(!i){
            printf("\nYou have not completed any transactions yet.\n");
        }
    }

    else if(strcmp(mode, "add") == 0){
        while(fgets(buffer, sizeof(buffer), file) != NULL){
            i++;
            if(buffer[11] == '+'){
            printf("%s", buffer);
            }
        }
        if(!i){
            printf("\nYou have not added any amount to your balance yet.\n");
        }
    }

    else if(strcmp(mode, "spent") == 0){
        while(fgets(buffer, sizeof(buffer), file) != NULL){
            i++;
            if(buffer[11] == '-')
            printf("%s", buffer);
        }
        if(!i){
            printf("\nYou have not spent any amount yet.\n");
        }
    }
    else{
        printf("invalid transaction mode.\n");
    }

    fclose(file);
}

/* char *get_transact_date(char *transaction){
    char *date;
    for(int i = 0; i < 9; i++){
        date[i] = transaction[i];
        printf("%c\n", date[i]);
    }
} */


/* 
store current date -> compare to next 

if(cur_date == next_date){continue;}
else{printf("\n");}


*/

/*

11-26-25 | - 10: no comment.
-- store current date
11-26-25 | - 200: no comment. //compares
11-26-25 | - 200: sample comment //compares

-- separates because of diff date-- 

11-27-25 | - 200: sample comment //compares != == separate & store date
11-27-25 | - 200: sample comment //compares
11-27-25 | - 200: sample comment //compares

-- separates because of diff date-- 

11-28-25 | - 200: sample comment //compares != == separate & store date
11-28-25 | - 200: sample comment
11-28-25 | - 200: sample comment



*/