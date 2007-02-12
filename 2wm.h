/* (C)opyright MMVII Anselm R. Garbe <garbeam at gmail dot com>
 * See LICENSE file for license details.
 */

#include "config.h"
#include <X11/Xlib.h>

/* mask shorthands, used in event.c and client.c */
#define BUTTONMASK		(ButtonPressMask | ButtonReleaseMask)

enum { NetSupported, NetWMName, NetLast };		/* EWMH atoms */
enum { WMProtocols, WMDelete, WMState, WMLast };	/* default atoms */
enum { CurNormal, CurResize, CurMove, CurLast };	/* cursor */
enum { ColBorder, ColFG, ColBG, ColLast };		/* color */

typedef union {
	const char *cmd;
	int i;
} Arg; /* argument type */

typedef struct {
	int ascent;
	int descent;
	int height;
	XFontSet set;
	XFontStruct *xfont;
} Fnt;

typedef struct {
	int x, y, w, h;
	unsigned long norm[ColLast];
	unsigned long sel[ColLast];
	Drawable drawable;
	Fnt font;
	GC gc;
} DC; /* draw context */

typedef struct Client Client;
struct Client {
	char name[256];
	int x, y, w, h;
	int rx, ry, rw, rh; /* revert geometry */
	int basew, baseh, incw, inch, maxw, maxh, minw, minh;
	int minax, minay, maxax, maxay;
	long flags; 
	unsigned int border;
	Bool isfixed, isfloat, ismax;
	Bool *tags;
	Client *next;
	Client *prev;
	Client *snext;
	Window win;
};

extern const char *tags[];			/* all tags */
extern char stext[256];				/* status text */
extern int bh, bmw;				/* bar height, bar mode label width */
extern int screen, sx, sy, sw, sh;		/* screen geometry */
extern int wax, way, wah, waw;			/* windowarea geometry */
extern unsigned int master, nmaster;		/* master percent, number of master clients */
extern unsigned int ntags, numlockmask;		/* number of tags, dynamic lock mask */
extern void (*handler[LASTEvent])(XEvent *);	/* event handler */
extern void (*arrange)(void);			/* arrange function, indicates mode  */
extern Atom wmatom[WMLast], netatom[NetLast];
extern Bool running, selscreen, *seltag;	/* seltag is array of Bool */
extern Client *clients, *sel, *stack;		/* global client list and stack */
extern Cursor cursor[CurLast];
extern DC dc;					/* global draw context */
extern Display *dpy;
extern Window root, barwin;

/* client.c */
extern void configure(Client *c);		/* send synthetic configure event */
extern void focus(Client *c);			/* focus c, c may be NULL */
extern Client *getclient(Window w);		/* return client of w */
extern Bool isprotodel(Client *c);		/* returns True if c->win supports wmatom[WMDelete] */
extern void killclient(Arg *arg);		/* kill c nicely */
extern void manage(Window w, XWindowAttributes *wa);	/* manage new client */
extern void resize(Client *c, Bool sizehints);	/* resize c*/
extern void updatesizehints(Client *c);		/* update the size hint variables of c */
extern void updatetitle(Client *c);		/* update the name of c */
extern void unmanage(Client *c);		/* destroy c */

/* draw.c */
extern void drawstatus(void);			/* draw the bar */
extern unsigned long getcolor(const char *colstr);	/* return color of colstr */
extern void setfont(const char *fontstr);	/* set the font for DC */
extern unsigned int textw(const char *text);	/* return the width of text in px*/

/* event.c */
extern void grabkeys(void);			/* grab all keys defined in config.h */
extern void procevent(void);			/* process pending X events */

/* main.c */
extern void quit(Arg *arg);			/* quit 2wm nicely */
extern void sendevent(Window w, Atom a, long value);	/* send synthetic event to w */
extern int xerror(Display *dsply, XErrorEvent *ee);	/* 2wm's X error handler */

/* tag.c */
extern void initrregs(void);			/* initialize regexps of rules defined in config.h */
extern Client *getnext(Client *c);		/* returns next visible client */
extern Client *getprev(Client *c);		/* returns previous visible client */
extern void settags(Client *c, Client *trans);	/* sets tags of c */
extern void tag(Arg *arg);			/* tags c with arg's index */
extern void toggletag(Arg *arg);		/* toggles c tags with arg's index */

/* util.c */
extern void *emallocz(unsigned int size);	/* allocates zero-initialized memory, exits on error */
extern void eprint(const char *errstr, ...);	/* prints errstr and exits with 1 */
extern void spawn(Arg *arg);			/* forks a new subprocess with to arg's cmd */

/* view.c */
extern void detach(Client *c);			/* detaches c from global client list */
extern void dofloat(void);			/* arranges all windows floating */
extern void dotile(void);			/* arranges all windows tiled */
extern void focusnext(Arg *arg);		/* focuses next visible client, arg is ignored  */
extern void focusprev(Arg *arg);		/* focuses previous visible client, arg is ignored */
extern void incnmaster(Arg *arg);		/* increments nmaster with arg's index value */
extern Bool isvisible(Client *c);		/* returns True if client is visible */
extern void resizemaster(Arg *arg);		/* resizes the master percent with arg's index value */
extern void restack(void);			/* restores z layers of all clients */
extern void togglefloat(Arg *arg);		/* toggles focusesd client between floating/non-floating state */
extern void togglemode(Arg *arg);		/* toggles global arrange function (dotile/dofloat) */
extern void toggleview(Arg *arg);		/* toggles the tag with arg's index (in)visible */
extern void view(Arg *arg);			/* views the tag with arg's index */
extern void zoom(Arg *arg);			/* zooms the focused client to master area, arg is ignored */