# ifndef SEMANTIC_H
# define SEMANTIC_H
# include <stdio.h>
# include <stdlib.h>
# include "tree.h"

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct FUN_* FUN;
typedef struct TABLE_* TABLE;

struct Type_ {
    enum {BASIC,ARRAY,STRUCTURE,FUNCT} kind;
    union{
        int basic;//基本类型 0表示int 1表示float
        struct {Type elem;int size;} array;//元素类型+数组大小
        FieldList structure;//结构体类型
        FUN function;
    }u;
};

struct FUN_ {
    int argc;
    FieldList argv;
    Type return_type;
    int definition;
};

struct FieldList_ {
    char* name;
    Type type;
    FieldList tail;
};

struct TABLE_ {
    int is_def_struct;
    FieldList field;
    TABLE next;
    int linenumber;
    int variable;
    int is_from_func;
};


unsigned int hash_pjw(char* name);
TABLE search(char* name);
void insert(FieldList f,int line,int is_def,int is_from_fun);
int funcmp (FUN a, FUN b);
int fieldcmp(FieldList a,FieldList b);
int typecmp(Type a,Type b);
int funccmp(FieldList funca, FieldList funcb);
Type search_define_struct(Type type,struct Node* now);

void Program(struct Node* now);
void ExtDef(struct Node* now);
Type Specifier(struct Node* now);
Type StructSpecifier(struct Node* now);

FieldList DefList(struct Node* now,int judge);
FieldList Def(struct Node* now,int judge);
FieldList DecList(struct Node* now,Type type,int judge);
FieldList Dec(struct Node* now,Type type,int judge);

FieldList VarDec(struct Node* now,Type type,int judge);
void ExtDecList(struct Node* now,Type type);

void FunDec(struct Node* now,Type type,int judge);
FieldList VarList(struct Node* now,int judge);
FieldList ParamDec(struct Node* now,int judge);
void CompSt(struct Node* now,Type type);
void StmtList(struct Node* now,Type type);
void Stmt(struct Node* now,Type type);
Type Exp(struct Node* now);
FieldList Args(struct Node* now);

# endif