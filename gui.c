#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "gui.h"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

char choices[128][32];

void initChoices() {
	struct dirent *de;  // Pointer for directory entry
 	int i = 0;
    // opendir() returns a pointer of DIR type. 
	DIR *dr = opendir(".");
 
	if (dr == NULL) {
		printf("Could not open current directory" );
		return;
	}
	while ((de = readdir(dr)) != NULL){
		if(de->d_type == DT_DIR){
			//printf("directory\n");
			//continue;
    			}
		//printf("%s\n", de->d_name);
		if(!strcmp(de->d_name,"..") || !strcmp(de->d_name,".")) {
			continue;
		}
			strcpy(choices[i++], de->d_name);
	} 
	strcpy(choices[i],"");
    closedir(dr);

}


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

int main() {
	ITEM **my_items;
	int c;				
	MENU *my_menu;
        WINDOW *my_menu_win;
        int n_choices, i;
	ITEM *cur_item;
	initChoices();
	
		initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);

	/* Create items */
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                my_items[i] = new_item(choices[i], choices[i]);

	/* Crate menu */
	my_menu = new_menu((ITEM **)my_items);
	
	/* Set menu option not to show the description */
	menu_opts_off(my_menu, O_SHOWDESC);

	/* Create the window to be associated with the menu */
        my_menu_win = newwin(10, 70, 4, 4);
        keypad(my_menu_win, TRUE);
     
	/* Set main window and sub window */
        set_menu_win(my_menu, my_menu_win);
        set_menu_sub(my_menu, derwin(my_menu_win, 6, 68, 3, 1));
	set_menu_format(my_menu, 5, 1);
			
	/* Set menu mark to the string " * " */
        set_menu_mark(my_menu, " * ");

	/* Print a border around the main window and print a title */
        box(my_menu_win, 0, 0);
	print_in_middle(my_menu_win, 1, 0, 70, "Select File", COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 68);
	mvwaddch(my_menu_win, 2, 69, ACS_RTEE);
        
	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_menu_win);
	
	attron(COLOR_PAIR(2));
	mvprintw(LINES - 5, 0, "Select only .ppm files");
	mvprintw(LINES - 4, 0, "Use PageUp and PageDown to scoll down or up a page of items");
	mvprintw(LINES - 3, 0, "Arrow Keys to navigate (F7 to Exit)");
	attroff(COLOR_PAIR(2));
	refresh();
	
	while((c = wgetch(my_menu_win)) != KEY_F(7))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case KEY_LEFT:
				menu_driver(my_menu, REQ_LEFT_ITEM);
				break;
			case KEY_RIGHT:
				menu_driver(my_menu, REQ_RIGHT_ITEM);
				break;
			case KEY_NPAGE:
				menu_driver(my_menu, REQ_SCR_DPAGE);
				break;
			case KEY_PPAGE:
				menu_driver(my_menu, REQ_SCR_UPAGE);
				break;
			case 10:	/* Enter */
				cur_item = current_item(my_menu);
				move(LINES - 2, 0);
				clrtoeol();
				int err = mainpro(item_name(cur_item), 1);
				if(err == -1) {
					mvprintw(LINES - 2, 0, "%s this is not a valid input image", item_name(cur_item));
				} 
				else if(err == 0) {
					mvprintw(LINES - 2, 0, "data is written in output.ppm");
				}
				else
					mvprintw(LINES - 2, 0, "You have chosen %s", item_name(cur_item));
				
				refresh();
				pos_menu_cursor(my_menu);
				break;
		}
                wrefresh(my_menu_win);
	}	
	

	/* Unpost and free all the memory taken up */
        unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
}
	
