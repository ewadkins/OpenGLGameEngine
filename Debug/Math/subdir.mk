################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Math/Complex.cpp \
../Math/ComplexMatrix.cpp \
../Math/GLMatrix.cpp \
../Math/Matrix.cpp \
../Math/Polynomial.cpp \
../Math/PolynomialMatrix.cpp \
../Math/Vector.cpp 

OBJS += \
./Math/Complex.o \
./Math/ComplexMatrix.o \
./Math/GLMatrix.o \
./Math/Matrix.o \
./Math/Polynomial.o \
./Math/PolynomialMatrix.o \
./Math/Vector.o 

CPP_DEPS += \
./Math/Complex.d \
./Math/ComplexMatrix.d \
./Math/GLMatrix.d \
./Math/Matrix.d \
./Math/Polynomial.d \
./Math/PolynomialMatrix.d \
./Math/Vector.d 


# Each subdirectory must supply rules for building sources it contributes
Math/%.o: ../Math/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/Cellar/glm/0.9.6.1/include -I/usr/local/Cellar/glew/1.11.0/include -I/usr/local/Cellar/glfw3/3.0.4/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


