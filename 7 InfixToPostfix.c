#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

char stack[100];
int tos = -1;

void push(char c)
{
	stack[++tos] = c;
}
char pop()
{
	return stack[tos--];
}
char peep()
{
	return stack[tos];
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

int getPrecedence(char op)
{
	switch(op)
	{
		case '(': return 0;
		case '+':
		case '-': return 1;
		case '*':
		case '/':
		case '%': return 2;
	}
	return INT_MIN;
}

void infixToPostfix(char infix[], char postfix[])
{
	int j = 0;
	char token;
	for(int i=0; infix[i] != '\0'; i++)
	{
		// read a token from infix
		token = infix[i];		
		
		if(token == '(')
			push(token);
		else if(token == ')')
		{
			// pop and send all the tokens to output until '(' is encountered
			while(tos > -1 && peep() != '(')
				postfix[j++] = pop();
			pop(); // pop '('
		}
		else if(isOperator(token)) // token is an operator
		{
			// pop and send all operators of greater or equal precedence than 
			// the token to output
			while(tos > -1 && getPrecedence(peep()) >= getPrecedence(token))
				postfix[j++] = pop();
			// then push the current token
			push(token);
		}
		else // token is an operand
			// send to output
			postfix[j++] = token;
	}
	
	// after processing all the tokens, pop all operands and send to output
	while(tos > -1)
		postfix[j++] = pop();
	
	// terminate postfix string
	postfix[j] = '\0';
}

int main(void)
{
	char infix[81];
	char postfix[81];
	// input
	printf("Enter infix expression: ");
	scanf(" %s", infix);
	// process
	infixToPostfix(infix, postfix);
	// output
	printf("Postfix expression:     %s\n", postfix);
	return 0;	
}
