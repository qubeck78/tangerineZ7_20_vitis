################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/gf3dEngine.c \
../src/main.c \
../src/platform.c 

OBJS += \
./src/gf3dEngine.o \
./src/main.o \
./src/platform.o 

C_DEPS += \
./src/gf3dEngine.d \
./src/main.d \
./src/platform.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O2 -g3 -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gf3dEngineTest\src" -I"C:\Users\qubeck\Documents\Development\ProjektyVitis\TangerineZ7_20\gfxLib" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/Users/qubeck/Documents/Development/ProjektyVitis/TangerineZ7_20/tangerineZ7_20_wrapper/export/tangerineZ7_20_wrapper/sw/tangerineZ7_20_wrapper/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


