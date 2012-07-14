/* Copyright 2006-2007 Anselm R. Garbe <garbeam at gmail dot com> */

#define CMD_TERMINAL "st"
#define CMD_BROWSER  "firefox"
#define CMD_LOCK     "xlock"

#define BORDERPX    2
#define NORMCOLOR   "#666"
#define SELCOLOR    "#f00"

#define SY      0
#define SH      DisplayHeight(dpy, screen)

#define MASTER  600      /* per thousand */
#define MODKEY  Mod1Mask
#define NMASTER 1        /* clients in master area */
#define SNAP    40       /* pixel */

#define KEYS \
static Key key[] = { \
   /* modifier          key         function    argument */ \
    { MODKEY|ShiftMask, XK_t,       spawn,        { .cmd = CMD_TERMINAL } }, \
    { MODKEY|ShiftMask, XK_w,       spawn,        { .cmd = CMD_BROWSER  } }, \
    { MODKEY|ShiftMask, XK_l,       spawn,        { .cmd = CMD_LOCK } }, \
    { MODKEY,           XK_j,       focusnext,    { 0 } }, \
    { MODKEY,           XK_k,       focusprev,    { 0 } }, \
    { MODKEY,           XK_h,       resizemaster, { .i = -20 } }, \
    { MODKEY,           XK_l,       resizemaster, { .i = 20 } }, \
    { MODKEY,           XK_Tab,     focusnext,    { 0 } }, \
    { MODKEY,           XK_Return,  zoom,         { 0 } }, \
    { MODKEY|ShiftMask, XK_c,       killclient,   { 0 } }, \
    { MODKEY|ShiftMask, XK_q,       quit,         { 0 } }, \
};
    /*
    { MODKEY,           XK_a,       attach,       { 0 } }, \
    { MODKEY,           XK_d,       detach,       { 0 } }, \
    { MODKEY,           XK_i,       incnmaster,   { .i = 1 } }, \
    { MODKEY,           XK_r,       incnmaster,   { .i = -1 } }, \
    { MODKEY,           XK_space,   toggleview,   { 0 } }, \
    */
