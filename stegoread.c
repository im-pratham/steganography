#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

int readmain(char *filename){
	//char filename[32];
	//printf("Enter Image Name\n");
	//scanf("%s", filename);
	int err = 0;
	char data[1024];
	err = readData(filename, data);
	if(err == -1) {
		return err;
	}
	printf("\nRead data :%s\n", data);
	getchar();
	return 0;
}
