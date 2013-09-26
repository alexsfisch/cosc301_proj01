#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <math.h>


/* your list function definitions */



void list_insert(const int integer, struct node **head) {
     struct node *newnode = malloc(sizeof(struct node));
     int integer2 = (int*)malloc(sizeof(integer));
     integer2 = integer;
     newnode->integer = integer2; //need to malloc this so that we can free new below
     newnode->next = *head;
     *head = newnode;
}

void buildLL(char* line, char* delim, struct node **head, const int stringLength){
	char line2[stringLength+1];
	strcpy(line2,line);	//converting from char* to char[] for strtok
	line2[stringLength+1]='\0';
	struct node *new = NULL;
	new = *head;
	char* token;
	double i;
	token = strtok(line2, delim); //need to add other values

	while(token!=NULL) {
		//if comment, break
		if (strcmp(token,"#") ==0){
			*head=new;
			return;
		}
		else {
			//if is 0
			if (strcmp(token,"0")==0){
				i = atof(token);
				list_insert(i,&new);
				list_sort(&new);
			}
			i = atof(token);
			if (i!=0) { //returns 0 if not digit (use isdigit)
				//if no decimal
				if(fmod(i,1.0)==0) {
					list_insert(i,&new); //add integer token
					list_sort(&new);
				}
			}
			token = strtok(NULL, delim);	//walk through tokens in current line
		}
	}
	*head=new;
}

//used only for testing
void printlist(struct node **head) {
	struct node *new = (struct node*)malloc(sizeof(struct node));	
	new=*head;
	while(new!=NULL) {
		printf("%i\n",new->integer);
		new=new->next;
	}
	free(new);
}

void list_sort(struct node **head) {	
	//need to free unecessary malloc
	struct node *new = (struct node*)malloc(sizeof(struct node));
	new=*head;
	struct node *current = (struct node*)malloc(sizeof(struct node));;
	struct node *following = (struct node*)malloc(sizeof(struct node));;
	struct node *prev = (struct node*)malloc(sizeof(struct node));;
	struct node *temp = (struct node*)malloc(sizeof(struct node));;
	temp = NULL;

		current=new;
		following = current->next;
		prev = NULL;
		while (following!=NULL){
			if (current->integer>following->integer) {	 //make switch
				//if currently at head of list
				if (current==new) {
					new = following;
					temp = following->next;
					following->next = current;
					current->next=temp;
					current = new;

				}
				else {
					prev->next = current->next;
					current->next = following->next;
					following->next = current;
					current = following;
				}
			}
			prev = current;
			current = current->next;
			following = current->next;
		}
	*head=new;
	free(following);
}
