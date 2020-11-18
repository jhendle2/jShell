#ifndef ERRORTABLE
#define ERRORTABLE

/* Shell Errors */
void ERROR_not_enough_params();

/* File Errors */
void ERROR_file_not_found();
void ERROR_file_not_in_lookup_table();

/* Macro Errors */
void ERROR_cannot_expand_macro();
void ERROR_macro_lacking_output();

/* Environment Variable Errors */
void ERROR_no_env_variable();
void ERROR_dup_env_variable();

#endif