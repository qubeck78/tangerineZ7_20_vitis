#include "bsp.h"
#include "osAlloc.h"
#include "osFile.h"
#include "gfFont.h"
#include "gfBitmap.h"
#include "gfJPEG.h"
#include "gfDrawing.h"


//#include "sleep.h"
#include <stdint.h>
#include <stddef.h>  // for size_t
#include <unistd.h>  // for STDERR_FILENO

uint32_t    randomSeed = 3242323459;

tgfTextOverlay  con;

_BSP_T 		               *bsp 		      = (_BSP_T *)0x42000000;
_PS2HOST_T 	               *ps2Host	      = (_PS2HOST_T*)0x43000000;
_AUDIO_REGISTERS_T         *aud           = (_AUDIO_REGISTERS_T*)0x44000000;
_GFXPIXELGEN_REGISTERS_T   *gfxPixelGen   = (_GFXPIXELGEN_REGISTERS_T *)0x45000000;

#ifdef __cplusplus
extern "C" 
#endif
int _write ( int file, const void * ptr, size_t len ) 
{
    char        buf[4];
    uint32_t    i;

    if( ( file == STDOUT_FILENO ) || ( file == STDERR_FILENO ) )
    {

        buf[1] = 0;

        for( i = 0; i < len; i++ )
        {
            buf[0] = ((char*)ptr)[i];
            toPrint( &con, buf );
        }

        return len;
    }
    else
    {
        return 0;
    }
}


uint32_t bspInit()
{
   bsp->videoMuxMode       = _VIDEOMODE_320_TEXT80_OVER_GFX; 

   //connect gfxlib con to hardware text overlay   
   con.type                = GF_TEXT_OVERLAY_TYPE_HARDWARE;
   con.flags               = 0;
   con.width               = 80;               //clear whole buffer
   con.height              = 60;
   con.cursX               = 0;
   con.cursY               = 0;
   con.textAttributes      = 0x0f;
   con.font                = NULL;
   con.textBuffer          = (uint8_t*) 0x40000000;

   toCls( &con );

   con.textAttributes   = 0x8f;
   con.height           = 30;

   //init alloc mechanism, use last 64MB of DDR3 memory
   
   //in ldscript.ld change ddr size to 0x1bf00000
   //to free last 64MB used in dynamic allocation

   osAllocInit();
   osAllocAddNode( 0, ( void* )_SYSTEM_MEMORY_BASE, _SYSTEM_MEMORY_SIZE, OS_ALLOC_MEMF_CHIP );

   randomSeed += getTicks();

   return 0;
}

uint32_t randomNumber()
{
    uint32_t r = randomSeed;

    r ^= r << 13;
    r ^= r >> 17;
    r ^= r << 5;

    randomSeed = r;

    return r;

/* 
    //https://github.com/cmcqueen/simplerandom/blob/main/c/lecuyer/lfsr88.c
   uint32_t b;

    b = (((s1 << 13) ^ s1) >> 19);
    s1 = (((s1 & 4294967294) << 12) ^ b);
    b = (((s2 << 2) ^ s2) >> 25);
    s2 = (((s2 & 4294967288) << 4) ^ b);
    b = (((s3 << 3) ^ s3) >> 11);
    s3 = (((s3 & 4294967280) << 17) ^ b);
    return (s1 ^ s2 ^ s3);
    */
} 

void hexDigit(char *string,char digit)
{
    digit &= 0x0f;
    
    if( digit<10 )
    {
        string[0] = digit + '0';
        string[1] = 0;
    }
    else
    {
        string[0] = digit + 'a' - 10;
        string[1] = 0;
    }
}

void itoaHex2Digits( uint32_t value, char* str )
{
    hexDigit(&str[0], ( value >> 4 ) & 0x0f );
    hexDigit(&str[1], ( value ) & 0x0f );
}

void itoaHex4Digits( uint32_t value, char* str )
{
    hexDigit(&str[4], ( value >> 12 ) & 0x0f );
    hexDigit(&str[5], ( value >> 8 ) & 0x0f );

    hexDigit(&str[6], ( value >> 4) & 0x0f );
    hexDigit(&str[7], ( value ) & 0x0f );
}


void itoaHex8Digits( uint32_t value, char* str )
{
    hexDigit(&str[0], ( value >> 28 ) & 0x0f );
    hexDigit(&str[1], ( value >> 24 ) & 0x0f );

    hexDigit(&str[2], ( value >> 20 ) & 0x0f );
    hexDigit(&str[3], ( value >> 16 ) & 0x0f );

    hexDigit(&str[4], ( value >> 12 ) & 0x0f );
    hexDigit(&str[5], ( value >> 8 ) & 0x0f );

    hexDigit(&str[6], ( value >> 4) & 0x0f );
    hexDigit(&str[7], ( value ) & 0x0f );
}

uint32_t getTicks()
{
   return bsp->tickTimerValue;
}

void delayMs( uint32_t delay )
{
    uint32_t startMs;
    
    startMs = bsp->tickTimerValue;
    
    while( bsp->tickTimerValue < ( startMs + delay ) );
}

uint32_t setVideoMode( uint32_t videoMode )
{
   bsp->videoMuxMode = videoMode;

   //check textmode: 40 or 80 column and adjust console width
   if( ( ( videoMode >> 2) & 3 ) == 1 )
   {
     con.width = 80;
   }
   else
   {
     con.width = 40;
   }


   //check texmode 30 or 60 rows and adjust console height
   if( ( ( videoMode >> 2 ) & 3 ) == 3 )
   {
      con.height = 60;
   }
   else
   {
      con.height = 30;
   }

   if( videoMode & 0x10 )
   {

       //640 x 480

       //line width = 2048 bytes
       //
       bsp->ch0DmaRequest0PtrAdd = 640;
       bsp->ch0DmaRequest1PtrAdd = 640 + 768;

       //dma request length: 160 long words ( 2 requests per line )
       bsp->ch0DmaRequestLength     = 0x9f;
   }
   else
   {
       //320 x 240

       if( videoMode & 0x20 )
       {
           //8bpp

           //512 bytes odd/even requests
           bsp->ch0DmaRequest0PtrAdd = 512;
           bsp->ch0DmaRequest1PtrAdd = 512;

           //dma request length: 80 long words ( 1 request per two lines )
           bsp->ch0DmaRequestLength  = 0x4f;

       }
       else
       {
           //16bpp

           //1024 bytes odd/even requests
            bsp->ch0DmaRequest0PtrAdd = 1024;
            bsp->ch0DmaRequest1PtrAdd = 1024;

           //dma request length: 160 long words ( 1 request per two lines )
            bsp->ch0DmaRequestLength  = 0x9f;
       }
   }


   return 0;
}


