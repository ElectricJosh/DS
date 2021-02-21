################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../led_control.c \
../main.c \
../wiced_platform.c 

OBJS += \
./led_control.o \
./main.o \
./wiced_platform.o 

C_DEPS += \
./led_control.d \
./main.d \
./wiced_platform.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -mfloat-abi=soft -Os -ffunction-sections -Wall  -g3 -DWICED_BT_TRACE_ENABLE -DHCI_CONTROL -DLOW_POWER_NODE=0 -DOTA_FW_UPGRADE_SFLASH_COPY -DENABLE_SFLASH_UPGRADE -DSS_LOCATION=0x500000 -DVS_LOCATION=0x500400 -DDS_LOCATION=0x501400 -DDS2_LOCATION=0x53E000 -DCYW20819A1=1 -DBCM20819A1=1 -DBCM20819=1 -DCYW20819=1 -DCHIP=20819 -DAPP_CHIP=20819 -DOTA_CHIP=20819 -DCHIP_REV_A_20819A1=1 -DCOMPILER_ARM -DSPAR_APP_SETUP=application_setup -D__TARGET_CPU_CORTEX_M4 -D__ARMCC_VERSION=400677 -DPLATFORM='"CYBT_213043_MESH"' -DWICED_SDK_MAJOR_VER=1 -DWICED_SDK_MINOR_VER=1 -DWICED_SDK_REV_NUMBER=3 -DWICED_SDK_BUILD_NUMBER=344 -DSPAR_CRT_SETUP=spar_crt_setup -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/include/20819/stack" -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/include/20819/hal" -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/include/20819/internal" -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/include" -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/common/include" -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/include/20819" -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/WICED/internal/20819A1" -I"C:\Users\Josh\OneDrive\CypressCode\Test12_Custom_Model\BLE_Mesh_LevelServer_mainapp" -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/common/libraries/mesh_app_lib" -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/platforms/CYBT_213043_MESH" -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/WICED/common" -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/WICED/libraries" -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/platforms" -I"C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/common/libraries/fw_upgrade_lib" -std=gnu11 -mlong-calls -ffreestanding -Wno-implicit-function-declaration -fshort-wchar -funsigned-char -Wno-strict-aliasing -std=gnu11 -isystem "C:/Users/Josh/ModusToolbox_1.1/tools/gcc-7.2.1-1.0/arm-none-eabi/include" -isystem "C:/Users/Josh/ModusToolbox_1.1/tools/gcc-7.2.1-1.0/arm-none-eabi/lib/include" -isystem "C:/Users/Josh/ModusToolbox_1.1/tools/gcc-7.2.1-1.0/arm-none-eabi/lib/include-fixed" -Wno-implicit-function-declaration -Wno-unused-variable -Wno-unused-function @C:/Users/Josh/ModusToolbox_1.1/libraries/bt_sdk-1.1/components/BT-SDK/208XX-A1_Bluetooth/WICED/internal/20819A1/gcc/20819A1.cflag -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


