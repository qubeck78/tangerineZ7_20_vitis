
#include "osSerial.h"

#ifdef _GFXLIB_ZYNQ7

#include "xparameters.h"
#include "platform_config.h"
#include "xuartps.h"

XUartPs uartZynq;

//https://github.com/Xilinx/embeddedsw/blob/master/XilinxProcessorIPLib/drivers/uartps/examples/xuartps_polled_example.c

#endif


#include "bsp.h"

extern _UART_REGISTERS_T   *uart0;




uint32_t osSerialOpen( uint32_t serialNum, uint32_t baudRate )
{

   #ifdef _GFXLIB_ZYNQ7

      XUartPs_Config *config;

      config = XUartPs_LookupConfig( UART_DEVICE_ID );
      XUartPs_CfgInitialize( &uartZynq, config, config->BaseAddress );
      XUartPs_SetOperMode( &uartZynq, XUARTPS_OPER_MODE_NORMAL );

      return 0;

   #endif

   return 1;
}

uint32_t osSerialClose( uint32_t serialNum )
{

   return 0;
}


int32_t  osSerialGetC( uint32_t serialNum )
{

   #ifdef _GFXLIB_ZYNQ7

      uint32_t rxb;
      uint8_t  rxBuf;

      rxb = XUartPs_Recv( &uartZynq, &rxBuf, 1 );

      if( rxb )
      {
         return rxBuf;
      }
      else
      {
         return -1;
      }

   #endif

   return -1;
}

uint32_t osSerialClearRxFifo( uint32_t serialNum )
{
   while( osSerialGetC( serialNum ) != -1 );

   return 0;
}

uint32_t osSerialPutC( uint32_t serialNum, uint8_t c )
{

   #ifdef _GFXLIB_ZYNQ7

      XUartPs_Send( &uartZynq, &c, 1 );

      return 0;

   #endif

   return 1;

}

uint32_t osSerialGetS( uint32_t serialNum, char *buf, uint32_t maxLength, uint32_t timeoutMs )
{
   uint32_t idx;   
   char  c;
   int32_t  rv;
   uint32_t startTicks;

   idx = 0;
   
   if( buf == NULL ) return 1;

   buf[0] = 0;

   startTicks = getTicks();

   do
   {

      do
      {
         
         rv = osSerialGetC( serialNum );

         if( getTicks() > startTicks + timeoutMs )
         {

            //timeout
            return 2;

         }

      }while( rv == -1 );

      c = (char) rv & 0xff;

      if( ( c != 13 ) && ( c != 10 ) )
      {
         if( idx < ( maxLength - 1 ) )
         {
            buf[idx++]  = c;
            buf[idx]    = 0;
         }
         else
         {
            //buffer overflow
            return 3;
         }
      }
      
   }while( c != 10 );

   return 0;
}

uint32_t osSerialPrint( uint32_t serialNum, char *buf )
{
   char c;

   if( buf == NULL ) 
   {
      return 1;
   }

   while( c = *buf++ )
   {
      osSerialPutC( serialNum, c );
   }

   return 0;

}
