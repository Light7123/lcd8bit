################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/openGLCD/bitmaps/utils/bmp2glcd/EasyBMP/EasyBMP.cpp 

OBJS += \
./Core/openGLCD/bitmaps/utils/bmp2glcd/EasyBMP/EasyBMP.o 

CPP_DEPS += \
./Core/openGLCD/bitmaps/utils/bmp2glcd/EasyBMP/EasyBMP.d 


# Each subdirectory must supply rules for building sources it contributes
Core/openGLCD/bitmaps/utils/bmp2glcd/EasyBMP/%.o Core/openGLCD/bitmaps/utils/bmp2glcd/EasyBMP/%.su: ../Core/openGLCD/bitmaps/utils/bmp2glcd/EasyBMP/%.cpp Core/openGLCD/bitmaps/utils/bmp2glcd/EasyBMP/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F107xC -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-openGLCD-2f-bitmaps-2f-utils-2f-bmp2glcd-2f-EasyBMP

clean-Core-2f-openGLCD-2f-bitmaps-2f-utils-2f-bmp2glcd-2f-EasyBMP:
	-$(RM) ./Core/openGLCD/bitmaps/utils/bmp2glcd/EasyBMP/EasyBMP.d ./Core/openGLCD/bitmaps/utils/bmp2glcd/EasyBMP/EasyBMP.o ./Core/openGLCD/bitmaps/utils/bmp2glcd/EasyBMP/EasyBMP.su

.PHONY: clean-Core-2f-openGLCD-2f-bitmaps-2f-utils-2f-bmp2glcd-2f-EasyBMP

