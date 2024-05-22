################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FocLib/bldcMotor.c \
../FocLib/current.c \
../FocLib/encoder.c \
../FocLib/lowpass_filter.c \
../FocLib/math_utils.c \
../FocLib/pid.c \
../FocLib/voltage.c 

OBJS += \
./FocLib/bldcMotor.o \
./FocLib/current.o \
./FocLib/encoder.o \
./FocLib/lowpass_filter.o \
./FocLib/math_utils.o \
./FocLib/pid.o \
./FocLib/voltage.o 

C_DEPS += \
./FocLib/bldcMotor.d \
./FocLib/current.d \
./FocLib/encoder.d \
./FocLib/lowpass_filter.d \
./FocLib/math_utils.d \
./FocLib/pid.d \
./FocLib/voltage.d 


# Each subdirectory must supply rules for building sources it contributes
FocLib/%.o FocLib/%.su FocLib/%.cyclo: ../FocLib/%.c FocLib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I"C:/Users/Administrator/Desktop/FOC/firmware/User" -I"C:/Users/Administrator/Desktop/FOC/firmware/FocLib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FocLib

clean-FocLib:
	-$(RM) ./FocLib/bldcMotor.cyclo ./FocLib/bldcMotor.d ./FocLib/bldcMotor.o ./FocLib/bldcMotor.su ./FocLib/current.cyclo ./FocLib/current.d ./FocLib/current.o ./FocLib/current.su ./FocLib/encoder.cyclo ./FocLib/encoder.d ./FocLib/encoder.o ./FocLib/encoder.su ./FocLib/lowpass_filter.cyclo ./FocLib/lowpass_filter.d ./FocLib/lowpass_filter.o ./FocLib/lowpass_filter.su ./FocLib/math_utils.cyclo ./FocLib/math_utils.d ./FocLib/math_utils.o ./FocLib/math_utils.su ./FocLib/pid.cyclo ./FocLib/pid.d ./FocLib/pid.o ./FocLib/pid.su ./FocLib/voltage.cyclo ./FocLib/voltage.d ./FocLib/voltage.o ./FocLib/voltage.su

.PHONY: clean-FocLib

