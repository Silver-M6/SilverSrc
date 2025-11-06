/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2002-2009 John Fitzgibbons and others
Copyright (C) 2010-2014 QuakeSpasm developers
Copyright (C) 2025-2025 SilverSrc Developers

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#pragma once
#if !defined(WADFILE_H)
#define WADFILE_H

/*
The .WAD archive format (WhereAllData)
Basically a list of compressed files
that can only be identified by TYPE_*
*/

#define IDWAD2HEADER	(('2'<<24)+('D'<<16)+('A'<<8)+'W')	// little-endian "WAD2" quake wads
#define IDWAD3HEADER	(('3'<<24)+('D'<<16)+('A'<<8)+'W')	// little-endian "WAD3" half-life wads
#define WAD3_NAMELEN	16

// attribs
#define ATTR_NONE		0	// allow to read-write
#define ATTR_READONLY	BIT( 0 )	// don't overwrite this lump in anyway
#define ATTR_COMPRESSED	BIT( 1 )	// not used for now, just reserved
#define ATTR_HIDDEN		BIT( 2 )	// not used for now, just reserved
#define ATTR_SYSTEM		BIT( 3 )	// not used for now, just reserved

// ===================================================
//  COMPRESSION (MOVED DUE TO IT BEING SIMPLER HERE)
// ===================================================

#define CMP_NONE    0 // no compression
#define CMP_LZSS    1 // lzss compression

//==========================================================
//   TYPES (INCLUDING HALF LIFE 1 TYPES AND QUAKE 1 TYPES)
//==========================================================

#define	TYP_NONE		0
#define	TYP_LABEL		1

#define TYP_ANY		-1	// any type can be accepted
#define TYP_NONE		0	// unknown lump type
#define TYP_LABEL		1	// legacy from Doom1. Empty lump - label (like P_START, P_END etc)
#define TYP_PALETTE		64	// quake or half-life palette (768 bytes)
#define TYP_DDSTEX		65	// contain DDS texture
#define TYP_GFXPIC		66	// menu or hud image (not contain mip-levels)
#define TYP_MIPTEX		67	// quake1 and half-life in-game textures with four miplevels
#define TYP_SCRIPT		68	// contain script files
#define TYP_COLORMAP2	69	// old stuff. build palette from LBM file (not used)
#define TYP_QFONT		70	// half-life font (qfont_t)

#define WADFILE_H "gfx.wad"  // hardcoded bne

// .lmp image format
typedef struct lmp_s
{
	unsigned int	width;
	unsigned int	height;
} lmp_t;

// .mip format
typedef struct mip_s
{
	char		name[16];
	unsigned int	width;
	unsigned int	height;
	unsigned int	offsets[4];	// mipmaps
} mip_t;
// wad header half life struct
typedef struct
{
    char		identification[4]; // old code whining about this, yet again
	int		ident;		// should be WAD3
	int		numlumps;		// num files
	int		infotableofs;	// LUT offset
} dwadinfo_t;

// .wad half life struct ig
typedef struct
{
	int		filepos;		// file offset in WAD
	int		disksize;		// compressed or uncompressed
	int		size;		// uncompressed
	signed char	type;		// TYP_*
	signed char	attribs;		// file attribs
	signed char	pad0;
	signed char	pad1;
	char		name[WAD3_NAMELEN];	// must be null terminated
} dlumpinfo_t;

typedef struct
{
	int			width, height;
	byte		data[4];			// variably sized
} qpic_t;

typedef struct
{
	char		identification[4];		// should be WAD2 or 2DAW
	int			numlumps;
	int			infotableofs;
} wadinfo_t;

typedef struct
{
	int		filepos;		// file offset in WAD
	int		disksize;		// compressed or uncompressed
	int		size;		// uncompressed
    char	type;		// TYP_*
    char	attribs;		// file attribs
    char	pad0;
    char	pad1;
	char		name[WAD3_NAMELEN];	// must be null terminated
} lumpinfo_t; // for compatibility's sake

extern	int			wad_numlumps;
extern	lumpinfo_t	*wad_lumps;
extern	byte		*wad_base;

void	W_LoadWadFile (void); //johnfitz -- filename is now hard-coded for honesty
void	W_CleanupName (const char *in, char *out);
lumpinfo_t	*W_GetLumpinfo (const char *name);
void	*W_GetLumpName (const char *name);
void	*W_GetLumpNum (int num);

void SwapPic (qpic_t *pic);

#endif	/* _QUAKE_WAD_H */

