################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LCD_4bit.c \
../source/Project5.c \
../source/adc.c \
../source/controller.c \
../source/debug.c \
../source/init.c \
../source/interrupts.c \
../source/mtb.c \
../source/pwm.c \
../source/semihost_hardfault.c \
../source/updatestate.c 

OBJS += \
./source/LCD_4bit.o \
./source/Project5.o \
./source/adc.o \
./source/controller.o \
./source/debug.o \
./source/init.o \
./source/interrupts.o \
./source/mtb.o \
./source/pwm.o \
./source/semihost_hardfault.o \
./source/updatestate.o 

C_DEPS += \
./source/LCD_4bit.d \
./source/Project5.d \
./source/adc.d \
./source/controller.d \
./source/debug.d \
./source/init.d \
./source/interrupts.d \
./source/mtb.d \
./source/pwm.d \
./source/semihost_hardfault.d \
./source/updatestate.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DCPU_MKL25Z128VFM4 -DCPU_MKL25Z128VFM4_cm0plus -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


