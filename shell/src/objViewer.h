#ifndef _OBJVIEWER_H
#define _OBJVIEWER_H



#include "bsp.h"
#include "osAlloc.h"
#include "osFile.h"
#include "gfBitmap.h"
#include "gfDrawing.h"
#include "gfFont.h"
#include "gfGouraud.h"
#include "osUIEvents.h"




int objvInit( void );
int objvView( char *fileName );

#endif
