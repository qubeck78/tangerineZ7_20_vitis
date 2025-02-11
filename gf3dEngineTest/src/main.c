#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "platform.h"

#include "bsp.h"
#include "osAlloc.h"
#include "osFile.h"
#include "gfFont.h"
#include "gfBitmap.h"
#include "gfDrawing.h"
#include "osUIEvents.h"

#include "gf3dEngine.h"

//defined in gfxLib/bsp.c
extern tgfTextOverlay  con;


tgfBitmap   screen1;
tgfBitmap   screen2;
tgfBitmap   zBuffer;

tgfScene    scene;


int main()
{
   uint32_t    rv;

   init_platform();
   bspInit();

   screen1.flags      = 0;
   screen1.width      = 320;
   screen1.height     = 240;
   screen1.rowWidth   = 512;
   screen1.buffer     = osAlloc( screen1.rowWidth * screen1.height * 2, OS_ALLOC_MEMF_CHIP );

   screen2.flags      = 0;
   screen2.width      = 320;
   screen2.height     = 240;
   screen2.rowWidth   = 512;
   screen2.buffer     = osAlloc( screen2.rowWidth * screen2.height * 2, OS_ALLOC_MEMF_CHIP );

   zBuffer.flags      = 0;
   zBuffer.width      = 320;
   zBuffer.height     = 240;
   zBuffer.rowWidth   = 512;
   zBuffer.buffer     = osAlloc( zBuffer.rowWidth * zBuffer.height * 2, OS_ALLOC_MEMF_CHIP );

   gfFillRect( &screen1, 0, 0, screen1.width - 1, screen1.height - 1, gfColor( 0, 0, 0) );
   gfFillRect( &screen2, 0, 0, screen2.width - 1, screen2.height - 1, gfColor( 0, 0, 0) );
   gfFillRect( &zBuffer, 0, 0, screen2.width - 1, screen2.height - 1, 0xffff );

   bspDCFlush();

   setVideoMode( _VIDEOMODE_320_TEXT80_OVER_GFX );
   gfDisplayBitmap( &screen1 );

   printf( "gf3dEngine test B20250207\n\n" );

   osFInit();
   osUIEventsInit();

   scene.frameBuffer = &screen1;
   scene.zBuffer     = &zBuffer;
   gf3dMeshNew( &scene.mesh );
   gf3dMeshNew( &scene.meshRaster );
   gf3dVectorClear( &scene.vCamera );
   gf3dVectorClear( &scene.vLookDir );

   gf3dMatrixClear( &scene.projectionMatrix );
   gf3dMatrixMakeProjection( &scene.projectionMatrix, 90.0f, (float)scene.frameBuffer->height / (float)scene.frameBuffer->width, 0.1f, 1000.0f );

   printf( "Loading mesh\n" );

   rv = gf3dMeshLoadOBJ( &scene.mesh, (char*)"0:/obj/torus4.obj", 2.0f , NULL );

   printf( "Done, rv:%d, numTriangles:%d\n", (int)rv, (int)scene.mesh.numTriangles );

   do{


   }while( 1 );


}
