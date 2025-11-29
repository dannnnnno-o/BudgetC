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

void goal_menu(Goal goal);
void set_goal_menu();
void print_goal(Goal goal);



void logout();


/* error handlers */
void invalid_input();
void invalid_choice(int limit);
void invalid_balance_update(char *mode);
void invalid_goal_input(char *mode);


#endif