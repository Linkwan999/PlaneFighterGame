################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/linri/Workspace/ELEC5620M-Resources/Drivers/FatFS/hwlib/alt_clock_manager.c \
C:/Users/linri/Workspace/ELEC5620M-Resources/Drivers/FatFS/hwlib/alt_sdmmc.c 

C_DEPS += \
./Drivers/FatFS/hwlib/alt_clock_manager.d \
./Drivers/FatFS/hwlib/alt_sdmmc.d 

OBJS += \
./Drivers/FatFS/hwlib/alt_clock_manager.o \
./Drivers/FatFS/hwlib/alt_sdmmc.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/FatFS/hwlib/alt_clock_manager.o: C:/Users/linri/Workspace/ELEC5620M-Resources/Drivers/FatFS/hwlib/alt_clock_manager.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon.no_vfp --arm -I"C:\Users\linri\Workspace\ELEC5620M-Resources\Drivers" -O0 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="Drivers/FatFS/hwlib" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/FatFS/hwlib/alt_sdmmc.o: C:/Users/linri/Workspace/ELEC5620M-Resources/Drivers/FatFS/hwlib/alt_sdmmc.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon.no_vfp --arm -I"C:\Users\linri\Workspace\ELEC5620M-Resources\Drivers" -O0 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="Drivers/FatFS/hwlib" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


