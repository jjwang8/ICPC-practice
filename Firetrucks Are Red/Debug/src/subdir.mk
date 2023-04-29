################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Firetrucks\ Are\ Red.cpp 

CPP_DEPS += \
./src/Firetrucks\ Are\ Red.d 

OBJS += \
./src/Firetrucks\ Are\ Red.o 


# Each subdirectory must supply rules for building sources it contributes
src/Firetrucks\ Are\ Red.o: ../src/Firetrucks\ Are\ Red.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Firetrucks Are Red.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Firetrucks\ Are\ Red.d ./src/Firetrucks\ Are\ Red.o

.PHONY: clean-src

