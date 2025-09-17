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

Token *infix_to_postfix(Token *tokens, int n, int *output_n)
{
	Token *output = malloc(n * sizeof(Token));
	stack_t *op_stack = st_create(sizeof(Token));

	int k = 0;
	for (int i = 0; i < n; i++) {
		Token t = tokens[i];

		switch (t.type) {
		
		case TOK_NUMBER:
			// numbers go straight to output
			output[k++] = t;
			break;
		case TOK_OPERATOR: {
			Token top;
			while (!st_is_empty(op_stack)) {
				
				// we dont use top = stpeek because it is dangerous to work with it after. rather just copy into it for less issues.
				memcpy(&top, st_peek(op_stack), sizeof(Token));

				if (top.type == TOK_OPERATOR &&
					top.op->precedence >= t.op->precedence) {
						st_pop(op_stack);
						output[k++] = top;
				} else {
					break;
				}
			}
			
			st_push(op_stack, &t);
			break;
		}
		case TOK_PARANTH_OPEN:
			st_push(op_stack, &t);
			break;
		case TOK_PARANTH_CLOSE: {
			Token top;
			while (!st_is_empty(op_stack)) {
				
				memcpy(&top, st_peek(op_stack), sizeof(Token));
				st_pop(op_stack);

				if (top.type == TOK_PARANTH_OPEN) {
					break;
				} else {
					output[k++] = top;
				}
			}
			break;
		}
		}
	}

	while (!st_is_empty(op_stack)) {
		Token top;
		memcpy(&top, st_peek(op_stack), sizeof(Token));
		st_pop(op_stack);
		output[k++] = top;
	}
	
	*output_n = k;


	printf("Postfix expression:\n");
	for (int i = 0; i < k; i++) {
		Token t = output[i];
		switch (t.type) {
			case TOK_NUMBER:
				printf("NUMBER: %s\n", t.value);
				break;
			case TOK_OPERATOR:
				printf("OPERATOR: %s (precedence %d)\n", t.value, t.op->precedence);
				break;
			case TOK_PARANTH_OPEN:
				printf("PAREN_OPEN: %s\n", t.value);
				break;
			case TOK_PARANTH_CLOSE:
				printf("PAREN_CLOSE: %s\n", t.value);
				break;
			default:
				printf("UNKNOWN TOKEN: %s\n", t.value);
				break;
		}
	}
	return output;
}

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

	int output_n;
	Token *formatted_to_postfix = infix_to_postfix(tokens, nr_of_tokens, &output_n);
	
	return 0;
}