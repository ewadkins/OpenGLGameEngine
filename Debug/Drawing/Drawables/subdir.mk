################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drawing/Drawables/Drawable.cpp \
../Drawing/Drawables/Triangle.cpp 

OBJS += \
./Drawing/Drawables/Drawable.o \
./Drawing/Drawables/Triangle.o 

CPP_DEPS += \
./Drawing/Drawables/Drawable.d \
./Drawing/Drawables/Triangle.d 


# Each subdirectory must supply rules for building sources it contributes
Drawing/Drawables/%.o: ../Drawing/Drawables/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/Cellar/glm/0.9.6.1/include -I/usr/local/Cellar/glew/1.11.0/include -I/usr/local/Cellar/glfw3/3.0.4/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


