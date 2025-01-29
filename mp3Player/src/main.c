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
#include "gfJPEG.h"
#include "gfDrawing.h"
#include "osUIEvents.h"
#include "gfAudio.h"
#include "mp3dec.h"

//defined in gfxLib/bsp.c
extern tgfTextOverlay  con;

tgfBitmap   screen;
tgfBitmap   background;

tosFile     in;

#define MP3_FILE_BUFFER_SIZE  65536
#define AUDIO_BUFFER_SIZE     65536

//check whole lib fork for esp32 https://github.com/pschatzmann/arduino-libhelix/tree/main/src/libhelix-mp3

static uint32_t waitKey()
{
    uint32_t    keyPressed;
    tosUIEvent  event;

    keyPressed = 0;

    do
    {
        while( !osGetUIEvent( &event ) )
        {
            if( event.type == OS_EVENT_TYPE_KEYBOARD_KEYPRESS )
            {
                keyPressed = 1;

                if( event.arg1 ==  _KEYCODE_PAUSE )
                {
                    //reboot();
                }
            }
        }
        delayMs( 10 );

    }while( !keyPressed );

    return 0;
}

uint32_t readAndFillBuffer( uint8_t *mp3Buffer, uint8_t *currentMp3, uint32_t mp3BufferSize, int32_t bytesLeft )
{
   uint32_t nbr;

   memmove( mp3Buffer, currentMp3, bytesLeft );

   osFRead( &in, mp3Buffer + bytesLeft, mp3BufferSize - bytesLeft, &nbr );

   if( nbr < ( mp3BufferSize - bytesLeft ) )
   {
      memset( mp3Buffer + bytesLeft + nbr, 0, mp3BufferSize - bytesLeft - nbr );
   }

   return nbr;
}

int main()
{
   uint32_t         nbr;

   MP3FrameInfo     mp3FrameInfo;
   HMP3Decoder      hMP3Decoder;
   char             mp3FileName[256];

   uint32_t         mp3Size;
   int              bytesLeft;
   int16_t         *audioBuffer;
   uint8_t         *mp3Buffer;
   uint8_t         *currentMp3;
   int32_t          offset;
   uint32_t         frameSize;

   init_platform();
   bspInit();

   screen.flags      = 0;
   screen.width      = 320;
   screen.height     = 240;
   screen.rowWidth   = 512;
   screen.buffer     = osAlloc( screen.rowWidth * screen.height * 2, OS_ALLOC_MEMF_CHIP );

   setVideoMode( _VIDEOMODE_320_TEXT80_60_OVER_GFX );
   gfDisplayBitmap( &screen );

   gfFillRect( &screen, 0, 0, 319, 239, gfColor( 0, 0, 0) );

   bspDCFlush();

   con.flags |= GF_TEXT_OVERLAY_FLAG_SHOW_CURSOR;

   printf( "     |.\\__/.|    (~\\ \n" );
   printf( "     | O O  |     ) ) \n" );
   printf( "   _.|  T   |_   ( (  \n" );
   printf( ".-- ((---- ((-------------.\n" );
   printf( "| Zynq MP3Player 20250129 |\n" );
   printf( "|     tangerine Z7_20     |\n" );
   printf( "|     SOC:%08x        |\n", (int)bsp->version );
   printf( "`-------------------------`\n" );
   printf( "\n\n");


   osFInit();
   osUIEventsInit();

   gfLoadBitmapFS( &background, "0:/snd/catheadphones.gbm" );

   gfBlitBitmap( &screen, &background, 0, 0 );
   bspDCFlush();

   audioBuffer = ( int16_t * )osAlloc( 65536, OS_ALLOC_MEMF_CHIP );

   if( !audioBuffer )
   {
     printf( "Can't alloc audio buffer\n" );

     do{
     }while( 1 );

   }

   hMP3Decoder = MP3InitDecoder();

   if( !hMP3Decoder )
   {
     printf( "Can't init mp3 decoder\n" );

     do{
     }while( 1 );
   }


   gfAudioInit();

//   strcpy( mp3FileName, "0:/snd/connectohm.mp3" );
     strcpy( mp3FileName, "0:/snd/fahrenheit.mp3" );
//   strcpy( mp3FileName, "0:/snd/tipper.mp3" );
//   strcpy( mp3FileName, "0:/snd/bloom1.mp3" );
//   strcpy( mp3FileName, "0:/snd/bloom2.mp3" );
//   strcpy( mp3FileName, "0:/snd/fauna.mp3" );
//   strcpy( mp3FileName, "0:/snd/starfish.mp3" );

   mp3Size = osFSize( mp3FileName );

   if( !mp3Size )
   {
       printf( "Can't get size of %s - press pause to reboot\n", mp3FileName );

       do{

       }while( 1 );

   }

   mp3Buffer   = (uint8_t*) osAlloc( MP3_FILE_BUFFER_SIZE, OS_ALLOC_MEMF_CHIP );


   if( !mp3Buffer )
   {
       printf( "Can't alloc %d bytes for mp3 file buffer - press pause to reboot\n", MP3_FILE_BUFFER_SIZE );

       do{

           waitKey();

       }while( 1 );

   }

   printf( "%s ( %dMB )\n", mp3FileName, (int)( mp3Size / 1048576 ) );

   if( osFOpen( &in, mp3FileName, OS_FILE_READ ) )
   {
       printf( "Can't open %s - press pause to reboot\n", mp3FileName );

       do{

           waitKey();

       }while( 1 );
   }

   //read header

   nbr = 0;

   osFRead( &in, mp3Buffer, MP3_FILE_BUFFER_SIZE, &nbr );

   bytesLeft       = MP3_FILE_BUFFER_SIZE;
   currentMp3      = mp3Buffer;

   //decode first frame

   offset = MP3FindSyncWord( currentMp3, bytesLeft ) ;

   //todo check if offset < 0

   currentMp3  += offset;
   bytesLeft   -= offset;

   MP3Decode( hMP3Decoder,&currentMp3, &bytesLeft, &audioBuffer[0], 0 );
   MP3GetLastFrameInfo( hMP3Decoder, &mp3FrameInfo );

   frameSize = mp3FrameInfo.outputSamps;

   gfAudioConfigure( mp3FrameInfo.samprate, 1 );

   printf( "Bitrate: %d kbps\n", mp3FrameInfo.bitrate / 1000 );
   printf( "Samplerate: %d Hz\n", mp3FrameInfo.samprate );
   printf( "Frame size: %d Samples\n", mp3FrameInfo.outputSamps );


   printf( "\nPlaying...\n" );

   //gfAudioPlayDMA( audioBuffer, frameSize * 4, GF_AUDIO_FORMAT_STEREO_16BIT, GF_AUDIO_FLAG_DMA_LOOP );

   gfAudioPlayFifo( audioBuffer, frameSize  );


   while( bytesLeft > 0 )
   {

       if( bytesLeft < 4096 )
       {
          nbr = readAndFillBuffer( mp3Buffer, currentMp3, MP3_FILE_BUFFER_SIZE, bytesLeft );

          bytesLeft += nbr;
          currentMp3 = mp3Buffer;

          if( !nbr )
          {
             break;
          }
       }

       offset = MP3FindSyncWord( currentMp3, bytesLeft ) ;

       if (offset < 0)
       {
           break;
       }

       currentMp3  += offset;
       bytesLeft   -= offset;

       MP3Decode( hMP3Decoder, &currentMp3, &bytesLeft, &audioBuffer[0], 0 );

       gfAudioPlayFifo( audioBuffer, frameSize );

   }

   osFClose( &in );

   printf( "done\n" );

   gfAudioStopDMA();

   do{
   }while( 1 );


}
