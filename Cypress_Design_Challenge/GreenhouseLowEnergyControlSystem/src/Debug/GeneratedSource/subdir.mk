################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GeneratedSource/cycfg.c \
../GeneratedSource/cycfg_gatt_db.c \
../GeneratedSource/cycfg_pins.c \
../GeneratedSource/cycfg_routing.c 

OBJS += \
./GeneratedSource/cycfg.o \
./GeneratedSource/cycfg_gatt_db.o \
./GeneratedSource/cycfg_pins.o \
./GeneratedSource/cycfg_routing.o 

C_DEPS += \
./GeneratedSource/cycfg.d \
./GeneratedSource/cycfg_gatt_db.d \
./GeneratedSource/cycfg_pins.d \
./GeneratedSource/cycfg_routing.d 


# Each subdirectory must supply rules for building sources it contributes
GeneratedSource/%.o: ../GeneratedSource/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -mfloat-abi=soft -Os -ffunction-sections -Wall  -g3 -DWICED_BT_TRACE_ENABLE -DCYW20819A1=1 -DBCM20819A1=1 -DBCM20819=1 -DCYW20819=1 -DCHIP=20819 -DAPP_CHIP=20819 -DOTA_CHIP=20819 -DCHIP_REV_A_20819A1=1 -DCOMPILER_ARM -DSPAR_APP_SETUP=application_setup -D__TARGET_CPU_CORTEX_M4 -D__ARMCC_VERSION=400677 -DPLATFORM='"CYW920819EVB_02"' -DWICED_SDK_MAJOR_VER=1 -DWICED_SDK_MINOR_VER=1 -DWICED_SDK_REV_NUMBER=4 -DWICED_SDK_BUILD_NUMBER=993 -DSPAR_CRT_SETUP=spar_crt_setup -I"C:/Users/joshb/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/include/20819/stack" -I"C:/Users/joshb/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/include/20819/hal" -I"C:/Users/joshb/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/include/20819/internal" -I"C:/Users/joshb/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/include" -I"C:/Users/joshb/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/common/include" -I"C:/Users/joshb/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/include/20819" -I"C:/Users/joshb/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/WICED/internal/20819A1" -I"C:\Users\joshb\Desktop\NewCypressCode\1_Blank\EmptyWicedBluetooth_mainapp" -I"C:/Users/joshb/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/platforms/CYW920819EVB_02" -I"C:/Users/joshb/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/WICED/common" -I"C:/Users/joshb/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/WICED/libraries" -I"C:/Users/joshb/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/platforms" -std=gnu11 -mlong-calls -ffreestanding -Wno-implicit-function-declaration -fshort-wchar -funsigned-char -Wno-strict-aliasing -std=gnu11 -isystem "C:/Users/joshb/ModusToolbox_1.1/tools/gcc-7.2.1-1.0/arm-none-eabi/include" -isystem "C:/Users/joshb/ModusToolbox_1.1/tools/gcc-7.2.1-1.0/arm-none-eabi/lib/include" -isystem "C:/Users/joshb/ModusToolbox_1.1/tools/gcc-7.2.1-1.0/arm-none-eabi/lib/include-fixed" -Wno-implicit-function-declaration -Wno-unused-variable -Wno-unused-function @C:/Users/joshb/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/WICED/internal/20819A1/gcc/20819A1.cflag -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


