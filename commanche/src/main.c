
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "platform.h"
#include "xil_printf.h"

#include "bsp.h"
#include "osAlloc.h"
#include "osFile.h"
#include "gfBitmap.h"
#include "gfDrawing.h"
#include "gfFont.h"
#include "osUIEvents.h"


extern tgfTextOverlay        con;

//extern _BSP_T        *bsp;
tgfBitmap            screen1;
tgfBitmap            screen2;
tgfBitmap            textureMap;
uint8_t             *heightMap;
tosFile              in;


struct
{
      float x;       // x position on the map
      float y;       // y position on the map
      int16_t height;  // height of the camera
      float angle;   // direction of the camera
      int16_t horizon; // horizon position (look up and down)
      float distance; // distance of map
} camera = { 256, 256, 40, 0.1, 40, 150 };

char buf[128];

int animLeds( int j )
{

   return 0;
}

#ifdef _GFXLIB_ZYNQ7

static void z7FastBlit( tgfBitmap *dest, tgfBitmap *src )
{
   uint32_t x;
   uint32_t y;
   uint32_t dxSrc;
   uint32_t dxDst;

   uint32_t *psrc;
   uint32_t *pdest;

   pdest = ( uint32_t* )dest->buffer;
   psrc  = ( uint32_t* )src->buffer;

   dxSrc = ( src->rowWidth - src->width ) / 2;
   dxDst = ( dest->rowWidth - dest->width ) / 2;

   for( y = 0; y < dest->height; y++ )
   {
      for( x = 0 ; x < dest->width; x += 2 )
      {
         *pdest++ = *psrc++;
      }
      pdest += dxDst;
      psrc  += dxSrc;
   }
}

static void z7FastFill( tgfBitmap *dest, uint32_t value )
{
   uint32_t x;
   uint32_t y;
   uint32_t dx;

   uint32_t *pdest;

   dx = ( dest->rowWidth - dest->width ) / 2;

   pdest = ( uint32_t* )dest->buffer;

   for( y = 0; y < dest->height; y++ )
   {
      for( x = 0 ; x < dest->width; x += 2 )
      {
         *pdest++ = value;
      }
      pdest += dx;
   }
}

#endif



uint32_t commanche( tgfBitmap *screen )
{

   uint32_t screenwidth = 320;
   //float    screenwidthf = screenwidth;

   uint32_t screenheight = 240;

   uint32_t mapwidthperiod = 512 - 1;
   uint32_t mapheightperiod = 512 - 1;
   uint32_t mapshift = 9;
   int32_t  mapoffset;
   float    deltaz = 1.0f;   //1.5f
   //int16_t  y;
   int16_t  x;
   float    z;
   //float    invz;
   int16_t  heightonscreen;
   uint16_t color;
   int32_t  cameraoffs;
   float    sinang;
   float    cosang;
   float    plx;
   float    ply;
   float    prx;
   float    pry;
   float    dx;
   float    dy;

   //int16_t  bw;
   //int16_t  bh;

   int32_t  linvz;
   int16_t  hiddeny[ 320 ];

   int32_t  lplx;
   int32_t  lply;
   int32_t  ldx;
   int32_t  ldy;
   float    cosangz;
   float    sinangz;


   //gfFillRect( screen, 0, 0, screenwidth, screenheight, 0 );

   z7FastFill( screen, 0 );

   sinang      = (float)sin( camera.angle );
   cosang      = (float)cos( camera.angle );
   cameraoffs  = ( ( ((int)camera.y) & mapwidthperiod ) << mapshift ) + ( ((int)camera.x) & mapheightperiod );

   // Collision detection. Don't fly below the surface.
   if( ( heightMap[ cameraoffs ] + 10.0f ) > camera.height )
   {
      camera.height = heightMap[ cameraoffs ] + 10.0f;
   }

   for( x = 0; x < screenwidth; x++ )
   {
      hiddeny[ x ] = screenheight;
   }

   // Draw from front to back
   for( z = 1.0f; z < camera.distance; z += deltaz )
   {
      // 90 degree field of view

      cosangz  = cosang * z;
      sinangz  = sinang * z;


/*    plx =  -cosang * z - sinang * z;
      ply =   sinang * z - cosang * z;
      prx =   cosang * z - sinang * z;
      pry =  -sinang * z - cosang * z;
*/

      plx =  ( -cosangz ) - sinangz;
      ply =   sinangz - cosangz;
      prx =   cosangz - sinangz;
      pry =  ( -sinangz ) - cosangz;

      dx = ( prx - plx ) / screenwidth;
      dy = ( pry - ply ) / screenheight;


      plx += camera.x;
      ply += camera.y;

//      invz = 1.0f / z * 100.0f;
//      invz = 100.0f / z;

//      linvz = invz * 256;
//      linvz = 25600 / (int32_t)z;
      linvz = 12800 / (int32_t)z;


      lplx  = plx * 256;
      lply  = ply * 256;
      ldx   = dx * 256;
      ldy   = dy * 256;


      for( x = 0; x < screenwidth; x++ )
      {
//          mapoffset = ( ( ((int32_t)ply) & mapwidthperiod ) << mapshift ) + ( ((int32_t)plx) & mapheightperiod );

         mapoffset = ( ( ( lply >> 8 ) & mapwidthperiod ) << mapshift ) + ( ( lplx >> 8 ) & mapheightperiod );

         heightonscreen = (int16_t)( ( ( ( camera.height - heightMap[ mapoffset ] ) * linvz ) >> 8 ) + camera.horizon );

         if( heightonscreen < 0 )
         {
            heightonscreen = 0;
         }

         color = ((uint16_t *)textureMap.buffer)[ mapoffset ];

         if( heightonscreen < hiddeny[x] )
         {

            //draw strip

            gfFillRect( screen, x, heightonscreen, x, hiddeny[x], color );

            hiddeny[ x ] = heightonscreen;

         }


         //plx += dx;
         //ply += dy;

         lplx += ldx;
         lply += ldy;

      }


      deltaz += 0.00250f;

   }

   return 0;
}

int main()
{
   uint32_t    i;
   uint32_t    rv;

   tosUIEvent  event;
   uint32_t    keyStatus;

   init_platform();
   bspInit();

   setVideoMode( _VIDEOMODE_320_TEXT80_OVER_GFX );

   toPrint( &con, (char*)"tangyRiscVSOC Commanche B20240917\n" );
   toPrint( &con, (char*)"Map loading..." );

   //alloc screen buffers
   screen1.width           = 320;
   screen1.rowWidth        = 512;
   screen1.height          = 240;
   screen2.width           = 320;
   screen2.rowWidth        = 512;
   screen2.height          = 240;


   screen1.flags              = 0;
   screen1.transparentColor   = 0;
   screen1.buffer             = osAlloc( screen1.rowWidth * screen1.height * 2, OS_ALLOC_MEMF_CHIP );

   if( screen1.buffer == NULL )
   {
      toPrint( &con, (char*)"\nCan't alloc screen 1\n" );
      do{}while( 1 );
   }

   screen2.flags           = 0;
   screen2.transparentColor = 0;
   screen2.buffer           = osAlloc( screen2.rowWidth * screen2.height * 2, OS_ALLOC_MEMF_CHIP );

   if( screen2.buffer == NULL )
   {
      toPrint( &con, (char*)"\nCan't alloc screen 2\n" );
      do{}while( 1 );
   }

   //display first buffer
   gfDisplayBitmap( &screen1 );

   gfFillRect( &screen1, 0, 0, screen1.width - 1, screen1.height - 1 , gfColor( 0, 0, 0 ) );
   gfFillRect( &screen2, 0, 0, screen1.width - 1, screen1.height - 1 , gfColor( 0, 0, 0 ) );

   bspDCFlush();

   //init filesystem
   rv = osFInit();

   //init events queue
   osUIEventsInit();

   rv = gfLoadBitmapFS( &textureMap, (char*)"ctexture.gbm" );

   if( rv )
   {
      toPrint( &con, (char*)"\nError, copy ctexture.gbm file to sd-card\n" );
   }

   heightMap = (uint8_t*)osAlloc( 262144, OS_ALLOC_MEMF_CHIP );

   if( !osFOpen( &in, (char*)"cheight.raw" , OS_FILE_READ ) )
   {
      osFRead( &in, (uint8_t*)heightMap, 262144, NULL );
      osFClose( &in );
   }
   else
   {
      toPrint( &con, (char*)"\nError, copy cheight.raw file to sd-card\n" );
   }

   i = 0;


   toPrint( &con, (char*)"done\n" );

   keyStatus = 0;

   bspDCFlush();

   do
   {
      animLeds( i++ );

      if( !osGetUIEvent( &event ) )
      {

         if( event.type == OS_EVENT_TYPE_KEYBOARD_KEYPRESS )
         {
            switch( event.arg1 )
            {
               case _KEYCODE_UP:

                  keyStatus |= 1;

               break;

               case _KEYCODE_DOWN:

                  keyStatus |= 2;

                  break;

               case _KEYCODE_RIGHT:

                  keyStatus |= 4;

               break;

               case _KEYCODE_LEFT:

                  keyStatus |= 8;

               break;

               case _KEYCODE_PGUP:

                  keyStatus |= 16;

                  break;

               case _KEYCODE_PGDOWN:

                  keyStatus |= 32;

                  break;

          case _KEYCODE_PAUSE:

              //reboot();
              break;

            }
         }else if( event.type == OS_EVENT_TYPE_KEYBOARD_KEYRELEASE )
         {
            switch( event.arg1 )
            {
               case _KEYCODE_UP:

                  keyStatus &= 1 ^ 0xffffffff;

               break;

               case _KEYCODE_DOWN:

                  keyStatus &= 2 ^ 0xffffffff;

                  break;

               case _KEYCODE_RIGHT:

                  keyStatus &= 4 ^ 0xffffffff;

               break;

               case _KEYCODE_LEFT:

                  keyStatus &= 8 ^ 0xffffffff;

               break;

               case _KEYCODE_PGUP:

                  keyStatus &= 16 ^ 0xffffffff;

                  break;

               case _KEYCODE_PGDOWN:

                  keyStatus &= 32 ^ 0xffffffff;

                  break;
            }
         }
      }



      if( keyStatus & 8 )
      {
         //left
         camera.angle += 0.1;

      }
      else if( keyStatus & 4 )
      {
         //right
         camera.angle -= 0.1;

      }

      if( keyStatus & 1 )
      {
         //up
         camera.height += 1;

      }
      else if( keyStatus & 2 )
      {
         //down

         if( camera.height > 0 )
         {
            camera.height -= 1;
         }

      }

      if( keyStatus & 16 )
      {
         camera.horizon += 1;
      }
      else if( keyStatus & 32 )
      {
         if( camera.horizon > 0 )
         {
            camera.horizon -= 1;
         }
      }


      camera.x -= (float)sin( camera.angle ) * 1.1f;
      camera.y -= (float)cos( camera.angle ) * 1.1f;


      if( i & 1 )
      {
         gfDisplayBitmap( &screen2 );

         do{}while( ! bsp->videoVSync );

         commanche( &screen1 );
         bspDCFlush();
      }
      else
      {

         gfDisplayBitmap( &screen1 );

         do{}while( ! bsp->videoVSync );

         commanche( &screen2 );
         bspDCFlush();
      }


   }while( 1 );

}

