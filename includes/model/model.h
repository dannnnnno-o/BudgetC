#ifndef MODEL_H
#define MODEL_H

#include "../goal.h"

int get_balance(); // returns current balance.

Goal get_goal();
void update_balance(char mode, int current_bal, int bal_buffer, char *bal_path);
void update_history(char mode, int bal_buffer, char *comment, char *history);
int update_goal(char *path, char *goal_history_path, Goal goal);
void remove_goal(char *path, char *goal_history_path, int investment, int isComplete);
void update_investment(char *path, Goal goal, int x, char *bal_path, char *history, char *goal_history, char mode);
void complete_goal(char *goal_path, char *goal_history_path, Goal goal);

int update_account(char mode, int current_balance, int bal_buffer, char *comment, char *balance_path, char *history_path); // returns 0 if process failed.


void view_transactions(char *mode, char *history_path);
void view_goal_history(char *history_path);


#endif