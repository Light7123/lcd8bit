################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/openGLCD/bitmaps/utils/bmp2glcd/bmp2glcd.cpp 

OBJS += \
./Core/openGLCD/bitmaps/utils/bmp2glcd/bmp2glcd.o 

CPP_DEPS += \
./Core/openGLCD/bitmaps/utils/bmp2glcd/bmp2glcd.d 


# Each subdirectory must supply rules for building sources it contributes
Core/openGLCD/bitmaps/utils/bmp2glcd/%.o Core/openGLCD/bitmaps/utils/bmp2glcd/%.su: ../Core/openGLCD/bitmaps/utils/bmp2glcd/%.cpp Core/openGLCD/bitmaps/utils/bmp2glcd/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-openGLCD-2f-bitmaps-2f-utils-2f-bmp2glcd

clean-Core-2f-openGLCD-2f-bitmaps-2f-utils-2f-bmp2glcd:
	-$(RM) ./Core/openGLCD/bitmaps/utils/bmp2glcd/bmp2glcd.d ./Core/openGLCD/bitmaps/utils/bmp2glcd/bmp2glcd.o ./Core/openGLCD/bitmaps/utils/bmp2glcd/bmp2glcd.su

.PHONY: clean-Core-2f-openGLCD-2f-bitmaps-2f-utils-2f-bmp2glcd

