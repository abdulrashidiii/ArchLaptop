/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const char *fonts[]          = { "ubuntumono:size=10" };
static const char dmenufont[]       = "ubuntumono:size=13";
// background color
static const char col_gray1[]       = "#111111";
// inactive window border color
static const char col_gray2[]       = "#acacac";
// font color
static const char col_gray3[]       = "#bbbbbb";
// current tag and current window font color
static const char col_gray4[]       = "#eeeeee";
//  top bar second color (blue) and active window border color
static const char col_cyan[]        = "#152c56";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
//static const char *tags[] = { "", "", "", "", "", "6", "7", "8", "9" };
static const char *tags[] = {"", "", "", "", ""};
//static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagsalt[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
  /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
  { "st",           NULL,     NULL,            0,         0,          1,           0,        -1 },
  { "Gimp",         NULL,     NULL,            0,         1,          0,           1,        -1 },
	{ "Telegram",     NULL,     NULL,       1 << 3,         1,          0,           1,        -1 },
	{ "Spotify",      NULL,     NULL,       1 << 4,         1,          0,           1,        -1 },
  { "Slack",        NULL,     NULL,            0,         1,          0,           1,        -1 },
  { "Pavucontrol",  NULL,     NULL,            0,         1,          0,           1,        -1 },
  { "Steam",        NULL,     NULL,            0,         1,          0,           1,        -1 },
  { "zoom",         NULL,     NULL,            0,         1,          0,           1,        -1 },
  { "Soffice",      NULL,     NULL,            0,         1,          0,           1,        -1 },
  { "firefox", "Browser",     "About Mozilla Firefox",  
                                               0,         1,          0,           1,        -1 },
  { "dota2",     "dota2",     "Dota 2",        0,         1,          0,           1,        -1 },
  // VMD Windows
	{ NULL,           NULL, "VMD Main",          0,         1,          0,           1,        -1 },
	{ NULL,           NULL, "VMD 1.9.4a43 OpenGL Display", \
                                               0,         1,          0,           1,        -1 },
	{ NULL,           NULL, "Graphical Representations", \
                                               0,         1,          0,           1,        -1 },
	{ NULL,           NULL, "VMD ViewMaster", \
                                               0,         1,          0,           1,        -1 },
	{ NULL,           NULL, "Color Controls", \
                                               0,         1,          0,           1,        -1 },
	{ NULL,           NULL, "File Render Controls", \
                                               0,         1,          0,           1,        -1 },
	{ "Toplevel", "qmtool", "QMtool", \
                                               0,         1,          0,           1,        -1 },
	{ "TkFDialog", "__tk_filedialog", "Choose file name", \
                                               0,         1,          0,           1,        -1 },
	{ NULL,           NULL, "Save Trajectory", \
                                               0,         1,          0,           1,        -1 },
  // PyMOL Windows
	{ "PyMOL",        NULL,     NULL,            0,         1,          0,           1,        -1 },
  // AutoDock Tools
	{ "Tk",           "tk",     "AutoDockTools", 0,         1,          0,           1,        -1 },

  // matplotlib windows
	{ "matplotlib",   NULL,     NULL,            0,         1,          0,           1,        -1 },
  // LigPlus
	{ "ligplus-LigPlusFrame", \
                    NULL,     NULL,            0,         1,          0,           1,        -1 },
  { NULL,           NULL,     "Event Tester",  0,         0,          0,           1,        -1 }, /* xev */
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
#define MODKEY2 Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-c", "-l", "20", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dbrowsecmd[]  = { "/data/bin/dbrowse_run", NULL };
static const char *dcalccmd[]  = { "/data/bin/dcalc", NULL };
static const char *bravecmd[]  = { "brave", NULL };
static const char *dbrowsepathcmd[]  = { "/data/bin/dbrowse_path", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *audioplaycmd[] = { "dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.PlayPause", NULL };
static const char *audioprevcmd[] = { "dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.Previous", NULL };
static const char *audionextcmd[] = { "dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.Next", NULL };
static const char *mutecmd[] = { "/data/bin/changeVolume", "toggle", NULL };
static const char *volupcmd[] = { "/data/bin/changeVolume", "+2%", NULL };
static const char *voldowncmd[] = { "/data/bin/changeVolume", "-2%", NULL };
static const char *brupcmd[] = { "/data/bin/changeBrightness", "+10", NULL };
static const char *brdowncmd[] = { "/data/bin/changeBrightness", "10-", NULL };
static const char *showmostcmd[] = { "/data/bin/showmost", NULL };
static const char *mountdrivecmd[] = { "/data/bin/mount_drive", NULL };
static const char *unmountdrivecmd[] = { "/data/bin/unmount_drive", NULL };
static const char *slockcmd[] = { "slock", NULL };
static const char *passmenucmd[] = { "passmenu", NULL };
static const char *togglenotifcmd[] = { "/data/bin/toggle_mute_notif", NULL };
static const char *flameshotcmd[] = { "flameshot-gui", NULL };
static const char *rangercmd[] = { "st", "-e", "ranger", NULL };
static const char *clipmenucmd[] = { "clipmenu", NULL };
static const char *clipdelcmd[] = { "clipdel", "-d", ".*", NULL };

#include "shiftview.c"
#include <X11/XF86keysym.h>
#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = dbrowsecmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_p,      spawn,          {.v = dbrowsepathcmd } },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = dcalccmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = clipmenucmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = clipdelcmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = bravecmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = showmostcmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = passmenucmd } },
	{ MODKEY2|ControlMask,          XK_l,      spawn,          {.v = slockcmd } },
	{ MODKEY2,                      XK_n,      spawn,          {.v = togglenotifcmd } },
	{ MODKEY2,                      XK_m,      spawn,          {.v = mountdrivecmd } },
	{ MODKEY2|ShiftMask,            XK_m,      spawn,          {.v = unmountdrivecmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = flameshotcmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = rangercmd } },
	{ 0,                 XF86XK_PowerOff,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { MODKEY,                       XK_n,      shiftview,      {.i = +1 } },
  { MODKEY,                       XK_v,      shiftview,      {.i = -1 } },
  { MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
  { MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
  { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
  { MODKEY|ShiftMask,             XK_n,      togglealttag,   {0} },
  { 0,                     XF86XK_AudioPlay, spawn,      {.v = audioplaycmd } },
  { 0,                     XF86XK_AudioPrev, spawn,      {.v = audioprevcmd } },
  { 0,                     XF86XK_AudioNext, spawn,      {.v = audionextcmd } },
  { 0,                     XF86XK_AudioMute, spawn,      {.v = mutecmd } },
  { 0,              XF86XK_AudioLowerVolume, spawn,      {.v = voldowncmd } },
  { 0,              XF86XK_AudioRaiseVolume, spawn,      {.v = volupcmd } },
  { 0,               XF86XK_MonBrightnessUp, spawn,      {.v = brupcmd} },
  { 0,             XF86XK_MonBrightnessDown, spawn,      {.v = brdowncmd} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_Escape,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
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

