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

int add_balance(int current_balance, int bal_buffer, char *comment, char *balance_path){
    FILE *balance = fopen(balance_path, "w");
    if(balance == NULL){
        perror("Error opening file");
        return 1;
    }
    int updated_bal = current_balance + bal_buffer;
    if(strcmp(comment, "n") == 0){
        if (fprintf(balance, "%d", updated_bal) < 0) {
            perror("fprintf failed");
            fclose(balance);
            return 1;
        }

        fclose(balance);
        return 0;
    }
    fclose(balance);
    return 1;
}