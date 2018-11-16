// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Copyright (C) 1993-1996 by id Software, Inc.
// Copyright (C) 1998-2000 by DooM Legacy Team.
// Copyright (C) 2011-2016 by Matthew "Inuyasha" Walsh.
// Copyright (C) 1999-2016 by Sonic Team Junior.
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  m_menu.h
/// \brief Menu widget stuff, selection and such

#ifndef __X_MENU__
#define __X_MENU__

#include "d_event.h"
#include "command.h"
#include "r_things.h" // for SKINNAMESIZE

//
// MENUS
//

// Menu IDs sectioned by numeric places to signify hierarchy
typedef enum
{
	MM_MAIN = 1,

	// Single Player
	MM_SP_MAIN = 1<<1,

	MM_SP_LOAD = 1<<2,
	MM_SP_PLAYER = 1<<3,

	MM_SP_LEVELSELECT = 1<<4,
	MM_SP_LEVELSTATS = 1<<5,

	MM_SP_TIMEATTACK = 1<<6,
	MM_SP_TIMEATTACK_LEVELSELECT = 1<<7,
	MM_SP_GUESTREPLAY = 1<<8,
	MM_SP_REPLAY = 1<<9,
	MM_SP_GHOST = 1<<10,

	MM_SP_NIGHTSATTACK = 1<<11,
	MM_SP_NIGHTSATTACK_LEVELSELECT = 1<<12,
	MM_SP_NIGHTS_GUESTREPLAY = 1<<13,
	MM_SP_NIGHTS_REPLAY = 1<<14,
	MM_SP_NIGHTS_GHOST = 1<<15,

	// Multiplayer
	MM_MP_MAIN = 1<<16,
	MM_MP_SPLITSCREEN = 1<<17, // SplitServer
	MM_MP_SERVER = 1<<18,
	MM_MP_CONNECT = 1<<19,
	MM_MP_ROOM = 1<<20,
	MM_MP_PLAYERSETUP = 1<<21, // MP_PlayerSetupDef shared with SPLITSCREEN if #defined NONET

	// Secrets
	MM_SR_MAIN = 1<<22,
	MM_SR_PANDORA = 1<<23,
	MM_SR_LEVELSELECT = 1<<24,
	MM_SR_UNLOCKCHECKLIST = 1<<25,
	MM_SR_EMBLEMHINT = 1<<26,

	// Addons (Part of MISC, but let's make it our own)
	MM_AD_MAIN = 1<<27,

	MM_ALL = 1<<28,

	// MISC
	// MM_MESSAGE = 20000,
	// MM_SPAUSE = 30000,

	// MM_MPAUSE = 40000,
	// MM_SCRAMBLETEAM = 41000,
	// MM_CHANGETEAM = 42000,
	// MM_CHANGELEVEL = 43000,

	// MM_MAPAUSE = 50000,
	// MM_HELP = 60000
} menutype_t; // up to 1<<31

typedef enum
{
	// Options
	MM2_OP_MAIN = 1,

	MM2_OP_P1CONTROLS = 1<<1,
	MM2_OP_CHANGECONTROLS = 1<<2, // OP_ChangeControlsDef shared with P2
	MM2_OP_P1MOUSE = 1<<3,
	MM2_OP_P1JOYSTICK = 1<<4,
	MM2_OP_JOYSTICKSET = 1<<5, // OP_JoystickSetDef shared with P2

	MM2_OP_P2CONTROLS = 1<<6,
	MM2_OP_P2MOUSE = 1<<7,
	MM2_OP_P2JOYSTICK = 1<<8,

	MM2_OP_VIDEO = 1<<9,
	MM2_OP_VIDEOMODE = 1<<10,
	MM2_OP_COLOR = 1<<11,
	MM2_OP_OPENGL = 1<<12,
	MM2_OP_OPENGL_LIGHTING = 1<<13,
	MM2_OP_OPENGL_FOG = 1<<14,
	MM2_OP_OPENGL_COLOR = 1<<15,

	MM2_OP_SOUND = 1<<16,

	MM2_OP_SERVER = 1<<17,
	MM2_OP_MONITORTOGGLE = 1<<18,

	MM2_OP_DATA = 1<<19,
	MM2_OP_ADDONS = 1<<20,
	MM2_OP_SCREENSHOTS = 1<<21,
	MM2_OP_ERASEDATA = 1<<22,

	MM2_ALL = 1<<23
} menutype2_t; // up to 1<<31


// Called by main loop,
// saves config file and calls I_Quit when user exits.
// Even when the menu is not displayed,
// this can resize the view and change game parameters.
// Does all the real work of the menu interaction.
boolean M_Responder(event_t *ev);

// Called by main loop, only used for menu (skull cursor) animation.
void M_Ticker(void);

// Called by main loop, draws the menus directly into the screen buffer.
void M_Drawer(void);

// Called by D_SRB2Main, loads the config file.
void M_Init(void);

// Called by intro code to force menu up upon a keypress,
// does nothing if menu is already up.
void M_StartControlPanel(void);

// Called upon end of a mode attack run
void M_EndModeAttackRun(void);

// Called on new server add, or other reasons
void M_SortServerList(void);

// Draws a box with a texture inside as background for messages
void M_DrawTextBox(INT32 x, INT32 y, INT32 width, INT32 boxlines);

// the function to show a message box typing with the string inside
// string must be static (not in the stack)
// routine is a function taking a INT32 in parameter
typedef enum
{
	MM_NOTHING = 0, // is just displayed until the user do someting
	MM_YESNO,       // routine is called with only 'y' or 'n' in param
	MM_EVENTHANDLER // the same of above but without 'y' or 'n' restriction
	                // and routine is void routine(event_t *) (ex: set control)
} menumessagetype_t;
void M_StartMessage(const char *string, void *routine, menumessagetype_t itemtype);

// Called by linux_x/i_video_xshm.c
void M_QuitResponse(INT32 ch);

// Determines whether to show a level in the list (platter version does not need to be exposed)
boolean M_CanShowLevelInList(INT32 mapnum, INT32 gt);


// flags for items in the menu
// menu handle (what we do when key is pressed
#define IT_TYPE             14     // (2+4+8)
#define IT_CALL              0     // call the function
#define IT_ARROWS            2     // call function with 0 for left arrow and 1 for right arrow in param
#define IT_KEYHANDLER        4     // call with the key in param
#define IT_SUBMENU           6     // go to sub menu
#define IT_CVAR              8     // handle as a cvar
#define IT_SPACE            10     // no handling
#define IT_MSGHANDLER       12     // same as key but with event and sometime can handle y/n key (special for message)

#define IT_DISPLAY   (48+64+128)    // 16+32+64+128
#define IT_NOTHING            0     // space
#define IT_PATCH             16     // a patch or a string with big font
#define IT_STRING            32     // little string (spaced with 10)
#define IT_WHITESTRING       48     // little string in white
#define IT_DYBIGSPACE        64     // same as noting
#define IT_DYLITLSPACE   (16+64)    // little space
#define IT_STRING2       (32+64)    // a simple string
#define IT_GRAYPATCH     (16+32+64) // grayed patch or big font string
#define IT_BIGSLIDER        128     // volume sound use this
#define IT_TRANSTEXT     (16+128)   // Transparent text
#define IT_TRANSTEXT2    (32+128)   // used for control names
#define IT_HEADERTEXT    (48+128)   // Non-selectable header option, displays in yellow offset to the left a little
#define IT_QUESTIONMARKS (64+128)   // Displays as question marks, used for secrets
#define IT_CENTER           256     // if IT_PATCH, center it on screen

//consvar specific
#define IT_CVARTYPE   (512+1024+2048)
#define IT_CV_NORMAL         0
#define IT_CV_SLIDER       512
#define IT_CV_STRING      1024
#define IT_CV_NOPRINT     1536
#define IT_CV_NOMOD       2048
#define IT_CV_INVISSLIDER 2560

//call/submenu specific
// There used to be a lot more here but ...
// A lot of them became redundant with the advent of the Pause menu, so they were removed
#define IT_CALLTYPE   (512+1024)
#define IT_CALL_NORMAL          0
#define IT_CALL_NOTMODIFIED   512

// in INT16 for some common use
#define IT_BIGSPACE    (IT_SPACE  +IT_DYBIGSPACE)
#define IT_LITLSPACE   (IT_SPACE  +IT_DYLITLSPACE)
#define IT_CONTROL     (IT_STRING2+IT_CALL)
#define IT_CVARMAX     (IT_CVAR   +IT_CV_NOMOD)
#define IT_DISABLED    (IT_SPACE  +IT_GRAYPATCH)
#define IT_GRAYEDOUT   (IT_SPACE  +IT_TRANSTEXT)
#define IT_GRAYEDOUT2  (IT_SPACE  +IT_TRANSTEXT2)
#define IT_HEADER      (IT_SPACE  +IT_HEADERTEXT)
#define IT_SECRET      (IT_SPACE  +IT_QUESTIONMARKS)

#define MAXSTRINGLENGTH 32

typedef union
{
	struct menu_s *submenu;      // IT_SUBMENU
	consvar_t *cvar;             // IT_CVAR
	void (*routine)(INT32 choice); // IT_CALL, IT_KEYHANDLER, IT_ARROWS
} itemaction_t;

//
// MENU TYPEDEFS
//
typedef struct menuitem_s
{
	// show IT_xxx
	UINT16 status;

	const char *patch;
	const char *text; // used when FONTBxx lump is found

// FIXME: should be itemaction_t
	void *itemaction;

	// hotkey in menu or y of the item
	UINT8 alphaKey;
} menuitem_t;

typedef struct menu_s
{
	UINT32         menutype;           // Flags to encode ID and hierarchy
	UINT32         menutype2;          // More flags to encode ID and hierarchy
	const char    *menutitlepic;
	INT16          numitems;           // # of menu items
	struct menu_s *prevMenu;           // previous menu
	menuitem_t    *menuitems;          // menu items
	void         (*drawroutine)(void); // draw routine
	INT16          x, y;               // x, y of menu
	INT16          lastOn;             // last item user was on in menu
	boolean      (*quitroutine)(void); // called before quit a menu return true if we can
} menu_t;

void M_SetupNextMenu(menu_t *menudef);
void M_ClearMenus(boolean callexitmenufunc);

extern menu_t *currentMenu;

extern menu_t MainDef;
extern menu_t SP_LoadDef;

// Stuff for customizing the player select screen
typedef struct
{
	boolean used;
	char notes[441];
	char picname[8];
	char skinname[SKINNAMESIZE*2+2]; // skin&skin\0
	UINT8 prev;
	UINT8 next;
} description_t;

// level select platter
typedef struct
{
	char header[22+5]; // mapheader_t lvltttl max length + " ZONE"
	INT32 maplist[3];
	char mapnames[3][17+1];
	boolean mapavailable[4]; // mapavailable[3] == wide or not
} levelselectrow_t;

typedef struct
{
	UINT8 numrows;
	levelselectrow_t *rows;
} levelselect_t;
// experimental level select end

// descriptions for gametype select screen
typedef struct
{
	UINT8 col[2];
	char notes[441];
} gtdesc_t;

// mode descriptions for video mode menu
typedef struct
{
	INT32 modenum; // video mode number in the vidmodes list
	const char *desc;  // XXXxYYY
	UINT8 goodratio; // aspect correct if 1
} modedesc_t;

// savegame struct for save game menu
typedef struct
{
	char levelname[32];
	UINT8 skinnum;
	UINT8 botskin;
	UINT8 numemeralds;
	UINT8 numgameovers;
	INT32 lives;
	INT32 continues;
	INT32 gamemap;
} saveinfo_t;

extern description_t description[32];

extern consvar_t cv_newgametype, cv_nextmap, cv_chooseskin, cv_serversort;
extern CV_PossibleValue_t gametype_cons_t[];

extern INT16 startmap;
extern INT32 ultimate_selectable;
extern INT16 char_on, startchar;

#define MAXSAVEGAMES 31 //note: last save game is "no save"
#define NOSAVESLOT 0 //slot where Play Without Saving appears

#define BwehHehHe() S_StartSound(NULL, sfx_bewar1+M_RandomKey(4)) // Bweh heh he

void M_TutorialSaveControlResponse(INT32 ch);

void M_ForceSaveSlotSelected(INT32 sslot);

void M_CheatActivationResponder(INT32 ch);

// Level select updating
void Nextmap_OnChange(void);

// Screenshot menu updating
void Moviemode_mode_Onchange(void);
void Screenshot_option_Onchange(void);

// Addons menu updating
void Addons_option_Onchange(void);

// These defines make it a little easier to make menus
#define DEFAULTMENUSTYLE(flags, flags2, header, source, prev, x, y)\
{\
	flags,\
	flags2,\
	header,\
	sizeof(source)/sizeof(menuitem_t),\
	prev,\
	source,\
	M_DrawGenericMenu,\
	x, y,\
	0,\
	NULL\
}

#define DEFAULTSCROLLMENUSTYLE(flags, flags2, header, source, prev, x, y)\
{\
	flags,\
	flags2,\
	header,\
	sizeof(source)/sizeof(menuitem_t),\
	prev,\
	source,\
	M_DrawGenericScrollMenu,\
	x, y,\
	0,\
	NULL\
}

#define PAUSEMENUSTYLE(source, x, y)\
{\
	0,\
	0,\
	NULL,\
	sizeof(source)/sizeof(menuitem_t),\
	NULL,\
	source,\
	M_DrawPauseMenu,\
	x, y,\
	0,\
	NULL\
}

#define CENTERMENUSTYLE(flags, flags2, header, source, prev, y)\
{\
	flags,\
	flags2,\
	header,\
	sizeof(source)/sizeof(menuitem_t),\
	prev,\
	source,\
	M_DrawCenteredMenu,\
	BASEVIDWIDTH/2, y,\
	0,\
	NULL\
}

#define MAPPLATTERMENUSTYLE(flags, flags2, header, source)\
{\
	flags,\
	flags2,\
	header,\
	sizeof (source)/sizeof (menuitem_t),\
	&MainDef,\
	source,\
	M_DrawLevelPlatterMenu,\
	0,0,\
	0,\
	NULL\
}

#define CONTROLMENUSTYLE(flags, flags2, source, prev)\
{\
	flags,\
	flags2,\
	"M_CONTRO",\
	sizeof (source)/sizeof (menuitem_t),\
	prev,\
	source,\
	M_DrawControl,\
	24, 40,\
	0,\
	NULL\
}

#define IMAGEDEF(source)\
{\
	0,\
	0,\
	NULL,\
	sizeof (source)/sizeof (menuitem_t),\
	NULL,\
	source,\
	M_DrawImageDef,\
	0, 0,\
	0,\
	NULL\
}

#endif //__X_MENU__
