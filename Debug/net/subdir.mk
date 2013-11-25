################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../net/CMsgDispatcher.cpp \
../net/epoll_handler.cpp \
../net/epoll_socket.cpp \
../net/socket_epoll.cpp \
../net/thread.cpp 

OBJS += \
./net/CMsgDispatcher.o \
./net/epoll_handler.o \
./net/epoll_socket.o \
./net/socket_epoll.o \
./net/thread.o 

CPP_DEPS += \
./net/CMsgDispatcher.d \
./net/epoll_handler.d \
./net/epoll_socket.d \
./net/socket_epoll.d \
./net/thread.d 


# Each subdirectory must supply rules for building sources it contributes
net/%.o: ../net/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/guanlei/workspace/omgserver-code-0" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


