################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Alarm.c \
../src/ProjWek.c \
../src/RC5.c \
../src/RIT.c \
../src/RTC.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/display.c \
../src/somGenerator.c \
../src/states.c \
../src/timer.c 

OBJS += \
./src/Alarm.o \
./src/ProjWek.o \
./src/RC5.o \
./src/RIT.o \
./src/RTC.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/display.o \
./src/somGenerator.o \
./src/states.o \
./src/timer.o 

C_DEPS += \
./src/Alarm.d \
./src/ProjWek.d \
./src/RC5.d \
./src/RIT.d \
./src/RTC.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/display.d \
./src/somGenerator.d \
./src/states.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


