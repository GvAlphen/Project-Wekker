################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Project_Microcontroller_MT.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/display.c 

OBJS += \
./src/Project_Microcontroller_MT.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/display.o 

C_DEPS += \
./src/Project_Microcontroller_MT.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/display.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


