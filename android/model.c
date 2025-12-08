#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../includes/model/model.h"
#include "../includes/ctrl/ctrl.h"
#include "../includes/view/view.h"
#include "../includes/goal.h"

int get_balance(){
    FILE *balance = fopen("../includes/db/balance.txt", "r");
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

Goal get_goal(){
    FILE *file = fopen("../includes/db/goal.txt", "r");

    if (file == NULL) {
    perror("Error opening file");
    }





    char buffer[255];
    Goal goal = {NULL, 0, NULL, 0}; // initialize all to null for error handling
    for(int i = 0; i < 4; i++){
        if(fgets(buffer, sizeof(buffer), file) == NULL){break;}
        switch(i){
            case 0: goal.name = strdup(buffer); break;
            case 1: goal.amount = atoi(strdup(buffer)); break;
            case 2: goal.date = strdup(buffer); break;
            case 3: goal.investment = atoi(strdup(buffer)); break;
        }
    }
    fclose(file);
    return goal;
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
    char *curr_date;
    char *next_date;
    char *line;
    int i = 0;

    if(strcmp(mode, "all") == 0){
        line = fgets(buffer, sizeof(buffer), file);
        while(line != NULL){
            i++;
            curr_date = get_transact_date(buffer); // get curr_date
            if(i == 1){
                title(curr_date);
                printf("%s", buffer + 11);
            }
            line = fgets(buffer, sizeof(buffer), file); // get next_line
            next_date = get_transact_date(buffer); //get next_date
            if(strncmp(curr_date, next_date, 8) != 0){print_transact_date(next_date);} //print if curr != next
            if(line != NULL){printf("%s", line + 11);} //print line if(line)
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
        printf("Invalid transaction mode.\n");
    }

    fclose(file);
}

void update_investment(char *path, Goal goal, int x, char *bal_path, char *history, char *goal_history, char mode){
    int current_balance = get_balance();
    char *date;
    date = get_date();

    FILE *goal_file = fopen(path, "w"); 
    FILE *balance = fopen(bal_path, "w");
    FILE *history_file = fopen(history, "a");
    FILE *goal_history_file = fopen(goal_history, "a");
    strip(strlen(goal.name), goal.name);
    strip(strlen(goal.date), goal.date);

    if(mode == '+'){
        fprintf(goal_file, "%s\n%d\n%s\n%d", goal.name, goal.amount, goal.date, goal.investment + x);
        fprintf(balance, "%d", current_balance - x);
        fprintf(history_file, "%s | - %d: Invested on goal \"%s\".\n", date, x, goal.name);
        fprintf(goal_history_file, "%s | + %d: Invested on goal \"%s\".\n", date, x, goal.name);
    }

    else if(mode == '-'){
        fprintf(goal_file, "%s\n%d\n%s\n%d", goal.name, goal.amount, goal.date, goal.investment - x);
        fprintf(balance, "%d", current_balance + x);
        fprintf(history_file, "%s | + %d: Taken from investments \"%s\".\n", date, x, goal.name);
        fprintf(goal_history_file, "%s | - %d: Taken from investments \"%s\".\n", date, x, goal.name);
    }
    fclose(goal_file);
    fclose(balance);
    fclose(history_file);
    fclose(goal_history_file);
}


void complete_goal(char *goal_path, char *goal_history_path, Goal goal){
    char *date = get_date();
    strip(strlen(date), date);
    strip(strlen(goal.name), goal.name);
    
    FILE *goal_history = fopen(goal_history_path, "a");
    fprintf(goal_history, "%s | -- Goal \"%s\" Completed with target amount of %d. --", date, goal.name, goal.amount);

    remove_goal(goal_path);
    fclose(goal_history);
}
