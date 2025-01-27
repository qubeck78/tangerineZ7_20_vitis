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

//defined in gfxLib/bsp.c
extern tgfTextOverlay  con;

tgfBitmap   screen;


uint32_t ffMandelbrot( tgfBitmap *bmp, uint16_t colorMask, float xmin, float ymin, float dx, float dy )
{
    uint32_t    x;
    uint32_t    y;

    float       ci;
    float       cr;
    float       zr;
    float       zi;
    float       zrr;
    float       zii;
    float       zri;

    float       zrmzi;

    int32_t     iter;
    uint16_t    color;

    uint16_t    r;
    uint16_t    g;
    uint16_t    b;


    if( ( colorMask & 3 ) == 0 )
    {
        colorMask = 1;
    }

    ci = ymin;

    for( y = 0; y < bmp->height; y++ )
    {
        //animLeds( y );

        cr = xmin;

        for( x = 0; x < bmp->width; x++ )
        {

            zr = cr;
            zi = ci;

            iter = 32;

            while( iter > 0 )
            {

                zrr = ffMul( zr, zr );
                //zrr = zr * zr;
                zii = ffMul( zi, zi );

                //zii = zi * zi;

                zrmzi   = ffMul( zr, zi );
                zri     = ffMul( 2.0f, zrmzi );

                //zri = 2.0f * ( zr * zi );

                zr      = ffSub( zrr, zii );
                zr      = ffAdd( zr, cr );

                //zr = zrr - zii + cr;

                zi      = ffAdd( zri, ci );
                //zi = zri + ci;

                if( ffAdd( zrr, zii ) > 4.0f )
//              if( zrr + zii > 4.0f )
                {
                    break;
                }
                iter--;

            }

            if( iter == 0 )
            {
                color = 0;
            }
            else
            {
                color = ( 32 - iter ) << 3;
            }

            if( colorMask & 1 )
            {
                r = color;
            }
            else
            {
                r = 0;
            }

            if( colorMask & 2 )
            {
                g = color;
            }
            else
            {
                g = 0;
            }

            if( colorMask & 4 )
            {
                b = color;
            }
            else
            {
                b = 0;
            }

            gfPlot( bmp, x, y, gfColor( r, g, b ) );

            cr = ffAdd( cr, dx );
            //cr += dx;

        }

        ci = ffAdd( ci, dy );
        //ci += dy;

        bspDCFlush();

    }

    return 0;
}

int main()
{

   init_platform();
   bspInit();

   screen.flags      = 0;
   screen.width      = 320;
   screen.height     = 240;
   screen.rowWidth   = 512;
   screen.buffer     = osAlloc( screen.rowWidth * screen.height * 2, OS_ALLOC_MEMF_CHIP );

   setVideoMode( _VIDEOMODE_320_TEXT80_OVER_GFX );
   gfDisplayBitmap( &screen );

   gfFillRect( &screen, 0, 0, 319, 239, gfColor( 0, 0, 0) );
   bspDCFlush();

   printf( "Mandelbrot\n" );



   osFInit();
   osUIEventsInit();

   ffMandelbrot( &screen, 7, -2.0f, -1.0f, 0.0085f, 0.0085f );

   delayMs( 30000 );

   do{

      ffMandelbrot( &screen, ( randomNumber() >> 7 ) & 7, -1.7f + ((uint32_t)randomNumber() ) / 3294967296.0f ,  -1.7f + ((uint32_t)randomNumber() ) / 3294967296.0f , 0.001f, 0.001f );
      delayMs( 10000 );

   }while( 1 );


}
