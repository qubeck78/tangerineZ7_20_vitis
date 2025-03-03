
#include "modPlayer.h"

#include <stdio.h>

//HxCModPlayer
//https://github.com/jfdelnero/HxCModPlayer

//sdl audio
////https://gist.github.com/armornick/3447121

#include "hxcmod.h"

#include "bsp.h"

#include "osAlloc.h"
#include "osFile.h"
#include "gfFont.h"
#include "osUIEvents.h"
#include "gfAudio.h"
#include "shellUI.h"


modcontext  modctx;
int16_t    *audioData;
uint32_t   *audioDataLong;
uint32_t    audioDataLength;
int16_t    *audioDataL;
int16_t    *audioDataH;

int16_t    *audioModData;
uint32_t    audioModDataLength;

uint32_t    audioSupported;

uint32_t mpInit()
{
   uint32_t rv;


   rv = gfAudioInit();

   if( rv )
   {
      audioSupported = 0;
   }
   else
   {
      audioSupported = 1;
   }

   //config audio ( 24kHz )
   //gfAudioConfigure( GF_AUDIO_SAMPLING_RATE_48000, 2 );

   //config audio ( 44.1kHz )
   gfAudioConfigure( GF_AUDIO_SAMPLING_RATE_44100, 1 );


   //alloc audio buffer
   audioDataLength      = 16384;   //8K samples

   audioData            = (short*)osAlloc( audioDataLength, OS_ALLOC_MEMF_CHIP ); 

   audioDataL           = &audioData[0];
   audioDataH           = &audioData[audioDataLength / 4];
   audioDataLong        = (uint32_t*)&audioData[0];


   return rv;
}

uint32_t mpPlay( char *fileName )
{
   uint32_t    rv;
   tosUIEvent  event; 
   tosFile     in;
   uint32_t    nbr;
   uint32_t    audioDmaStatus;
   uint32_t    quitPlayer;
   char        buf[80];
   uint32_t    i;
   uint32_t    j;


   if( !audioSupported )
   {
      return 1;
   }

   //init hxcmod
   hxcmod_init( &modctx );

   //config hxcmod 24kHz
   //hxcmod_setcfg( &modctx, 48000 / 2, 0, 0 );

   //config hxcmod 44.1kHz
   hxcmod_setcfg( &modctx, 44100, 0, 0 );


   uiDrawInfoWindow( (char*)"Loading", fileName, _UI_INFO_WINDOW_BUTTONS_NONE );


   audioModDataLength = osFSize( fileName );

   if( audioModDataLength  == 0 )
   {
      return 1;
   }

   audioModData = (short*)osAlloc( audioModDataLength, OS_ALLOC_MEMF_CHIP );

   if( !audioModData )
   {
      return 1;
   }

   if( osFOpen( &in, fileName, OS_FILE_READ ) )
   {

      osFree( audioModData );
      audioModData = NULL;

      return 1;

   }

   osFRead( &in, (uint8_t*)audioModData, audioModDataLength, &nbr );

   osFClose( &in );

   hxcmod_load( &modctx, (void*)audioModData, audioModDataLength  );

   //pre-fill lower part of the buffer
   //length in samples ( 2 x 16-bit, l + r ) -> half of the buffer
   hxcmod_fillbuffer( &modctx, audioDataL, audioDataLength / 8, NULL ); 

   quitPlayer = 0;

   //FIFO audio player
   do
   {


      if( modctx.song.length > 0 )
      {
         j =  modctx.tablepos * 40 / modctx.song.length;
      }
      else
      {
         j = 0;
      }

      strcpy( buf, "" );
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

      uiDrawInfoWindow( fileName, buf, _UI_INFO_WINDOW_BUTTONS_NONE );

      //write samples to queue, length in samples
      gfAudioPlayFifo( audioDataL, audioDataLength / 4 );

      //re-fill buffer - length in 2x samples (l+r)
      hxcmod_fillbuffer( &modctx, audioDataL, audioDataLength / 8, NULL );


      while( !osGetUIEvent( &event ) )
      {
         if( event.type == OS_EVENT_TYPE_KEYBOARD_KEYPRESS )
         {

               gfAudioStopDMA();
               quitPlayer = 1;

         }
      }

   }while( !quitPlayer );


   //DMA Player
/*
   gfAudioPlayDMA( audioData, audioDataLength, GF_AUDIO_FORMAT_STEREO_16BIT, GF_AUDIO_FLAG_DMA_LOOP );


   do
   {


      if( modctx.song.length > 0 )
      {
         j =  modctx.tablepos * 40 / modctx.song.length;
      }
      else
      {
         j = 0;
      }

      strcpy( buf, "" );
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

      uiDrawInfoWindow( fileName, buf, _UI_INFO_WINDOW_BUTTONS_NONE );

      do{
      }while( gfAudioDMAStatus() & GF_AUDIO_DMA_STATUS_SECOND_HALF );


      //lower part of buffer is played, fill upper
      hxcmod_fillbuffer( &modctx, audioDataH, audioDataLength / 8, NULL );

      do{
      }while( ! ( gfAudioDMAStatus() & GF_AUDIO_DMA_STATUS_SECOND_HALF ) );

      //upper part of buffer is played, fill lower
      hxcmod_fillbuffer( &modctx, audioDataL, audioDataLength / 8, NULL );

   
      while( !osGetUIEvent( &event ) )
      { 
         if( event.type == OS_EVENT_TYPE_KEYBOARD_KEYPRESS )
         {

               gfAudioStopDMA();
               quitPlayer = 1;

         }
      }

   }while( !quitPlayer );
*/
   osFree( audioModData );
   audioModData = NULL;

   return 0;
}
