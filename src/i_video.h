// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Copyright (C) 1993-1996 by id Software, Inc.
// Copyright (C) 1998-2000 by DooM Legacy Team.
// Copyright (C) 1999-2020 by Sonic Team Junior.
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  i_video.h
/// \brief System specific interface stuff.

#ifndef __I_VIDEO__
#define __I_VIDEO__

#include "doomtype.h"

#ifdef __GNUG__
#pragma interface
#endif

typedef enum
{
	/// Software
	render_soft = 1,

	/// OpenGL
	render_opengl = 2,

	/// Dedicated
	render_none = 3  // for dedicated server
} rendermode_t;

/**	\brief current render mode
*/
extern rendermode_t rendermode;

/**	\brief render mode set by command line arguments
*/
extern rendermode_t chosenrendermode;

/**	\brief use highcolor modes if true
*/
extern boolean highcolor;

/**	\brief setup video mode
*/
void I_StartupGraphics(void);

/**	\brief shutdown video mode
*/
void I_ShutdownGraphics(void);

/**	\brief	The I_SetPalette function

	\param	palette	Takes full 8 bit values

	\return	void
*/
void I_SetPalette(RGBA_t *palette);

/**	\brief return the number of video modes
*/
INT32 VID_NumModes(void);

/**	\brief	The VID_GetModeForSize function

	\param	w	width
	\param	h	height

	\return	vidmode closest to w : h
*/
INT32 VID_GetModeForSize(INT32 w, INT32 h);

/**	\brief	The VID_SetMode function

	Set the video mode right now,
	the video mode change is delayed until the start of the next refresh
	by setting the setmodeneeded to a value >0
	setup a video mode, this is to be called from the menu

	\param	modenum	video mode to set to

	\return	current video mode
*/
INT32 VID_SetMode(INT32 modenum);

/**	\brief Returns the device's native resolution
*/
void VID_GetNativeResolution(INT32 *width, INT32 *height);

/**	\brief Creates a rendering context.
	\return	1 if the context was changed, 0 if it was not
*/
INT32 VID_CreateContext(void);

/**	\brief Destroys the current rendering context.
	\return	1 if the context was destroyed, 0 if it was not
*/
INT32 VID_DestroyContext(void);

/**	\brief Recreates the current rendering context.
*/
void VID_RecreateContext(void);

/**	\brief Checks the render state
	\return	1 if the renderer changed, 0 if it did not
*/
INT32 VID_CheckRenderer(void);

/**	\brief Blits a region of the current framebuffer surface into the texture (does not present it.)
*/
void VID_BlitSurfaceRegion(INT32 x, INT32 y, INT32 w, INT32 h);

/**	\brief Clears the current texture.
*/
void VID_ClearTexture(void);

/**	\brief Copies the current texture into the context and presents it.
*/
void VID_PresentTexture(void);

/**	\brief Load OpenGL mode
*/
void VID_StartupOpenGL(void);

/**	\brief Checks if OpenGL successfully loaded
*/
void VID_CheckGLLoaded(rendermode_t oldrender);

/**	\brief Displays an error if OpenGL failed to load
*/
void VID_DisplayGLError(void);

/**	\brief Loads the splash screen
	\return	1 if the splash screen was successfully loaded, 0 if it was not
*/
INT32 VID_LoadSplashScreen(void);

/**	\brief Blits the splash screen (does not present it.)
*/
void VID_BlitSplashScreen(void);

/**	\brief Presents the splash screen.
*/
void VID_PresentSplashScreen(void);

/**	\brief	The VID_GetModeName function

	\param	modenum	video mode number

	\return	name of video mode
*/
const char *VID_GetModeName(INT32 modenum);
void VID_PrepareModeList(void); /// note hack for SDL


/**	\brief can video system do fullscreen
*/
extern boolean allow_fullscreen;

/**	\brief Update video system without updating frame
*/
void I_UpdateNoBlit(void);

/**	\brief Update video system with updating frame
*/
void I_FinishUpdate(void);

/**	\brief I_FinishUpdate(), but checks the rendering context
*/
void I_CheckFinishUpdate(void);

/**	\brief I_FinishUpdate(), but vsync disabled
*/
void I_UpdateNoVsync(void);

/**	\brief	Wait for vertical retrace or pause a bit.

	\param	count	max wait

	\return	void
*/
void I_WaitVBL(INT32 count);

/**	\brief	The I_ReadScreen function

	\param	scr	buffer to copy screen to

	\return	void
*/
void I_ReadScreen(UINT8 *scr);

/**	\brief Start disk icon
*/
void I_BeginRead(void);

/**	\brief Stop disk icon
*/
void I_EndRead(void);

/**	\brief Report visual progress for some long operation
*/
void I_ReportProgress(int progress);

#endif
