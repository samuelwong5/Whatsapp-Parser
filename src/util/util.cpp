#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include "util.h"

/* Checks that character given is '0' to '9'. */
bool 
is_int(char c) 
{
    if (c - '0' > 9) 
        return false;
    if (c - '0' < 0)
        return false;
   
    return true;   
}

/* Lower-case entire string. */
void 
to_lower(char *str)
{
    int slen = strlen(str);
    for (int i = 0; i < slen; i++) {
        if (str[i] - 'A' >= 0 && str[i] - 'Z' <= 0)
            str[i] = tolower(str[i]);
    }    
}

/* Non case-sensitive substring search. */
bool
str_cont(char *string, char *sub)
{  
    to_lower(string);
    return (strstr(string, sub) != NULL);
}
