%locations
%{
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "tree.h"
extern int yylineno;
extern char* yytext;
extern int yylex();
extern struct Node* head;
// extern struct Node* create_Node(struct Node* ch,char* name,int line);
// extern void print_tree(struct Node* now,int depth);
void yyerror(const char* s);

int Err = 0;
int lastErrLineno = 0;

#define YYSTYPE struct Node* 

// struct Node* head=NULL;
// struct Node* create_Node(struct Node* ch,char* name,int line);
// void print_tree(struct Node* now,int depth);
void printError(char errorType, char* msg);
int isNewError(int errorLineno);
%}

%token STRUCT
%token RETURN
%token IF
%token ELSE
%token WHILE
%token SEMI
%token COMMA
%token ASSIGNOP
%token PLUS
%token MINUS
%token STAR
%token DIV
%token AND
%token OR
%token NOT
%token LP
%token RP
%token LB
%token RB
%token LC
%token RC
%token TYPE
%token INT
%token FLOAT
%token ID
%token RELOP
%token DOT
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right LOWER_THAN_NOT NOT
%right DOT LP LB RP RB
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%

Program:ExtDefList{     
    if($1->int_number==0)
        $$=create_Node($1,"Program\0",$1->linenumber);
    else
        $$=create_Node($1,"Program\0",@1.first_line);
};

ExtDefList: {
    $$ = create_Node(NULL,"ExtDefList\0",yylineno);
    $$ -> int_number=0;
}|ExtDef ExtDefList {
    $$ = create_Node($1,"ExtDefList\0",@1.first_line);
    $$ -> int_number = 2;
    $1 -> brother = $2;
}

ExtDef:Specifier ExtDecList SEMI{
    $$ = create_Node($1,"ExtDef\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}|Specifier SEMI{
    $$ = create_Node($1,"ExtDef\0",@1.first_line);
    $1 -> brother = $2;
}|Specifier FunDec CompSt{
    $$ = create_Node($1,"ExtDef\0",@1.first_line);
    $1 -> brother=$2;
    $2 -> brother=$3;
}| Specifier error {
    Err = 1;
    if (lastErrLineno != yylineno)
        printError('B', "Missing \";\"");
}|Specifier FunDec SEMI{
    $$=create_Node($1,"ExtDef\0",@1.first_line);
    $1->brother=$2;
    $2->brother=$3;
}

ExtDecList:VarDec{
    $$ = create_Node($1,"ExtDecList\0",@1.first_line);
}|VarDec COMMA ExtDecList{
    $$ = create_Node($1,"ExtDecList\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}| VarDec error ExtDecList{
    Err = 1;
    if (lastErrLineno != yylineno)
        printError('B', "text");
}

Specifier:TYPE{
    $$ = create_Node($1,"Specifier\0",@1.first_line);
}|StructSpecifier{
    $$ = create_Node($1,"Specifier\0",@1.first_line);
}

StructSpecifier:STRUCT OptTag LC DefList RC{
    $$ = create_Node($1,"StructSpecifier\0",@1.first_line);
    $1 -> brother=$2;
    $2 -> brother=$3;
    $3 -> brother=$4;
    $4 -> brother=$5;
}|STRUCT Tag{
    $$ = create_Node($1,"StructSpecifier\0",@1.first_line);
    $1 -> brother=$2;
}

OptTag: {
    $$ = create_Node(NULL,"OptTag\0",0);
    $$ -> int_number = 0;
}|ID{
    $$ = create_Node($1,"OptTag\0",@1.first_line);
}

Tag:ID{
    $$ = create_Node($1,"Tag\0",@1.first_line);
}

VarDec:ID{
    $$ = create_Node($1,"VarDec\0",@1.first_line);
}|VarDec LB INT RB{
    $$ = create_Node($1,"VarDec\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
    $3 -> brother = $4;
}| VarDec LB error RB {
    Err = 1;
    char msg[32];
    sprintf(msg, "Syntax error, near \'%c\'", yytext[0]);
    if (lastErrLineno != yylineno)
        printError('B', msg);
}

FunDec:ID LP VarList RP{
    $$ = create_Node($1,"FunDec\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
    $3 -> brother = $4;
}|ID LP RP{
    $$ = create_Node($1,"FunDec\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}| ID LP error RP {
    Err = 1;
    if (lastErrLineno != yylineno) 
        printError('B', "Syntax error between ()");
}

VarList:ParamDec COMMA VarList{
    $$ = create_Node($1,"VarList\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}|ParamDec{
    $$ = create_Node($1,"VarList\0",@1.first_line);
}

ParamDec:Specifier VarDec{
    $$ = create_Node($1,"ParamDec\0",@1.first_line);
    $1 -> brother = $2;
}

CompSt:LC DefList StmtList RC{
    $$ = create_Node($1,"CompSt\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
    $3 -> brother = $4;
}

StmtList: {
    $$ = create_Node(NULL,"StmtList\0",0);
    $$ -> int_number=0;
}|Stmt StmtList{
    $$ = create_Node($1,"StmtList\0",@1.first_line);
    $1 -> brother = $2;
}

Stmt:Exp SEMI{
    $$ = create_Node($1,"Stmt\0",@1.first_line);
    $1 -> brother = $2;
}|CompSt{
    $$ = create_Node($1,"Stmt\0",@1.first_line);
}|RETURN Exp SEMI{
    $$ = create_Node($1,"Stmt\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}|IF LP Exp RP Stmt %prec LOWER_THAN_ELSE{
    $$ = create_Node($1,"Stmt\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
    $3 -> brother = $4;
    $4 -> brother = $5;
}|IF LP Exp RP Stmt ELSE Stmt{
    $$ = create_Node($1,"Stmt\0",@1.first_line);
    $1 -> brother=$2;
    $2 -> brother=$3;
    $3 -> brother=$4;
    $4 -> brother=$5;
    $5 -> brother=$6;
    $6 -> brother=$7;
}|WHILE LP Exp RP Stmt{
    $$ = create_Node($1,"Stmt\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
    $3 -> brother = $4;
    $4 -> brother = $5;
}| Exp error {
    Err = 1;
    if (lastErrLineno != yylineno)
        printError('B', "Missing \";\"");
}

DefList: {
    $$ = create_Node(NULL,"DefList\0",0);
    $$ -> int_number = 0;
}|Def DefList{
    $$ = create_Node($1,"DefList\0",@1.first_line);
    $1 -> brother = $2;
}

Def:Specifier DecList SEMI{
    $$ = create_Node($1,"Def\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}|Specifier error SEMI{
    Err = 1;
    char msg[32];
    sprintf(msg, "Syntax error, near \'%c\'", yytext[0]);
    if (lastErrLineno != yylineno)
        printError('B', msg);
}| Specifier DecList error {
    if (lastErrLineno != yylineno)
        printError('B',"Missing \";\"");
}

DecList:Dec{
    $$ = create_Node($1,"DecList\0",@1.first_line);
}|Dec COMMA DecList{
    $$ = create_Node($1,"DecList\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}

Dec:VarDec{
    $$ = create_Node($1,"Dec\0",@1.first_line);
}|VarDec ASSIGNOP Exp{
    $$ = create_Node($1,"Dec\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}

Exp:Exp ASSIGNOP Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}|Exp AND Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}|Exp OR Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}|Exp RELOP Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}|Exp PLUS Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}|Exp MINUS Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother=$2;
    $2 -> brother=$3;
}|Exp STAR Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother=$2;
    $2 -> brother=$3;
}|Exp DIV Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother=$2;
    $2 -> brother=$3;
}|LP Exp RP{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother=$2;
    $2 -> brother=$3;
}|MINUS Exp %prec LOWER_THAN_NOT{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother = $2;
}|NOT Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother = $2;
}|ID LP Args RP{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
    $3 -> brother = $4;
}|ID LP RP{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}|Exp LB Exp RB{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
    $3 -> brother = $4;
}|Exp DOT ID{
    $$ = create_Node($1,"Exp\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}|ID{
    $$ = create_Node($1,"Exp\0",@1.first_line);
}|INT{
    $$ = create_Node($1,"Exp\0",@1.first_line);
}|FLOAT{
    $$ = create_Node($1,"Exp\0",@1.first_line);
}| Exp LB error RB {
    Err = 1;
    if (lastErrLineno != yylineno)
        printError('B', "Syntax error between \"[]\"");
}| Exp ASSIGNOP error {
    Err = 1;
    if (lastErrLineno != yylineno)
        printError('B', "Syntax error in Exp");
}| LP error RP {
    Err = 1;
    if (lastErrLineno != yylineno)
        printError('B', "Syntax error in Exp");
}| ID LP error RP{
    Err = 1;
    if (lastErrLineno != yylineno)
        printError('B', "Syntax error in Exp");
}|Exp LB Exp error RB{
    Err = 1;
    if (lastErrLineno != yylineno)
        printError('B', "Missing \"]\"");
}
;

Args:Exp COMMA Args{
    $$ = create_Node($1,"Arg\0",@1.first_line);
    $1 -> brother = $2;
    $2 -> brother = $3;
}|Exp{
    $$ = create_Node($1,"Args\0",@1.first_line);
}

%%

#include "lex.yy.c"

void printError(char errorType, char* msg) {
    fprintf(stderr, "Error type %c at Line %d: %s.\n", errorType, yylineno, msg);
    lastErrLineno = yylineno;
}

void yyerror(const char* s) {}