################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/bsp.c \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/gfAudio.c \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/gfBitmap.c \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/gfDrawing.c \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/gfFont.c \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/gfGouraud.c \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/gfJPEG.c \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/osAlloc.c \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/osFile.c \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/osSerial.c \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/osUIEvents.c \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/picojpeg.c \
C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/ps2Host.c 

OBJS += \
./src/gfxLib/bsp.o \
./src/gfxLib/gfAudio.o \
./src/gfxLib/gfBitmap.o \
./src/gfxLib/gfDrawing.o \
./src/gfxLib/gfFont.o \
./src/gfxLib/gfGouraud.o \
./src/gfxLib/gfJPEG.o \
./src/gfxLib/osAlloc.o \
./src/gfxLib/osFile.o \
./src/gfxLib/osSerial.o \
./src/gfxLib/osUIEvents.o \
./src/gfxLib/picojpeg.o \
./src/gfxLib/ps2Host.o 

C_DEPS += \
./src/gfxLib/bsp.d \
./src/gfxLib/gfAudio.d \
./src/gfxLib/gfBitmap.d \
./src/gfxLib/gfDrawing.d \
./src/gfxLib/gfFont.d \
./src/gfxLib/gfGouraud.d \
./src/gfxLib/gfJPEG.d \
./src/gfxLib/osAlloc.d \
./src/gfxLib/osFile.d \
./src/gfxLib/osSerial.d \
./src/gfxLib/osUIEvents.d \
./src/gfxLib/picojpeg.d \
./src/gfxLib/ps2Host.d 


# Each subdirectory must supply rules for building sources it contributes
src/gfxLib/bsp.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/bsp.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gfxLib/gfAudio.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/gfAudio.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gfxLib/gfBitmap.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/gfBitmap.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gfxLib/gfDrawing.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/gfDrawing.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gfxLib/gfFont.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/gfFont.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gfxLib/gfGouraud.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/gfGouraud.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gfxLib/gfJPEG.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/gfJPEG.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gfxLib/osAlloc.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/osAlloc.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gfxLib/osFile.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/osFile.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gfxLib/osSerial.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/osSerial.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gfxLib/osUIEvents.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/osUIEvents.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gfxLib/picojpeg.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/picojpeg.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gfxLib/ps2Host.o: C:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/gfxLib/ps2Host.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


