/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
#define ICONSIZE 16   /* icon size */
#define ICONSPACING 5 /* space between icon and title */
static const int vertpad            = 9;       /* vertical padding of bar */
static const int sidepad            = 9;       /* horizontal padding of bar */
static const int user_bh            = 2;        /* 2 is the default spacing around the bar's font */
static char font[]            = "GoMono Nerd Font:size=10";
static char dmenufont[]       = "GoMono Nerd Font:size=10";
static const char *fonts[]          = { font };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char termcol0[] = "#000000"; /* black   */
static char termcol1[] = "#ff0000"; /* red     */
static char termcol2[] = "#33ff00"; /* green   */
static char termcol3[] = "#ff0099"; /* yellow  */
static char termcol4[] = "#0066ff"; /* blue    */
static char termcol5[] = "#cc00ff"; /* magenta */
static char termcol6[] = "#00ffff"; /* cyan    */
static char termcol7[] = "#d0d0d0"; /* white   */
static char termcol8[]  = "#808080"; /* black   */
static char termcol9[]  = "#ff0000"; /* red     */
static char termcol10[] = "#33ff00"; /* green   */
static char termcol11[] = "#ff0099"; /* yellow  */
static char termcol12[] = "#0066ff"; /* blue    */
static char termcol13[] = "#cc00ff"; /* magenta */
static char termcol14[] = "#00ffff"; /* cyan    */
static char termcol15[] = "#ffffff"; /* white   */
static char *termcolor[] = {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
};
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */
 
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"keepassxc",   spcmd3},
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* launcher commands (They must be NULL terminated) */
static const char* surf[]      = { "surf", "duckduckgo.com", NULL };
static const char* komikku[]      = { "komikku",  NULL };
static const char* brave[]      = { "brave", "duckduckgo.com", NULL };
static const char* telegram[]      = { "telegram-desktop",  NULL };
static const char* qutebrowser[]      = { "qutebrowser", "duckduckgo.com", NULL };
static const char* pavucontrol[]      = { "pavucontrol", NULL };
static const char* zoomet[]      = { "zoom", NULL };
static const char* ai[]      = { "/home/DrRoot/.local/bin/ai", NULL };

/* Helper macros for spawning commands */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define CMD(...)   { .v = (const char*[]){ __VA_ARGS__, NULL } }

static const Launcher launchers[] = {
       /* command       name to display */
	// { surf,         "surf" },
	{ komikku,         	"" },
	{ brave,         	"" },
	{ telegram, 		""},
	{ qutebrowser, 	"" },
	{ pavucontrol, 	"" },
	{ zoomet,	 	"" },
	{ ai,	 		"" },
	
	
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,      "spterm", NULL,	    SPTAG(0),	 1,	      -1,	     0,	 -1 },
	{ NULL,      "spfm",	  NULL,	    SPTAG(1),	 1,	      -1,	     0,	 -1 },
	{ NULL,      "keepassxc",	NULL,	    SPTAG(2),	 0,	      -1,	     0,	 -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
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
static const char *dmenucmd[] = { "dmenu_run", NULL }; //"-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *roficmd[] = { "rofi -show run", NULL};
static const char *netdcmd[] = { "networkmanager_dmenu", NULL}; 
static const char *clipcmd[] = { "clipmenu", NULL }; // "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *browserd[]  = { "qutebrowser", NULL };
static const char *browserdd[]  = { "firefox", "--new-tab", NULL };
static const char *coded[]  = { "zeditor", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *filed_cmd[]  = { "kitty", "start", "yazi" , NULL };
// static const char *tfiled[]  = { "sakura -e  ranger", NULL };
// static const char *kbd_cmd  = "/home/DrRoot/.local/bin/lang";
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
		{ "color6",		STRING,	&selbordercolor },
		{ "color1",		STRING,	&normbgcolor },
		{ "color0",		STRING,	&normfgcolor },
		{ "color14",		STRING,	&selfgcolor },
		{ "color0",		STRING,	&selbgcolor },
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

		{ "color0",  		STRING,	&termcol0 },
        	{ "color1",  		STRING,	&termcol1 },
        	{ "color2",  		STRING,	&termcol2 },
        	{ "color3",  		STRING,	&termcol3 },
        	{ "color4",  		STRING,	&termcol4 },
        	{ "color5",  		STRING,	&termcol5 },
        	{ "color6",  		STRING,	&termcol6 },
        	{ "color7",  		STRING,	&termcol7 },
        	{ "color8",  		STRING,	&termcol8 },
        	{ "color9",  		STRING,	&termcol9 },
        	{ "color10", 		STRING,	&termcol10 },
        	{ "color11", 		STRING,	&termcol11 },
        	{ "color12", 		STRING,	&termcol12 },
        	{ "color13", 		STRING,	&termcol13 },
        	{ "color14", 		STRING,	&termcol14 },
        	{ "color15", 		STRING,	&termcol15 },

		{ "termcol0",  	STRING,	&termcol0 },
        	{ "termcol1",  	STRING,	&termcol1 },
        	{ "termcol2",  	STRING,	&termcol2 },
        	{ "termcol3",  	STRING,	&termcol3 },
        	{ "termcol4",  	STRING,	&termcol4 },
        	{ "termcol5",  	STRING,	&termcol5 },
        	{ "termcol6",  	STRING,	&termcol6 },
        	{ "termcol7",  	STRING,	&termcol7 },
        	{ "termcol8",  	STRING,	&termcol8 },
        	{ "termcol9",  	STRING,	&termcol9 },
        	{ "termcol10", 	STRING,	&termcol10 },
        	{ "termcol11", 	STRING,	&termcol11 },
        	{ "termcol12", 	STRING,	&termcol12 },
        	{ "termcol13", 	STRING,	&termcol13 },
        	{ "termcol14", 	STRING,	&termcol14 },
        	{ "termcol15", 	STRING,	&termcol15 },

};


#include <X11/XF86keysym.h>
#include "selfrestart.c"
#include "exitdwm.c"
#include "nextprevtag.c"
#include "shiftview.c"
// #include "bulkill.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,      {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,      SHCMD("rofi -show drun") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,      {.v = termcmd } },
	{MODKEY, 	                  XK_v,	 spawn, 	   {.v = clipcmd} },
	{MODKEY, 	                  XK_n,	 spawn, 	   {.v = netdcmd} },
	{MODKEY|ShiftMask,              XK_b,	 spawn, 	   {.v = browserd} },
	{MODKEY|ControlMask,            XK_b,	 spawn, 	   {.v = browserdd} },
	{MODKEY,		           XK_c,	 spawn, 	   {.v = coded} },
	{MODKEY|ShiftMask,              XK_t,	 spawn, 	   {.v = filed_cmd} },
	{MODKEY,		           XK_e,	     spawn, 	   SHCMD("kitty --detach  yazi") },
	/*XF86 Keys control keys */
	/* Light */
 	/*{ 0, XF86XK_MonBrightnessDown, spawn, {.v = downbri}},*/
    /*{ 0, XF86XK_MonBrightnessUp,   spawn, {.v = upbri}},*/
 	/* Audio */
 	{ 0, XF86XK_AudioMicMute,	   spawn, {.v = micmute}},
 	{ 0, XF86XK_AudioLowerVolume, spawn, {.v = downvol}},
 	{ 0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol}},
 	{ 0, XF86XK_AudioMute, spawn, {.v = mute}},
 	/* Other */
  	// { 0, XF86XK_Explorer,          spawn, {.v = autowall}},
	// { 0, XF86XK_LaunchA,           spawn, {.v = }},
  	{ 0, XF86XK_Tools,             spawn, {.v = autowall}},
  	{ 0, XF86XK_Search,            spawn, {.v = setabg}},
  	// { 0, XF86XK_Display,           spawn, {.v = }},
  	/* Custom Key */
	// {Mod1Mask,              	ShiftMask,	 spawn, 	   {.v = kbd_cmd} },
	/* */
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
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,			    XK_q,      killclient,     {0} },
	{ MODKEY|ControlMask,           XK_c,      killclient,     {.ui = 1} },  // kill unselect
	{ MODKEY|ShiftMask|ControlMask,  XK_c,      killclient,     {.ui = 2} },  // killall
	{ MODKEY|ControlMask,     	    XK_i,           view_adjacent,  { .i = +1 } },
	{ MODKEY|ControlMask,      	    XK_u,           view_adjacent,  { .i = -1 } },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,       		    XK_y,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            	    XK_u,	   togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,             XK_x,	   togglescratch,  {.ui = 2 } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	{ MODKEY,			    XK_g,      shiftview,      { .i = -1 } },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
	{ MODKEY,			    XK_x,      exitdwm,	   {0} }, 
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
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            0,              Button4,        view_adjacent,     { .i = -1 } },
	{ ClkTagBar,            0,              Button5,        view_adjacent,     { .i = +1 } },
};
