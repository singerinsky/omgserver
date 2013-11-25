################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../gate_server/CMsgDispatcher.cpp \
../gate_server/CSocketMap.cpp \
../gate_server/main.cpp 

OBJS += \
./gate_server/CMsgDispatcher.o \
./gate_server/CSocketMap.o \
./gate_server/main.o 

CPP_DEPS += \
./gate_server/CMsgDispatcher.d \
./gate_server/CSocketMap.d \
./gate_server/main.d 


# Each subdirectory must supply rules for building sources it contributes
gate_server/%.o: ../gate_server/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/guanlei/workspace/omgserver-code-0" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


