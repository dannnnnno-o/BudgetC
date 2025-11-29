#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>
#include "model.h"
#include "../ctrl/ctrl.h"

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

int update_goal(char *path, Goal goal){
    FILE *file = fopen(path, "w");
        if (fprintf(file, "%s\n%d\n%s", goal.name, goal.amount, goal.date ) < 0) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    fclose(file);
    return 0;
}

void remove_goal(char *path){
    FILE *file = fopen(path, "w");
    fclose(file);
}


void view_transactions(char *mode, char *history_path){
    FILE *file = fopen(history_path, "r");
    char buffer[256];
    int i = 0;


    if(strcmp(mode, "all") == 0){
        while(fgets(buffer, sizeof(buffer), file) != NULL){
            i++;
            printf("%s", buffer);
        }
        if(!i){
            printf("\nYou have not completed any transactions yet.\n");
        }
    }

    else if(strcmp(mode, "add") == 0){
        while(fgets(buffer, sizeof(buffer), file) != NULL){
            if(buffer[11] == '+'){
                i++;
                printf("%s", buffer);
            }
        }
        if(!i){
            printf("\nYou have not added any amount to your balance yet.\n");
        }
    }

    else if(strcmp(mode, "spent") == 0){
        while(fgets(buffer, sizeof(buffer), file) != NULL){
            if(buffer[11] == '-'){
                i++;
                printf("%s", buffer);
            }
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

