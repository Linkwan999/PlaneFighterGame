################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SevenSeg/SevenSeg.c 

C_DEPS += \
./SevenSeg/SevenSeg.d 

OBJS += \
./SevenSeg/SevenSeg.o 


# Each subdirectory must supply rules for building sources it contributes
SevenSeg/%.o: ../SevenSeg/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon.no_vfp --arm -I"C:\Users\linri\Workspace\ELEC5620M-Resources\Drivers" -O0 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="SevenSeg" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


