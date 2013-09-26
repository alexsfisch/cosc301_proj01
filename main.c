/*
 *Alex Fisch
 *Ross Nicholson
 *September 25
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "list.h"
#include <sys/resource.h>

void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}


int main(int argc, char **argv) {
	//system and user time variables
        struct rusage usage2;
	struct timeval end, end2;
	getrusage(RUSAGE_SELF, &usage2);
	//if use getline, user must free
	struct node *head = NULL;
	FILE *datafile;
	char* delim = " , \n,\t";
	char* line;
	size_t numberBytes=NULL;
	ssize_t read;
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
			free(line);
			line=NULL;
		}
		printf("%s\n","*** List Contents Begin*** ");
		printlist(&head);
		printf("%s\n","*** List Contents End ***");

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
		stringLength = strlen(line);
		buildLL(line, delim, &head, stringLength);
		free(line);
		line=NULL;
	    }
		printf("%s\n","*** List Contents Begin*** ");
		printlist(&head);
		printf("%s\n","*** List Contents End ***");
		
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    //print out user and system times
    getrusage(RUSAGE_SELF, &usage2);
    end = usage2.ru_utime;
    end2 = usage2.ru_stime;
    printf("%s","User time:  ");
    printf("%ld.%lds\n",end.tv_sec, end.tv_usec);
    printf("%s","System time:  ");
    printf("%ld.%lds\n",end2.tv_sec, end2.tv_usec);

    fclose(datafile);
    return 0;
}

