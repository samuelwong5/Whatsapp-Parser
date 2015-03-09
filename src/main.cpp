#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"
#include "util/util.h"

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

	/* Prints total message count. */
    if (total_msg) {    
        printf("Total messages:\n");
        parse_messages(input, NULL, sort);
        printf("\n");
    }

    fclose(input);
}