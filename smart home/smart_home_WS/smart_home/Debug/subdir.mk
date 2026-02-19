################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../LCD.c \
../LED.c \
../application.c \
../buzzer.c \
../dc_motor.c \
../flame_sensor.c \
../gpio.c \
../pwm.c \
../sensor_ldr.c \
../sensor_lm35.c 

OBJS += \
./ADC.o \
./LCD.o \
./LED.o \
./application.o \
./buzzer.o \
./dc_motor.o \
./flame_sensor.o \
./gpio.o \
./pwm.o \
./sensor_ldr.o \
./sensor_lm35.o 

C_DEPS += \
./ADC.d \
./LCD.d \
./LED.d \
./application.d \
./buzzer.d \
./dc_motor.d \
./flame_sensor.d \
./gpio.d \
./pwm.d \
./sensor_ldr.d \
./sensor_lm35.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


