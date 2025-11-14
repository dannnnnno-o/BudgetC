#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>
#include "model.h"

int get_balance(){
    FILE *balance = fopen("includes/db/balance.txt", "r");
    int bal;
    fscanf(balance, "%d", &bal);
    fclose(balance);
    return bal;
}

int update_balance(int current_balance, int bal_buffer, char *comment, char *balance_path, char *add_history_path){
    FILE *balance = fopen(balance_path, "w");
    if(balance == NULL){
        perror("Error opening file");
        return 1;
    }
    int updated_bal = current_balance + bal_buffer;

    if(strcmp(comment, "n") == 0){
        if (fprintf(balance, "%d", updated_bal) < 0) {
            perror("fprintf failed.\n");
            fclose(balance);
            return 1;
        }

        fclose(balance);
        return 0;
    }

    else if(strcmp(comment, "n") != 0){
        FILE *add_history = fopen(add_history_path, "a");

        if (fprintf(balance, "%d", updated_bal) < 0){
            perror("fprintf failed.\n");
            fclose(balance);
            return 1;
        }

        if(fprintf(add_history, "+ %d - %s", bal_buffer, comment) < 0){
            perror("add_balance fprintf failed.\n");
            fclose(balance);
            fclose(add_history);
            return 1;
        }
        fclose(balance);
        fclose(add_history);
        return 0;
    }

    fclose(balance);
    return 1;
}