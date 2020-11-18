#ifndef SHELLCOMMANDS
#define SHELLCOMMANDS

enum ShellCommand{
	SC_none, // Noop
	SC_tree, // List files in directory as hierarchy tree
	SC_mkdir, // Make a directory
	SC_mkfil, // Make a file
	SC_cd, // List current directory or move to another
	SC_ls, // List all files in a current directory
	SC_env, // Create?, display, or modify an environment variable
	SC_macro, // Create, display, or modify a macro
	SC_echo, // Echo back what was written
	SC_lac, // List all commands
	SC_prtc // Modify or display file's protections
};

#endif