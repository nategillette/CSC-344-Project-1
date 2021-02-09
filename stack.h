#ifndef C_PROJECT_STACK_H
#define C_PROJECT_STACK_H
#include "main.h"
struct node
{
    int data;
    struct node *next;
};
typedef struct node node;
void initialize();
void push(int value);
int pop();
int Top();
int isempty();
void display(node *head);

#endif //C_PROJECT_STACK_H
