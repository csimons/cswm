/* (C)opyright MMVI-MMVII Anselm R. Garbe <garbeam at gmail dot com>
 * See LICENSE file for license details.
 */

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
    { MODKEY|ShiftMask, XK_t,       spawn,      { .cmd = "exec st" } }, \
    { MODKEY|ShiftMask, XK_w,       spawn,      { .cmd = "exec firefox" } }, \
    { MODKEY,           XK_j,       focusnext,    { 0 } }, \
    { MODKEY,           XK_k,       focusprev,    { 0 } }, \
    { MODKEY|ShiftMask, XK_q,       quit,        { 0 } }, \
};
    /*
    { MODKEY,           XK_a,       attach,        { 0 } }, \
    { MODKEY,           XK_d,       detach,        { 0 } }, \
    { MODKEY,           XK_Return,  zoom,        { 0 } }, \
    { MODKEY,           XK_g,       resizemaster,    { .i = 15 } }, \
    { MODKEY,           XK_s,       resizemaster,    { .i = -15 } }, \
    { MODKEY,           XK_i,       incnmaster,    { .i = 1 } }, \
    { MODKEY,           XK_r,       incnmaster,    { .i = -1 } }, \
    { MODKEY|ShiftMask, XK_c,       killclient,    { 0 } }, \
    { MODKEY,           XK_space,   toggleview,    { 0 } }, \
    { MODKEY|ShiftMask, XK_space,   togglefloat,    { 0 } }, \
    */

#define FLOATS \
static char *floats[] = { "Gimp.*", "MPlayer.*", "Acroread.*", NULL };
