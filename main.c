/*
 *
 * author name, date, and other info here
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "list.h"


void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}


int main(int argc, char **argv) {
	//if use getline, user must free
	struct node *head = NULL;
	FILE *datafile;
	char* delim = " ";
	char* line;
	size_t numberBytes=NULL;
	ssize_t read;
	int counter= 0;
	int stringLength = 0;
	/* find out how we got invoked and deal with it */
	switch (argc) {
        case 1:
        	/* only one program argument (the program name) */ 
        	/* just equate stdin with our datafile */
            	datafile = stdin;  
		//need to free malloc
		while(read = getline(&line,&numberBytes, datafile)!=-1) { ///loop to read file 
			buildLL(line, delim, &head, stringLength);
			//read = getline(&line,&numberBytes, datafile);//need to free mallo
		}
		printf("%s\n","linked list: ");
		printlist(&head);
           	break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
	    while(read = getline(&line,&numberBytes, datafile)!=-1) { ///loop to read file 
		//need to add null character strcat(line,'\0');
		stringLength = strlen(line);
		buildLL(line, delim, &head, stringLength);
	    }
		printf("%s\n","linked list: ");
		printlist(&head);
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */





    fclose(datafile);
    return 0;
}

