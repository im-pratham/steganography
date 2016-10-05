#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("ERROR:specify source file\n");
	}
	else{
		PPMImage *image;
		image = readPPM(argv[1]);
		char data[image->y];
		printf("Enter max %d character data to write: \n", image->y - 10);
		fgets(data,image->y-10,stdin);		
		//scanf("%[^'\n']s", data);
		if(strlen(data) > (image->y-10)) {
			printf("Sorry, your data is too large to kept in image\n");
			return 0;
		}
		changeColorPPM(image, data);
		writePPM(strcat(argv[1],"-output.ppm"),image);
		printf("Press any key...\n");
		/*char data[1024];
		readData(argv[1], data);
		printf("\nRead data :%s\n", data);
		*/
		getchar();
	}
	return 0;
}
