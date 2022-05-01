%{
# include <stdio.h>
# include <stdlib.h>
# include "syntax.tab.h"
int yycolumn = 1;

#define YY_USER_ACTION\
    yylloc.first_line=yylloc.last_line=yylineno;\
    yylloc.first_column=yycolumn;\
    yylloc.last_column=yycolumn+yyleng-1;\
    yycolumn+=yyleng;

struct Node* create_Node_l(char* name) {
    struct Node* newnode=(struct Node*)malloc(sizeof(struct Node));
    newnode->judge=0;
    newnode->child=NULL;
    newnode->brother=NULL;
    newnode->linenumber=0;
    strcpy(newnode->index,name);
    return newnode;
}
%}
%option yylineno
IGNORE [\r \t]
CHANGELINE [\n]
INT 0|[1-9][0-9]*
FLOAT {INT}\.[0-9]+
ID [_a-zA-Z][0-9_a-zA-Z]*
TYPE int|float
DIGIT [0-9]
%%
";" {
    yylval = create_Node_l("SEMI\0");
    return SEMI;
}

"," {
    yylval = create_Node_l("COMMA\0");
    return COMMA;
}

"=" {
    yylval = create_Node_l("ASSIGNOP\0");
    return ASSIGNOP;
}

">" {
    yylval = create_Node_l("RELOP\0");
    yylval -> linenumber = 3;
    return RELOP;
}

"<" {
    yylval = create_Node_l("RELOP\0");
    yylval -> linenumber = 2;
    return RELOP;
}

">=" {
    yylval = create_Node_l("RELOP\0");
    yylval -> linenumber = 5;
    return RELOP;
}

"<=" {
    yylval = create_Node_l("RELOP\0");
    yylval -> linenumber = 4;
    return RELOP;
}

"==" {
    yylval = create_Node_l("RELOP\0");
    return RELOP;
}

"!=" {
    yylval = create_Node_l("RELOP\0");
    yylval -> linenumber = 1;
    return RELOP;
}

"+" {
    yylval = create_Node_l("PLUS\0");
    return PLUS;
}

"-" {
    yylval = create_Node_l("MINUS\0");
    return MINUS;
}

"*" {
    yylval = create_Node_l("STAR\0");
    return STAR;
}

"/" {
    yylval = create_Node_l("DIV\0");
    return DIV;
}

"&&" {
    yylval = create_Node_l("AND\0");
    return AND;
}

"||" {
    yylval = create_Node_l("OR\0");
    return OR;
}

"." {
    yylval = create_Node_l("DOT\0");
    return DOT;
}

"!" {
    yylval = create_Node_l("NOT\0");
    return NOT;
}

{TYPE} {
    yylval = create_Node_l("TYPE\0");
    strcpy(yylval->char_name,yytext);
    return TYPE;
}

"(" {
    yylval = create_Node_l("LP\0");
    return LP;
}

")" {
    yylval = create_Node_l("RP\0");
    return RP;
}

"[" {
    yylval = create_Node_l("LB\0");
    return LB;
}

"]" {
    yylval = create_Node_l("RB\0");
    return RB;
}

"{" {
    yylval = create_Node_l("LC\0");
    return LC;
}

"}" {
    yylval = create_Node_l("RC\0");
    return RC;
}

"struct" {
    yylval = create_Node_l("STRUCT\0");
    return STRUCT;
}

"return" {
    yylval = create_Node_l("RETURN\0");
    return RETURN;
}

"if" {
    yylval = create_Node_l("IF\0");
    return IF;
}

"else" {
    yylval = create_Node_l("ELSE\0");
    return ELSE;
}

"while" {
    yylval = create_Node_l("WHILE\0");
    return WHILE;
}

{IGNORE} {}

{CHANGELINE} {yycolumn=1;}

{INT} {
    yylval = create_Node_l("INT\0");
    yylval -> int_number = atoi(yytext);
    return INT;
}

{FLOAT} {
    yylval = create_Node_l("FLOAT\0");
    yylval -> float_number = atof(yytext);
    return FLOAT;
}

{ID} {
    yylval = create_Node_l("ID\0");
    strcpy(yylval->char_name,yytext);
    return ID;
}

. {
    char msg[32];
    sprintf(msg, "Mysterious character \"%s\"", yytext);
    printError('A', msg);
    Err = 1;
}

%%
