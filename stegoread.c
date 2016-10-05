#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("ERROR:specify source file\n");
	}
	else{
		char data[1024];
		readData(argv[1], data);
		printf("\nRead data :%s\n", data);
		getchar();
	}
	return 0;
}
