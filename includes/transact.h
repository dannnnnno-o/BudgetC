#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct {
    char mode; // + or -
    char *tag;
    int amount; 
    char *comment;
} Transaction;


#endif