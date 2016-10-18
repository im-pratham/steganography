#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

int writemain(){
	char filename[32];
	printf("Enter Image Name\n");
	scanf("%s", filename);
	
	PPMImage *image;
	image = readPPM(filename);
	char data[image->y];
	getchar();
	printf("Enter max %d character data to write: \n", image->y - 10);
	fgets(data,image->y-10,stdin);
	//scanf("%[^'\n']s", data);
	if(strlen(data) > (image->y-10)) {
		printf("Sorry, your data is too large to kept in image\n");
		return 0;
	}
	changeColorPPM(image, data);
	writePPM("output.ppm",image);
	printf("Press any key...\n");
	/*char data[1024];
	readData(argv[1], data);
	printf("\nRead data :%s\n", data);
	*/
	getchar();
	return 0;
}
