# include "interim.h"
# include "semantic.h"

int lab_num = 1;
int interim_is_error;
InterCode in_head = NULL;
InterCode in_now = NULL;
extern int temp_num;
int intercode_num;

void translate_print(FILE* f) {
    InterCode temp = in_head;
    int judge_is_null = 0;
    int a = 0;
    // printf("%d %d\n",lab_num,temp_num);
    while (temp != NULL) {
        // printf("%d ",temp -> kind);
        if (temp -> kind == ILABEL) {
            fprintf(f,"LABEL label");
            fprintf(f, "%d ", temp -> u.ulabel.op -> u_int);
            fprintf(f, ":");
        } else if (temp -> kind == IFUNCTION) {
            fprintf(f, "FUNCTION ");
            fprintf(f, "%s ", temp -> u.ulabel.op -> u_char);
            fprintf(f, ":");
        } else if (temp -> kind == ASSIGN){
            Operand temp1 = temp -> u.uassign.op1;
            Operand temp2 = temp -> u.uassign.op2;
            if (temp1 == NULL || temp2 == NULL) judge_is_null = 1;
            else if (temp1 -> kind == ADDRESS&&temp2 -> kind == ADDRESS){
                fprintf(f, "*t%d", temp1 -> u_int);
                fprintf(f, " := ");
                fprintf(f, "*t%d", temp2 -> u_int);
            } else if (temp2 -> kind == ADDRESS) {
                fprintf(f, "t%d", temp1 -> u_int);
                fprintf(f, " := ");
                fprintf(f, "*t%d", temp2 -> u_int);
            } else if (temp1 -> kind == ADDRESS){
                fprintf(f, "&t%d", temp1 -> u_int);
                fprintf(f, " := ");
                if (temp2 -> kind == CONSTANT) fprintf(f, "#%d", temp2 -> u_int);
                else fprintf(f, "t%d", temp2 -> u_int);
            } else {
                fprintf(f, "t%d", temp1 -> u_int);
                fprintf(f, " := ");
                if (temp2 -> kind == CONSTANT) fprintf(f, "#%d", temp2 -> u_int);
                else fprintf(f, "t%d", temp2 -> u_int);
            }
        } else if (temp -> kind == ADD || temp -> kind == SUB 
                 ||temp -> kind == MUL || temp -> kind == DIV) {
            Operand temp1 = temp -> u.ubinop.result;
            Operand temp2 = temp -> u.ubinop.op1;
            Operand temp3 = temp -> u.ubinop.op2;
            if (temp1 != NULL) {
                fprintf(f, "t%d", temp1 -> u_int);
                fprintf(f, " := ");
                if (temp2 -> kind == CONSTANT) fprintf(f, "#%d", temp2 -> u_int);
                else fprintf(f, "t%d", temp2 -> u_int);
                if (temp -> kind == ADD) fprintf(f, " + ");
                else if (temp -> kind == SUB) fprintf(f, " - ");
                else if (temp -> kind == MUL) fprintf(f, " * ");
                else if (temp -> kind == DIV) fprintf(f, " / ");
                if (temp3 -> kind == CONSTANT) fprintf(f, "#%d", temp3 -> u_int);
                else fprintf(f, "t%d", temp3 -> u_int);
            }
        } else if (temp -> kind == ADDRASS2){
            Operand temp1 = temp -> u.uassign.op1;
            Operand temp2 = temp -> u.uassign.op2;
            fprintf(f, "t%d", temp1 -> u_int);
            fprintf(f, " := ");
            fprintf(f, "*t%d", temp2 -> u_int);
        } else if (temp -> kind == ADDRASS3) {
            Operand temp1 = temp -> u.uassign.op1;
            Operand temp2 = temp -> u.uassign.op2;
            fprintf(f, "*t%d", temp1 -> u_int);
            fprintf(f, " := ");
            if (temp2 -> kind == CONSTANT) fprintf(f, "#%d", temp2 -> u_int);
            else fprintf(f, "t%d", temp2 -> u_int);
        } else if (temp -> kind == ADDRASS1) {
            Operand temp1 = temp -> u.uassign.op1;
            Operand temp2 = temp -> u.uassign.op2;
            fprintf(f, "t%d", temp1 -> u_int);
            fprintf(f, " := ");
            fprintf(f, "&t%d", temp2 -> u_int);
        } else if (temp -> kind == GOTO) {
            fprintf(f, "GOTO label");
            fprintf(f, "%d", temp -> u.ulabel.op -> u_int);
        } else if (temp -> kind == IF ) {
            Operand temp1 = temp -> u.uif .x;
            Operand temp2 = temp -> u.uif .y;
            Operand temp3 = temp -> u.uif .z;
            Operand re = temp -> u.uif .relop;
            fprintf(f, "IF  ");
            if (temp1 -> kind == CONSTANT) fprintf(f, "#%d", temp1 -> u_int);
            else if (temp1 -> kind == ADDRESS) fprintf(f, "*t%d", temp1 -> u_int);
            else fprintf(f, "t%d", temp1 -> u_int);

            if (re -> u_int == 0) fprintf(f, "  ==  ");
            else if (re -> u_int == 1) fprintf(f, " != ");
            else if (re -> u_int == 2) fprintf(f, " < ");
            else if (re -> u_int == 3) fprintf(f, " > ");
            else if (re -> u_int == 4) fprintf(f, " <= ");
            else if (re -> u_int == 5) fprintf(f, " >= ");

            if (temp2 -> kind == CONSTANT) fprintf(f, "#%d", temp2 -> u_int);
            else if (temp2 -> kind == ADDRESS) fprintf(f, "*t%d", temp2 -> u_int);
            else fprintf(f, "t%d", temp2 -> u_int);
            fprintf(f, " GOTO label");
            fprintf(f, "%d", temp3 -> u_int);
        } else if (temp -> kind == RETURN) {
            fprintf(f, "RETURN ");
            if (temp -> u.ulabel.op -> kind == CONSTANT) fprintf(f, "#%d", temp -> u.ulabel.op -> u_int);
            else fprintf(f, "t%d", temp -> u.ulabel.op -> u_int);
        } else if (temp -> kind == DEC) {
            fprintf(f, "DEC ");
            fprintf(f, "t%d ", temp -> u.udec.op -> u_int);
            fprintf(f, "%d", temp -> u.udec.size);
        } else if (temp -> kind == ARG){
            fprintf(f, "ARG ");
            if (temp -> u.ulabel.op -> kind == CONSTANT) fprintf(f, "#%d", temp -> u.ulabel.op -> u_int);
            else if (temp -> u.ulabel.op -> kind == ADDRESS) fprintf(f, "&t%d", temp -> u.ulabel.op -> u_int);
            else if (temp -> u.ulabel.op -> kind == WADDRESS) fprintf(f, "*t%d", temp -> u.ulabel.op -> u_int);
            else fprintf(f, "t%d", temp -> u.ulabel.op -> u_int);
        } else if (temp -> kind == CALL){
            Operand temp1 = temp -> u.uassign.op1;
            Operand temp2 = temp -> u.uassign.op2;
            if (temp1!=NULL) fprintf(f, "t%d := ", temp1 -> u_int);
            else{
                Operand temp0 = new_temp();
                fprintf(f,"t%d := ", temp0 -> u_int);
            }
            fprintf(f, "CALL ");
            fprintf(f, "%s", temp2 -> u_char);
        } else if (temp -> kind == PARAM){
            fprintf(f, "PARAM ");
            if (temp -> u.ulabel.op -> kind == CONSTANT) fprintf(f, "#%d", temp -> u.ulabel.op -> u_int);
            else fprintf(f, "t%d", temp -> u.ulabel.op -> u_int);
        } else if (temp -> kind == READ){
            fprintf(f, "READ ");
            if (temp -> u.ulabel.op -> kind == CONSTANT) fprintf(f, "#%d", temp -> u.ulabel.op -> u_int);
            else fprintf(f, "t%d",temp -> u.ulabel.op -> u_int);
        } else if (temp -> kind == WRITE){
            fprintf(f, "WRITE ");
            if (temp -> u.ulabel.op -> kind == CONSTANT) fprintf(f, "#%d", temp -> u.ulabel.op -> u_int);
            else fprintf(f, "t%d", temp -> u.ulabel.op -> u_int);
        }
        if (!judge_is_null) fprintf(f, "\n");
        else judge_is_null = 0;
        temp = temp -> next;
    }
}

void insert_intercode(InterCode it) {
    // printf("%d ",it -> kind);
    it -> before = NULL;
    it -> next = NULL;
    if (in_head == NULL) in_head = it, intercode_num++;
    if (in_now != NULL) {
        in_now -> next = it,
        it -> before = in_now;
    }
    in_now = it;
}

Operand new_temp() {
    // printf(" --- \n");
    Operand now = (Operand)malloc(sizeof(struct Operand_));
    now -> kind = TEMP;
    now -> u_int = temp_num;
    now -> u_char = "Youngsc\0";
    temp_num++;
    return now;
}

Operand new_label() {
    Operand now = (Operand)malloc(sizeof(struct Operand_));
    now -> kind = LABEL;
    now -> u_int = lab_num;
    lab_num++;
    return now;
}

int get_size(Type type) {
    if (type == NULL) return 0;
    if (type -> kind == BASIC) return 4;
    else if (type -> kind == ARRAY) {
        int temp = type -> u.array.size * get_size(type -> u.array.elem);
        return temp;
    }
    else if(type -> kind == STRUCTURE) {
        int offset = 0;
        FieldList count = type -> u.structure;
        while (count != NULL) {
            offset += get_size(count->type);
            count = count -> tail;
        }
        return offset;
    }
}

int get_offset(Type return_type, struct Node* after) {
    if (return_type == NULL) return 0;
    if (return_type -> kind == BASIC) return 4;
    else if (return_type -> kind == STRUCTURE) {
        int offset = 0;
        FieldList count = return_type -> u.structure;
        while (count != NULL) {
            if (!strcmp(count -> name, after -> char_name)) break;
            offset += get_size(count -> type);
            count = count -> tail;
        }
        return offset;
    }
    else if (return_type -> kind == ARRAY) {
        if (return_type -> u.array.elem -> kind == ARRAY) {
            interim_is_error=1;
            printf("Cannot translate: Code contains variables of error array type.\n");
            return -1;
        }
        int offset = 0;
        Type elem = return_type -> u.array.elem;
        offset = get_size(elem);
        return offset;
    }
}

void translate_Program(struct Node* now, FILE* F) {
    // printf("Program\n");
    if (interim_is_error == 1) return;
    struct Node* child = now -> child;
    while (child -> child != NULL) {
        struct Node* extdef = child -> child;
        translate_ExtDef(extdef);
        child = extdef -> brother;
    }
    if (interim_is_error == 0) {
        translate_print(F);
    }
}

void translate_ExtDef(struct Node* now) {
    // printf("ExtDef\n");
    /*
    ExtDef -> Specifier ExtDecList SEMI
    | Specifier SEMI
    | Specifier FunDec CompSt
    */
    if (interim_is_error) return;
    struct Node* bro = now -> child -> brother;
    if (!strcmp(bro -> index, "FunDec\0"))
        translate_FunDec(bro),
        translate_CompSt(bro -> brother);

    else if (!strcmp(now -> child -> index, "Specifier\0"))
        translate_Specifier(now->child);
}

void translate_FunDec(struct Node* now) {
    // printf("FunDec\n");
    //FunDec -> ID LP VarList RP| ID LP RP
    if (interim_is_error) return;
    struct Node* child = now -> child;
    Operand func_op = (Operand)malloc(sizeof(struct Operand_));
    InterCode func_in = (InterCode)malloc(sizeof(struct InterCode_));
    func_op -> kind = FUNCTION;
    func_op -> u_char = child -> char_name;
    func_in -> kind = IFUNCTION;
    func_in -> u.ulabel.op = func_op;
    insert_intercode(func_in);
    if (child -> brother -> brother -> brother == NULL) return;
    TABLE find_func = search(child -> char_name);
    FieldList func_field = find_func -> field -> type -> u.function -> argv;
    while (func_field != NULL) {
        Operand field_op = (Operand)malloc(sizeof(struct Operand_));
        InterCode field_in=(InterCode)malloc(sizeof(struct InterCode_));
        field_op -> u_char = func_field -> name;
        if(func_field -> type -> kind == BASIC) field_op -> kind = VARIABLE;
        else field_op->kind = ADDRESS;
        TABLE find_it = search(func_field -> name);
        field_op -> u_int = find_it -> variable;
        field_in -> kind = PARAM;
        field_in -> u.ulabel.op = field_op;
        insert_intercode(field_in);
        func_field = func_field->tail;
    }
}

void translate_CompSt(struct Node* now) {
    //CompSt -> LC DefList StmtList RC
    // printf("CompSt\n");
    if (interim_is_error) return;
    struct Node* deflist = now -> child -> brother;
    struct Node* stmtlist = deflist -> brother;
    translate_DefList(deflist);
    translate_StmtList(stmtlist);
    return;
}

void translate_DefList(struct Node* now) {
    //DefList -> Def DefList| 
    // printf("DefList\n");
    if (interim_is_error) return;
    struct Node* def = now->child;
    while (def != NULL) {
        translate_Def(def);
        def = def -> brother -> child;
    }
    return;
}

void translate_StmtList(struct Node* now) {
    //StmtList -> Stmt StmtList| 
    // printf("StmtList\n");
    if (interim_is_error) return;
    struct Node* stmt = now -> child;
    while (stmt!=NULL){
        translate_Stmt(stmt);
        stmt = stmt -> brother -> child;
    }
    return;
}

void translate_Def(struct Node* now) {
    //Def -> Specifier DecList SEMI
    // printf("Def\n");
    if (interim_is_error) return;
    struct Node* declist = now -> child -> brother;
    translate_DecList(declist);
}

void translate_Stmt(struct Node* now) {
/*   
    Stmt -> Exp SEMI
    | CompSt
    | RETURN Exp SEMI
    | IF LP Exp RP Stmt
    | IF LP Exp RP Stmt ELSE Stmt
    | WHILE LP Exp RP Stmt
*/
    // printf("Stmt\n");
    if (interim_is_error) return;
    struct Node* child = now -> child;

    if (!strcmp(child -> index, "Exp\0"))
        //Stmt -> Exp SEMI
        translate_Exp(now->child, NULL);
    else if(!strcmp(child->index, "CompSt\0"))
        //Stmt ->CompSt
        translate_CompSt(now->child);
    else if(!strcmp(child->index, "RETURN\0")) {
        //Stmt ->RETURN Exp SEMI
        Operand temp1 = new_temp();
        translate_Exp(now -> child -> brother, temp1);
        Operand temp2 = NULL;
        if (temp1 -> kind == ADDRESS){
            temp2 = new_temp();
            InterCode now_in = (InterCode)malloc(sizeof(struct InterCode_));
            now_in -> kind = ADDRASS2;
            now_in -> u.uassign.op1 = temp2;
            now_in -> u.uassign.op2 = temp1;
            insert_intercode(now_in);
        }
        InterCode return_in = (InterCode)malloc(sizeof(struct InterCode_));
        return_in -> kind = RETURN;
        if (temp2 == NULL) return_in -> u.ulabel.op = temp1;
        else return_in -> u.ulabel.op = temp2;
        insert_intercode(return_in);
    }
    else if (!strcmp(child->index,"IF\0")) {
        //Stmt ->IF LP Exp RP Stmt | IF LP Exp RP Stmt ELSE Stmt
        struct Node* bro = child -> brother -> brother;
        struct Node* else_node = bro -> brother -> brother -> brother;
        if (else_node == NULL) {
            //Stmt ->IF LP Exp RP Stmt
            Operand temp1 = new_label();
            Operand temp2 = new_label();
            InterCode temp1_in = (InterCode)malloc(sizeof(struct InterCode_));
            InterCode temp2_in = (InterCode)malloc(sizeof(struct InterCode_));
            translate_Cond(bro, temp1, temp2);
            temp1_in -> kind = ILABEL;
            temp1_in -> u.ulabel.op = temp1;
            insert_intercode(temp1_in);
            translate_Stmt(bro -> brother -> brother);
            temp2_in -> kind = ILABEL;
            temp2_in -> u.ulabel.op = temp2;
            insert_intercode(temp2_in);
            return;      
        } else{
            //IF LP Exp RP Stmt ELSE Stmt
            Operand temp1 = new_label();
            Operand temp2 = new_label();
            Operand temp3 = new_label();
            InterCode temp1_in = (InterCode)malloc(sizeof(struct InterCode_));
            InterCode temp2_in = (InterCode)malloc(sizeof(struct InterCode_));
            InterCode temp3_in = (InterCode)malloc(sizeof(struct InterCode_));
            InterCode temp4_in = (InterCode)malloc(sizeof(struct InterCode_));
            translate_Cond(bro, temp1, temp2);
            temp1_in -> kind = ILABEL;
            temp1_in -> u.ulabel.op = temp1;
            insert_intercode(temp1_in);
            translate_Stmt(bro -> brother -> brother);
            temp2_in -> kind = GOTO;
            temp2_in -> u.ulabel.op = temp3;
            insert_intercode(temp2_in);
            temp3_in -> kind = ILABEL;
            temp3_in -> u.ulabel.op = temp2;
            insert_intercode(temp3_in);
            translate_Stmt(bro -> brother -> brother -> brother -> brother);
            temp4_in -> kind = ILABEL;
            temp4_in -> u.ulabel.op = temp3;
            insert_intercode(temp4_in);
            return;
        }
    }
    else if(strcmp(child->index,"WHILE\0")==0){
        //Stmt ->WHILE LP Exp RP Stmt
        struct Node* bro = child -> brother -> brother;
        Operand temp1=new_label();
        Operand temp2=new_label();
        Operand temp3=new_label();
        InterCode temp1_in=(InterCode)malloc(sizeof(struct InterCode_));
        InterCode temp2_in=(InterCode)malloc(sizeof(struct InterCode_));
        InterCode temp3_in=(InterCode)malloc(sizeof(struct InterCode_));
        InterCode temp4_in=(InterCode)malloc(sizeof(struct InterCode_));
        temp1_in -> kind = ILABEL;
        temp1_in -> u.ulabel.op = temp1;
        insert_intercode(temp1_in);

        translate_Cond(bro, temp2, temp3);
        temp3_in -> kind = ILABEL;
        temp3_in -> u.ulabel.op = temp2;
        insert_intercode(temp3_in); 

        translate_Stmt(bro -> brother -> brother);
        temp2_in -> kind = GOTO;
        temp2_in -> u.ulabel.op = temp1;
        insert_intercode(temp2_in);

        temp4_in -> kind = ILABEL;
        temp4_in -> u.ulabel.op = temp3;
        insert_intercode(temp4_in); 
    }   
}

void translate_DecList(struct Node* now){
    //DecList -> Dec| Dec COMMA DecList
    // printf("DecList\n");
    if (interim_is_error) return;
    struct Node* child = now -> child;
    translate_Dec(child);
    if (child -> brother != NULL) translate_DecList(child -> brother -> brother);
}

void translate_Exp(struct Node* now,Operand place){
    // printf("Exp\n");
    // printf("Exp\n");
    if (interim_is_error) return;
    struct Node* child=now->child;
    struct Node* fir_bro=child->brother;
    if (fir_bro == NULL) {
        if(!strcmp(child->index, "INT\0")) {
            //Exp -> INT
            int value = child -> int_number;
            if (place == NULL) return;
            place -> kind = CONSTANT;
            place -> u_int = value;
            // printf("a translate_Exp INT\n");
            return;
        }
        else if (strcmp(child -> index, "ID\0") == 0) {
            //Exp -> ID
            TABLE find_id = search(child -> char_name);
            char* name = child -> char_name;
            if (place == NULL) return;
            if (!find_id -> is_from_func && find_id -> field -> type -> kind != BASIC && find_id -> field -> type -> kind != FUNCT)
                 place->kind=ADDRESS;
            else if (!find_id -> is_from_func && find_id -> field -> type -> kind != BASIC) place -> kind = VARIABLE;
            place -> u_char = name;
            place -> u_int = find_id -> variable;
            place -> type = find_id -> field -> type;
            return;
        }
    }
    struct Node* sec_bro = fir_bro -> brother;
    if (sec_bro==NULL) {
        if(!strcmp(child->index, "MINUS\0")) {
            //Exp -> MINUS Exp
            if (place == NULL) return;
            Operand temp1 = new_temp();
            Operand temp2 = (Operand)malloc(sizeof(struct Operand_));
            InterCode minus_in = (InterCode)malloc(sizeof(struct InterCode_));
            translate_Exp(child -> brother, temp1);
            minus_in -> kind=SUB;
            minus_in -> u.ubinop.result = place;
            minus_in -> u.ubinop.op2 = temp1;
            temp2 -> kind = CONSTANT;
            temp2 -> u_int = 0;
            minus_in -> u.ubinop.op1 = temp2;
            if (place -> kind == FROM_ARG) place -> kind = VARIABLE;
            insert_intercode(minus_in); 
            return;      
        }
        else if(!strcmp(child->index, "NOT\0")){
            //Exp ->NOT Exp
            Operand l1=new_label();
            Operand l2=new_label();
            Operand temp1 = (Operand)malloc(sizeof(struct Operand_));
            InterCode code0_in = (InterCode)malloc(sizeof(struct InterCode_));
            InterCode code2_in = (InterCode)malloc(sizeof(struct InterCode_));
            InterCode code22_in = (InterCode)malloc(sizeof(struct InterCode_));
            code0_in -> kind=ASSIGN;
            code0_in -> u.uassign.op1 = place;
            temp1 -> kind = CONSTANT;
            temp1 -> u_int = 0;
            code0_in -> u.uassign.op2 = temp1;
            insert_intercode(code0_in); 
            translate_Cond(now,l1,l2);
            code2_in -> kind = ILABEL;
            code2_in -> u.ulabel.op = l1;
            insert_intercode(code2_in);
            code22_in -> kind=ASSIGN;
            code22_in -> u.uassign.op1=place;
            Operand temp2 = (Operand)malloc(sizeof(struct Operand_));
            temp2 -> kind = CONSTANT;
            temp2 -> u_int = 1;
            code22_in -> u.uassign.op2 = temp2;
            insert_intercode(code22_in);
            InterCode label_in = (InterCode)malloc(sizeof(struct InterCode_));
            label_in -> kind = ILABEL;
            label_in -> u.ulabel.op = l2;
            insert_intercode(label_in);   
            return; 
        }
    }
    if (!strcmp(fir_bro -> index, "ASSIGNOP\0")) {
        //Exp -> Exp ASSIGNOP Exp
        // printf("a translate_Exp ASSIGNOP\n");
        if(!strcmp(child->child->index,"ID\0")) {
            Operand temp1 = new_temp();
            Operand temp2 = (Operand)malloc(sizeof(struct Operand_));
            InterCode code21_in = (InterCode)malloc(sizeof(struct InterCode_));
            InterCode code22_in = (InterCode)malloc(sizeof(struct InterCode_));
            translate_Exp(fir_bro -> brother, temp1);
            code21_in -> kind = ASSIGN;
            code21_in -> u.uassign.op2 = temp1;
            TABLE find_it = search(child -> child -> char_name);
            temp2 -> kind = VARIABLE;
            temp2 -> u_char = child -> child -> char_name;
            temp2 -> u_int = find_it -> variable;
            code21_in -> u.uassign.op1 = temp2;
            insert_intercode(code21_in);
            code22_in -> kind = ASSIGN;
            code22_in -> u.uassign.op1 = place;
            code22_in -> u.uassign.op2 = temp2;
            insert_intercode(code22_in);
            return;
        }
        else{
            Operand temp1 = new_temp();
            translate_Exp(fir_bro -> brother, temp1);
            Operand temp0 = NULL;
            if (temp1 -> kind == ADDRESS) {
                temp0 = new_temp();
                InterCode in_1 = (InterCode)malloc(sizeof(struct InterCode_));
                in_1 -> u.uassign.op1 = temp0;
                in_1 -> u.uassign.op2 = temp1;
                insert_intercode(in_1);
            }
            InterCode code21_in = (InterCode)malloc(sizeof(struct InterCode_));
            InterCode code22_in = (InterCode)malloc(sizeof(struct InterCode_));
            code21_in -> kind = ADDRASS3;
            if (temp0 == NULL) code21_in -> u.uassign.op2 = temp1;
            else code21_in -> u.uassign.op2 = temp0;
            Operand temp2 = new_temp();
            translate_Exp(child, temp2);
            code21_in -> u.uassign.op1 = temp2;
            insert_intercode(code21_in);
            code22_in -> kind = ASSIGN;
            code22_in -> u.uassign.op1 = place;
            code22_in -> u.uassign.op2 = temp2;
            insert_intercode(code22_in);
            return;
        }
    }
    if (!strcmp(fir_bro->index, "AND\0")||!strcmp(fir_bro->index,"OR\0")||!strcmp(fir_bro->index,"RELOP\0")) {
        //Exp -> Exp AND\OR\RELOP Exp
        Operand l1 = new_label();
        Operand l2 = new_label();
        Operand temp1 = (Operand)malloc(sizeof(struct Operand_));
        Operand temp2 = (Operand)malloc(sizeof(struct Operand_));
        InterCode code0_in = (InterCode)malloc(sizeof(struct InterCode_));
        InterCode code2_in = (InterCode)malloc(sizeof(struct InterCode_));
        InterCode code22_in = (InterCode)malloc(sizeof(struct InterCode_));
        InterCode label_in = (InterCode)malloc(sizeof(struct InterCode_));
        code0_in -> kind = ASSIGN;
        code0_in -> u.uassign.op1 = place;
        temp1 -> kind = CONSTANT;
        temp1 -> u_int = 0;
        code0_in -> u.uassign.op2 = temp1;
        insert_intercode(code0_in); 
        translate_Cond(now,l1,l2);
        code2_in -> kind = ILABEL;
        code2_in -> u.ulabel.op = l1;
        insert_intercode(code2_in);
        code22_in -> kind = ASSIGN;
        code22_in -> u.uassign.op1 = place;
        temp2 -> kind = CONSTANT;
        temp2 -> u_int = 1;
        code22_in -> u.uassign.op2 = temp2;
        insert_intercode(code22_in);
        label_in -> kind = ILABEL;
        label_in -> u.ulabel.op = l2;
        insert_intercode(label_in);   
        return;
    }
    if (!strcmp(fir_bro -> index, "PLUS\0") || !strcmp(fir_bro -> index, "MINUS\0")
      ||!strcmp(fir_bro -> index, "STAR\0") || !strcmp(fir_bro -> index, "DIV\0")) {
        //Exp -> Exp PLUS Exp
        Operand temp1 = new_temp();
        Operand temp2 = new_temp();
        Operand temp3 = NULL;
        Operand temp4 = NULL;
        translate_Exp(child, temp1);
        translate_Exp(fir_bro -> brother, temp2);
        if (temp1 -> kind == CONSTANT && temp2 -> kind == CONSTANT) place -> kind = VARIABLE;
        if (temp1 -> kind == ADDRESS) {
            temp3 = new_temp();
            InterCode in1 = (InterCode)malloc(sizeof(struct InterCode_));
            in1 -> u.uassign.op1 = temp3;
            in1 -> u.uassign.op2 = temp1;
            insert_intercode(in1);
        }
        if (temp2 -> kind == ADDRESS) {
            temp4 = new_temp();
            InterCode in1 = (InterCode)malloc(sizeof(struct InterCode_));
            in1 -> u.uassign.op1 = temp4;
            in1 -> u.uassign.op2 = temp2;
            insert_intercode(in1);
        }
        InterCode code0_in = (InterCode)malloc(sizeof(struct InterCode_));
        if (!strcmp(fir_bro -> index, "PLUS\0")) code0_in -> kind = ADD;
        else if (!strcmp(fir_bro -> index, "MINUS\0")) code0_in -> kind = SUB;
        else if (!strcmp(fir_bro -> index, "STAR\0")) code0_in -> kind = MUL;
        else if (!strcmp(fir_bro -> index, "DIV\0")) code0_in -> kind = DIV;
        code0_in -> u.ubinop.result = place;
        if (temp3 == NULL) code0_in -> u.ubinop.op1 = temp1;
        else code0_in -> u.ubinop.op1 = temp3;
        if (temp4 == NULL) code0_in -> u.ubinop.op2 = temp2;
        else code0_in -> u.ubinop.op2 = temp4;
        insert_intercode(code0_in);
        return; 
    }
    
    if (!strcmp(fir_bro->index,"DOT\0")) {
        //Exp -> Exp DOT ID
        Operand temp1 = new_temp();
        translate_Exp(child, temp1);
        if (temp1 -> kind == VARIABLE) {
            Operand temp0 = new_temp();
            temp0 -> kind = ADDRESS;
            InterCode in = (InterCode)malloc(sizeof(struct InterCode_));
            in -> kind = ADDRASS1;
            in -> u.uassign.op1 = temp0;
            in -> u.uassign.op2 = temp1;
            insert_intercode(in);
            int offset = get_offset(temp1->type, fir_bro->brother);
            if (offset==-1) return;
            Operand temp3 = (Operand)malloc(sizeof(struct Operand_));
            temp3 -> kind = CONSTANT;
            temp3 -> u_int = offset;
            if (place == NULL) return;
            if (place -> kind == FROM_ARG) place -> kind = WADDRESS;
            else place -> kind = ADDRESS;
            TABLE find_it = search(fir_bro -> brother -> char_name);
            place -> type = find_it -> field -> type;
            InterCode code0_in = (InterCode)malloc(sizeof(struct InterCode_));
            code0_in -> kind = ADD;
            code0_in -> u.ubinop.result = place;
            code0_in -> u.ubinop.op1 = temp0;
            code0_in -> u.ubinop.op2 = temp3;
            insert_intercode(code0_in);
        }
        else{
            int offset = get_offset(temp1 -> type, fir_bro -> brother);
            if (offset == -1) return;
            Operand temp3 = (Operand)malloc(sizeof(struct Operand_));
            temp3 -> kind = CONSTANT;
            temp3 -> u_int = offset;
            if (place == NULL) return;
            if (place -> kind == FROM_ARG) place -> kind = WADDRESS;
            else place -> kind = ADDRESS;
            TABLE find_it = search(fir_bro->brother->char_name);
            place -> type = find_it -> field -> type;
            InterCode code0_in=(InterCode)malloc(sizeof(struct InterCode_));
            code0_in -> kind = ADD;
            code0_in -> u.ubinop.result = place;
            code0_in -> u.ubinop.op1 = temp1;
            code0_in -> u.ubinop.op2 = temp3;
            insert_intercode(code0_in);
        }
        return;
    }
    if (!strcmp(fir_bro->index,"LB\0")) {
        //Exp -> Exp LB Exp RB，数组
        Operand temp1 = new_temp();
        translate_Exp(child, temp1);
        if (temp1 -> kind == VARIABLE) {
            Operand temp0 = new_temp();
            temp0 -> kind = ADDRESS;
            InterCode in = (InterCode)malloc(sizeof(struct InterCode_));
            in -> kind = ADDRASS1;
            in -> u.uassign.op1 = temp0;
            in -> u.uassign.op2 = temp1;
            insert_intercode(in);
            int offset = get_offset(temp1 -> type, NULL);
            if (offset == -1) return;
            Operand i = new_temp();
            translate_Exp(fir_bro -> brother, i);
            Operand temp2 = new_temp();
            Operand o_offset = (Operand)malloc(sizeof(struct Operand_));
            InterCode in2 = (InterCode)malloc(sizeof(struct InterCode_));
            o_offset -> kind = CONSTANT;
            o_offset -> u_int = offset;
            in2 -> kind = MUL;
            in2 -> u.ubinop.result = temp2;
            in2 -> u.ubinop.op1 = i;
            in2 -> u.ubinop.op2 = o_offset;
            insert_intercode(in2);
            if (place == NULL) return;
            if (place -> kind == FROM_ARG) place -> kind = WADDRESS;
            else place -> kind = ADDRESS;
            place -> type = temp1 -> type -> u.array.elem;
            InterCode code0_in = (InterCode)malloc(sizeof(struct InterCode_));
            code0_in -> kind = ADD;
            code0_in -> u.ubinop.result = place;
            code0_in -> u.ubinop.op1 = temp0;
            code0_in -> u.ubinop.op2 = temp2;
            insert_intercode(code0_in);
        }
        else{
            int offset = get_offset(temp1 -> type, NULL);
            if (offset == -1) return;
            Operand i = new_temp();
            translate_Exp(fir_bro -> brother, i);
            Operand temp2 = new_temp();
            Operand o_offset = (Operand)malloc(sizeof(struct Operand_));
            InterCode in2=(InterCode)malloc(sizeof(struct InterCode_));
            o_offset -> kind = CONSTANT;
            o_offset -> u_int = offset;
            in2 -> kind = MUL;
            in2 -> u.ubinop.result = temp2;
            in2 -> u.ubinop.op1 = i;
            in2 -> u.ubinop.op2 = o_offset;
            insert_intercode(in2);
            if (place == NULL) return;
            if (place -> kind == FROM_ARG) place -> kind = WADDRESS;
            else place -> kind = ADDRESS;
            place -> type = temp1 -> type -> u.array.elem;
            InterCode code0_in = (InterCode)malloc(sizeof(struct InterCode_));
            code0_in -> kind = ADD;
            code0_in -> u.ubinop.result = place;
            code0_in -> u.ubinop.op1 = temp1;
            code0_in -> u.ubinop.op2 = temp2;
            insert_intercode(code0_in);
        }
        return;
    }
    if (!strcmp(fir_bro->index,"Exp\0")) {
        translate_Exp(fir_bro,place);
        return;
    }
    if (!strcmp(sec_bro->index, "Args\0")) {
        //Exp -> ID LP Args RP
        char* function_name = child -> char_name;
        if (!strcmp(function_name,"write")) {
            Operand temp1 = new_temp();
            Operand temp0 = NULL;
            translate_Exp(sec_bro -> child, temp1);
            if (temp1 -> kind == ADDRESS) {
                temp0 = new_temp();
                InterCode code0_in = (InterCode)malloc(sizeof(struct InterCode_));
                code0_in -> u.uassign.op1 = temp0;
                code0_in -> u.uassign.op2 = temp1;
                insert_intercode(code0_in);
            }
            InterCode code1_in = (InterCode)malloc(sizeof(struct InterCode_));
            code1_in -> kind = WRITE;
            if (temp0 == NULL) code1_in -> u.ulabel.op = temp1;
            else code1_in -> u.ulabel.op = temp0;
            insert_intercode(code1_in);
            return;
        }
        translate_Args(sec_bro, NULL);
        Operand func_ope = (Operand)malloc(sizeof(struct Operand_));
        func_ope -> kind = FUNCTION;
        func_ope -> u_char = function_name;
        InterCode code1_in=(InterCode)malloc(sizeof(struct InterCode_));
        code1_in -> kind = CALL;
        code1_in -> u.uassign.op1 = place;
        code1_in -> u.uassign.op2 = func_ope;
        insert_intercode(code1_in);
        return;
    }
    if (!strcmp(sec_bro->index,"RP\0")) {
        //Exp -> ID LP RP
        char* function_name = child -> char_name;
        if (!strcmp(function_name,"read")) {
            InterCode code1_in=(InterCode)malloc(sizeof(struct InterCode_));
            code1_in -> kind = READ;
            code1_in -> u.ulabel.op = place;
            insert_intercode(code1_in);
            return;
        }
        Operand func_ope = (Operand)malloc(sizeof(struct Operand_));
        func_ope -> kind = FUNCTION;
        func_ope -> u_char = function_name;
        InterCode code1_in = (InterCode)malloc(sizeof(struct InterCode_));
        code1_in -> kind = CALL;
        code1_in -> u.uassign.op1 = place;
        code1_in -> u.uassign.op2 = func_ope;
        insert_intercode(code1_in);
        return;
    }
}

void translate_Cond(struct Node* now,Operand lt,Operand lf) {
    // printf("Cond\n");
    if (interim_is_error) return;
    struct Node* child = now -> child;
    if (child -> brother != NULL && !strcmp(child -> brother -> index, "RELOP\0")) {
        Operand temp1 = new_temp();
        Operand temp2 = new_temp();
        Operand op = (Operand)malloc(sizeof(struct Operand_));
        InterCode code3 = (InterCode)malloc(sizeof(struct InterCode_));
        InterCode code4 = (InterCode)malloc(sizeof(struct InterCode_));
        translate_Exp (child, temp1);
        translate_Exp (child -> brother -> brother, temp2);
        op -> kind = RELOP;
        op -> u_int = child -> brother -> linenumber;
        code3 -> kind = IF;
        code3 -> u.uif.x = temp1;
        code3 -> u.uif.relop = op;
        code3 -> u.uif.y = temp2;
        code3 -> u.uif.z = lt;
        insert_intercode(code3);
        code4 -> kind = GOTO;
        code4 -> u.ulabel.op = lf;
        insert_intercode(code4);
        // printf("a translate_Cond RELOP\n");
    }
    else if (!strcmp(child->index,"NOT\0")) {
        translate_Cond(now -> child -> brother, lf, lt);
    }
    else if (child -> brother != NULL && !strcmp(child -> brother -> index, "AND\0")) {
        Operand l1 = new_label();
        translate_Cond(child, l1, lf);
        InterCode code1 = (InterCode)malloc(sizeof(struct InterCode_));
        code1 -> kind = ILABEL;
        code1 -> u.ulabel.op = l1;
        insert_intercode(code1);
        translate_Cond(child -> brother -> brother, lt, lf);
    }
    else if(child -> brother != NULL && !strcmp(child -> brother -> index, "OR\0")) {
        Operand l1 = new_label();
        translate_Cond(child, lt, l1);
        InterCode code1 = (InterCode)malloc(sizeof(struct InterCode_));
        code1 -> kind = ILABEL;
        code1 -> u.ulabel.op = l1;
        insert_intercode(code1);
        translate_Cond(child -> brother -> brother, lt, lf);
    }
    else {
        Operand temp1 = new_temp();
        Operand temp2=(Operand)malloc(sizeof(struct Operand_));
        Operand op = (Operand)malloc(sizeof(struct Operand_));
        InterCode code2 = (InterCode)malloc(sizeof(struct InterCode_));
        InterCode code4 = (InterCode)malloc(sizeof(struct InterCode_));
        translate_Exp(now, temp1);
        op -> kind = RELOP;
        op -> u_int = 1;
        temp2 -> kind = CONSTANT;
        temp2 -> u_int = 0;
        code2 -> kind = IF;
        code2 -> u.uif.x = temp1;
        code2 -> u.uif.relop = op;
        code2 -> u.uif.y = temp2;
        code2 -> u.uif.z = lt;
        insert_intercode(code2);
        code4 -> kind = GOTO;
        code4 -> u.ulabel.op = lf;
        insert_intercode(code4);
    }
    return;
}

void translate_Dec(struct Node* now){
    //Dec -> VarDec | VarDec ASSIGNOP Exp
    // printf("Dec\n");
    if (interim_is_error) return;
    struct Node* vardec = now -> child;
    struct Node* fir_bro = vardec -> brother;
    if (fir_bro == NULL) {
        Operand temp1 = new_temp();
        translate_VarDec(vardec, temp1);
    } else{
        Operand rem1 = new_temp();
        Operand rem2 = new_temp();
        InterCode func_in = (InterCode)malloc(sizeof(struct InterCode_));
        translate_VarDec(vardec, rem1);
        translate_Exp(fir_bro -> brother, rem2);
        func_in -> kind = ASSIGN;
        func_in -> u.uassign.op1 = rem1;
        func_in -> u.uassign.op2 = rem2;
        insert_intercode(func_in);
    }
}

void translate_VarDec(struct Node* now,Operand place){
    //VarDec -> ID| VarDec LB INT RB
    // printf("VerDec\n");
    if (interim_is_error) return;
    if (now -> child -> brother == NULL) {
        TABLE find_it = search(now -> child -> char_name);
        FieldList find_field = find_it -> field;
        if (find_field -> type -> kind == BASIC) {
            if (place == NULL) return;
            place -> kind = VARIABLE;
            place -> u_int = find_it -> variable;
            place -> u_char = now->child -> char_name;
            return;
        }
        else if(find_field -> type -> kind == STRUCTURE) {
            if (place == NULL) return;
            place -> kind = VARIABLE;
            place -> u_int = find_it -> variable;
            place -> u_char = now->child -> char_name;
            InterCode func_in = (InterCode)malloc(sizeof(struct InterCode_));
            func_in -> kind = DEC;
            func_in -> u.udec.op = place;
            func_in -> u.udec.size = get_size(find_field->type);
            insert_intercode(func_in);
            return;
        }
    } else {
        if (!strcmp(now -> child -> child -> index, "ID\0")) {
            interim_is_error = 1;
            printf("Cannot translate: Code contains variables of error array type.\n");
            return;
        }
        if (place == NULL) return;
        place -> kind = VARIABLE;
        place -> u_char = now -> child -> char_name;
        TABLE find_it = search(now -> child -> child -> char_name);
        place -> u_int = find_it -> variable;
        InterCode func_in = (InterCode)malloc(sizeof(struct InterCode_));
        func_in -> kind = DEC;
        func_in -> u.udec.op = place;
        func_in -> u.udec.size = get_size(find_it -> field -> type);
        insert_intercode(func_in);
        return;
    }
}

void translate_Args(struct Node* now,InterCode here){
    //Args -> Exp COMMA Args| Exp
    // printf("Args\n");
    if (interim_is_error) return;
    struct Node* exp = now -> child;
    Operand temp1 = new_temp();
    temp1 -> kind = FROM_ARG;
    translate_Exp(exp, temp1);
    if (temp1 -> kind != CONSTANT && temp1 -> kind != ADDRESS && temp1 -> kind != WADDRESS) {
        TABLE find_id = search(temp1 -> u_char);
        if (find_id == NULL) temp1 -> kind = VARIABLE;
        else if (find_id -> field -> type -> kind != BASIC) temp1 -> kind = ADDRESS;
        else temp1->kind = VARIABLE;
    }

    InterCode code1_in = (InterCode)malloc(sizeof(struct InterCode_));
    code1_in -> kind = ARG;
    code1_in -> u.ulabel.op = temp1;
    if (here == NULL) {
        code1_in -> next = NULL;
        code1_in -> before = NULL;
    } else{
        here -> next = code1_in;
        code1_in -> before = here;
    }
    exp = exp -> brother;
    if (exp != NULL) translate_Args(exp -> brother, code1_in);
    if (here == NULL) {
        InterCode temp = code1_in;
        while (temp -> next != NULL) temp = temp -> next;
        while (temp != NULL) {
            InterCode rem = temp;
            temp = temp -> before;
            insert_intercode(rem);
        }
    }
}

void translate_Specifier(struct Node* now){
    //Specifier -> TYPE| StructSpecifier
    // printf("Specifier\n");
    if (interim_is_error) return;
    if (!strcmp(now -> child -> index, "StructSpecifier")) {
        translate_StructSpecifier(now -> child);
    }
}

void translate_StructSpecifier(struct Node* now){
    //StructSpecifier -> STRUCT OptTag LC DefList RC| STRUCT Tag
    // printf("StructSpecifier\n");
    if (interim_is_error) return;
    struct Node* child = now -> child;
    struct Node* fir_bro = child -> brother;
    struct Node* sec_bro = fir_bro -> brother;
    if (sec_bro == NULL) {
        Operand temp1 = (Operand)malloc(sizeof(struct Operand_));
        TABLE find_it = search(fir_bro -> child -> char_name);
        temp1 -> kind = VARIABLE;
        temp1 -> u_int = find_it -> variable;
        temp1 -> u_char = fir_bro -> child -> char_name;
        InterCode func_in = (InterCode)malloc(sizeof(struct InterCode_));
        func_in -> kind = DEC;
        func_in -> u.udec.op = temp1;
        func_in -> u.udec.size = get_size(find_it -> field -> type);
        insert_intercode(func_in);
        return;
    }
}