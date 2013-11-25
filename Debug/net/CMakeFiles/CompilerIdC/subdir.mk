################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../net/CMakeFiles/CompilerIdC/CMakeCCompilerId.c 

OBJS += \
./net/CMakeFiles/CompilerIdC/CMakeCCompilerId.o 

C_DEPS += \
./net/CMakeFiles/CompilerIdC/CMakeCCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
net/CMakeFiles/CompilerIdC/%.o: ../net/CMakeFiles/CompilerIdC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


