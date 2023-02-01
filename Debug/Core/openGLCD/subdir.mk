################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/openGLCD/gText.cpp \
../Core/openGLCD/glcd.cpp \
../Core/openGLCD/glcd_Device.cpp 

OBJS += \
./Core/openGLCD/gText.o \
./Core/openGLCD/glcd.o \
./Core/openGLCD/glcd_Device.o 

CPP_DEPS += \
./Core/openGLCD/gText.d \
./Core/openGLCD/glcd.d \
./Core/openGLCD/glcd_Device.d 


# Each subdirectory must supply rules for building sources it contributes
Core/openGLCD/%.o Core/openGLCD/%.su: ../Core/openGLCD/%.cpp Core/openGLCD/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-openGLCD

clean-Core-2f-openGLCD:
	-$(RM) ./Core/openGLCD/gText.d ./Core/openGLCD/gText.o ./Core/openGLCD/gText.su ./Core/openGLCD/glcd.d ./Core/openGLCD/glcd.o ./Core/openGLCD/glcd.su ./Core/openGLCD/glcd_Device.d ./Core/openGLCD/glcd_Device.o ./Core/openGLCD/glcd_Device.su

.PHONY: clean-Core-2f-openGLCD

