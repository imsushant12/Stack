//by Sushant Gaurav

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct arraystack
{
    int top;
    int capacity;
    char *ptr;
};

struct arraystack* createstack()
{
    struct arraystack *stackblock;
    stackblock=malloc(sizeof(struct arraystack));
    stackblock->capacity=50;
    stackblock->top=-1;
    stackblock->ptr=malloc(sizeof(char)*stackblock->capacity);
    return(stackblock);
};

char stacktop(struct arraystack *stack)
{
    return stack->ptr[stack->top];
}

int isEmpty(struct arraystack *stack)
{
    if(stack->top == -1)
        return 1;
    else
        return 0;
}

int isFull(struct arraystack *stack)
{
    if(stack->top == stack->capacity-1)
        return 1;
    else
        return 0;
}

void push(struct arraystack *stack,char data)
{
    stack->top++;
    stack->ptr[stack->top]=data;
}

char pop(struct arraystack *stack)
{
    char item=stack->ptr[stack->top];
    stack->top--;
    return item;
}

int isOperand(char x)
{
    if(x=='+' || x=='-' || x=='*' || x=='/' || x=='%')
        return 1;                                           
    else
        return 0;                                          
}

int precedence(char x)
{
    if(x=='+' || x=='-')
        return 1;                                           
    else if(x=='*' || x=='/' || x=='%')
        return 2;
    else
        return 0;
}

char * conversion(char *infix)
{
    struct arraystack *stack;
    stack=createstack();
    
    int i=0,j=0;

    char *postfix=(char *)malloc((strlen(infix)+1)*sizeof(char));
    
    while(infix[i] != '\0')
    {
        if(!isOperand(infix[i]))                             
        {
            postfix[j]=infix[i];
            j++;
            i++;
        }
        else
        {
            if(precedence(infix[i]) > precedence(stacktop(stack)))
            {
                push(stack,infix[i]);
                i++;
            }
            else
            {
                postfix[j]=pop(stack);
                j++;
            }
        }
    }
    while(!isEmpty(stack))
    {
        postfix[j]=pop(stack);
        j++;
    }
    postfix[j]='\0';
    return postfix;
}

void main()
{
    int cap;
    char *infix[50];
    printf("\nEnter your expression : ");
    gets(infix);
    printf("\nPostfix is %s \n\n",conversion(infix));
}
