#include <stdio.h>
#include "osFile.h"
#include "bsp.h"

//osFile.c - zynq version

FATFS             fatfs;
static FILINFO    finfo;


uint32_t osFInit( void )
{
   FRESULT     frv;

   frv = f_mount( &fatfs, "0:/", 0 );

   if( frv != FR_OK )
   {
       printf( (char*)"ERROR: osFInit() f_mount failed\n" );
       return 1;
   }

   return 0;
}

uint32_t osFOpen( tosFile *file, char *path, uint32_t mode )
{

   FRESULT  res;
   BYTE     stmMode;


   if( !file )
   {
      return 1;
   }


   switch( mode )
   {
      case OS_FILE_READ:

         stmMode = FA_READ | FA_OPEN_EXISTING;
         break;

      case OS_FILE_WRITE:

         stmMode = FA_WRITE | FA_CREATE_ALWAYS;
         break;

      case OS_FILE_APPEND:

         stmMode = FA_OPEN_APPEND | FA_OPEN_EXISTING;
         
         break;

      default:

         return 2;
         break;
   }



   res = f_open( &file->fd, path, stmMode );

   if( res == FR_OK )
   {
      return 0;
   }
   else
   {
      return 3;
   }

}

uint32_t osFClose( tosFile *file )
{

   if( !file )
   {
      return 1;
   }

   f_close( &file->fd );

   return 0;

}

uint32_t osFWrite( tosFile *file, uint8_t *buffer, uint32_t numBytesToWrite )
{

   FRESULT res;
   UINT    nbw;

   
   if( ( !file ) || ( !buffer ) )
   {
      return 1;
   }

   res = f_write( &file->fd, buffer, numBytesToWrite, &nbw );

   if( res == FR_OK )
   {
      return 0;
   }
   else
   {
      return 2;
   }

}

uint32_t osFRead( tosFile *file, uint8_t *buffer, uint32_t numBytesToRead, uint32_t *numBytesRead )
{

   FRESULT res;
   UINT    nbr;



   if( ( !file ) || ( !buffer ) )
   {
      return 1;
   }


   res = f_read( &file->fd, buffer, numBytesToRead, &nbr );

   if( numBytesRead )
   {
      *numBytesRead = nbr;
   }

      if( nbr == numBytesToRead )
      {
         return 0;
      }
      else
      {
         return 2;
      }


}


uint32_t osFGetS( tosFile *file, uint8_t *buffer, uint32_t maxLength )
{
   uint8_t rbuf[4];
   uint32_t idx;
   uint32_t rv;
   uint32_t nbr;

   idx = 0;

   buffer[idx] = 0;
   do
   {
      rv = osFRead( file, rbuf, 1, &nbr );

      if( !rv )
      {
         if(( rbuf[0] == 0x0a ) || ( rbuf[0] == 0x0d ) )
         {
            break;
         }

         if( idx < maxLength - 1 )
         {
            buffer[idx++] = rbuf[0];
            buffer[idx] = 0;

         }

      }

   }while( !rv );


   return rv;
}

uint32_t osFSeek( tosFile *file, int32_t offset, uint32_t whence )
{

   FRESULT    rc;             

   if( file == NULL )
   {
      return 1;
   }

   switch( whence )
   {
      case OS_SEEK_SET: 
      
         rc = f_lseek( &file->fd, offset );
         
         if( rc != FR_OK )
         {
            return 1;
         }
         else
         {
            return 0;
         }

         break;

      default:
         //not supported yet
         return 1;
  }
 
}

uint32_t osDirOpen( tosDir *dir, char *path )
{

   FRESULT    rc;             


   if( dir == NULL )
   {
      return 1;
   }

   rc = f_opendir( &dir->dd, path );

   if( rc == FR_OK )
   {
      return 0;
   }
   else
   {
      return 1;
   }

   return 1;
}

uint32_t osDirClose( tosDir *dir )
{

   if( dir == NULL )
   {
      return 1;
   }


   return 0;


}

uint32_t osDirRead( tosDir *dir, tosDirItem *dirItem )
{
  
   FRESULT         rc;

   if( dirItem == NULL )
   {
      return 1;
   }

   if( dir == NULL )
   {      
      return 1;
   }


   //finfo.lfname = dirItem->name;
   //finfo.lfsize = 255;

   //clear long file name
   dirItem->name[0] = 0;

   rc = f_readdir( &dir->dd, &finfo );

   if( rc != FR_OK )
   {
      strcpy( dirItem->name, "" );
      dirItem->type  = OS_DIRITEM_NONE;
      dirItem->size  = 0;

      return 2;
   }
   else {
      strcpy( dirItem->name, finfo.fname );
   }

   if( finfo.fattrib & AM_DIR )
   {
      dirItem->type  = OS_DIRITEM_DIR;
      dirItem->size  = 0;
   }
   else
   {
      dirItem->type  = OS_DIRITEM_FILE;
      dirItem->size  = finfo.fsize;
   }

   //check if short file name
   if( dirItem->name[0] == 0 )
   {
      strcpy( dirItem->name, finfo.fname );

   }
   
   if( dirItem->name[0] != 0 )
   {
      return 0;
   }
   else
   {
      return 1;
   }

}

uint32_t osFSize( char *path )
{
   uint32_t rv;
   
   FRESULT  rc;
   FILINFO  fi;

   rv = 0;

   
   //lfn not used
   //fi.lfsize   = 0;
   //fi.lfname   = NULL;

   rc = f_stat( (const char*) path, &fi );

   if( rc == FR_OK )
   {
      rv = fi.fsize;
   }



   return rv;
}


uint32_t osFDelete( char *path )
{
   
   FRESULT  rc;

   rc = f_unlink( path );

   if( rc == FR_OK )
   {
      return 0;
   }
   else
   {
      return 1;
   }


   return 1;
}

uint32_t osMkDir( char *path )
{
   
   FRESULT  rc;

   rc = f_mkdir( path );

   if( rc == FR_OK )
   {
      return 0;
   }
   else
   {
      return 1;
   }

   return 1;
}

uint32_t osRename( char *pathOld, char *pathNew )
{
   
   FRESULT  rc;

   rc = f_rename( pathOld, pathNew );

   if( rc == FR_OK )
   {
      return 0;
   }
   else
   {
      return rc;
   }

   return 1;
   
}
