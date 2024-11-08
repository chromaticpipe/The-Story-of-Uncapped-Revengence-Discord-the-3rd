// SONIC ROBO BLAST 2; TSOURDT3RD
//-----------------------------------------------------------------------------
// Copyright (C) 2023-2024 by Star "Guy Who Names Scripts After Him" ManiaKG.
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  star_vars.h
/// \brief star variables, typically used when allowing lua support or just for making and doing dumb stuff

/// \todo remove this entire file eventually, spread everything out :)

#ifndef __STAR_VARS__
#define __STAR_VARS__

#include "ss_main.h" // main star varaibles
#include "star_webinfo.h" // star variables
#include "smkg-jukebox.h" // tsourdt3rd_global_jukebox //

#include "../command.h" // command variables
#include "../g_input.h" // input variables
#include "../s_sound.h" // sound variables

// ============================================================================	//																//
//   Just so you know, some of this stuff is also handled in tsourdt3rd.pk3.	//
//      If you want to look at some other code, check that PK3 out.             //
// ============================================================================ //

//// DEFINITIONS ////
#ifdef DEVELOP
#define TSOURDT3RDBYSTARMANIAKGSTRING "(By StarManiaKG); Dev Mode Edition"
#else
#define TSOURDT3RDBYSTARMANIAKGSTRING "(By StarManiaKG)"
#endif
#define TSOURDT3RDVERSIONSTRING "TSoURDt3rd v"TSOURDT3RDVERSION

//// STRUCTS ////
// Audio //
typedef struct TSoURDt3rdBossMusic_s {
	const char *bossMusic;
	const char *bossPinchMusic;

	UINT32 pinchMusicPos;
} TSoURDt3rdBossMusic_t;

typedef struct TSoURDt3rdFinalBossMusic_s {
	const char *finalBossMusic, *finalBossPinchMusic;
	const char *trueFinalBossMusic, *trueFinalBossPinchMusic;
} TSoURDt3rdFinalBossMusic_t;

typedef struct TSoURDt3rdActClearMusic_s {
	const char *actClear;
	const char *bossClear, *finalBossClear, *trueFinalBossClear;
} TSoURDt3rdActClearMusic_t;

typedef struct TSoURDt3rdDefaultMusicTracks_s {
	const char *track;
} TSoURDt3rdDefaultMusicTracks_t;

// Main //
typedef struct TSoURDt3rd_s {
	UINT8                     public_key[32]; // User authentication
	UINT8                     secret_key[64];
	char                      user_hash [18];

	boolean usingTSoURDt3rd;
	boolean checkedVersion;
	boolean masterServerAddressChanged;

	boolean timeOver;

	union
	{
		size_t loadCount;
		UINT8 loadPercentage;
		INT32 bspCount;
		INT32 screenToUse;
		boolean loadComplete;
	} loadingScreens;

	union
	{
		boolean serverUsesTSoURDt3rd;
		UINT8 majorVersion, minorVersion, subVersion;
		UINT32 serverTSoURDt3rdVersion;
	} serverPlayers;
} TSoURDt3rd_t;

extern TSoURDt3rd_t TSoURDt3rdPlayers[MAXPLAYERS];

extern TSoURDt3rdBossMusic_t bossMusic[];
extern TSoURDt3rdFinalBossMusic_t finalBossMusic[];
//extern TSoURDt3rdActClearMusic_t actClearMusic[];
extern TSoURDt3rdDefaultMusicTracks_t defaultMusicTracks[];

//// VARIABLES ////
// TSoURDt3rd Stuff //
extern boolean TSoURDt3rd_LoadExtras;
extern boolean TSoURDt3rd_LoadedExtras;
extern boolean TSoURDt3rd_NoMoreExtras;

// Events //
// Easter
extern INT32 TOTALEGGS;

extern INT32 foundeggs;
extern INT32 collectedmapeggs;
extern INT32 currenteggs;
extern INT32 numMapEggs;

// Game //
// Audio //
// Game Over Music
extern const char gameoverMusic[9][7];
extern const INT32 gameoverMusicTics[9];

// Star SFX
extern INT32 STAR_JoinSFX;
extern INT32 STAR_LeaveSFX;
extern INT32 STAR_SynchFailureSFX;

// Discord SFX
extern INT32 DISCORD_RequestSFX;

// Extras //
// TF2
extern boolean SpawnTheDispenser;

//// COMMANDS ////
// Game //
extern consvar_t cv_loadingscreen, cv_loadingscreenimage;

// Audio //
extern consvar_t cv_vapemode;

//// FUNCTIONS ////
// Events //
void TSoURDt3rd_CheckTime(void);

// Game //
void TSoURDt3rd_InitializePlayer(INT32 playernum);

void TSoURDt3rd_ClearPlayer(INT32 playernum);

void STAR_LoadingScreen(void);

#ifdef HAVE_SDL
void STAR_RenameWindow(const char *title);
const char *STAR_SetWindowTitle(void);
#endif

void TSoURDt3rd_BuildTicCMD(UINT8 player);

// Audio //
void TSoURDt3rd_ControlMusicEffects(void);
const char *TSoURDt3rd_DetermineLevelMusic(void);

UINT32 TSoURDt3rd_PinchMusicPosition(void);
boolean TSoURDt3rd_SetPinchMusicSpeed(void);

void STAR_SetSavefileProperties(void);

// Files //
void TSoURDt3rd_TryToLoadTheExtras(void);

INT32 STAR_DetectFileType(const char* filename);
boolean STAR_DoesStringMatchHarcodedFileName(const char *string);

// Servers //
// Nobody came.

// Miscellanious //
UINT32 TSoURDt3rd_CurrentVersion(void);

UINT8 TSoURDt3rd_CurrentMajorVersion(void);
UINT8 TSoURDt3rd_CurrentMinorVersion(void);
UINT8 TSoURDt3rd_CurrentSubversion(void);

INT32 STAR_ConvertStringToCompressedNumber(char *STRING, INT32 startIFrom, INT32 startJFrom, boolean turnIntoVersionNumber);
char *STAR_ConvertNumberToString(INT32 NUMBER, INT32 startIFrom, INT32 startJFrom, boolean turnIntoVersionString);
INT32 STAR_ConvertNumberToStringAndBack(INT32 NUMBER, INT32 startI1From, INT32 startJ1From, INT32 startI2From, INT32 startJ2From, boolean turnIntoVersionString, boolean turnIntoVersionNumber);

INT32 STAR_CombineNumbers(INT32 ARGS, INT32 FIRSTNUM, ...);

#endif // __STAR_VARS__
