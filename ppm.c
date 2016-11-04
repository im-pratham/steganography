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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

Image *readImage(char *filename)
{
	char buff[16];
	Image *img;
	FILE *fp;
	int c, rgb_comp_color;
	
	fp = fopen(filename, "rb");
	if (!fp) {
		return NULL;
	}
	
	//read image format
	if (!fgets(buff, sizeof(buff), fp)) {
		return NULL;
	}
 	//the ppm image has a format P6
	if (buff[0] != 'P' || buff[1] != '6') {
		return NULL;
	}

	img = (Image *)malloc(sizeof(Image));
	if (!img) {
		//error in malloc
		return NULL;
	}	

	//excluding comments as comments are written in image preceding #
	c = getc(fp);
	while (c == '#') {
		while (getc(fp) != '\n') ;
			c = getc(fp);
	}

	ungetc(c, fp);
	//read image x and y size
	if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
		return NULL;
	}
	
	//read rgb component
	if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
		return NULL;
	}

	//check rgb component depth
	if (rgb_comp_color != MAX_COLOR) {
		return NULL;
	}

	while (fgetc(fp) != '\n') ;
	//memory allocation for pixels
	img->data = (Pixel*)malloc(img->x * img->y * sizeof(Pixel));

	if (!img) {
		return NULL;
	}

	/*
	read (img->y) sized pixel data of size each (3 * img->x) from file
	3 becoz of RGB structure of pixel
	*/
	if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
		return NULL;
	}

	fclose(fp);
	return img;
}


int readData(char *filename, char *dataout) {
	char buff[16];
	Image *img;
	FILE *fp;
	int c, rgb_comp_color;
	
	fp = fopen(filename, "rb");
	if (!fp) {
		return -1;
	}
	
	//read image format
	if (!fgets(buff, sizeof(buff), fp)) {
		return -1;
	}
 	//check the image format
	if (buff[0] != 'P' || buff[1] != '6') {
		return -1;
	}

	img = (Image *)malloc(sizeof(Image));
	if (!img) {
		return -1;
	}	

	c = getc(fp);
	while (c == '#') {
		while (getc(fp) != '\n') ;
			c = getc(fp);
	}

	ungetc(c, fp);
	if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
		return -1;
	}
	
	if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
		return -1;
	}

	if (rgb_comp_color != MAX_COLOR) {
		return -1;
	}

	while (fgetc(fp) != '\n') ;
	//memory allocation for pixels
	img->data = (Pixel*)malloc(img->x * img->y * sizeof(Pixel));

	if (!img) {
		return -1;
	}

	//read pixel data from file
	if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
		return -1;
	}
	
	//reading the data
	int i;
	char *p = dataout;
	char ch = 'a';
	if(img){
		for(i=0; i < (img->x * img->y); i++){  
			if(ch == 0)
					break;
			if((i % (img ->x)) == (img->x - 1)) {
				int x = img->data[i - 1].red;
				int y = img->data[i].red ;
				ch = (char) x^y;
				*p++ = ch;
				continue;
			}
		}
	*p = '\0';
	}
	fclose(fp);
	return 0;
}

int writeImage(char *filename, Image *img)
{
	FILE *fp;
	//open file for output
	fp = fopen(filename, "wb");
	if (!fp) {
		return -1;
	}

	//write the header file
	//image format
	fprintf(fp, "P6\n");
	
	//image size
	fprintf(fp, "%d %d\n",img->x,img->y);

	// rgb component depth
	fprintf(fp, "%d\n",MAX_COLOR);

	// pixel data
	fwrite(img->data, 3 * img->x, img->y, fp);
	fclose(fp);
	return 0; 	
}

void addDataToImage(Image *img, char *inputd)
{
	char data[strlen(inputd)];
	strcpy(data, inputd);
	//initializing to strlen(data) because we are passing string, but when use fgets add -1
	int i, len = strlen(data) - 1;
	if(img) {
		for(i = 0; i < (img->x * img->y); i++) {  
			if((i % (img ->x)) == (img->x - 1) && len > 0) {
				img->data[i - 1].red = img->data[i].red;
				img->data[i - 1].green = img->data[i].green;
				img->data[i - 1].blue = img->data[i].blue;
				
				img->data[i].red = img->data[i].red ^ (int) data[strlen(data) - (len) - 1] ;
				img->data[i].green = img->data[i].green;
				img->data[i].blue = img->data[i].blue;
				len--;
				continue;
			}
			if((i % (img ->x)) == (img->x -1) && len == 0) {
				img->data[i - 1].red = img->data[i].red;
				img->data[i - 1].green = img->data[i].green;
				img->data[i - 1].blue = img->data[i].blue;
				img->data[i].red = img->data[i].red;
				img->data[i].green = img->data[i].green;
				img->data[i].blue = img->data[i].blue;
				len--;
				break;
			}

		}
	}
}
