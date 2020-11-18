#ifndef COMMANDEXECUTOR
#define COMMANDEXECUTOR

#include "Shell.h"

void expand_macro(token t); // *-->Home, .-->Parent_Directory, etc.

void exec_tree(token* tokens, int num_tokens);
void exec_mkdir(token* tokens, int num_tokens);
void exec_mkfil(token* tokens, int num_tokens);
void exec_cd(token* tokens, int num_tokens);
void exec_ls(token* tokens, int num_tokens);
void exec_env(token* tokens, int num_tokens);
void exec_macro(token* tokens, int num_tokens);
void exec_echo(token* tokens, int num_tokens);
void exec_lac();
void exec_prtc(token* tokens, int num_tokens);

#endif