#ifndef MODEL_H
#define MODEL_H

int get_balance(); // returns current balance.
int update_balance(int current_balance, int bal_buffer, char *comment, char *balance_path, char *add_history_path); // returns 0 if process failed.

#endif