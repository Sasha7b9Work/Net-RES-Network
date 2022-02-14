# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (Device)

message("------------------------------------------------------------------------ ${PROJECT_NAME}")

include_directories(../common/_VS_KEIL/CMSIS/
                    ../common/_VS_KEIL/std_includes/
                    src/STM32Cube_F1/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc/
                    src/STM32Cube_F1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc/
                    src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/
                    src/STM32Cube_F1/Drivers/CMSIS/Device/ST/STM32F1xx/Include/
                    src/Hardware/HAL/
                    src/Hardware/CDC/
                    src/
                    )

add_definitions(-DSTM32F103xB)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")

add_compile_options(/wd4159)    # #pragma pack(pop,...): has popped previously pushed identifier xxx
add_compile_options(/wd4255)
add_compile_options(/wd4514)    # 'function' : unreferenced inline function has been removed
add_compile_options(/wd4623)    # 'xxx': default constructor was implicitly defined as deleted
add_compile_options(/wd4668)    # 'xxx' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
add_compile_options(/wd4820)    # 'xxx': '4' bytes padding added after data member 'yyy'
add_compile_options(/wd5039)    # 'xxx': pointer or reference to potentially throwing function passed to extern C function under -EHc.
add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
add_compile_options(/wd5219)    # implicit conversion from 'xxx' to 'float', possible loss of data
add_compile_options(/wd5220)    # a non-static data member with a volatile qualified type no longer implies
add_compile_options(/wd26812)   # The enum type %type% is unscoped. Prefer 'enum class' over 'enum' (Enum.3)


file(GLOB STM32F1        src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_gpio.h
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd.c
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_pcd.h
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc.h
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_rcc_ex.h
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_cortex.h
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll_usb.c
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_ll_usb.h
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_i2c.c
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_i2c.h
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_dma.h
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_uart.c
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_uart.h
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pcd_ex.c
                         src/STM32Cube_F1/Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_pcd_ex.h)
file(GLOB SRC             src/*.*)
file(GLOB HARDWARE_CMSIS  src/Hardware/CMSIS/*.*)
file(GLOB HARDWARE_CDC    src/Hardware/CDC/*.*)
file(GLOB HARDWARE_HAL    src/Hardware/HAL/*.*)
file(GLOB HARDWARE_I2C    src/Hardware/I2C/*.*)
file(GLOB MODULES_BME280  src/Modules/BME280/*.*)
file(GLOB MODULES_CG_ANEM src/Modules/CG-Anem/*.*)
file(GLOB MODULES_HC12    src/Modules/HC12/*.*)

source_group(STM32F1         FILES ${STM32F1})
source_group(src             FILES ${SRC})
source_group(Hardware/CMSIS  FILES ${HARDWARE_CMSIS})
source_group(Hardware/CDC    FILES ${HARDWARE_CDC})
source_group(Hardware/HAL    FILES ${HARDWARE_HAL})
source_group(Hardware/I2C    FILES ${HARDWARE_I2C})
source_group(Modules/BME280  FILES ${MODULES_BME280})
source_group(Modules/CG-Anem FILES ${MODULES_CG_ANEM})
source_group(Modules/HC12    FILES ${MODULES_HC12})

set_source_files_properties(${STM32F1} ${HARDWARE_CMSIS}
                            src/Hardware/CDC/usbd_desc.c
                            src/Hardware/CDC/usb_device.c
                            src/Hardware/CDC/usbd_conf.c
                            PROPERTIES HEADER_FILE_ONLY TRUE)

add_library(${PROJECT_NAME}
            ${STM32F1}
            ${SRC}
            ${HARDWARE_CMSIS}
            ${HARDWARE_CDC}
            ${HARDWARE_HAL}
            ${HARDWARE_I2C}
            ${MODULES_BME280}
            ${MODULES_CG_ANEM}
            ${MODULES_HC12}
            )
