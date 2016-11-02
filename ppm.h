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