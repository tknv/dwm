/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack:size=8.5:antialias=true:autohint=false" };
static const char dmenufont[]       = "Hack:size=8.5:antialias=true:autohint=false";
static const char col_gray1[]       = "#fdf6e3";
static const char col_gray2[]       = "#fdf6e3";
static const char col_gray3[]       = "#839496";
static const char col_gray4[]       = "#fdf6e3";
static const char col_purple[]        = "#586e75";
static const char col_yellow[]         = "#586e75";
static const char *colors[][4]      = {
	/*               fg         bg         border     float */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2, col_gray2 },
	[SchemeSel] =  { col_gray4, col_purple,  col_yellow,   col_yellow },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Google-chrome",  NULL,       NULL,       1 << 8,       0,           -1 },
/*	{ "TelegramDesktop",   NULL,       NULL,       0,            1,           -1 }, */
	{ "feh",      NULL,       NULL,       0,            1,           -1 },
	{ "Gajim",    NULL,       NULL,       0,            1,           -1 },
/*	{ "Slack",    NULL,       NULL,       0,            1,           -1 }, */
	{ "skypeforlinux", NULL,  NULL,       0,            1,           -1 },
	{ "Kio_uiserver", NULL,   NULL,       0,            1,           -1 },
	{ "Xchat",    NULL,       NULL,       1,            1,           -1 },
	{ "Hexchat",  NULL,       NULL,       1,            1,           -1 },
	{ "Jitsi",    NULL,       NULL,       0,            1,           -1 },
	{ "Rainlendar2", NULL,    NULL,       1,            1,           -1 },
	{ "Turpial",  NULL,       NULL,       1,            1,           -1 },
	{ "krunner",  NULL,       NULL,       0,            1,           -1 },
	{ "Scratchpad", NULL,     NULL,       1,            1,           -1 },
	{ "Psi-plus", NULL,       NULL,       0,            1,           -1 },
	{ "Riot",     NULL,       NULL,       1,            1,           -1 },
	{ "Rambox",   NULL,       NULL,       1,            1,           -1 },
	{ "Standard Notes", NULL, NULL,       1,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "+++",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "[ ]",      clear },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-i", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_purple, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "toggleview_focus.c"
#include "moveresize.c"
#include "tagall.c"
#include "maximize.c"
#include "zoomswap.c"
#include "centredmaster.c"
#include "push.c"
#include "focusmaster.c"
#include "shifttags.c"
#include "focusurgent.c"
#include "clear.c"
#include "keepfloatingposition.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {.f = 1} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {.f = 1} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ Mod1Mask,                     XK_Tab,    swapfocus,      {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_space,  toggleview_focus, {.ui = 1} },
	{ MODKEY|ControlMask,           XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_q,      quit,           {1} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask,           XK_l,      togglehorizontalmax, {0} },
	{ MODKEY|ControlMask,           XK_h,      togglehorizontalmax, {0} },
	{ MODKEY|ControlMask,           XK_j,      toggleverticalmax,   {0} },
	{ MODKEY|ControlMask,           XK_k,      toggleverticalmax,   {0} },
	{ MODKEY|ControlMask,           XK_m,      togglemaximize,      {0} },
	{ MODKEY|ShiftMask,             XK_F1,     tagall,         {.v = "F1" } },
	{ MODKEY|ShiftMask,             XK_F2,     tagall,         {.v = "F2" } },
	{ MODKEY|ShiftMask,             XK_F3,     tagall,         {.v = "F3" } },
	{ MODKEY|ShiftMask,             XK_F4,     tagall,         {.v = "F4" } },
	{ MODKEY|ShiftMask,             XK_F5,     tagall,         {.v = "F5" } },
	{ MODKEY|ShiftMask,             XK_F6,     tagall,         {.v = "F6" } },
	{ MODKEY|ShiftMask,             XK_F7,     tagall,         {.v = "F7" } },
	{ MODKEY|ShiftMask,             XK_F8,     tagall,         {.v = "F8" } },
	{ MODKEY|ShiftMask,             XK_F9,     tagall,         {.v = "F9" } },
	{ MODKEY,                       XK_a,      moveresize,     {.v = "-10x 0y 0w 0h" } },
	{ MODKEY,                       XK_d,      moveresize,     {.v = "10x 0y 0w 0h" } },
	{ MODKEY,                       XK_s,      moveresize,     {.v = "0x 10y 0w 0h" } },
	{ MODKEY,                       XK_w,      moveresize,     {.v = "0x -10y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_a,      moveresize,     {.v = "0X 0y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_d,      moveresize,     {.v = "9000X 0y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_s,      moveresize,     {.v = "0x 9000Y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_w,      moveresize,     {.v = "0x 16Y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_a,      moveresize,     {.v = "0x 0y -10w 0h" } },
	{ MODKEY|ShiftMask,             XK_d,      moveresize,     {.v = "0x 0y 10w 0h" } },
	{ MODKEY|ShiftMask,             XK_s,      moveresize,     {.v = "0x 0y 0w 10h" } },
	{ MODKEY|ShiftMask,             XK_w,      moveresize,     {.v = "0x 0y 0w -10h" } },
	{ MODKEY|ControlMask,           XK_Return, focusmaster,    {0} },
	{ MODKEY,                       XK_Left,   shifttags,      {.i = -1} },
	{ MODKEY,                       XK_Right,  shifttags,      {.i = +1} },
	{ MODKEY,                       XK_u,      focusurgent,     {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

