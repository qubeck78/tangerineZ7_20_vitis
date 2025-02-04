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
#include "osUIEvents.h"
#include "gfAudio.h"
#include "mp3dec.h"

#include "shellUI.h"

#include "mp3Player.h"

#define MP3_FILE_BUFFER_SIZE  65536
#define AUDIO_BUFFER_SIZE     65536


uint32_t mp3Init()
{

   return 0;
}


static uint32_t mp3ReadAndFillBuffer( tosFile *in, uint8_t *mp3Buffer, uint8_t *currentMp3, uint32_t mp3BufferSize, int32_t bytesLeft )
{
   uint32_t nbr;

   memmove( mp3Buffer, currentMp3, bytesLeft );

   osFRead( in, mp3Buffer + bytesLeft, mp3BufferSize - bytesLeft, &nbr );

   if( nbr < ( mp3BufferSize - bytesLeft ) )
   {
      memset( mp3Buffer + bytesLeft + nbr, 0, mp3BufferSize - bytesLeft - nbr );
   }

   return nbr;
}

uint32_t mp3Play( char *mp3FileName )
{
   uint32_t         nbr;

   tosFile          in;

   MP3FrameInfo     mp3FrameInfo;
   HMP3Decoder      hMP3Decoder;

   uint32_t         mp3Size;
   int              bytesLeft;
   int16_t         *audioBuffer;
   uint8_t         *mp3Buffer;
   uint8_t         *currentMp3;
   int32_t          offset;
   uint32_t         frameSize;

   char             buf[80];
   uint32_t         quitPlayer;
   tosUIEvent       event;

   uint32_t         i;
   uint32_t         j;
   uint32_t         uiRefreshCounter;
   uint32_t         mp3FilePosition;

   audioBuffer = ( int16_t * )osAlloc( 65536, OS_ALLOC_MEMF_CHIP );

   if( !audioBuffer )
   {
     printf( "Can't alloc audio buffer\n" );

    return 1;

   }

   hMP3Decoder = MP3InitDecoder();

   if( !hMP3Decoder )
   {
      printf( "Can't init mp3 decoder\n" );

      return 1;
   }


   gfAudioInit();

   mp3Size = osFSize( mp3FileName );

   if( !mp3Size )
   {
      printf( "Can't get size of %s - press pause to reboot\n", mp3FileName );

      return 1;
   }

   mp3Buffer   = (uint8_t*) osAlloc( MP3_FILE_BUFFER_SIZE, OS_ALLOC_MEMF_CHIP );


   if( !mp3Buffer )
   {
      printf( "Can't alloc %d bytes for mp3 file buffer - press pause to reboot\n", MP3_FILE_BUFFER_SIZE );

      return 1;
   }

//       printf( "%s ( %dMB )\n", mp3FileName, (int)( mp3Size / 1048576 ) );

   if( osFOpen( &in, mp3FileName, OS_FILE_READ ) )
   {

      printf( "Can't open %s - press pause to reboot\n", mp3FileName );

      return 1;
   }




   //read header

   nbr = 0;

   osFRead( &in, mp3Buffer, MP3_FILE_BUFFER_SIZE, &nbr );

   mp3FilePosition   = MP3_FILE_BUFFER_SIZE;

   bytesLeft         = MP3_FILE_BUFFER_SIZE;
   currentMp3        = mp3Buffer;

   //decode first frame

   offset = MP3FindSyncWord( currentMp3, bytesLeft ) ;

   //todo check if offset < 0

   currentMp3  += offset;
   bytesLeft   -= offset;

   MP3Decode( hMP3Decoder,&currentMp3, &bytesLeft, &audioBuffer[0], 0 );
   MP3GetLastFrameInfo( hMP3Decoder, &mp3FrameInfo );

   frameSize = mp3FrameInfo.outputSamps;

   gfAudioConfigure( mp3FrameInfo.samprate, 1 );

/*       printf( "Bitrate: %d kbps\n", mp3FrameInfo.bitrate / 1000 );
       printf( "Samplerate: %d Hz\n", mp3FrameInfo.samprate );
       printf( "Frame size: %d Samples\n", mp3FrameInfo.outputSamps );


       printf( "\nPlaying...\n" );
*/

   gfAudioPlayFifo( audioBuffer, frameSize  );


   quitPlayer        = 0;
   uiRefreshCounter  = 0;

   while( ( bytesLeft > 0 ) && ( quitPlayer == 0 ) )
   {

      if( uiRefreshCounter )
      {
         uiRefreshCounter--;
      }
      else
      {
         uiRefreshCounter = 10;

         //display info window

         strcpy( buf, "" );

         j = mp3FilePosition * 40 / mp3Size;

         for( i = 0; i < 40; i++ )
         {
            if( i >= j )
            {
               strcat( buf, "\xb0" );
            }
            else
            {
               strcat( buf, "\xb1" );
            }
         }

         uiDrawInfoWindow( mp3FileName, buf, _UI_INFO_WINDOW_BUTTONS_NONE );

         //check events
         while( !osGetUIEvent( &event ) )
         {
            if( event.type == OS_EVENT_TYPE_KEYBOARD_KEYPRESS )
            {

                  gfAudioStopDMA();
                  quitPlayer = 1;

            }
         }

      }

      if( bytesLeft < 4096 )
      {
         nbr = mp3ReadAndFillBuffer( &in, mp3Buffer, currentMp3, MP3_FILE_BUFFER_SIZE, bytesLeft );

         bytesLeft         += nbr;
         currentMp3        = mp3Buffer;
         mp3FilePosition   += nbr;

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

   osFree( audioBuffer );
   osFree( mp3Buffer );

   return 0;
}
