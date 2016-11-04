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
