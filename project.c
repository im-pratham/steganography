/*************************************************************************
*   <Steganography>
*   Copyright (C) 2016  Prathamesh Anil Mane manepa16.it@coep.ac.in
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
#include <curses.h>
#include <form.h>
#include <ctype.h>
#include <menu.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "project.h"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void showWin(int win_n);
char *showInputWindow();

char *choices[3] = {
	"Write Data to Image",
	"Read data from Image",
	"Exit",
};

int main() {
	ITEM **home_items;
	int c;				
	MENU *home_menu;
	WINDOW *home_menu_win;
	int n_choices, i;
	ITEM *cur_item;
	initscr();
	WINDOW *cur = newwin(LINES, COLS, 0, 0);
	start_color();
	cbreak();
	noecho();
	keypad(cur, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);

	/* Create items */
	n_choices = ARRAY_SIZE(choices);
	home_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
	for(i = 0; i < n_choices; ++i)
		home_items[i] = new_item(choices[i], choices[i]);

	/* Crate menu */
	home_menu = new_menu((ITEM **)home_items);
	
	/* Set menu option not to show the description */
	menu_opts_off(home_menu, O_SHOWDESC);

	/* Create the subwindow to be associated with the menu */
	home_menu_win = subwin(cur, 10, COLS - 10, 4, 4);
	keypad(home_menu_win, TRUE);
     
	/* Set main menu window and sub window */
	set_menu_win(home_menu, home_menu_win);
	set_menu_sub(home_menu, derwin(home_menu_win, 6, 68, 3, 1));
	set_menu_format(home_menu, 5, 1);
			
	/* Set menu mark to the string as" * " */
	set_menu_mark(home_menu, " * ");

	/* Print a border around the main window and print a title */
	box(home_menu_win, 0, 0);
	print_in_middle(home_menu_win, 1, 0, COLS - 10, "Select File", COLOR_PAIR(1));
	mvwaddch(home_menu_win, 2, 0, ACS_LTEE);
	mvwhline(home_menu_win, 2, 1, ACS_HLINE, COLS - 12);
	mvwaddch(home_menu_win, 2, COLS - 11, ACS_RTEE);
	
	/* Post the menu */
	post_menu(home_menu);
	wrefresh(home_menu_win);
	
	attron(COLOR_PAIR(2));
	//mvwprintw(cur, LINES - 5, 2, "Select only .ppm files");
	mvwprintw(cur, LINES - 4, 2, "Use PageUp and PageDown to scroll down or up a page");
	mvwprintw(cur, LINES - 3, 2, "Arrow Keys to navigate (F7 to Exit)");
	attroff(COLOR_PAIR(2));
	wrefresh(cur);
	
	/* specifying what to be done on keypress */
	while((c = wgetch(home_menu_win)) != KEY_F(7)) {
		switch(c) {
			case KEY_DOWN:
				menu_driver(home_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(home_menu, REQ_UP_ITEM);
				break;
			case KEY_LEFT:
				menu_driver(home_menu, REQ_LEFT_ITEM);
				break;
			case KEY_RIGHT:
				menu_driver(home_menu, REQ_RIGHT_ITEM);
				break;
			case KEY_NPAGE:
				menu_driver(home_menu, REQ_SCR_DPAGE);
				break;
			case KEY_PPAGE:
				menu_driver(home_menu, REQ_SCR_UPAGE);
				break;
			case 10:	/* Enter */
				cur_item = current_item(home_menu);
				move(LINES - 2, 0);
				/* if Exit is selected */
				if(strcmp(item_name(cur_item), choices[2]) == 0) {
					/* Unpost and free all the memory taken up */
					unpost_menu(home_menu);
					free_menu(home_menu);
					for(i = 0; i < n_choices; ++i)
						free_item(home_items[i]);
					endwin();
					return 0;
				}
				/*if read from an image is selected */
				else if(strcmp(item_name(cur_item), choices[1]) == 0) {
					showWin(2);
				}
				/*if write to an image is selected */
				else if(strcmp(item_name(cur_item), choices[0]) == 0) {
					showWin(1);
				}
				wrefresh(cur);
				pos_menu_cursor(home_menu);
				break;
		}
		wrefresh(home_menu_win);
		touchwin(cur);
	}
	wrefresh(home_menu_win);
	touchwin(cur);
	/* Unpost and free all the memory taken up */
	unpost_menu(home_menu);
	free_menu(home_menu);
	for(i = 0; i < n_choices; ++i)
		free_item(home_items[i]);
	endwin();
	return 0;
}

void showWin(int win_n) {
	/*check if value of win_n is correct or not*/
	if(win_n > 4) {
		return;
	}
	char **filenames;
	ITEM **file_items;
	int c, err;		
	MENU *file_menu;
	WINDOW *file_menu_win;
	int n_choices, i;
	ITEM *cur_item;
	/*creating new window */
	WINDOW *cur = newwin(LINES , COLS, 0, 0);
	start_color();
	cbreak();
	noecho();
	keypad(cur, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_WHITE, COLOR_BLUE);
	/* initializing array to the files in a directory */
	filenames = (char **)malloc(sizeof(char *) * 128);
	struct dirent *de;
	i = 0;
	/* opening a current directory to list all files */
	DIR *dr = opendir(".");
	if (dr == NULL) {
		/* Could not open current directory */
		return;
	}
	while ((de = readdir(dr)) != NULL) {
		/* if de is a file */
		if(de->d_type == DT_REG){
			filenames[i] = malloc(sizeof(char) * strlen(de->d_name) + 1);
			strcpy(filenames[i++], de->d_name);
		}
	}
	filenames[i] = malloc(sizeof(char) * 1);
	strcpy(filenames[i], "");
	closedir(dr);

	/* Create items */
	//n_choices = ARRAY_SIZE(filenames);
	n_choices = i;
	file_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
	for(i = 0; i < n_choices; ++i)
		file_items[i] = new_item(filenames[i], filenames[i]);

	/* Creating menu */
	file_menu = new_menu((ITEM **)file_items);
	
	/* Setting menu option not to show the description */
	menu_opts_off(file_menu, O_SHOWDESC);

	/* Creating the window to be associated with the menu */
	file_menu_win = subwin(cur, 10, COLS - 10, 4, 4);
	keypad(file_menu_win, TRUE);
     
	/* Setting main window and sub window */
	set_menu_win(file_menu, file_menu_win);
	set_menu_sub(file_menu, derwin(file_menu_win, 6, COLS - 12, 3, 1));
	set_menu_format(file_menu, 5, 1);
			
	/* Setting menu mark to the string " * " */
	set_menu_mark(file_menu, " * ");

	/* Printing a border around the main window and print a title */
	box(file_menu_win, 0, 0);
	
	/*checking window number and printing header accordingly */
	if(win_n == 2)
		print_in_middle(file_menu_win, 1, 0, COLS - 10, "Select File To Read", COLOR_PAIR(1));
	if(win_n == 1)
		print_in_middle(file_menu_win, 1, 0, COLS - 10, "Select File To Write", COLOR_PAIR(1));
	mvwaddch(file_menu_win, 2, 0, ACS_LTEE);
	mvwhline(file_menu_win, 2, 1, ACS_HLINE, COLS - 12);
	mvwaddch(file_menu_win, 2, COLS - 11, ACS_RTEE);
        
	/* Posting the menu */
	post_menu(file_menu);
	wrefresh(file_menu_win);
	wrefresh(cur);
	attron(COLOR_PAIR(2));
	mvwprintw(cur, LINES - 5, 2, "Select only .ppm files");
	attron(COLOR_PAIR(1));
	mvwprintw(cur, LINES - 4, 2, "Use PageUp and PageDown to scroll down or up a page");
	attron(COLOR_PAIR(3));
	mvwprintw(cur, LINES - 3, 2, "Arrow Keys to navigate (F8 to Exit)");
	wrefresh(cur);
	
	/* action to be taken on perticular keystroke */
	while((c = wgetch(file_menu_win)) != KEY_F(8))
	{       switch(c)
	        {
			case KEY_DOWN:
				menu_driver(file_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(file_menu, REQ_UP_ITEM);
				break;
			case KEY_LEFT:
				menu_driver(file_menu, REQ_LEFT_ITEM);
				break;
			case KEY_RIGHT:
				menu_driver(file_menu, REQ_RIGHT_ITEM);
				break;
			case KEY_NPAGE:
				menu_driver(file_menu, REQ_SCR_DPAGE);
				break;
			case KEY_PPAGE:
				menu_driver(file_menu, REQ_SCR_UPAGE);
				break;
			case 10:	/* Enter */
				cur_item = current_item(file_menu);
				move(LINES - 2, 0);
				
				/* If window number is 2 i.e. Read Data window */
				if(win_n == 2) {
					char filen[64];
					/* Copying name of selected file into filen */
					strcpy(filen, item_name(cur_item));
					char *p = readmain(filen);
					/* if file name is not valid */
					if(!p) {
						/* creating subwindow for displaying output */
						WINDOW *output = newwin(10, COLS - 10, 4, 4);
						mvwprintw(output, 1, 1, "%s this is not a valid input image", item_name(cur_item));
						box(output, 0, 0);
						wrefresh(output);
						/* wait until user presses F8 */
						while((c = wgetch(file_menu_win)) != KEY_F(8));
						delwin(output);
					}
					/* if file is valid then read data and display it */
					else {
						WINDOW *output = newwin(10, COLS - 10, 4, 4);
						//sprintf(data, "%%-%ds", COLS);
						/* code for printing data in a window */
						int tmp = strlen(p);
						int line = 0, total = COLS - 15;
						char tm[12];
						sprintf(tm, "%%.%ds", total);
						mvwprintw(output, line++, 1, "%s", p);
						for(; tmp > 12; tmp -= total) {
							char tm[12];
							sprintf(tm, "%%.%ds", total);
							mvwprintw(output, line++, 1, tm, p);
							p = p + total;
						}
						mvwprintw(output, line++, 1, "%s", p);
						/* end */
						box(output, 0, 0);
						wrefresh(output);
						/* wait until user presses F8 */
						while((c = wgetch(file_menu_win)) != KEY_F(8));
						delwin(output);
					}
				}
				/*write window*/
				else if(win_n == 1) {
					cur_item = current_item(file_menu);
					char data[64];
					strcpy(data, item_name(cur_item));
					move(LINES - 2, 0);
					clrtoeol();
					/* call writemain with cas = 1 to check if input file is valid or not */
					err = writemain(data, 1, NULL);
					/* if not valid */
					if(err == -1) {
						WINDOW *output = newwin(10, COLS - 10, 4, 4);
						char tmp[128];
						sprintf(tmp, "%s this is not a valid input image", item_name(cur_item));
						print_in_middle(output, 4, 0, COLS - 14, tmp, COLOR_PAIR(1));
						//mvwprintw(output, 1, 1, "%s this is not a valid input image", item_name(cur_item));
						box(output, 0, 0);
						wrefresh(output);
						/* wait until user presses any key */
						wgetch(file_menu_win);
						delwin(output);
					} 
					/* if valid, write data */
					else {
						char *p = showInputWindow();
						/* call writemain with inputted data by user */
						writemain(data, 2, p);
						WINDOW *output = newwin(10, COLS - 10, 4, 4);
						print_in_middle(output, 4, 0, COLS - 14, "Data is written in output.ppm", COLOR_PAIR(1));
						//mvwprintw(output, 1, 1, "data is written in output.ppm");
						box(output, 0, 0);
						wrefresh(output);
						/* wait until user presses F8 */
						while((c = wgetch(file_menu_win)) != KEY_F(8));
						delwin(output);
					}
				}
				pos_menu_cursor(file_menu);
				break;
		}
		touchwin(cur);
		touchwin(file_menu_win);
	}
	touchwin(cur);
	touchwin(file_menu_win);
	/* Unpost and free all the memory taken up */
        unpost_menu(file_menu);
        free_menu(file_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(file_items[i]);

	delwin(file_menu_win);
	delwin(cur);
	free(filenames);
}

char *showInputWindow()
{
	FIELD *textfield[2];
	FORM  *input_form;
	WINDOW *input_form_win;
	int ch, rows, cols;
	/* Initializing color pairs */
   	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);
	init_pair(3, COLOR_WHITE, COLOR_BLUE);
	/* Initialize the fields */
	textfield[0] = new_field(1, COLS - 15, 1, 1, 0, 0);
	textfield[1] = NULL;

	/* Setting field options */
	set_field_fore(textfield[0], COLOR_PAIR(2)); /* foreground color */
	set_field_back(textfield[0], COLOR_PAIR(3)); /* backround color */
	set_field_back(textfield[0], A_UNDERLINE); /* underline the field */
	field_opts_off(textfield[0], O_AUTOSKIP); /* Don't go to next field when this Field is filled up */
	field_opts_off(textfield[0], O_STATIC); /* make filed length dynamic */
	set_max_field(textfield[0], 15); /* set maximum dyanmic field size */
	/* Create the form and post it */
	input_form = new_form(textfield);
	
	/* Calculate the area required for the form */
	scale_form(input_form, &rows, &cols);

        input_form_win = newwin(rows + 8, cols + 4, 4, 4);
        keypad(input_form_win, TRUE);

	/* Set main window and sub window */
        set_form_win(input_form, input_form_win);
        set_form_sub(input_form, derwin(input_form_win, rows, cols, 2, 2));

	/* Print a border around the main window and print a title */
        box(input_form_win, 0, 0);
	print_in_middle(input_form_win, 1, 0, cols + 4, "ENTER DATA", COLOR_PAIR(1));
	
	post_form(input_form);
	wrefresh(input_form_win);
	//refresh();
	char *data = (char *) malloc(1024);
	int i = 0;
	data[i] = '\0';
	/* Loop through to get user requests */
	form_driver(input_form, REQ_NEXT_FIELD);
	while((ch = wgetch(input_form_win)) != KEY_F(7))
	{	switch(ch)
		{	case KEY_DOWN:
				/* Go to next field */
				form_driver(input_form, REQ_NEXT_FIELD);
				/* Go to the end of the present buffer */
				form_driver(input_form, REQ_END_LINE);
				break;
			case KEY_UP:
				/* Go to previous field */
				form_driver(input_form, REQ_PREV_FIELD);
				form_driver(input_form, REQ_END_LINE);
				break;
			case KEY_BACKSPACE:
				form_driver(input_form, REQ_DEL_PREV);
				if(i > 0)
					data[--i] = '\0';
				break;
			
			case 10:
				//mvwprintw(input_form_win,1, 1, data);
				//touchwin();
				pos_form_cursor(input_form);
				unpost_form(input_form);
				free_form(input_form);
				free_field(textfield[0]);
				free_field(textfield[1]); 
				delwin(input_form_win);
				return data;
			default:
				form_driver(input_form, ch);
				if(isprint(ch) || isspace(ch)) {
					data[i++] = ch;
					data[i] = '\0';
					}
				break;
		}
	}
	/* Un post form and free the memory */
	unpost_form(input_form);
	free_form(input_form);
	free_field(textfield[0]);
	free_field(textfield[1]); 
	delwin(input_form_win);
	return data;
}

/*
This function prints the data in 'string' with color-pair 'color' into window 'win' 
from position 'starty' and startx having width 'width'
*/
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}
