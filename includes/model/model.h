#ifndef MODEL_H
#define MODEL_H

#include "../transact.h"


int get_balance(); // returns current balance.

void update_balance(char mode, int current_bal, int bal_buffer, char *bal_path);
void update_history(char mode, int bal_buffer, char *comment, char *history);

int update_account(char mode, int current_balance, int bal_buffer, char *comment, char *balance_path, char *history_path); // returns 0 if process failed.



#endif