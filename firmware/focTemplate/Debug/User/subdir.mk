################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Adc.c \
../User/Initialize.c \
../User/app.c \
../User/bldcMotor.c \
../User/current.c \
../User/foc_utils.c \
../User/key.c \
../User/lowpass_filter.c \
../User/memory.c \
../User/motor.c \
../User/pid.c \
../User/pwm.c \
../User/userMain.c \
../User/userTimer.c \
../User/voltage.c 

OBJS += \
./User/Adc.o \
./User/Initialize.o \
./User/app.o \
./User/bldcMotor.o \
./User/current.o \
./User/foc_utils.o \
./User/key.o \
./User/lowpass_filter.o \
./User/memory.o \
./User/motor.o \
./User/pid.o \
./User/pwm.o \
./User/userMain.o \
./User/userTimer.o \
./User/voltage.o 

C_DEPS += \
./User/Adc.d \
./User/Initialize.d \
./User/app.d \
./User/bldcMotor.d \
./User/current.d \
./User/foc_utils.d \
./User/key.d \
./User/lowpass_filter.d \
./User/memory.d \
./User/motor.d \
./User/pid.d \
./User/pwm.d \
./User/userMain.d \
./User/userTimer.d \
./User/voltage.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o User/%.su User/%.cyclo: ../User/%.c User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User

clean-User:
	-$(RM) ./User/Adc.cyclo ./User/Adc.d ./User/Adc.o ./User/Adc.su ./User/Initialize.cyclo ./User/Initialize.d ./User/Initialize.o ./User/Initialize.su ./User/app.cyclo ./User/app.d ./User/app.o ./User/app.su ./User/bldcMotor.cyclo ./User/bldcMotor.d ./User/bldcMotor.o ./User/bldcMotor.su ./User/current.cyclo ./User/current.d ./User/current.o ./User/current.su ./User/foc_utils.cyclo ./User/foc_utils.d ./User/foc_utils.o ./User/foc_utils.su ./User/key.cyclo ./User/key.d ./User/key.o ./User/key.su ./User/lowpass_filter.cyclo ./User/lowpass_filter.d ./User/lowpass_filter.o ./User/lowpass_filter.su ./User/memory.cyclo ./User/memory.d ./User/memory.o ./User/memory.su ./User/motor.cyclo ./User/motor.d ./User/motor.o ./User/motor.su ./User/pid.cyclo ./User/pid.d ./User/pid.o ./User/pid.su ./User/pwm.cyclo ./User/pwm.d ./User/pwm.o ./User/pwm.su ./User/userMain.cyclo ./User/userMain.d ./User/userMain.o ./User/userMain.su ./User/userTimer.cyclo ./User/userTimer.d ./User/userTimer.o ./User/userTimer.su ./User/voltage.cyclo ./User/voltage.d ./User/voltage.o ./User/voltage.su

.PHONY: clean-User

