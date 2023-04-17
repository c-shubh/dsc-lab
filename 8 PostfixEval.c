#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int stack[100];
int tos = -1;

void push(int c)
{
	stack[++tos] = c;
}
int pop()
{
	return stack[tos--];
}

bool isOperator(char c)
{
	switch(c)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '%': return true;
	}
	return false;
}

int compute(int op1, char op, int op2)
{
	switch(op)
	{
		case '+': return op1 + op2;
		case '-': return op1 - op2;
		case '*': return op1 * op2;
		case '/': if(op2 != 0) 
					return op1 / op2;
				  break;
		case '%': if(op2 != 0)
					return op1 % op2;
				  break;
	}
	return INT_MIN;
}

int evaluate(char postfix[])
{
	int op1, op2;
	char token;
	for(int i=0; postfix[i] != '\0'; i++)
	{
		// read a token from postfix
		token = postfix[i];
		
		if(isOperator(token)) // token is an operator
		{
			// get operands from stack
			op2 = pop();
			op1 = pop();
			// push the computed result to stack
			push(compute(op1, token, op2));
		}
		else // token is an operand
			// push to operand stack
			push(token - '0');
	}
	
	// after processing all tokens, the last value in stack is the result
	int result = pop();
	return result;
}

int main(void)
{
	char postfix[81];
	// input
	printf("Enter postfix expression: ");
	scanf(" %s", postfix);
	// process
	int res = evaluate(postfix);
	// output
	printf("Result: %d\n", res);
	return 0;	
}
