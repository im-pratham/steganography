/*
This function is for writing the data d in a filename.
Possible values of 'cas',
	1: check validity
	2: write
Return values
	Success: 0
	Failure: -1
*/
int writemain(char *filename, int cas, char *d);
/*
This function reads the data from given image i.e. filename and returns a pointer to data buffer.
return values:
	Success: Pointer to buffer data
	Failure: NULL

*/
char *readmain(char *filename);
