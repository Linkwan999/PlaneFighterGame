################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bitmap/bg1.c \
../Bitmap/bg2.c \
../Bitmap/bg3.c \
../Bitmap/bg4.c \
../Bitmap/blast1.c \
../Bitmap/blast2.c \
../Bitmap/blast3.c \
../Bitmap/blast4.c \
../Bitmap/blast5.c \
../Bitmap/bombshoot.c \
../Bitmap/enemyfly.c \
../Bitmap/gameover.c \
../Bitmap/intro.c \
../Bitmap/planefront.c \
../Bitmap/planestatic.c 

C_DEPS += \
./Bitmap/bg1.d \
./Bitmap/bg2.d \
./Bitmap/bg3.d \
./Bitmap/bg4.d \
./Bitmap/blast1.d \
./Bitmap/blast2.d \
./Bitmap/blast3.d \
./Bitmap/blast4.d \
./Bitmap/blast5.d \
./Bitmap/bombshoot.d \
./Bitmap/enemyfly.d \
./Bitmap/gameover.d \
./Bitmap/intro.d \
./Bitmap/planefront.d \
./Bitmap/planestatic.d 

OBJS += \
./Bitmap/bg1.o \
./Bitmap/bg2.o \
./Bitmap/bg3.o \
./Bitmap/bg4.o \
./Bitmap/blast1.o \
./Bitmap/blast2.o \
./Bitmap/blast3.o \
./Bitmap/blast4.o \
./Bitmap/blast5.o \
./Bitmap/bombshoot.o \
./Bitmap/enemyfly.o \
./Bitmap/gameover.o \
./Bitmap/intro.o \
./Bitmap/planefront.o \
./Bitmap/planestatic.o 


# Each subdirectory must supply rules for building sources it contributes
Bitmap/%.o: ../Bitmap/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon.no_vfp --arm -I"C:\Users\linri\Workspace\ELEC5620M-Resources\Drivers" -O0 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="Bitmap" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


