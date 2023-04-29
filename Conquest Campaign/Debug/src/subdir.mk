################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Conquest\ Campaign.cpp 

CPP_DEPS += \
./src/Conquest\ Campaign.d 

OBJS += \
./src/Conquest\ Campaign.o 


# Each subdirectory must supply rules for building sources it contributes
src/Conquest\ Campaign.o: ../src/Conquest\ Campaign.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Conquest Campaign.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Conquest\ Campaign.d ./src/Conquest\ Campaign.o

.PHONY: clean-src

