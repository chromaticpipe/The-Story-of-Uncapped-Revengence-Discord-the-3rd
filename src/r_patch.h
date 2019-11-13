// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Copyright (C) 1993-1996 by id Software, Inc.
// Copyright (C) 1998-2000 by DooM Legacy Team.
// Copyright (C) 1999-2018 by Sonic Team Junior.
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  r_patch.h
/// \brief Patch generation.

#ifndef __R_PATCH__
#define __R_PATCH__

#include "r_defs.h"
#include "doomdef.h"

// structs
#ifdef ROTSPRITE
typedef enum
{
	ROLLAXIS_X, // the default
	ROLLAXIS_Y,
	ROLLAXIS_Z
} rollaxis_t;

typedef struct
{
	INT32 x, y;
	rollaxis_t rollaxis;
} spriteframepivot_t;
#endif

typedef struct
{
#ifdef ROTSPRITE
	spriteframepivot_t pivot[64];
#endif
	boolean available;
} spriteinfo_t;

extern spriteinfo_t spriteinfo[NUMSPRITES];

// patches, flats, textures...
boolean R_CheckIfPatch(lumpnum_t lump);
boolean R_IsLumpPNG(const UINT8 *d, size_t s);

void R_TextureToFlat(size_t tex, UINT8 *flat);
void R_PatchToFlat(patch_t *patch, UINT8 *flat);
void R_PatchToFlat_16bpp(patch_t *patch, UINT16 *raw, boolean flip);
patch_t *R_FlatToPatch(UINT8 *raw, UINT16 width, UINT16 height, UINT16 leftoffset, UINT16 topoffset, size_t *destsize, boolean transparency);
patch_t *R_FlatToPatch_16bpp(UINT16 *raw, UINT16 width, UINT16 height, size_t *size);

// png
#ifndef NO_PNG_LUMPS
UINT8 *R_PNGToFlat(UINT16 *width, UINT16 *height, UINT8 *png, size_t size);
patch_t *R_PNGToPatch(const UINT8 *png, size_t size, size_t *destsize, boolean transparency);
boolean R_PNGDimensions(UINT8 *png, INT16 *width, INT16 *height, size_t size);
#endif

// spriteinfo
void R_LoadSpriteInfoLumps(UINT16 wadnum, UINT16 numlumps);
void R_ParseSPRTINFOLump(UINT16 wadNum, UINT16 lumpNum);

// rotsprite
#ifdef ROTSPRITE
void R_CacheRotSprite(spritenum_t sprnum, UINT8 frame, spriteinfo_t *sprinfo, spriteframe_t *sprframe, INT32 rot, UINT8 flip);
extern fixed_t cosang2rad[ROTANGLES];
extern fixed_t sinang2rad[ROTANGLES];
#endif

#endif // __R_PATCH__
