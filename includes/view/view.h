#ifndef VIEW_H
#define VIEW_H

void clear();

/* loading pages */
void loading(int start, char *message, int intervals);

/* UI */
void landing_page();
void menu();
void update_balance_menu();
void add_menu();
void spend_menu();
void history_menu();

void logout();


/* error handlers */
void invalid_input();
void invalid_choice(int limit);
void invalid_balance_update(char *mode);



#endif