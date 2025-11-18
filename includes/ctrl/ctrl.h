#ifndef CTRL_H
#define CTRL_H

#include <stddef.h> // for size_t
#include "../transact.h"


void flush();
void strip(size_t len, char *comment_buffer);

int login();
int get_choice(char *mode);
int get_update_value();
int confirm(char mode, int bal_buffer, int comment, char *comment_buffer);
char *get_comment();

#endif