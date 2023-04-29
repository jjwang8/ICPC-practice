################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Careful\ Ascent.cpp 

CPP_DEPS += \
./src/Careful\ Ascent.d 

OBJS += \
./src/Careful\ Ascent.o 


# Each subdirectory must supply rules for building sources it contributes
src/Careful\ Ascent.o: ../src/Careful\ Ascent.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Careful Ascent.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Careful\ Ascent.d ./src/Careful\ Ascent.o

.PHONY: clean-src

