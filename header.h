// header.h

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void comment_remove(char* );
void macro_substitute(char* );
void header_include(char* file);
void replace_word(char *file,  char *new, char *old);
