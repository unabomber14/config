/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=8" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char white[]        = "#FFFFFF";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { white, col_gray1,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,  NULL,       NULL,       NULL,       NULL,           NULL },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *webbrowser[]  = { "qutebrowser", NULL };
static const char *htop[]  = { "st", "-e", "htop", NULL };
static const char *filebrowser[]  = { "st", "-e", "lf", NULL };
static const char *mocp[]  = { "st", "-e", "mocp", "-T", "ex", NULL };
static const char *mocpdown[]  = {"mocp", "--exit", NULL };
static const char *mocptoggle[]  = {"mocp", "--toggle-pause", NULL };
//static const char *mocpvolup[]  = {"mocp", "--volume", "+5", NULL };
//static const char *mocpvoldown[]  = {"mocp", "--volume", "-5", NULL };
static const char *mocpvolup[]  = {"amixer", "set", "Master", "2dB+", NULL };
static const char *mocpvoldown[]  = {"amixer", "set", "Master", "2dB-", NULL };
//static const char *mocpseekup[]  = {"mocp", "--seek", "+5", NULL };
//static const char *mocpseekdown[]  = {"mocp", "--seek", "-5", NULL };
static const char *mocpnext[]  = {"mocp", "--next", NULL };
static const char *mocpprevious[]  = {"mocp", "--previous", NULL };
//static const char *sar[]  = {"groff", "-ms", "~/docs/sa.ms", ">", "~/docs/sa.ps", NULL };
static const char *zzz[]  = {"loginctl", "suspend", NULL };
static const char *dmenumount[]  = {"sudo", "dmenumount", NULL };
static const char *dmenuumount[]  = {"sudo", "dmenuumount", NULL };
static const char *neomutt[]  = {"st", "-e", "neomutt", NULL };
static const char *screenshot[]  = {"maim", "~/screens/$(date +%F_%R).png", NULL };
//static const char *telegram[]  = {"telegram-desktop", NULL };
static const char *bookbinder[]  = {"boo", NULL };
static const char *texcomp[]  = {"texcomp", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "60x34", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,             		XK_c,      spawn,          {.v = texcomp } },
	{ MODKEY,             		XK_S,      spawn,          {.v = bookbinder } },
//	{ MODKEY,             		XK_h,      spawn,          {.v = telegram } },
	//{ MODKEY,             		XK_c,      spawn,          {.v = neomutt } },
	{ MODKEY,          	     XK_F12,      spawn,          {.v = dmenuumount } },
	{ MODKEY,             XK_F11,      spawn,          {.v = dmenumount } },
	{ MODKEY,             XK_x,      spawn,          {.v = zzz } },
	//{ MODKEY,                       XK_y,  spawn,          {.v = sar } },
	{ MODKEY,                       XK_comma,  spawn,          {.v = mocpprevious } },
	{ MODKEY,                       XK_period,  spawn,          {.v = mocpnext } },
	{ MODKEY,                       XK_minus,  spawn,          {.v = mocpvoldown } },
	{ MODKEY,                       XK_equal,  spawn,          {.v = mocpvolup } },
	{ MODKEY,                       XK_p,      spawn,          {.v = mocptoggle } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = mocpdown } },
	{ MODKEY,                       XK_n,      spawn,          {.v = mocp } },
	{ MODKEY,                       XK_r,      spawn,          {.v = filebrowser } },
	{ MODKEY,                       XK_u,      spawn,          {.v = htop } },
	{ MODKEY,                       XK_w,      spawn,          {.v = webbrowser } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
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
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

