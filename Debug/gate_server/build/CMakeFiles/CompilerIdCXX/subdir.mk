################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../gate_server/build/CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.cpp 

OBJS += \
./gate_server/build/CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.o 

CPP_DEPS += \
./gate_server/build/CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
gate_server/build/CMakeFiles/CompilerIdCXX/%.o: ../gate_server/build/CMakeFiles/CompilerIdCXX/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/guanlei/workspace/omgserver-code-0" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


