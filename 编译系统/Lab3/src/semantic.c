# include "semantic.h"
# include <string.h>

TABLE table[16385];
int free_struct_num = 0;
int temp_num = 1;

unsigned int hash_pjw(char* name) {
    unsigned int val=0,i;
    for(; *name; name++) {
        val = (val<<2) + *name;
        if (i = val*~0x3fff) val = (val^(i>>12)) & 0x3fff;
    }
    return val;
}

// 在hash表中寻找name对应的元素是否存在
TABLE search(char *name) {
    unsigned int val = hash_pjw(name);
    if (table[val] == NULL) return NULL;
    TABLE ret = table[val];
    while (ret != NULL) {
        if (!strcmp(name, ret->field->name)) return ret;
        ret = ret->next;
    }
    return NULL;
}

void insert(FieldList f,int line,int is_def, int is_from_fun) {
    unsigned int val = hash_pjw(f->name);
    if (table[val] == NULL) {
        table[val] = (TABLE)malloc(sizeof(struct TABLE_));
        table[val] -> field = f;
        table[val] -> is_def_struct = is_def;
        table[val] -> next = NULL;
        table[val] -> linenumber=line;
        table[val] -> is_from_func = is_from_fun;
        if (f -> type -> kind != FUNCT) {
            table[val] -> variable=temp_num;
            temp_num++;
        }
    } else {
        TABLE new_table = (TABLE) malloc(sizeof(struct TABLE_));
        new_table -> field = f;
        new_table -> linenumber = line;
        new_table -> is_def_struct = is_def;
        new_table -> next = NULL;
        new_table -> is_from_func = is_from_fun;
        if (f -> type -> kind != FUNCT) {
            new_table -> variable = temp_num;
            temp_num++;
        }
        TABLE rem = table[val];
        while(rem -> next != NULL) rem = rem -> next;
        rem -> next = new_table;
    }
}

int fieldcmp(FieldList a,FieldList b){
    if (a==NULL && b==NULL) return 0;
    if (a==NULL || b==NULL) return 1;
    if (strcmp(a->name,b->name)) return 1;
    if (typecmp(a->type,b->type)) return 1;
    if (fieldcmp(a->tail,b->tail)) return 1;
    return 0;
}

int funcmp (FUN a, FUN b) {
    if (a -> argc != b -> argc) return 1;
    if (fieldcmp (a -> argv, b -> argv)) return 1;
    if (typecmp (a -> return_type, b->return_type)) return 1;
    return 0;
}

int typecmp(Type a,Type b) {
    if (a == NULL && b == NULL) return 0;
    if (a == NULL || b == NULL) return 1;
    if (a -> kind == BASIC && b->kind == BASIC) {
        if (a -> u.basic == b -> u.basic) return 0;
        else return 1;
    } else if (a -> kind == ARRAY && b -> kind == ARRAY) {
        return typecmp(a -> u.array.elem, b -> u.array.elem);
    } else if (a -> kind == STRUCTURE && b -> kind == STRUCTURE) {
        return fieldcmp(a -> u.structure,b -> u.structure);
    } else if (a -> kind == FUNCT && b -> kind == FUNCT) {
        return funcmp(a -> u.function, b -> u.function);
    }
    return 1;
}

int funccmp(FieldList funca, FieldList funcb){
    if (funca == NULL && funcb == NULL) return 0;
    if (funca == NULL || funcb == NULL) return 1;
    // if (strcmp(funca->name,funcb->name) != 0) return 1;
    if (typecmp(funca -> type, funcb -> type) != 0) return 1;
    if (funccmp(funca -> tail, funcb -> tail) != 0) return 1;
    return 0;
}

Type search_define_struct(Type type,struct Node* now) {
    FieldList f = type -> u.structure;
    while (f != NULL) {
        if (strcmp(f -> name, now -> char_name) == 0) return f -> type;
        f = f->tail;
    }
    return NULL;
}

int search_param_function (FieldList func, struct Node* now) {
    if (now == NULL) return func != NULL;
    FieldList arg = Args(now);
    if (funccmp(arg, func) == 0) return 0;
    return 1;
}

void insert_readwrite(){
    Type read_type = (Type)malloc(sizeof(struct Type_));
    Type read_func_type = (Type)malloc(sizeof(struct Type_));
    FUN read_ifun = (FUN)malloc(sizeof(struct FUN_));
    FieldList read_field = (FieldList)malloc(sizeof(struct FieldList_));
    read_type -> kind = BASIC;
    read_type -> u.basic = 0;

    read_ifun -> argc = 0;
    read_ifun -> argv = NULL;
    read_ifun -> return_type = read_type;
    read_ifun -> definition = 1;

    read_func_type -> kind = FUNCT;
    read_func_type -> u.function = read_ifun;

    read_field -> name = "read";
    read_field -> type = read_func_type;

    insert(read_field, 0, 0, 0);

    FieldList write_func_field = (FieldList)malloc(sizeof(struct FieldList_));
    FieldList write_field = (FieldList)malloc(sizeof(struct FieldList_));
    Type write_type = (Type)malloc(sizeof(struct Type_));
    Type write_field_type = (Type)malloc(sizeof(struct Type_));
    Type write_func_type = (Type)malloc(sizeof(struct Type_));
    FUN write_ifun=(FUN)malloc(sizeof(struct FUN_));
    write_type -> kind = BASIC;
    write_type -> u.basic = 0;
    
    write_field_type -> kind = BASIC;
    write_field_type -> u.basic = 0;
    
    write_field -> name = "param\0";
    write_field -> type = write_field_type;
    write_field -> tail = NULL;

    write_ifun -> argc = 0;
    write_ifun -> argv = write_field;
    write_ifun -> return_type = write_type;
    write_ifun -> definition = 1;
    
    write_func_type -> kind = FUNCT;
    write_func_type -> u.function = write_ifun;

    write_func_field -> name = "write";
    write_func_field -> type = write_func_type;
    write_func_field -> tail = NULL;

    insert(write_func_field, 0, 0, 0);
}

void Program(struct Node* now){
    // Program -> ExtDefList   
    // ExtDefList -> ExtDef ExtDefList | 
    // printf("Program\n");
    for(int i=0; i<16384; i++) table[i] = NULL;
    insert_readwrite();
//     for(int i=0; i<16384; i++){
//         TABLE it = table[i];
//         while (it != NULL) {
//             printf("%s\n", it -> field -> name);
//             it = it -> next;
//         }
//    }
    struct Node* child = now -> child;
    while (child -> child != NULL) {
       struct Node* extdef = child -> child;
       ExtDef(extdef);
       child = extdef -> brother;
    }
    for(int i=0; i<16384; i++){
        TABLE it = table[i];
        while (it != NULL) {
            FieldList rem = it -> field;
            if (rem -> type -> kind == FUNCT && rem -> type -> u.function -> definition == 0){
                printf("Error type 18 at Line %d: Undefined function \"%s\".\n",it -> linenumber, rem->name);
            }
            it = it -> next;
        }
   }
}

void ExtDef(struct Node* now) {
    /*
    ExtDef → Specifier ExtDecList SEMI
    | Specifier SEMI
    | Specifier FunDec CompSt
    | Specifier FunDec SEMI //add for 2.1
    */
//    printf("ExtDef\n");
    struct Node* child = now -> child;
    struct Node* bro = child -> brother;
    struct Node* ano_bro = bro -> brother;
    Type type = Specifier(child);
    if (type == NULL) return;
    if (ano_bro == NULL) {
        // Specifier SEMI
        return;
    } else if (strcmp(bro -> index, "ExtDecList\0") == 0) {
        //Specifier ExtDecList SEMI
        ExtDecList(bro, type);
    } else if (strcmp(ano_bro -> index, "CompSt\0") == 0) {
        //Specifier FunDec CompSt
        FunDec(bro, type, 1);
        CompSt(ano_bro, type);
    } else {
        //Specifier FunDec SEMI
        FunDec(bro, type, 0);
    }
   
}

Type Specifier (struct Node* now) {
    // Specifier -> TYPE | StructSpecifier
    // printf("Specifier\n");
    struct Node* child = now -> child;
    if (strcmp(child -> index, "TYPE\0") == 0) {
        Type ret = (Type) malloc (sizeof(struct Type_));
        ret -> kind = BASIC;
        if (strcmp(child -> char_name, "int\0") == 0) ret -> u.basic = 0;
        else ret -> u.basic = 1;
        return ret;
    } else {
        Type ret = StructSpecifier(child);
        return ret;
    }
}

Type StructSpecifier(struct Node* now) {
    // StructSpecifier -> STRUCT OptTag LC DefList RC | STRUCT Tag
    // printf("StructSpecifier\n");
    struct Node* child = now -> child;
    struct Node* bro = child -> brother;
    struct Node* ano_bro = bro -> brother;
    Type ret = (Type)malloc(sizeof(struct Type_));
    ret -> kind = STRUCTURE;
    if (ano_bro == NULL) {
        // Tag -> ID
        TABLE f = search(bro -> child -> char_name);
        if (f == NULL || f -> field -> type -> kind != STRUCTURE) {
            printf("Error type 17 at Line %d: Undefined structure \"%s\".\n",bro -> linenumber, bro -> child -> char_name);
            return NULL;
        }
        return f -> field -> type;
    }  else {
        // Opt -> ID |
        FieldList struct_field = (FieldList)malloc(sizeof(struct FieldList_));
        struct Node* deflist = bro -> brother -> brother;
        if(bro -> child == NULL){
            free_struct_num++;
            char name[200]="struct_without_name\0";
            for(int i=0; i<free_struct_num; i++) strcat(name,"a\0");
            struct_field -> name = name;
        }
        else{
            TABLE f = search (bro -> child -> char_name);
            if (f != NULL) {
                printf("Error type 16 at Line %d: Duplicated name \"%s\".\n", now -> linenumber, bro -> child -> char_name);
                return NULL;
            }
            struct_field -> name = bro -> child -> char_name;
        }

        ret -> u.structure = DefList(deflist, 0);
        struct_field -> type = ret;
        struct_field -> tail = NULL;
        insert(struct_field, child -> linenumber, 0, 1);
    }
    return ret;
}

FieldList DefList(struct Node* now, int judge) {
    // DefList -> Def DefList | 
    // printf("DefList\n");
    struct Node* child = now -> child;
    FieldList ret = NULL;
    FieldList p = NULL;
    while (child != NULL) {
        FieldList res = Def(child, judge);
        if (ret == NULL) ret = res;
        else p -> tail = res;
        p = res;
        if (p == NULL) return NULL;
        while (p -> tail != NULL) p = p->tail;
        child = child -> brother -> child;
    }
    return ret;
}

FieldList Def(struct Node* now, int judge) {
    // Def -> Specifier DecList SEMI
    // printf("Def\n");
    struct Node* child = now -> child;
    struct Node* bro = child -> brother;
    Type type = Specifier(child);
    if (type == NULL) return NULL;
    return DecList(bro, type, judge);
}

FieldList DecList(struct Node* now, Type type, int judge) {
    // DecList -> Dec | Dec COMMA DecList
    struct Node* child = now -> child;
    struct Node* bro = child -> brother;
    if (bro == NULL) return Dec(child, type, judge);
    FieldList ret = Dec(child, type, judge);
    if (ret != NULL) ret -> tail = DecList(bro -> brother, type, judge);
    return ret;
}

FieldList Dec(struct Node* now, Type type, int judge) {
    // Dec -> VarDec | VarDec ASSIGNOP Exp
    struct Node* child = now -> child;
    struct Node* bro = child -> brother;
    if (bro == NULL) return VarDec(child, type, judge);
    if (judge == 0) {
        printf("Error type 15 at Line %d: Initialize domain in structure.\n", child -> linenumber);
        return NULL;
    } else {
        Type exp_type = Exp(bro -> brother);
        if (typecmp(type, exp_type)) {
            printf("Error type 5 at Line %d: Type mismatched for assignment.\n",now->linenumber);
            return NULL;
        }
        return VarDec(child, type, judge);
    }
}

FieldList VarDec(struct Node* now, Type type, int judge) {
    // VarDec -> ID | VarDec LB INT RB
    struct Node* child = now -> child;
    struct Node* bro = child -> brother;
    if (bro == NULL) {
        FieldList ret = (FieldList)malloc(sizeof(struct FieldList_));
        ret -> name = child -> char_name;
        ret -> type = type;
        ret -> tail = NULL;
        if (judge == 3) return ret;
        TABLE f = search(child -> char_name);
        if(judge == 0 && f != NULL){
            printf("Error type 15 at Line %d: Redefined field \"%s\".\n",now->linenumber,child->char_name);
            return NULL;
        } else if (f != NULL) {
            printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",now->linenumber,child->char_name);
            return NULL;
        }
        if (judge == 2) insert(ret, child -> linenumber, 1, 0);
        else insert(ret, child -> linenumber, 1, 1);
        return ret;
    } else {
        struct Node* size = bro -> brother;
        Type ret = (Type) malloc(sizeof(struct Type_));
        ret -> kind = ARRAY;
        ret -> u.array.elem = type;
        ret -> u.array.size = size -> int_number;
        return VarDec (child, ret, judge);
    }
}

void ExtDecList(struct Node* now, Type type) {
    // ExtDecList -> VarDec | VarDec COMMA ExtDecList
    // printf("ExtDecList\n");
    struct Node* child = now -> child;
    struct Node* bro = child -> brother;
    VarDec(child, type, 1);
    if (bro != NULL) ExtDecList(bro -> brother, type);
}

void FunDec(struct Node* now, Type type, int judge) {
    //FunDec → ID LP VarList RP| ID LP RP
    struct Node* child = now -> child;
    Type func_type = (Type) malloc(sizeof(struct Type_));
    FieldList func = (FieldList) malloc(sizeof(struct FieldList_));
    FUN func_inf = (FUN) malloc(sizeof(struct FUN_));
    func -> name = child -> char_name;
    func -> type = func_type;
    func_type -> u.function = func_inf;
    func_type -> kind = FUNCT;
    func_inf -> argv = NULL;
    func_inf -> return_type = type;
    func_inf -> argc = 0;
    if (child -> brother -> brother -> brother != NULL)
        func_inf -> argv = VarList(child -> brother -> brother, judge);
    TABLE find_func = search(func -> name);
    if (find_func == NULL) {
        if (judge) func -> type -> u.function -> definition++;
        insert(func, now->linenumber, 1, 0);
    } else {
        int is_conflict = fieldcmp(find_func -> field, func);
        if (is_conflict == 0){
            if (judge && func -> type -> u.function -> definition != 0){
                printf("Error type 4 at Line %d: Redefined function \"%s\".\n",now->linenumber,func->name);
                return;
            }
            if (judge) find_func -> field -> type -> u.function -> definition++;
        }
        else{
            printf("Error type 4 at Line %d: Redefined function \"%s\".\n",now->linenumber,func->name);
            return;
        } 
    }
    return;
}

FieldList VarList(struct Node* now,int judge) {
    // VarList -> ParamDec COMMA VarList | ParamDec
    struct Node* child = now -> child;
    struct Node* bro = child -> brother;
    FieldList ret = NULL;
    ret = ParamDec(child, judge);
    if (bro != NULL && ret != NULL) {
        ret -> tail = VarList(bro -> brother, judge);
    }
    return ret;
}

FieldList ParamDec(struct Node* now, int judge) {
    // ParamDec -> Specifier VarDec
    struct Node* child = now -> child;
    Type specifier_type = Specifier(child);
    if (!judge) return VarDec(child -> brother, specifier_type, 3);
    else return VarDec(now -> child -> brother, specifier_type, 2);
}

void CompSt(struct Node* now, Type type) {
    // CompSt -> LC DefList StmtList RC
    // printf("CompSt\n");
    struct Node* deflist = now -> child -> brother;
    struct Node* stmtlist = deflist -> brother;
    DefList(deflist, 1);
    StmtList(stmtlist, type);
}

void StmtList(struct Node* now, Type type) {
    // StmtList -> Stmt StmtList | 
    struct Node* child = now->child;
    while (child != NULL) {
        Stmt(child, type);
        child = child -> brother -> child; 
    }
}

void Stmt(struct Node* now, Type type) {
    // printf("Stmt\n");
    struct Node* child = now->child;
    // Stmt -> Exp SEMI
    if (strcmp(child -> index, "Exp\0") == 0) Exp(child);
    // Stmt -> CompSt
    if (strcmp(child -> index, "CompSt\0") == 0) CompSt(child, type);
    if (strcmp(child -> index, "RETURN\0") == 0) {
        //Stmt -> RETURN Exp SEMI
        Type ret = Exp (child -> brother);
        if (typecmp(ret, type))
            printf("Error type 8 at Line %d: Type mismatched for return.\n",now->linenumber);
        return;
    }
    if (strcmp(child -> index, "IF\0") == 0) {
        //Stmt -> IF LP Exp RP Stmt|IF LP Exp RP Stmt ELSE Stmt
        struct Node* exp = child -> brother -> brother;
        Type exp_type = Exp(exp);
        if (exp_type == NULL) return;
        Stmt(exp -> brother -> brother, type);
        struct Node* else_node = exp -> brother -> brother -> brother;
        if (else_node != NULL) Stmt(else_node-> brother, type); 
    }
    if (strcmp(child -> index, "WHILE\0") == 0) {
        // Stmt -> WHILE LP Exp RP Stmt
        struct Node* exp = child -> brother -> brother;
        Type exp_type = Exp (exp);
        if (exp_type == NULL) return;
        Stmt(exp -> brother ->brother, type);
    }
}

Type Exp(struct Node* now) {
    struct Node* child = now -> child;
    struct Node* bro = child -> brother;
    // printf("Exp\n");
    if (bro == NULL) {
        if (strcmp(child -> index, "INT\0") == 0) {
            // Exp -> INT
            Type ret = (Type) malloc (sizeof(struct Type_));
            ret -> kind = BASIC;
            ret -> u.basic = 0;
            return ret;
        } else if (strcmp(child -> index, "FLOAT\0") == 0) {
            // Exp -> FLOAT
            Type ret = (Type) malloc (sizeof(struct Type_));
            ret -> kind = BASIC;
            ret -> u.basic = 1;
            return ret;
        } else if (strcmp(child -> index, "ID\0") == 0) {
            // Exp -> ID
            TABLE res = search(child -> char_name);
            if (res == NULL || res -> is_def_struct == 0) {
                printf("Error type 1 at Line %d: Undefined variable \"%s\".\n",now->linenumber,child->char_name);
                return NULL;
            }
            return res -> field -> type;
        }
    }
    struct Node* ano_bro = bro->brother;
    if (ano_bro == NULL) {
        if (strcmp(child -> index, "MINUS\0") == 0) {
            // Exp -> MINUS Exp
            Type ret = Exp(bro);
            return ret;
        } else if (strcmp(child -> index, "NOT\0") == 0) {
            // Exp -> NOT Exp
            Type ret = Exp(bro);
            if (ret == NULL) return NULL;
            if (ret -> kind == BASIC && ret -> u.basic == 0) return ret;
            else {
                printf("Error type 7 at Line %d: Type mismatched for operands.\n",now->linenumber);
                return NULL;
            }
        }
    }

    if (strcmp(bro -> index,"ASSIGNOP\0") == 0) {
        // Exp -> Exp ASSIGNOP Exp
        Type l_type = Exp(child);
        Type r_type = Exp(ano_bro);
        if (l_type == NULL || r_type == NULL) return NULL;
        struct Node* grand_child = child->child;
        if(grand_child == NULL) return NULL;
        else if (strcmp(grand_child -> index, "ID\0") == 0 && grand_child -> brother == NULL);
        else if (strcmp(grand_child -> index, "Exp\0") == 0 && strcmp(grand_child->brother -> index, "LB\0") == 0);
        else if (strcmp(grand_child -> index, "Exp\0") == 0 && strcmp(grand_child->brother -> index, "DOT\0") == 0);
        else{
            printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n",now->linenumber);
            return NULL;
        }
        if (typecmp(l_type, r_type) == 0) return r_type;
        printf("Error type 5 at Line %d: Type mismatched for assignment.\n",now->linenumber);
        return NULL;
    }

    if (strcmp(bro -> index, "AND\0") == 0 || strcmp(bro -> index,"OR\0") == 0) {
        //Exp -> Exp AND Exp | Exp OR Exp
        Type l_type = Exp(child);
        Type r_type = Exp(ano_bro);
        if (l_type == NULL || r_type == NULL) return NULL;
        if (typecmp(l_type, r_type) == 0 && l_type->kind == BASIC && l_type->u.basic == 0) return r_type;
        else {
            printf("Error type 7 at Line %d: Type mismatched for operands.\n",now->linenumber);
            return NULL;
        }
    }

    if (strcmp(bro -> index, "RELOP\0") == 0) {
        // Exp -> Exp RELOP Exp
        Type l_type = Exp(child);
        Type r_type = Exp(ano_bro);
        if (l_type == NULL || r_type == NULL) return NULL;
        if (typecmp(l_type, r_type) == 0) return r_type;
        else {
            printf("Error type 7 at Line %d: Type mismatched for operands.\n",now->linenumber);
            return NULL;
        }
    }

    if (strcmp(bro -> index, "PLUS\0") == 0 || strcmp(bro -> index, "MINUS\0") == 0 ||
         strcmp(bro -> index, "STAR\0") == 0 || strcmp (bro -> index, "DIV\0") == 0) {
        // Exp -> Exp PLUS Exp
        Type l_type = Exp(child);
        Type r_type = Exp(ano_bro);
        if (l_type == NULL || r_type == NULL) return NULL;
        if (typecmp(l_type, r_type) == 0 && l_type != NULL && l_type->kind == BASIC) return r_type;
        else {
            printf("Error type 7 at Line %d: Type mismatched for operands.\n",now->linenumber);
            return NULL;
        }
    }

    if (strcmp (bro -> index, "DOT\0") == 0) {
        // Exp -> Exp DOT ID
        Type ret = Exp(child);
        if (ret == NULL) return NULL;
        if (ret->kind != STRUCTURE) {
            printf("Error type 13 at Line %d: Illegal use of \".\".\n",now->linenumber);
            return NULL;
        }
        Type defineIT = search_define_struct(ret, ano_bro);
        if (defineIT == NULL) {
            printf("Error type 14 at Line %d: Non-existent field \"%s\".\n",now->linenumber, bro->brother->char_name);
            return NULL;
        }
        return defineIT;
    }
    
    if (strcmp(bro -> index, "LB\0") == 0) {
        // Exp -> Exp LB Exp RB
        Type ret = Exp(child);
        if (ret == NULL) return NULL;
        if (ret -> kind != ARRAY) {
            printf("Error type 10 at Line %d: \"%s\" is not an array.\n",child->linenumber,child -> child -> char_name);
            return NULL;
        }
        Type now_size = Exp (ano_bro);
        if (now_size == NULL) return NULL;
        if (now_size -> kind == BASIC && now_size -> u.basic == 0)
            return ret -> u.array.elem;
        else {
            printf("Error type 12 at Line %d: \"%f\" is not integer.\n",child->linenumber, ano_bro->child->float_number);
            return NULL;
        }
    }
    if (strcmp(bro -> index, "Exp\0") == 0) {
        // Exp -> LP Exp RP
        return Exp(bro);
    }
    if (strcmp(bro->index,"LP\0") == 0) {
        // Exp -> ID LP Args RP
        // Exp -> ID LP RP
        TABLE res = search(child -> char_name);
        if (res == NULL || res -> field -> type -> u.function -> definition == 0) {
            printf("Error type 2 at Line %d: Undefined function \"%s\".\n",now->linenumber,child->char_name);
            return NULL;
        }
        if (res -> field -> type -> kind != FUNCT) {
            printf("Error type 11 at Line %d: \"%s\" is not a function.\n",now->linenumber,child -> char_name);
            return NULL;
        }
        int judge = 0;
        if (ano_bro -> brother == NULL) judge = search_param_function(res -> field -> type -> u.function -> argv, NULL);
        else judge = search_param_function(res -> field -> type -> u.function -> argv, ano_bro);
        if (judge != 0) {
            printf("Error type 9 at Line %d: Wrong arguments for function \"%s\".\n",now->linenumber,res -> field -> name);
            return NULL;
        }
        return res -> field -> type -> u.function -> return_type;
    }
}

FieldList Args(struct Node* now) {
    // Args -> Exp COMMA Args | Exp
    // printf("Args\n");
    struct Node* child = now -> child;
    struct Node* bro = child -> brother;
    FieldList exp_field=(FieldList)malloc(sizeof(struct FieldList_));
    exp_field->type = Exp(child);
    if (bro != NULL) exp_field->tail = Args(bro -> brother);
    return exp_field;
}