/* Copyright 2006-2007 Anselm R. Garbe <garbeam at gmail dot com> */

#include "cswm.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <X11/Xutil.h>


typedef struct { regex_t *regex; } RReg;

/* static */

static RReg *rreg = NULL;
static unsigned int reglen = 0;

static Client *
getnext(Client *c) {
    for(; c && c->view != view; c = c->next);
    return c;
}

static Client *
getprev(Client *c) {
    for(; c && c->view != view; c = c->prev);
    return c;
}

static void
pop(Client *c) {
    detachclient(c);
    if(clients)
        clients->prev = c;
    c->next = clients;
    clients = c;
}

static void
togglemax(Client *c) {
    XEvent ev;
        
    if(c->isfixed)
        return;

    if((c->ismax = !c->ismax)) {
        c->rx = c->x; c->x = sx;
        c->ry = c->y; c->y = sy;
        c->rw = c->w; c->w = sw - 2 * BORDERPX;
        c->rh = c->h; c->h = sh - 2 * BORDERPX;
    }
    else {
        c->x = c->rx;
        c->y = c->ry;
        c->w = c->rw;
        c->h = c->rh;
    }
    resize(c, True);
    while(XCheckMaskEvent(dpy, EnterWindowMask, &ev));
}

/* extern */

void
arrange(void) {
    unsigned int i, n, mw, mh, tw, th;
    Client *c;

    for(n = 0, c = getnext(clients); c; c = getnext(c->next))
        n++;
    /* window geoms */
    mh = (n > nmaster) ? sh / nmaster : sh / (n > 0 ? n : 1);
    mw = (n > nmaster) ? (sw * master) / 1000 : sw;
    th = (n > nmaster) ? sh / (n - nmaster) : 0;
    tw = sw - mw;

    for(i = 0, c = clients; c; c = c->next)
        if(c->view == view) {
            c->ismax = False;
            c->x = sx;
            c->y = sy;
            if(i < nmaster) {
                c->y += i * mh;
                c->w = mw - 2 * BORDERPX;
                c->h = mh - 2 * BORDERPX;
            }
            else {  /* tile window */
                c->x += mw;
                c->w = tw - 2 * BORDERPX;
                if(th > 2 * BORDERPX) {
                    c->y += (i - nmaster) * th;
                    c->h = th - 2 * BORDERPX;
                }
                else /* fallback if th <= 2 * BORDERPX */
                    c->h = sh - 2 * BORDERPX;
            }
            resize(c, False);
            i++;
        }
        else
            XMoveWindow(dpy, c->win, c->x + 2 * sw, c->y);
    if(!sel || sel->view != view) {
        for(c = stack; c && c->view != view; c = c->snext);
        focus(c);
    }
    restack();
}

void
attach(Arg *arg) {
    Client *c;

    for(c = clients; c && c->view == view; c = c->next);
    if(!c)
        return;
    c->view = !c->view;
    pop(c);
    focus(c);
    arrange();
}

void
detach(Arg *arg) {
    if(!sel)
        return;
    sel->view = !sel->view;
    pop(sel);
    arrange();
}

void
focusnext(Arg *arg) {
    Client *c;
   
    if(!sel)
        return;
    if(!(c = getnext(sel->next)))
        c = getnext(clients);
    if(c) {
        focus(c);
        restack();
    }
}

void
focusprev(Arg *arg) {
    Client *c;

    if(!sel)
        return;
    if(!(c = getprev(sel->prev))) {
        for(c = clients; c && c->next; c = c->next);
        c = getprev(c);
    }
    if(c) {
        focus(c);
        restack();
    }
}

void
incnmaster(Arg *arg) {
    if((nmaster + arg->i < 1) || (sh / (nmaster + arg->i) <= 2 * BORDERPX))
        return;
    nmaster += arg->i;
    if(sel)
        arrange();
}

void
resizemaster(Arg *arg) {
    if(arg->i == 0)
        master = MASTER;
    else {
        if(sw * (master + arg->i) / 1000 >= sw - 2 * BORDERPX
            || sw * (master + arg->i) / 1000 <= 2 * BORDERPX)
            return;
        master += arg->i;
    }
    arrange();
}

void
restack(void) {
    Client *c;
    XEvent ev;

    if(!sel)
        return;
    else
        XLowerWindow(dpy, sel->win);
    for(c = getnext(clients); c; c = getnext(c->next)) {
        if(c == sel)
            continue;
        XLowerWindow(dpy, c->win);
    }
    XSync(dpy, False);
    while(XCheckMaskEvent(dpy, EnterWindowMask, &ev));
}

void
toggleview(Arg *arg) {
    view = !view;
    arrange();
}

void
zoom(Arg *arg) {
    unsigned int n;
    Client *c;

    if(!sel)
        return;

    for(n = 0, c = getnext(clients); c; c = getnext(c->next))
        n++;

    if((c = sel) == getnext(clients))
        if(!(c = getnext(c->next)))
            return;
    pop(c);
    focus(c);
    arrange();
}
