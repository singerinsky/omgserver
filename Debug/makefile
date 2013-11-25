################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include ut/subdir.mk
-include net/subdir.mk
-include net/CMakeFiles/CompilerIdCXX/subdir.mk
-include net/CMakeFiles/CompilerIdC/subdir.mk
-include gate_server/subdir.mk
-include gate_server/build/objs/net/CMakeFiles/net.dir/subdir.mk
-include gate_server/build/CMakeFiles/gate_server.dir/home/guanlei/workspace/omgserver-code-0/gate_server/subdir.mk
-include gate_server/build/CMakeFiles/CompilerIdCXX/subdir.mk
-include gate_server/build/CMakeFiles/CompilerIdC/subdir.mk
-include client/subdir.mk
-include build/CMakeFiles/CompilerIdCXX/subdir.mk
-include build/CMakeFiles/CompilerIdC/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: omgserver-code-0

# Tool invocations
omgserver-code-0: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o"omgserver-code-0" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) omgserver-code-0
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
