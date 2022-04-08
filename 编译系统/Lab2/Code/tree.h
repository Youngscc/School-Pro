# ifndef TREE_H
# define TREE_H

struct Node {
    struct Node* child;
    struct Node* brother;
    int linenumber;
    char index[15];
    short judge;
    union{
        char char_name[30];
        int int_number;
        float float_number;
    };
};

struct Node* create_Node(struct Node* ch,char* name,int line);
void print_tree(struct Node* now,int depth);

# endif