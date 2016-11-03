/*************************************************************************
*   <Steganography>
*   Copyright (C) 2016  Prathamesh Anil Mane manepa16.it@coep.ac.in
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
