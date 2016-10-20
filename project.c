#include <stdio.h>
#include <string.h>
#include "project.h"

void menu() {
	printf("1. Write data to image\n");
	printf("2. Read data from image\n");
	printf("3. Exit\n");
}

int mainpro(char *filename, int cas) {
	//char filename[32];
	int err;
		int c = cas;
		//scanf("%d", &c);
		switch(c) {
			case 1:
				//printf("Enter Image Name\n");
				//scanf("%s", filename);
				err = writemain(filename);
				if(err == -1) {
					//printf("Error while handling input file\n");
					return -1;
				}
				break;
			case 2:
				printf("Enter Image Name\n");
				scanf("%s", filename);
				err = readmain(filename);
				if(err == -1) {
					//printf("Error while handling input file\n");
					return -1;
				}
				break;
			case 3:
				return 0;
		}
	return 0;
}
