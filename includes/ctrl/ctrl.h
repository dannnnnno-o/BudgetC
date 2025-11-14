#ifndef CTRL_H
#define CTRL_H

#include <stddef.h> // for size_t

void flush();
void strip(size_t len, char *comment_buffer);

int get_choice(char *mode);
int get_update_value(char *mode);
char comment_check(char comment);
int confirm(int bal_buffer, char *comment_buffer);

#endif