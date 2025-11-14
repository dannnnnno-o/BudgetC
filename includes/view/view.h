#ifndef VIEW_H
#define VIEW_H

void clear();

/* loading pages */
void load_add_bal();


/* UI */
int login();
void landing_page();
void menu();
void update_balance_menu();
void add_menu();
void spend_menu();


/* error handlers */
void invalid_input();
void invalid_choice(int limit);
void invalid_balance_update(char *mode);

#endif