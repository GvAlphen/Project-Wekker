################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Project_Microcontroller_MT.axf

# Tool invocations
Project_Microcontroller_MT.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="Project_Microcontroller_MT.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "Project_Microcontroller_MT_Debug.ld" -o "Project_Microcontroller_MT.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) Project_Microcontroller_MT.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Project_Microcontroller_MT.axf"; # arm-none-eabi-objcopy -v -O binary "Project_Microcontroller_MT.axf" "Project_Microcontroller_MT.bin" ; # checksum -p LPC1769 -d "Project_Microcontroller_MT.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
