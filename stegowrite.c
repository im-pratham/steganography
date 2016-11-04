/*************************************************************************
*   <Steganography>
*   Copyright (C) 2017  Prathamesh Anil Mane manepa16.it@coep.ac.in
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>
**************************************************************************/
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
