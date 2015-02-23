################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Logger.cpp \
../Main.cpp \
../OpenGLApplication.cpp \
../Renderer.cpp \
../ShaderProgram.cpp 

OBJS += \
./Logger.o \
./Main.o \
./OpenGLApplication.o \
./Renderer.o \
./ShaderProgram.o 

CPP_DEPS += \
./Logger.d \
./Main.d \
./OpenGLApplication.d \
./Renderer.d \
./ShaderProgram.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/Cellar/glm/0.9.6.1/include -I/usr/local/Cellar/glew/1.11.0/include -I/usr/local/Cellar/glfw3/3.0.4/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


