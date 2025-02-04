#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_cache.h"
#include "xparameters.h"   /* SDK generated parameters */


//
//text mode ram     0x40000000 - 0x40001fff
//root regs (bsp)   0x42000000

//https://github.com/Xilinx/embeddedsw/tree/master
//Hardware bitstream update

//https://adaptivesupport.amd.com/s/question/0D54U00008GmLxbSAF/workaround-updating-hardware-specifications-in-a-vitis-unified-project-using-xsa-doesnt-work?language=en_US
//copy bitstream files to:
//\helloWorld2\_ide\bitstream\system_wrapper.bit
//\helloWorld2\_ide\bitstream\system_wrapper.mmi

//tutorials:
//https://xilinx.github.io/Embedded-Design-Tutorials/docs/2022.1/build/html/index.html

//vitis ide
//https://docs.amd.com/r/en-US/ug1400-vitis-embedded/Vitis-Component-View
//https://www.adiuvoengineering.com/post/microzed-chronicles-introducing-vitis-unified-ide

//dma m2s s2m
//https://www.youtube.com/watch?v=tQpt2N7__NQ&t=73s


//Programming with Zynq :)
//https://docs.amd.com/r/en-US/ug821-zynq-7000-swdev/Introduction-to-Programming-with-Zynq-7000-AP-SoC-Devices

//PetaLinux
//https://docs.amd.com/r/2023.1-English/ug1144-petalinux-tools-reference-guide/Installation-Requirements

#define SLIDESHOW_ALPHA_ANIMATION

#include "ff.h"
#include "sleep.h"

#include "bsp.h"
#include "osAlloc.h"
#include "osFile.h"
#include "gfFont.h"
#include "gfBitmap.h"
#include "gfJPEG.h"
#include "gfDrawing.h"
#include "osUIEvents.h"

//defined in gfxLib/bsp.c
extern tgfTextOverlay  con;

tgfBitmap         screen;
tgfBitmap         bmp;
tgfBitmap         background;
tgfBitmap         fileBmp;
char              buf[ 128 ];

tosDir            dir;
tosDirItem        dirItem;

uint32_t          numDirEntries;




uint32_t getNumEntries()
{
    uint32_t rv;
    uint32_t numEntries;

    #ifdef _GFXLIB_SDL

    rv = osDirOpen( &dir, (char*)"./img" );

    #else

    rv = osDirOpen( &dir, (char*)"0:img" );

    #endif

    printf( "Dir open\n" );

    numEntries = 0;

    do
    {
        rv = osDirRead( &dir, &dirItem );

        if( rv )
        {
            break; // Error or end of dir
        }

        printf( "%s\n", dirItem.name );

        numEntries++;

    }while( 1 );

    osDirClose( &dir );

    printf( "%d entries\n", numEntries );

    return numEntries;
}

uint32_t getEntry( uint32_t entryNumber )
{
    uint32_t i;
    uint32_t rv;

    #ifdef _GFXLIB_SDL

    rv = osDirOpen( &dir, (char*)"./img" );

    #else

    rv = osDirOpen( &dir, (char*)"0:img" );

    #endif

    for( i = 0; i < entryNumber; i++ )
    {

        osDirRead( &dir, &dirItem );

    }

    osDirClose( &dir );

    return 0;
}

int32_t drawBackground( tgfBitmap *bmp )
{
   uint32_t i;
   uint32_t j;
   uint32_t df;

   df = bmp->height / 120;

   for( i = 0; i < bmp->height; i++ )
   {
      j = i / df;
      gfFillRect( bmp, 0, i, bmp->width - 1, i, gfColor( j, j / 2, j ) );
   }

   bspDCFlush();

   return 0;
}


uint32_t slideshow()
{
    uint32_t        rv;
    uint32_t        i;
    int16_t         x;
    int16_t         y;
    char            extension[8];
    tosUIEvent      event;
    uint32_t        bgRedrawCounter;

    bgRedrawCounter = 0;


    do{

        getEntry( randomNumber() % numDirEntries );


        if ( dirItem.type != OS_DIRITEM_DIR )
        {

            i = strlen( dirItem.name );

            if( i >= 4 )
            {
                extension[0] = dirItem.name[ i - 4 ];
                extension[1] = dirItem.name[ i - 3 ];
                extension[2] = dirItem.name[ i - 2 ];
                extension[3] = dirItem.name[ i - 1 ];
                extension[4] = 0;

                if( ( strcmp( extension, ".jpg" ) == 0 ) || ( strcmp( extension, ".gbm" ) == 0 ) )
                {

                    if( !bgRedrawCounter )
                    {

                       drawBackground( &screen );

                       bgRedrawCounter = 49;

                    }
                    else
                    {
                       bgRedrawCounter--;
                    }

                    strcpy( buf, "img/" );
                    strcat( buf, dirItem.name );

                    con.textAttributes = 0x0f;
                    toCls( &con );
                    con.textAttributes  = 0x8f;

                    toPrintF( &con, (char*) "Loading:%s\n", dirItem.name );

                    if( dirItem.name[ i - 3 ] == 'g' )
                    {
                        gfLoadBitmapFS( &fileBmp, buf );
                    }
                    else
                    {
                        gfLoadJPEGFS( &fileBmp, buf );
                    }

                    if( fileBmp.width > 320 )
                    {
                       fileBmp.width = 320;
                    }
                    if( fileBmp.height > 240 )
                    {
                       fileBmp.height = 240;
                    }

                    if( screen.width > 512 )
                    {
                        x  = ((uint32_t)randomNumber() ) % 320;
                        y  = ((uint32_t)randomNumber() ) % 240;

                    }
                    else
                    {

                        x = ( screen.width / 2 ) - ( fileBmp.width / 2);
                        y = ( screen.height / 2 ) - ( fileBmp.height / 2 );
                    }



                    #ifdef SLIDESHOW_ALPHA_ANIMATION

                    background.width            = fileBmp.width;
                    background.height           = fileBmp.height;
                    background.rowWidth         = background.width;
                    background.flags            = 0;
                    background.transparentColor = 0;
                    background.buffer           = osAlloc( background.rowWidth * background.height * 2, OS_ALLOC_MEMF_CHIP );

                    gfBlitBitmapSrcRect( &background, &screen, x, y, background.width, background.height, 0, 0 );


                    for( i = 0; i < 256; i += 8 )
                    {
                        do{}while( ! bsp->videoVSync );

                        gfBlitBitmapA2Src( &screen, &fileBmp, &background, x, y, i );
                        bspDCFlush();
                    }

                    osFree( background.buffer );
                    background.buffer   = NULL;

                    #endif

                    gfBlitBitmap( &screen, &fileBmp, x, y );
                    bspDCFlush();

                    osFree( fileBmp.buffer );

                    fileBmp.buffer          = NULL;
                    con.textAttributes      = 0x0f;

                    toCls( &con );
                    con.textAttributes      = 0x8f;

                    toPrintF( &con, (char*) "%s %d\n", dirItem.name, dirItem.size );

                    for( i = 0; i < 500; i++ )
                    {
                        delayMs( 20 );

                        if( !osGetUIEvent( &event ) )
                        {
                            if( event.type == OS_EVENT_TYPE_KEYBOARD_KEYPRESS )
                            {
                                switch( event.arg1 )
                                {

                                    case _KEYCODE_PAUSE:

                                        //reboot();
                                        break;

                                    case _KEYCODE_F1:

                                        break;

                                    default:

                                        //exit delay loop
                                        i = 500;
                                        break;
                                }
                            }

                        }

                    }
                }
            }
        }

    }while( 1 );

}


int main()
{
   tosUIEvent     event;

   //volatile       uint32_t *paletteRegs = (uint32_t*)0x45000400;

   init_platform();
   bspInit();

   screen.flags      = 0;
   screen.width      = 640;
   screen.height     = 480;
   screen.rowWidth   = 1024;
   screen.buffer     = osAlloc( screen.rowWidth * screen.height * 2, OS_ALLOC_MEMF_CHIP );

   setVideoMode( _VIDEOMODE_640_TEXT80_OVER_GFX );
   gfDisplayBitmap( &screen );

   drawBackground( &screen );


   //display cursor
   con.flags |= GF_TEXT_OVERLAY_FLAG_SHOW_CURSOR;

   printf( "\n" );
   printf( "        |.\\__/.|    (~\\ \n" );
   printf( "        | O O  |     ) ) \n" );
   printf( "      _.|  T   |_   ( (  \n" );
   printf( "   .-- ((---- ((-------------.\n" );
   printf( "   | Zynq slideshow 20250129 |\n" );
   printf( "   |     tangerine Z7_20     |\n" );
//   printf( "   |     SD BOOT             |\n" );
   printf( "   |     SOC:%08x        |\n", (int)bsp->version );
   printf( "   `-------------------------`\n" );
   printf( "\n\n\n");

   osFInit();
   osUIEventsInit();

   printf( ">" );
   fflush( stdout );


   do
   {
      if( !osGetUIEvent( &event ) )
      {
          if( event.type == OS_EVENT_TYPE_KEYBOARD_KEYPRESS )
          {
             //printf( "%02x ", event.arg1 );
             printf( "%c", (int)event.arg1 );
             fflush( stdout );
             //ps2HostSetKeyboardLeds( i++ );

             if( event.arg1 == 27 )
             {
                break;
             }
          }
      }
   }while( 1 );

   //delayMs( 5000 );

   numDirEntries = getNumEntries();

   //hide cursor
   con.flags &= 0xffff ^ GF_TEXT_OVERLAY_FLAG_SHOW_CURSOR;

   if( numDirEntries )
   {
      slideshow();
   }

   cleanup_platform();

   return 0;
}
