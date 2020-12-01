################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/gameoflife.cpp \
../src/gameoflife_test.cpp \
../src/main.cpp \
../src/renderingengine.cpp 

OBJS += \
./src/gameoflife.o \
./src/gameoflife_test.o \
./src/main.o \
./src/renderingengine.o 

CPP_DEPS += \
./src/gameoflife.d \
./src/gameoflife_test.d \
./src/main.d \
./src/renderingengine.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


