#ifndef __LIST_H__
#define __LIST_H__
/* your list data structure declarations */
//Change 
struct node {
    int integer;
    struct node *next; 
};

/* your function declarations associated with the list */
void list_insert(const int integer, struct node **head);
void buildLL(char* line, char* delim, struct node **head, const int stringLength);
void printlist(struct node **head);

#endif // __LIST_H__
