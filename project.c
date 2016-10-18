#include <stdio.h>
#include <string.h>
#include "project.h"

void menu() {
	printf("1. Write data to image\n");
	printf("2. Read data from image\n");
	printf("3. Exit\n");
}

int main() {
	char filename[32];
	do {
		menu();
		int c;
		scanf("%d", &c);
		switch(c) {
			case 1:
				printf("Enter Image Name\n");
				scanf("%s", filename);
				writemain(filename);
				break;
			case 2:
				printf("Enter Image Name\n");
				scanf("%s", filename);
				readmain(filename);
				break;
			case 3:
				return 0;
			default:
				printf("Invalid choice\n");
		}
	}while(1);
	return 0;
}
