/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const double defaultopacity  = 0.8;
#define ICONSIZE 16   /* icon size */
#define ICONSPACING 5 /* space between icon and title */
static const int user_bh            = 0;        /* 2 is the default spacing around the bar's font */
static const int vertpad            = 4;       /* vertical padding of bar */
static const int sidepad            = 14;       /* horizontal padding of bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static char font[]            = "GoMono Nerd Font:size=10";
static char dmenufont[]       = "GoMono Nerd Font:size=10";
static const char *fonts[]          = { font };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  opacity  monitor  float x,y,w,h         floatborderpx*/
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        1.0, 		  -1,	   50,50,500,500,        5 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        defaultopacity, -1,	   50,50,500,500,        5 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        defaultopacity, -1,	   50,50,500,500,        5 },
	{ "Zoom",    NULL,     NULL,           0,         1,          0,	     -1,       1.0, 		   -1,				      },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        defaultopacity, -1,	   50,50,500,500,        5 }, /* xev */
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *roficmd[] = { "rofi -show run", NULL};
static const char *clipcmd[] = { "clipmenu", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *browserd[]  = { "qutebrowser", NULL };
static const char *browserdd[]  = { "firefox-esr", "--new-tab", NULL };
static const char *coded[]  = { "zeditor", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *filed_cmd[]  = { "wezterm", "start", "yazi" , NULL };
// static const char *tfiled[]  = { "sakura -e  ranger", NULL };
// static const char *kbd_cmd  = "switch_layout";
static const char *downbri[]  = { "/home/DrRoot/.local/bin/backlight", " --dec", NULL };
static const char *upbri[]  = { "/home/DrRoot/.local/bin/backlight", " --inc", NULL };

//static const char *micmute[]  = {"pactl set-source-mute @DEFAULT_SOURCE@ toggle", NULL};
static const char *micmute[]  = { "/home/DrRoot/.local/bin/volume", "--toggle-mic", NULL };
static const char *downvol[]  = { "/home/DrRoot/.local/bin/volume", "--dec", NULL };
static const char *upvol[]  = { "/home/DrRoot/.local/bin/volume", "--inc", NULL };
static const char *mute[]  = { "/home/DrRoot/.local/bin/volume", "--toggle", NULL };

static const char *layoutmenu_cmd = "/home/DrRoot/.local/bin/layoutmenu.sh";
static const char *setabg[]  = { "/home/DrRoot/.local/bin/setbg", NULL };
static const char *autowall[]  = { "/home/DrRoot/.local/bin/autowall", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color0",		STRING,	&normbordercolor },
		{ "color8",		STRING,	&selbordercolor },
		{ "color0",		STRING,	&normbgcolor },
		{ "color4",		STRING,	&normfgcolor },
		{ "color0",		STRING,	&selfgcolor },
		{ "color4",		STRING,	&selbgcolor },
		{ "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "selfrestart.c"
#include "nextprevtag.c"
#include "shiftview.c"
#include "exitdwm.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	// { MODKEY|ShiftMask,             XK_p,      spawn,         SHCMD("rofi -show drun") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{MODKEY, 	                  XK_c,	 spawn, 	   {.v = clipcmd} },
	{MODKEY|ShiftMask,              XK_b,	 spawn, 	   {.v = browserd} },
	{MODKEY|ControlMask,            XK_b,	 spawn, 	   {.v = browserdd} },
	{MODKEY|ShiftMask,              XK_c,	 spawn, 	   {.v = coded} },
	{MODKEY|ShiftMask,              XK_t,	 spawn, 	   {.v = filed_cmd} },
	{MODKEY,		           XK_e,	 spawn, 	   SHCMD("kitty --detach  yazi") },
	/*brightness control keys */
 	// { 0, XF86XK_MonBrightnessDown, spawn, {.v = downbri}},
 	// { 0, XF86XK_MonBrightnessUp,   spawn, {.v = upbri}},
 	{ 0, XF86XK_AudioMicMute,	   spawn, {.v = micmute}},
 	{ 0, XF86XK_Tools,             spawn, {.v = autowall}},
 	{ 0, XF86XK_AudioLowerVolume, spawn, {.v = downvol}},
 	{ 0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol}},
 	{ 0, XF86XK_AudioMute, spawn, {.v = mute}},
  	// { 0, XF86XK_Explorer,          spawn, {.v = }},
	// { 0, XF86XK_LaunchA,           spawn, {.v = }},
  	{ 0, XF86XK_Search,            spawn, {.v = setabg}},
  	// { 0, XF86XK_Display,           spawn, {.v = }},
	// {Mod1Mask,              	ShiftMask,	 spawn, 	   {.v = kbd_cmd} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,		           XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_a,      toggletopbar,   {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,	    XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,		    XK_KP_Add, changeopacity,	{.f = +0.1}},
	{ MODKEY|ShiftMask,		    XK_KP_Subtract, changeopacity,  {.f = -0.1}},
	{ MODKEY,                       XK_n,      focussame,      {.i = +1 } },
   	{ MODKEY|ShiftMask,             XK_n,      focussame,      {.i = -1 } },
	{ MODKEY|ControlMask,     	    XK_i,           view_adjacent,  { .i = +1 } },
	{ MODKEY|ControlMask,      	    XK_u,           view_adjacent,  { .i = -1 } },
	// { MODKEY,			    XK_g,          shiftview,              { .i = -1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    	{ MODKEY|ShiftMask,             XK_r,      self_restart,   {0} },
	// { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      exitdwm,       {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            0,              Button4,        view_adjacent,     { .i = -1 } },
	{ ClkTagBar,            0,              Button5,        view_adjacent,     { .i = +1 } },
};