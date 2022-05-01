# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "tree.h"

struct Node* head = NULL;

struct Node* create_Node(struct Node* ch,char* name, int line) {
    struct Node* newnode=(struct Node*)malloc(sizeof(struct Node));
    newnode->judge=1;
    newnode->child=ch;
    newnode->brother=NULL;
    newnode->linenumber=line;
    newnode->int_number=1;
    strcpy(newnode->index,name);
    head=newnode;
    return newnode;
}

void print_node(struct Node* now){
    if (now -> judge == 0) {
        if (!strcmp (now -> index, "ID\0")) {
            printf("ID: %s\n",now -> char_name);
        } else if (!strcmp (now -> index, "TYPE\0")){
            printf("TYPE: %s\n",now -> char_name);
        } else if (!strcmp (now -> index, "INT\0")){
            printf("INT: %u\n",now->int_number);
        } else if (!strcmp(now->index,"FLOAT\0")){
            printf("FLOAT: %f\n",now->float_number);}
        else{
            printf("%s\n",now->index);
        }
    } else printf("%s (%d)\n",now->index,now->linenumber);
}


void print_tree(struct Node* now,int depth) {
    if(now->judge == 0 || now->int_number) {
        for (int i=0; i<depth; ++i) printf("  ");
        print_node(now);
    }
    if (now -> child != NULL) print_tree(now -> child, depth+1);
    if (now -> brother != NULL) print_tree(now -> brother,depth);
    return;
}
