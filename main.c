#include "main.h"

#define MAX_BUFFER_SIZE 1024
#define MAX_NUMBER_SIZE 64

typedef enum {
	TOK_NUMBER,
	TOK_OPERATOR,
	TOK_PARANTH_OPEN,
	TOK_PARANTH_CLOSE
} TokenType;

typedef struct {
	const char *symbol;
	int precedence;
} Operator;

typedef struct {
	TokenType type;
	char *value;
	Operator *op;
} Token;

// operators[i].symbol[0] to access
Operator operators[] = {
	{"+", 10},
	{"-", 10},
	{"*", 20},
	{"/", 20},
	{"^", 50}
};

// macro for ease of for loop n'ing
#define NR_OF_OPERATORS (sizeof(operators) / sizeof(operators[0]))

char *my_strndup(const char *s, size_t n)
{
	size_t len = strlen(s);
	
	if (len > n)
		len = n;
	
	char *copy = malloc(len + 1);
	if (!copy)
		return NULL;

	memcpy(copy, s, len);
	copy[len] = '\0';

	return copy;
}

void remove_whitespace(char *str)
{
	char *src = str;
	char *dst = str;

	while (*src) {
		if (*src != ' ' && *src != '\t' && *src != '_') {
			*dst++ = *src;
		}
		src++;
	}
	*dst = '\0';
	printf("String after removing whitespace: %s\n", str);
}

// convert , to .
void standardise(char *input)
{
	int i = 0;
	int len = strlen(input);
	
	while (i < len) {
		if (input[i] == ',') {
			input[i] = '.';
		}
		i++;
	}
}
// convert string without spaces in it to tokens (string separated by null terminators)
// todo: handle EVERY INPUT not just the ones here, every input should go to else not to else if like is doing now
Token *tokenize_input(char *input, int *nr_of_tokens)
{
	int len = strlen(input);
	// char **array_of_tokens = malloc(len * sizeof(char *));
	Token *tokens = malloc(len * sizeof(Token));

	int i = 0;
	int k = 0;
	while (i < len) {
		if (isdigit(input[i])) {
			char number[MAX_NUMBER_SIZE];
			int j = 0;

			while (i < len && (isdigit(input[i]) || input[i] == '.'))
				number[j++] = input[i++];

			number[j] = '\0';

			// array_of_tokens[k] =  malloc(strlen(number) + 1); 
			tokens[k].type = TOK_NUMBER;
			tokens[k].value = strdup(number);
			tokens[k].op = NULL;
			k++;

			printf("Token: %s\n", number);
		} else if (isalpha(input[i])) {
			i++;
			continue;	
		} else {
			char c = input[i];
			
			if (c == '(') {
				tokens[k].type = TOK_PARANTH_OPEN;
				tokens[k].value = my_strndup(&c, 1);
				tokens[k].op = NULL;
			} else if (c == ')') {
				tokens[k].type = TOK_PARANTH_CLOSE;
				tokens[k].value = my_strndup(&c, 1);
				tokens[k].op = NULL;
			} else {
				tokens[k].type = TOK_OPERATOR;
				tokens[k].value = my_strndup(&c, 1);
				
				for (size_t a = 0; a < NR_OF_OPERATORS; a++) {
					if (operators[a].symbol[0] == c) {
						tokens[k].op = &operators[a];
					}
				}
				
			}
			
			printf("Token %c\n", c);

			// incrementor of while loop.
			i++;
			// counter of tokens
			k++;
		}
	}

	*nr_of_tokens = k;

	return tokens;
}	

//todo: convert the tokens to postfix format
// char **infix_to_postfix(char **tokens, int n)
// {
// 	// only holds pointers to strings that will be allocated later
// 	char **output = malloc(n * sizeof(char *));
// 	int k = 0;

// 	stack_t *op_stack = st_create(sizeof(char));

// 	for (int i = 0; i < n; i++) {
// 		if (isdigit(tokens[i][0])) {
// 			output[k] = malloc(strlen(tokens[i]) + 1);
// 			strcpy(output[k], tokens[i]);			
// 			k++;
// 		} else if (tokens[i][0] == '(') {
// 			st_push(op_stack, (void *)tokens[i]);
// 		} else if (tokens[i][0] == ')') {

// 		} else {
// 			int isOperator = 0;
// 			for (size_t i = 0; i < NR_OF_OPERATORS; i++) {
// 				if (operators->symbol[i] == tokens[i][0]) {
// 					isOperator = 1;
// 					break;
// 				}
// 			}

// 			if (isOperator) {
				
// 			} else {
// 				printf("Unknown operand: %s", tokens[i][0]);
// 				break;
// 			}
			
// 		}
		
// 	}
// 	return output;
// }

int main() {
	char input[MAX_BUFFER_SIZE];

	printf("Enter a string: ");

	if (fgets(input, sizeof(input), stdin)) {		
		int len = strlen(input);

		// remove newline
		if (input[len - 1] == '\n')
			input[len - 1] = '\0';
		
		printf("You entered: %s\n", input);
	} else {
		printf("Error reading input.\n");
		return 1;
	}

	remove_whitespace(input);
	standardise(input);
	int nr_of_tokens;
	Token *tokens = tokenize_input(input, &nr_of_tokens);

	// char **postfix_input = infix_to_postfix(tokens, nr_of_tokens);
	
	return 0;
}