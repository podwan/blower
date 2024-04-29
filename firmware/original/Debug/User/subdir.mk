################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/app.c \
../User/foc_utils.c \
../User/key.c \
../User/memory.c \
../User/motor.c \
../User/pwm.c \
../User/sensor.c \
../User/svPwm.c \
../User/userMain.c \
../User/userTimer.c 

OBJS += \
./User/app.o \
./User/foc_utils.o \
./User/key.o \
./User/memory.o \
./User/motor.o \
./User/pwm.o \
./User/sensor.o \
./User/svPwm.o \
./User/userMain.o \
./User/userTimer.o 

C_DEPS += \
./User/app.d \
./User/foc_utils.d \
./User/key.d \
./User/memory.d \
./User/motor.d \
./User/pwm.d \
./User/sensor.d \
./User/svPwm.d \
./User/userMain.d \
./User/userTimer.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o User/%.su User/%.cyclo: ../User/%.c User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User

clean-User:
	-$(RM) ./User/app.cyclo ./User/app.d ./User/app.o ./User/app.su ./User/foc_utils.cyclo ./User/foc_utils.d ./User/foc_utils.o ./User/foc_utils.su ./User/key.cyclo ./User/key.d ./User/key.o ./User/key.su ./User/memory.cyclo ./User/memory.d ./User/memory.o ./User/memory.su ./User/motor.cyclo ./User/motor.d ./User/motor.o ./User/motor.su ./User/pwm.cyclo ./User/pwm.d ./User/pwm.o ./User/pwm.su ./User/sensor.cyclo ./User/sensor.d ./User/sensor.o ./User/sensor.su ./User/svPwm.cyclo ./User/svPwm.d ./User/svPwm.o ./User/svPwm.su ./User/userMain.cyclo ./User/userMain.d ./User/userMain.o ./User/userMain.su ./User/userTimer.cyclo ./User/userTimer.d ./User/userTimer.o ./User/userTimer.su

.PHONY: clean-User

