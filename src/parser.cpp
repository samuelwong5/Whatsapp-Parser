#include "parser.h"

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
