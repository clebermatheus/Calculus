/****************************************************************************
 * This is the implementation file for conio.h - a conio.h for Linux.       *
 * It uses ncurses and some internal functions of Linux to simulate the     *
 * I/O-functions.                                                           *
 * This is copyright (c) 1996,97 by Fractor / Mental eXPlosion (MXP)        *
 * Use and distribution is only allowed if you follow the terms of the      *
 * GNU Library Public License Version 2.                                    *
 * Since this work bases on ncurses please read it's copyright notices as   *
 * well !                                                                   *
 * Look into the readme to this file for further information.               *
 * Thanx to SubZero / MXP for his little tutorial on the curses library !   *
 * Many thanks to Mark Hahn and Rich Cochran for solving the inpw and inpd  *
 * mega-bug !!!                                                             *
 * Watch out for other MXP releases, too !                                  *
 * Send bugreports to: fractor@germanymail.com                              *
 ****************************************************************************/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curses.h>
#include "conio.h" 

static int txtattr,oldattr;
static int fgc,bgc;
static int initialized=0;
char color_warning=1;
int directvideo;
WINDOW *conio_scr;

/* Some internals... */
int colortab(int a) /* convert LINUX Color code to DOS-standard */
{
   switch(a) {
      case 0 : return COLOR_BLACK;
      case 1 : return COLOR_BLUE;
      case 2 : return COLOR_GREEN;
      case 3 : return COLOR_CYAN;
      case 4 : return COLOR_RED;
      case 5 : return COLOR_MAGENTA;
      case 6 : return COLOR_YELLOW;
      case 7 : return COLOR_WHITE;
   }
} 

void docolor (int color) /* Set DOS-like text mode colors */
{
   wattrset(conio_scr,0); /* My curses-version needs this ... */
   if ((color&128)==128) txtattr=A_BLINK; else txtattr=A_NORMAL;
   if ((color&15)>7) txtattr|=A_STANDOUT; else txtattr|=A_NORMAL;
   txtattr|=COLOR_PAIR((1+(color&7)+(color&112)) >> 1);
   if (((color&127)==15) | ((color&127)==7)) txtattr=COLOR_PAIR(0);
   if (((color&127)==127) | ((color&127)==119)) txtattr=COLOR_PAIR(8);
   wattron(conio_scr,txtattr);
   wattron(conio_scr,COLOR_PAIR(1+(color&7)+((color&112)>>1))); 
}

/* This is Intel-specific ! */
static inline int inport (int port)
{
   unsigned char value;
  __asm__ volatile ("inb %1,%0"
                    : "=a" (value)
                    : "d" ((unsigned short) port));
   return value;
}

static inline int inportd (int port)
{
   unsigned int value;
  __asm__ volatile ("inl %1,%0"
                    : "=a" (value)
                    : "d" ((unsigned short)port));
   return value;
}

static inline int inportw (int port)
{
   unsigned short value;
  __asm__ volatile ("inw %1,%0"
                    : "=a" (value)
                    : "d" ((unsigned short)port));
   return value;
}

static inline void outport (unsigned short int port, unsigned char val)
{
  __asm__ volatile (
                    "outb %0,%1\n"
                    :
                    : "a" (val), "d" (port)
                    );
}

static inline void outportw (unsigned short int port, unsigned int val)
{
  __asm__ volatile (
                    "outw %0,%1\n"
                    :
                    : "a" (val), "d" (port)
                    );
}

static inline void outportd (unsigned short int port, unsigned int val)
{
  __asm__ volatile (
                    "outl %0,%1\n"
                    :
                    : "a" (val), "d" (port)
                    );
}

/* Call this before any call to linux conio - except the port functions ! */
void initconio (void) /* This is needed, because ncurses needs to be initialized */
{
   int x,y;
   attr_t dummy1;
   short dummy2;
   initialized=1;
   initscr();
   start_color();
   oldattr=wattr_get(stdscr,&dummy1,&dummy2,NULL);
   nonl();
   raw();
   if (!has_colors() & (color_warning>-1))
      fprintf(stderr,"Attention: A color terminal may be required to run this application !\n");   
   noecho();
   conio_scr=newwin(0,0,0,0);
   keypad(conio_scr,TRUE);
   meta(conio_scr,TRUE);
   idlok(conio_scr,TRUE);
   scrollok(conio_scr,TRUE);
   /* Color initialization */
   for (y=0;y<=7;y++)
      for (x=0;x<=7;x++)
         init_pair((8*y)+x+1, colortab(x), colortab(y));              
   txtattr=wattr_get(conio_scr,&dummy1,&dummy2,NULL);
   bgc=0;
   textcolor(7);
   textbackground(0);
}

/* Call this on exiting your program */
void doneconio (void)
{
   endwin();
}

/* Here it starts... */
char *cgets (char *str) /* ugly function :-( */
{
   char strng[257];
   unsigned char i=2;
   if (initialized==0) initconio();
   echo();
   strncpy(strng,str,1);
   wgetnstr(conio_scr,&strng[2],(int) strng[0]);
   while (strng[i]!=0) i++;
   i=i-2;
   strng[1]=i;
   strcpy(str,strng);
   noecho();
   return(&str[2]);
}

void clreol (void)
{
   if (initialized==0) initconio();
   wclrtoeol(conio_scr);
   wrefresh(conio_scr);
}

void clrscr (void)
{
   if (initialized==0) initconio();
   wclear(conio_scr);
   wmove(conio_scr,0,0);
   wrefresh(conio_scr);
}

int cprintf (char *format, ... )
{
   int i;
   char buffer[BUFSIZ]; /* Well, BUFSIZ is from ncurses...  */
   va_list argp;
   if (initialized==0) initconio();
   va_start(argp,format);
   vsprintf(buffer,format,argp);
   va_end(argp);
   i=waddstr(conio_scr,buffer);
   wrefresh(conio_scr);
   return(i);
}

void cputs (char *str)
{
   if (initialized==0) initconio();
   waddstr(conio_scr,str);
   wrefresh(conio_scr);
}

int cscanf (const char *format, ...)
{
   int i;
   char buffer[BUFSIZ]; /* See cprintf */
   va_list argp;
   if (initialized==0) initconio();
   echo();
   if (wgetstr(conio_scr,buffer)==ERR) return(-1);                    
   va_start(argp,format);
   i=vsscanf(buffer,format,argp);                         
   va_end(argp);
   noecho();
   return(i);
}

void delline (void)
{
   if (initialized==0) initconio();  
   wdeleteln(conio_scr);
   wrefresh(conio_scr);
}

/* By Flash, 10/2001 */

void cursor(void)
{
	curs_set(1);
}

void nocursor(void)
{
	curs_set(0);
}

int key(void)
{
   int i;
   if(initialized==0) initconio();
   i=wgetch(conio_scr);
   if(i==-1) i=0;
   return i;
}

/* end */

int getche (void)
{
   int i;
   if (initialized==0) initconio();
   echo();
   i=wgetch(conio_scr);
   if (i==-1) i=0;
   noecho();
   return(i);
}

void gettextinfo(struct text_info *inforec)
{
   attr_t dummy1;
   short dummy2;
   unsigned char xp,yp;
   unsigned char x1,x2,y1,y2;
   unsigned char cols,lines;
   unsigned char dattr,dnattr,a; /* The "d" stands for DOS */
   if (initialized==0) initconio();
   getyx(conio_scr,yp,xp);
   getbegyx(conio_scr,y1,x1);
   getmaxyx(conio_scr,y2,x2);
   dattr=(bgc*16)+fgc;
   a=wattr_get(conio_scr,&dummy1,&dummy2,NULL);
   if (a==(a & A_BLINK)) dattr=dattr+128;
   dnattr=oldattr;  /* Well, this cannot be right, 
                       because we don't know the COLORPAIR values from before initconio() !*/
   inforec->winleft=x1+1;
   inforec->wintop=y1+1;
   if (x1==0) x2--;
   if (y1==0) y2--;
   inforec->winright=x1+x2+1;
   inforec->winbottom=y1+y2+1;
   inforec->curx=xp+1;
   inforec->cury=yp+1;
   inforec->screenheight=y2+1;
   inforec->screenwidth=x2+1;
   inforec->currmode=3; /* This is C80 */
   inforec->normattr=dnattr; /* Don't use this ! */
   inforec->attribute=dattr;
} 

void gotoxy (int x, int y)
{
   if (initialized==0) initconio();
   y--;
   x--;
   wmove(conio_scr,y,x);
   wrefresh(conio_scr);
}

void highvideo (void)
{
   if (initialized==0) initconio();
   textcolor(15); /* White */
   textbackground(0); /* Black */
}
/*
unsigned inp (unsigned port)
{
   if (ioperm(port,1,1)!=0) { 
   fprintf(stderr,"Could not get IO permissions to read port %d\n",port);
   return(65535);
   } else return(inport(port));
}

unsigned inpd (unsigned port)
{
   if (ioperm(port,4,1)!=0) { 
   fprintf(stderr,"Could not get IO permissions to read port %d\n",port);
   return(65535);
   } else return(inportd(port));
}

unsigned inpw (unsigned port)
{
   if (ioperm(port,2,1)!=0) { 
   fprintf(stderr,"Could not get IO permissions to read port %d\n",port);
   return(65535);
   } else  return(inportw(port));
}

unsigned outp (unsigned port, unsigned value)
{
   if (ioperm(port,1,1)!=0) { 
   fprintf(stderr,"Could not get IO permissions to write to port %d\n",port);
   return(65535);
   } else outport(port,value);
   return(value);
}

unsigned outpd (unsigned port, unsigned value)
{
   if (ioperm(port,4,1)!=0) { 
   fprintf(stderr,"Could not get IO permissions to write to port %d\n",port);
   return(65535);
   } else outportd(port,value);
   return(value);
}
unsigned outpw (unsigned port, unsigned value)
{
   if (ioperm(port,2,1)!=0) { 
   fprintf(stderr,"Could not get IO permissions to write to port %d\n",port);
   return(65535);
   } else outportw(port,value);
   return(value);
}
*/

void insline (void)
{ 
   if (initialized==0) initconio();
   winsertln(conio_scr);
   wrefresh(conio_scr);
}

int kbhit (void)
{
   int i;
   if (initialized==0) initconio();
   nodelay(conio_scr,TRUE);
   i=wgetch(conio_scr);
   nodelay(conio_scr,FALSE);
   if (i==-1) i=0;
   return(i);
}

void lowvideo (void)
{
   if (initialized==0) initconio();
   textbackground(0); /* Black */
   textcolor(8); /* Should be darkgray */
}

void normvideo (void)
{
   if (initialized==0) initconio();
   wattrset(conio_scr,oldattr);
}

int putch (int c)
{
   if (initialized==0) initconio();
   if (waddch(conio_scr,c)!=ERR) {
      wrefresh(conio_scr); 
      return(c);
   }
   return(0);
}
                                     
void textattr (int attr)
{
   if (initialized==0) initconio();
   docolor(attr);
}

void textbackground (int color)
{
   if (initialized==0) initconio();
   bgc=color;
   color=(bgc*16)+fgc;
   docolor(color);
}

void textcolor (int color)
{
   if (initialized==0) initconio();
   fgc=color;
   color=(bgc*16)+fgc;
   docolor(color);
}
 
void textmode (int mode)
{
   if (initialized==0) initconio();
   /* Ignored */
}

int wherex (void)
{
   int y;
   int x;
   if (initialized==0) initconio();
   getyx(conio_scr,y,x);
   x++;
   return(x);
}

int wherey (void)
{
   int y;
   int x;
   if (initialized==0) initconio();
   getyx(conio_scr,y,x);
   y++;
   return(y);
}

void window (int left,int top,int right,int bottom)
{
   int nlines,ncols;
   if (initialized==0) initconio();
   delwin(conio_scr);
   top--;
   left--;
   right--;
   bottom--;
   nlines=bottom-top;
   ncols=right-left;
   if (top==0) nlines++;
   if (left==0) ncols++;
   if ((nlines<1) | (ncols<1)) return;
   conio_scr=newwin(nlines,ncols,top,left);   
   keypad(conio_scr,TRUE);
   meta(conio_scr,TRUE);
   idlok(conio_scr,TRUE);
   scrollok(conio_scr,TRUE);
   wrefresh(conio_scr);
}

/* Linux is cool */
