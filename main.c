#include "main.h"

#define MAX_BUFFER_SIZE 1024
#define MAX_NUMBER_SIZE 64

void remove_whitespace(char *str)
{
	char *src = str;
	char *dst = str;

	while (*src) {
		if (*src != ' ' && *src != '\t') {
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
void tokenize_input(char *input)
{
	int i = 0;
	int len = strlen(input);

	while (i < len) {
		if (isdigit(input[i])) {
			char number[MAX_NUMBER_SIZE];
			int j = 0;
			while (i < len && (isdigit(input[i]) || input[i] == '.')) {
				number[j++] = input[i++];
			}
			number[j] = '\0';
			printf("Token: %s\n", number);
		} else {
			// hardcoded to operator + '\0' for now
			char op[2] = {input[i], '\0'};
			printf("Token %s\n", op);
			i++;
		}
	}
}	

//todo: convert the tokens to postfix format
char *infix_to_postfix(char *s)
{
	
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
	tokenize_input(input);

	char *postfix_input;

	// postfix_input = infix_to_postfix(input);
	
	return 0;
}