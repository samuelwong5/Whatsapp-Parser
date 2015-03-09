#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "util/list.h"
#include "util/util.h"

void parse_message(char *, struct list *, char *);
void parse_messages(FILE *, char *, bool);

#endif