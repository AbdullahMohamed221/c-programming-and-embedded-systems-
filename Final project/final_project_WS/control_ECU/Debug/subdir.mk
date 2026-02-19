################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../application_control.c \
../dc_motor.c \
../external_eeprom.c \
../gpio.c \
../icu.c \
../pwm.c \
../sensor_lm35.c \
../twi.c \
../uart.c \
../ultrasonic_sensor.c 

OBJS += \
./ADC.o \
./application_control.o \
./dc_motor.o \
./external_eeprom.o \
./gpio.o \
./icu.o \
./pwm.o \
./sensor_lm35.o \
./twi.o \
./uart.o \
./ultrasonic_sensor.o 

C_DEPS += \
./ADC.d \
./application_control.d \
./dc_motor.d \
./external_eeprom.d \
./gpio.d \
./icu.d \
./pwm.d \
./sensor_lm35.d \
./twi.d \
./uart.d \
./ultrasonic_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


