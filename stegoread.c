#include <stdlib.h>
#include "ppm.h"

char *readmain(char *filename){
	char *data = (char *) malloc(2048);
	/*
	read the data from the image filename into the buffer data
	*/
	int err = readData(filename, data);
	/*
	check for error occured during reading data from image
	*/
	if(err == -1) {
		return NULL;
	}
	/*
	return data read
	*/
	return data;
}
