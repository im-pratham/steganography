#include <stdio.h>
#include "project.h"

void menu() {
	printf("1. Write data to image\n");
	printf("2. Read data from image\n");
	printf("3. Exit\n");
}

int main() {
	do {
		menu();
		int c;
		scanf("%d", &c);
		switch(c) {
			case 1:
				writemain();
				break;
			case 2:
				readmain();
				break;
			case 3:
				return 0;
			default:
				printf("Invalid choice\n");
		}
	}while(1);
	return 0;
}
