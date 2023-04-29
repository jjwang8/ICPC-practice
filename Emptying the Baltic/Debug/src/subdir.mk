################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Emptying\ the\ Baltic.cpp 

CPP_DEPS += \
./src/Emptying\ the\ Baltic.d 

OBJS += \
./src/Emptying\ the\ Baltic.o 


# Each subdirectory must supply rules for building sources it contributes
src/Emptying\ the\ Baltic.o: ../src/Emptying\ the\ Baltic.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Emptying the Baltic.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Emptying\ the\ Baltic.d ./src/Emptying\ the\ Baltic.o

.PHONY: clean-src

