################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/focLib/bldcMotor.c \
../User/focLib/current.c \
../User/focLib/encoder.c \
../User/focLib/lowpass_filter.c \
../User/focLib/math_utils.c \
../User/focLib/pid.c \
../User/focLib/voltage.c 

OBJS += \
./User/focLib/bldcMotor.o \
./User/focLib/current.o \
./User/focLib/encoder.o \
./User/focLib/lowpass_filter.o \
./User/focLib/math_utils.o \
./User/focLib/pid.o \
./User/focLib/voltage.o 

C_DEPS += \
./User/focLib/bldcMotor.d \
./User/focLib/current.d \
./User/focLib/encoder.d \
./User/focLib/lowpass_filter.d \
./User/focLib/math_utils.d \
./User/focLib/pid.d \
./User/focLib/voltage.d 


# Each subdirectory must supply rules for building sources it contributes
User/focLib/%.o User/focLib/%.su User/focLib/%.cyclo: ../User/focLib/%.c User/focLib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -I"C:/Users/Administrator/Desktop/FOC/firmware/User/focLib" -I"C:/Users/Administrator/Desktop/FOC/firmware/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User-2f-focLib

clean-User-2f-focLib:
	-$(RM) ./User/focLib/bldcMotor.cyclo ./User/focLib/bldcMotor.d ./User/focLib/bldcMotor.o ./User/focLib/bldcMotor.su ./User/focLib/current.cyclo ./User/focLib/current.d ./User/focLib/current.o ./User/focLib/current.su ./User/focLib/encoder.cyclo ./User/focLib/encoder.d ./User/focLib/encoder.o ./User/focLib/encoder.su ./User/focLib/lowpass_filter.cyclo ./User/focLib/lowpass_filter.d ./User/focLib/lowpass_filter.o ./User/focLib/lowpass_filter.su ./User/focLib/math_utils.cyclo ./User/focLib/math_utils.d ./User/focLib/math_utils.o ./User/focLib/math_utils.su ./User/focLib/pid.cyclo ./User/focLib/pid.d ./User/focLib/pid.o ./User/focLib/pid.su ./User/focLib/voltage.cyclo ./User/focLib/voltage.d ./User/focLib/voltage.o ./User/focLib/voltage.su

.PHONY: clean-User-2f-focLib

