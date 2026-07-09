cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)
# STM32CubeMX generated symbols (macros)
set(MX_Defines_Syms 
	USE_HAL_DRIVER 
    STM32U575xx
    $<$<CONFIG:Debug>:DEBUG>
)

# STM32CubeMX generated include paths
set(MX_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/../../AI_INERTIAL/App
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/Components
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/AppModel
    ${CMAKE_CURRENT_SOURCE_DIR}/../../X-CUBE-MEMS1/Target
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/smart_sensors
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/AI/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Device/ST/STM32U5xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/CMSIS/DSP/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/PnPLCompManager/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Parson_DataOoExchange/parson
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/BSP/Components/Common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/BSP/Components/ism6hg256x
)

# STM32CubeMX generated application sources
set(MX_Application_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/AppModel/App_model_Controller.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/AppModel/App_model_Ism6hg256x_Acc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/AppModel/App_model_Ism6hg256x_Gyro.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/AppModel/App_model_Deviceinformation.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/AppModel/App_model_Firmware_Info.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/AppModel/App_model.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/AppModel/App_model_Ism6hg256x_Mlc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/Components/Controller_PnPL.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/Components/Deviceinformation_PnPL.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/Components/Firmware_Info_PnPL.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/Components/Ism6hg256x_Acc_PnPL.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/Components/Ism6hg256x_Gyro_PnPL.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/Components/PnPL_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Addons/PnPL/Components/Ism6hg256x_Mlc_PnPL.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../X-CUBE-MEMS1/Target/MEMS_integration.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../X-CUBE-MEMS1/Target/custom_motion_sensors.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../X-CUBE-MEMS1/Target/custom_motion_sensors_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../AI_INERTIAL/App/app_ai_inertial.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/custom_bus.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stlink_transport.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32u5xx_it.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/stm32u5xx_hal_msp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/sysmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/syscalls.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../startup_stm32u575xx.s
)

# STM32 HAL/LL Drivers
set(STM32_Drivers_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Src/system_stm32u5xx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_spi_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_i2c_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_cortex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_flash.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_flash_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_exti.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pwr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pwr_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_gtzc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_icache.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_crc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_crc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_uart_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_tim_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/BSP/Components/ism6hg256x/ism6hg256x_reg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/BSP/Components/ism6hg256x/ism6hg256x.c
)

# Drivers Midllewares


set(STAIOTCRAFT_Src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/Parson_DataOoExchange/parson/parson.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/PnPLCompManager/Src/IPnPLComponent.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/PnPLCompManager/Src/PnPLCompManager.c
)

# Link directories setup
set(MX_LINK_DIRS

    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/AI/Lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/ST/CMSIS/DSP/Lib/GCC
)
# Project static libraries
set(MX_LINK_LIBS  
	:NetworkRuntime1000_CM33_GCC.a 
	:libarm_ARMv8MMLlfsp_math.a
    STM32_Drivers
    ${TOOLCHAIN_LINK_LIBRARIES}
    STAIOTCRAFT
	
)
# Interface library for includes and symbols
add_library(stm32cubemx INTERFACE)
target_include_directories(stm32cubemx INTERFACE ${MX_Include_Dirs})
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

# Create STM32_Drivers static library
add_library(STM32_Drivers OBJECT)
target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)


# Create STAIOTCRAFT static library
add_library(STAIOTCRAFT OBJECT)
target_sources(STAIOTCRAFT PRIVATE ${STAIOTCRAFT_Src})
target_link_libraries(STAIOTCRAFT PUBLIC stm32cubemx)

# Add STM32CubeMX generated application sources to the project
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})

# Add libraries to the project
target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
