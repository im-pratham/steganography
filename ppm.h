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
#define MAX_COLOR 255

typedef struct Pixel{
	unsigned char red,green,blue;
}Pixel;

typedef struct Image{
	int x, y;
	Pixel *data;
}Image;

/*
This function reads an image from given filename and returns a pointer to image created.
return values:
	Success: Pointer to image
	Failure: NULL

*/
Image *readImage(char *filename);
/*
This function writes an image to the given filename.
return values:
	Success: 0
	Failure: -1

*/
int writeImage(char *filename, Image *img);
/*
This function writes the given data(i.e. inputd) to a given image.
*/
void addDataToImage(Image *img, char *inputd);
/*
This function reads the data to passes buffer(i.e. dataout) from an image i.e. filename.
return values:
	Success: 0
	Failure: -1

*/
int readData(char *filename, char *dataout);
