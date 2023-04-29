################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Peculiar\ primes.cpp 

CPP_DEPS += \
./src/Peculiar\ primes.d 

OBJS += \
./src/Peculiar\ primes.o 


# Each subdirectory must supply rules for building sources it contributes
src/Peculiar\ primes.o: ../src/Peculiar\ primes.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Peculiar primes.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Peculiar\ primes.d ./src/Peculiar\ primes.o

.PHONY: clean-src

