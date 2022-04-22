# include <stdio.h>
# include <stdlib.h>
# include "semantic.h"
# include "interim.h"

extern FILE* yyin;
extern int yylineno;
extern int Err;
extern TABLE table[16385];

extern struct Node* head;
extern int yylex();
extern int yyparse (void);
extern void yyrestart (FILE *input_file);

int main(int argc, char** argv) {
    if (argc <= 1) return 1;
    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror(argv[1]);
        return 1;
    }
    FILE* f2=fopen(argv[2],"w+");
    if (!f2) {
        perror(argv[2]);
        return 1;
    }
    yylineno = 1;
    yyrestart(f);
    yyparse();
    if (Err == 0) {
        Program(head);
        translate_Program(head,f2);
    }
    return 0;
}