#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

int readmain(char *filename){
	//char filename[32];
	//printf("Enter Image Name\n");
	//scanf("%s", filename);
	
	char data[1024];
	readData(filename, data);
	printf("\nRead data :%s\n", data);
	getchar();
	return 0;
}
