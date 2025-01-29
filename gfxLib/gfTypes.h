#ifndef _GFTYPES_H
#define _GFTYPES_H

#include <stdint.h>

//Version

#define _GFXLIB_VERSION 20250128


//Platform

//#define _GFXLIB_SDL
//#define _GFXLIB_STM32_FATFS
//#define _GFXLIB_ESP32_FFAT
#define _GFXLIB_RISCV_FATFS
#define _GFXLIB_ZYNQ7

//Features

//#define _GFXLIB_HW_BLITTER_2D
//#define _GFXLIB_HW_BLITTER_3D
//#define _GFXLIB_USB_HOST
#define _GFXLIB_PS2_HOST
//#define _GFXLIB_FPALU


#ifndef NULL
#define NULL 0
#endif


#define gfAbs(x) ((x)>0?(x):-(x))

#endif
