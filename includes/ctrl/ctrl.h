#ifndef CTRL_H
#define CTRL_H

#include <stddef.h> // for size_t
#include "../goal.h" // for Goal

void flush();
void strip(size_t len, char *comment_buffer);

int login();
int get_choice(char *mode);
int get_update_value(char mode);
int confirm(char mode, int bal_buffer, int comment, char *comment_buffer);
char *get_comment();
void wait_for_enter();
char *get_date();

char *get_goal_name();
int get_goal_amount();
char *get_goal_date();
float get_goal_progress(int investment, int amount);

int confirm_goal_removal(Goal goal);
int invest(int bal);
int confirm_investment(int investment);

int take_investment(int goal_investment);

#endif