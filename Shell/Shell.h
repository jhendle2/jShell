#ifndef SHELL
#define SHELL

#define SHELL_BUFFER_LENGTH 128
#define TOKEN_LENGTH 16
#define MAX_TOKENS 32

#include "ShellCommands.h"

typedef struct token{
	char str[TOKEN_LENGTH];
} token;

char* Shell_bootup_message;
void boot();

void shell_loop();
int tokens_from_line(char line[SHELL_BUFFER_LENGTH], token* tokens);
enum ShellCommand get_command(token* tokens);
void evaluate_command(enum ShellCommand sc, token* tokens, int num_tokens);
void print_tokens();

#endif