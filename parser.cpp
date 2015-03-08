#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include "list.h"

void parse_message(char *text, struct list *l, char *keyword);
void parse_messages(FILE *input, char *keyword);

/* Helper functions */

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

/* Checks that the given parameter string has the same
   length and is the same with the flag. */
bool 
check_flag(char *param, const char *flag) 
{
    unsigned slen = strlen(param);
    if (slen != strlen(flag)) { return false; }
    if (strncmp(param, flag, slen) == 0) 
        return true;
    return false;    
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

/* Parses one message and adds to the list of counters. */
void
parse_message(char *text, struct list *l, char *keyword)
{
    char *name;
    char *message;
    
    /* Check text contains a date. */
    if (strlen(text) < 5) { return; }
    if (!(is_int(text[0]) && is_int(text[1]) && is_int(text[3]) && is_int(text[4]))) { return; }
    if (strstr(text, "-") == NULL) { return; }
    
    name = strtok(text, "-");               /* Name points to date. */
    name = strtok(NULL, "-");               /* Name points to name and message. */
    while (name[0] == ' ') { name++; }
    if (strstr(name, ":") == NULL) { return; }
    name = strtok(name, ":");               /* Name points to name and excludes message. */
    if(keyword==NULL){
        char *new_name = (char *) malloc(strlen(name));
        strcpy(new_name, name);
        list_add(l, new_name);
    } else {
        message = strtok(NULL, ":");
        if(str_cont(message, keyword)){ /* Message contains keyword. */
            char *new_name = (char *) malloc(strlen(name));
            strcpy(new_name, name);
            list_add(l, new_name);
        }    
    }
} 

/* Parses a whole file of messages. */
void 
parse_messages(FILE *input, char *keyword, bool sort)
{
    struct list *l = list_init();
    char *text = (char *) malloc(500);
          
    while (fgets(text, 500, input) != NULL) {
        parse_message(text, l, keyword);
    }
    if (sort) 
        list_sort(l);
    list_print(l);
    list_free(l);    
}

int 
main(int argc, char **argv)
{
    char *keyword;
    FILE *input;

    /* Check whether file exists. */
    if ((input = fopen(argv[1], "r")) == NULL) {
        printf("Error reading input file.");  
        exit(-1);
    }
    
    /* Declare flags. */
    bool total_msg = false;
    bool sort = false;
    
    const char *key = "--keyword";
    const char *key2 = "-k";
    const char *media = "--media";
    const char *media2 = "-m";
    char *media_kw = "<media omitted>";
    const char *totalmsg = "--all";
    const char *totalmsg2 = "-a";
    const char *srt = "--sort";
    const char *srt2 = "-s";
  
    for(int i = 2; i < argc; i++) {
        if (check_flag(argv[i], srt) || check_flag(argv[i], srt2)) 
            sort = true;
    }
    
    /* Check flags. */
    for(int i = 2; i < argc; i++) {
        if (check_flag(argv[i], key) || check_flag(argv[i], key2)) {
            while (i < argc - 1) {
                i++;
                if (argv[i][0] == '-') {
                    i--;
                    break;
                } else {
                    keyword = (char *) malloc(strlen(argv[i]));
                    strcpy(keyword, argv[i]);
                    to_lower(keyword);
                    printf("Messages containing %s:\n", keyword);
                    parse_messages(input, keyword, sort);
                    printf("\n");
                    fseek(input, 0, SEEK_SET);
                    free(keyword);
                }
            }
        } else if (check_flag(argv[i], media) || check_flag(argv[i], media2)) {
            printf("Messages containing media.\n");
            parse_messages(input, media_kw, sort);
            printf("\n");
            fseek(input, 0, SEEK_SET);
        } else if (check_flag(argv[i], totalmsg) || check_flag(argv[i], totalmsg2)){
            total_msg = true;
        } else {
            if (!(check_flag(argv[i], srt) || check_flag(argv[i], srt2)))
                printf("Unknown parameter: %s\n", argv[i]);
        }
    }   

    if (total_msg) {    
        /* Prints total message count. */
        printf("Total messages:\n");
        parse_messages(input, NULL, sort);
        printf("\n");
    }

    fclose(input);
}