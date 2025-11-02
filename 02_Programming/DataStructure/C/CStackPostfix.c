#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void init(Stack *s) { s->top = -1; }
void push(Stack *s, int val) { s->data[++(s->top)] = val; }
int pop(Stack *s) { return s->data[(s->top)--]; }

bool isNumber(const char *token)
{
    for (int i = 0; token[i] != '\0'; i++)
        if (!isdigit(token[i])) 
            return false;

    return true;
}

int Postfix()
{
    char expr[] = "10 2 8 + *";
    Stack stack;
    init(&stack);

    char *token = strtok(expr, " ");
    while (token != NULL)
    {
        if (isNumber(token))
        {
            push(&stack, atoi(token));
        }
        else
        {
            int right = pop(&stack);
            int left  = pop(&stack);

            switch (token[0])
            {
                case '+': 
                    push(&stack, left + right); 
                    break;
                case '-': 
                    push(&stack, left - right); 
                    break;
                case '*': 
                    push(&stack, left * right); 
                    break;
                case '/': 
                    push(&stack, left / right); 
                    break;
            }
        }

        token = strtok(NULL, " ");
    }

    printf("결과: %d\n", pop(&stack));
    return 0;
}