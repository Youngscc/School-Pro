# ifndef INTERIM_H
# define INTERIM_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "semantic.h"

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;

struct Operand_{
    enum{FROM_ARG,VARIABLE,TEMP,CONSTANT,ADDRESS,WADDRESS,FUNCTION,LABEL,RELOP}kind;
    int u_int;
    char* u_char;
    Type type;
};

struct InterCode_{
    enum{ILABEL,IFUNCTION,ASSIGN,ADD,SUB,MUL,DIV,ADDRASS1,ADDRASS2,ADDRASS3,
        GOTO,IF,RETURN,DEC,ARG,CALL,PARAM,READ,WRITE}kind;
    union{
        //LABEL,FUNCTION,GOTO,RETURN,ARG
        //PARAM,READ,WRITE
        struct{Operand op;}ulabel;
        //ASSIGN,CALL
        //ADDRASS1,ADDRASS2,ADDRASS3
        struct{Operand op1,op2;}uassign;
        //ADD,SUB,MUL,DIV
        struct{Operand result,op1,op2;}ubinop;
        //IF
        struct{Operand x,relop,y,z;}uif;
        //DEC
        struct{Operand op;int size;}udec;
    }u;
    InterCode before;
    InterCode next;
};

void translate_print_test(InterCode temp);
void translate_print(FILE* f);
void insert_intercode(InterCode it);
Operand new_temp();
Operand new_label();
int get_size(Type type);
int get_offset(Type return_type, struct Node* after);
void translate_Program(struct Node* now, FILE* F);
void translate_ExtDef(struct Node* now);
void translate_FunDec(struct Node* now);
void translate_CompSt(struct Node* now);
void translate_DefList(struct Node* now);
void translate_StmtList(struct Node* now);
void translate_Def(struct Node* now);
void translate_Stmt(struct Node* now);
void translate_DecList(struct Node* now);
void translate_Exp(struct Node* now,Operand place);
void translate_Cond(struct Node* now,Operand lt,Operand lf);
void translate_Dec(struct Node* now);
void translate_VarDec(struct Node* now,Operand place);
void translate_Args(struct Node* now,InterCode here);
void translate_Specifier(struct Node* now);
void translate_StructSpecifier(struct Node* now);

# endif
