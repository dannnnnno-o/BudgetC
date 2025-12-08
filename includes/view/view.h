#ifndef VIEW_H
#define VIEW_H
#include "../goal.h"
void clear();

/* loading pages */
void loading(int start, char *message, int intervals);

/* UI */
void title(char *title);
void landing_page();
void menu();
void update_balance_menu();
void add_menu();
void spend_menu();
void history_menu();
void print_transact_date(char *date);

void print_goal();
void print_goal_buffer(Goal goal);
void format_goal(Goal goal);
void goal_menu();



void logout();


/* error handlers */
void invalid_input();
void invalid_choice(int limit);
void invalid_balance_update(char *mode);

void print_transact_date(char *date);

void invalid_goal_input(char *mode);
void invalid_invest(char *mode);
void invalid_take_investment(char *mode);

#endif