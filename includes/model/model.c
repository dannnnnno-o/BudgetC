#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>

#include "model.h"
#include "../transact.h"

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
    if(strcmp(comment, "n") == 0){
        comment = "no comment.";
    }
    FILE *history_file = fopen(history, "a");
    if(mode == '+'){
        fprintf(history_file, "+ %d: %s\n", bal_buffer, comment);
    }
    else{
        fprintf(history_file, "- %d: %s\n", bal_buffer, comment);
    }
    fclose(history_file);
}

int update_account(char mode, int current_balance, int bal_buffer, char *comment, char *balance_path, char *history_path){
    update_balance(mode, current_balance, bal_buffer, balance_path);
    update_history(mode, bal_buffer, comment, history_path);
    return 0;
}

int get_line_count(char *path){
    FILE *file = fopen(path, "r");
    char buffer[256];
    int line = 0;
    while(fgets(buffer, sizeof(buffer), file) != NULL){
        line++;
        // printf("%d == %s", line, buffer);
    }
    fclose(file);
    return line;
}

Transact *get_transactions(char *mode, char *history_path, int count){

Transact *transactions = malloc(count);
FILE *file = fopen(history_path, "r");
char buffer[1024];

while(fgets(buffer, sizeof(buffer), file)){
    if(strcmp(mode, "all") == 0){
        
    }
    else if(strcmp(mode, "add") == 0){

    }
    else if(strcmp(mode, "spent") == 0){

    }
    else{
        printf("invalid transaction mode.\n");
    }
}
return transactions;
}