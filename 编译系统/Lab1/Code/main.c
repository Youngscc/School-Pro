#include <stdio.h>
#include <stdlib.h>

extern FILE* yyin;
extern int yylineno;
extern int Err;
extern struct Node* head;

extern int yylex();
extern int yyparse (void);
extern void yyrestart (FILE *input_file  );
extern void print_tree(struct Node* heads,int depth);

int main(int argc, char** argv) {
    if(argc<=1)
        return 1;
    FILE* f=fopen(argv[1],"r");
    if(!f)
    {
        perror(argv[1]);
        return 1;
    }
    yylineno=1;
    yyrestart(f);
    yyparse();
    if (Err == 0) print_tree(head, 0);
    return 0;
}