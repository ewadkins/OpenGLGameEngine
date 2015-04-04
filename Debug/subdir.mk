################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Camera.cpp \
../GLMatrix.cpp \
../Logger.cpp \
../Main.cpp \
../OpenGLApplication.cpp \
../Polynomial.cpp \
../Renderer.cpp \
../ShaderProgram.cpp 

OBJS += \
./Camera.o \
./GLMatrix.o \
./Logger.o \
./Main.o \
./OpenGLApplication.o \
./Polynomial.o \
./Renderer.o \
./ShaderProgram.o 

CPP_DEPS += \
./Camera.d \
./GLMatrix.d \
./Logger.d \
./Main.d \
./OpenGLApplication.d \
./Polynomial.d \
./Renderer.d \
./ShaderProgram.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/Cellar/glm/0.9.6.1/include -I/usr/local/Cellar/glew/1.11.0/include -I/usr/local/Cellar/glfw3/3.0.4/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


