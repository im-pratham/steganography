#include <stdlib.h>
#include <string.h>
#include "ppm.h"

int writemain(char *filename, int cas, char *d){
	Image *image;
	image = readImage(filename);
	if(image == NULL) {
		return -1;
	}
	if(cas != 1) {
		char data[image->y];
		strcpy(data, d);
		strcat(data, " ");
		/*
		return when the data to be written is greater than the actual data holding capacity of image
		*/
		if(strlen(data) > (image->y-10)) {
			return -1;
		}
		addDataToImage(image, data);
		/*
		write the data in output.ppm image
		*/
		int err = writeImage("output.ppm",image);
		/*
		check for error occured during writing image
		*/
		if(err == -1) {
			return err;
		}
	}
	return 0;
}
