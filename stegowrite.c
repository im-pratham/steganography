#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

int writemain(char *filename){
	//char filename[32];
	//printf("Enter Image Name\n");
	//scanf("%s", filename);
	int err = 0;
	PPMImage *image;
	image = readPPM(filename);
	if(image == NULL) {
		return -1;
	}
	//char data[image->y];
	char data[50] = "hey its gui data written in a image";
	getchar();
	//printf("Enter max %d character data to write: \n", image->y - 10);
	//fgets(data,image->y-10,stdin);
	//data ;
	//scanf("%[^'\n']s", data);
	if(strlen(data) > (image->y-10)) {
		//printf("Sorry, your data is too large to kept in image\n");
		return -1;
	}
	changeColorPPM(image, data);
	err = writePPM("output.ppm",image);
	if(err == -1) {
		return err;
	}
	//printf("Press any key...\n");
	/*char data[1024];
	readData(argv[1], data);
	printf("\nRead data :%s\n", data);
	*/
	getchar();
	return 0;
}
