#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct lst{
    char *name;
    int count;
    struct lst *next;
} list;

typedef struct lsthead{
    list *first;
} listhead;

list* list_new(char *str){
    list *l = malloc(sizeof(list));
    l->name = strdup(str);
    l->count = 1;
    l->next = NULL;
    return l;
}

void list_free(list *l){
    if(l->next!=NULL){ list_free(l->next); }
    free(l->name);
    free(l);
}

void listhead_free(listhead *l){
    list_free(l->first);
    free(l);
}

listhead *listhead_new(){
    listhead *lh = malloc(sizeof(listhead));
    lh->first = NULL;
    return lh;
}

void list_add(listhead *l, char *str){
    list *curr;
    if(l->first==NULL){ l->first = list_new(str); } else {
        curr = l->first;
        while (curr->next!=NULL){ curr = curr->next; }
        curr->next = list_new(str);
    }
}

list* list_get(listhead *l, char *str){
    list *curr;
    if(l->first==NULL){ 
        return NULL;
    } else {
        curr = l->first;
        if(strcmp(curr->name, str)==0){
            return curr;
        }
        while(curr->next!=NULL){
            curr = curr->next;
            if(strcmp(curr->name, str)==0){
                return curr;
            }
        }
        return NULL;
    }
}

void list_print(listhead *l){
    list *curr = l->first;
    while(curr!=NULL){
        printf("%s : %d\n", curr->name, curr->count);
        curr = curr->next;
    }
}
void getname(char *text, listhead *names, char *keyword){
    int i = text[0] - '0';
    list *curr;
    char *name = strtok(text, "-");
    char *message;
    name = strtok(NULL, "-");
    if(i<=9&& i>=0 && text[2]==':'){
        while(name[0]==' '||name[0]=='+'){ name++; }
        name = strtok(name, ":");
        if(keyword==NULL){
            curr = list_get(names, name);
            if(curr==NULL){ list_add(names, name); } else {
                (curr->count)++;
            }
        } else {
            curr = list_get(names, name);
            message = strtok(NULL, ":");
            if(strstr(message, keyword)!=NULL){
                if(curr==NULL){ list_add(names, name); } else {
                    (curr->count)++;
                }
            }
        }
    }    
}

int main(int argc, char **argv){
    FILE *input;
    listhead *names = listhead_new();
    int i = 0;
    char *text = malloc(1000);
    /*handles[0] = "nai"; handles[1] = "Waylon Rich Yu"; handles[2] = "Larry Laren";
    handles[3] = "Yo Wes"; handles[4] = "Smart Pin"; handles[5] = "Gaving";
    handles[6] = "Salary"; handles[7] = "hi im samuel"; handles[8] = "Ingmar \"CKING\" Chung";
    handles[9] = "Big Mic"; handles[10] = "MK Adreeyo";
    */
    if ((input = fopen(argv[1], "r")) == NULL){
       printf("Error reading input file.");
    } else {
        while(fgets(text, 500, input)!=NULL) {
           getname(text, names, NULL);
        }
        printf("Total messages sent:\n");
        list_print(names); 
        for(i = 0; i < argc-2; i++){
            fseek(input, 0, SEEK_SET);
            listhead_free(names);
            names = listhead_new();
            if(strcmp(argv[i+2],"$media")==0){
                while(fgets(text, 500, input)!=NULL) {
                    getname(text, names, "<Media omitted>");
                }
                printf("\nTotal media sent:\n", argv[i+2]);
            } else {
                while(fgets(text, 500, input)!=NULL) {
                    getname(text, names, argv[i+2]);
                }
                printf("\nTotal messages containing '%s' sent:\n", argv[i+2]);
            }
            list_print(names); 
        }
    }
    fclose(input);
    free(text); 
}