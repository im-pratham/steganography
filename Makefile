project: gui.o project.o stegowrite.o stegoread.o
	cc gui.o project.o stegowrite.o stegoread.o ppm.o -o project -lmenu -lncurses
gui.o: gui.c gui.h
	cc -Wall -c gui.c
project.o: project.c project.h
	cc -Wall -c project.c
stegowrite.o: stegowrite.c ppm.o ppm.h
	cc -Wall -c stegowrite.c
stegoread.o: stegoread.c ppm.h ppm.o
	cc -Wall -c stegoread.c
ppm.o: ppm.c ppm.h
	cc -Wall -c ppm.c

