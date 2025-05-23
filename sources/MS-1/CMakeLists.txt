# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (MS-1)

#set(CMAKE_UNITY_BUILD OFF)

message("------------------------------------------------------------------------ ${PROJECT_NAME}")

include_directories(
    ../common/_VS_KEIL/CMSIS/
    ../common/_VS_KEIL/std_includes/
    ../common/STM32Cube_F3/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc/
    ../common/STM32Cube_F3/Middlewares/ST/STM32_USB_Device_Library/Core/Inc/
    ../common/STM32Cube_F3/Drivers/STM32F3xx_HAL_Driver/Inc/
    ../common/STM32Cube_F3/Drivers/CMSIS/Device/ST/STM32F3xx/Include/
    src/Hardware/HAL/
    src/Hardware/CDC/
    src/
)

add_definitions(-DSTM32F303xC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")

add_compile_options(
    /wd4131    # 'malloc' : uses old-style declarator
    /wd4201
    /wd4310
    /wd4514    # 'function' : unreferenced inline function has been removed
    /wd4623    # default constructor was implicitly defined as deleted
    /wd4626    # assignment operator was implicitly defined as deleted
    /wd4820    # 'xxx': '4' bytes padding added after data member 'yyy'
    /wd5027    # move assignment operator was implicitly defined as deleted
    /wd5045    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
    /wd5220    # a non-static data member with a volatile qualified type no longer implies
    /wd5264
    /wd26812   # The enum type %type% is unscoped. Prefer 'enum class' over 'enum' (Enum.3)
)

file(GLOB STM32F3               ../common/STM32Cube_F3/Drivers/STM32F3xx_HAL_Driver/Src/*.c
                                ../common/STM32Cube_F3/Drivers/STM32F3xx_HAL_Driver/Inc/*.h)
file(GLOB SRC                   src/*.*)
file(GLOB DISPLAY               src/Display/*.*)
file(GLOB DISPLAY_FONT          src/Display/Font/*.*)
file(GLOB HARDWARE              src/Hardware/*.*)
file(GLOB HARDWARE_CMSIS        src/Hardware/CMSIS/*.*)
file(GLOB HARDWARE_CDC          src/Hardware/CDC/*.*)
file(GLOB HARDWARE_HAL          src/Hardware/HAL/*.*)
file(GLOB HARDWARE_HAL_I2C      src/Hardware/HAL/I2C/*.*)
file(GLOB MENU                  src/Menu/*.*)
file(GLOB MENU_PAGES            src/Menu/Pages/*.*)
file(GLOB MODULES_BME280        src/Modules/BME280/*.*)
file(GLOB MODULES_CG_ANEM       src/Modules/CG-Anem/*.*)
file(GLOB MODULES_GY511         src/Modules/GY511/*.*)
file(GLOB MODULES_HC12          src/Modules/HC12/*.*)
file(GLOB MODULES_NEO_M8N       src/Modules/NEO-M8N/*.*)
file(GLOB MODULES_ST7735        src/Modules/ST7735/*.*)
file(GLOB MODULES_W25Q80DV      src/Modules/W25Q80DV/*.*)
file(GLOB SCPI                  src/SCPI/*.*)
file(GLOB SETTINGS              src/Settings/*.*)
file(GLOB STORAGE               src/Storage/*.*)
file(GLOB TESTS                 src/Tests/*.*)
file(GLOB UTILS                 src/Utils/*.*)
file(GLOB UTILS_TEXT            src/Utils/Text/*.*)

source_group(STM32F3            FILES ${STM32F3})
source_group(src                FILES ${SRC})
source_group(Display            FILES ${DISPLAY})
source_group(Display/Font       FILES ${DISPLAY_FONT})
source_group(Hardware           FILES ${HARDWARE})
source_group(Hardware/CMSIS     FILES ${HARDWARE_CMSIS})
source_group(Hardware/CDC       FILES ${HARDWARE_CDC})
source_group(Hardware/HAL       FILES ${HARDWARE_HAL})
source_group(Hardware/HAL/I2C   FILES ${HARDWARE_HAL_I2C})
source_group(Menu               FILES ${MENU})
source_group(Menu/Pages         FILES ${MENU_PAGES})
source_group(Modules/BME280     FILES ${MODULES_BME280})
source_group(Modules/CG-Anem    FILES ${MODULES_CG_ANEM})
source_group(Modules/GY511      FILES ${MODULES_GY511})
source_group(Modules/HC12       FILES ${MODULES_HC12})
source_group(Modules/ST7735     FILES ${MODULES_ST7735})
source_group(Modules/NEO-M8N    FILES ${MODULES_NEO_M8N})
source_group(Modules/W25Q80DV   FILES ${MODULES_W25Q80DV})
source_group(SCPI               FILES ${SCPI})
source_group(Settings           FILES ${SETTINGS})
source_group(Storage            FILES ${STORAGE})
source_group(Tests              FILES ${TESTS})
source_group(Utils              FILES ${UTILS})
source_group(Utils/Text         FILES ${UTILS_TEXT})

set_source_files_properties(
    ${STM32F3} ${HARDWARE_CMSIS}
    PROPERTIES HEADER_FILE_ONLY TRUE
)

set_source_files_properties(
    src/Storage/MemoryStorage.cpp
    PROPERTIES SKIP_UNITY_BUILD_INCLUSION ON
)

add_library(
    ${PROJECT_NAME}
    ${STM32F3}
    ${SRC}
    ${DISPLAY}
    ${DISPLAY_FONT}
    ${HARDWARE}
    ${HARDWARE_CMSIS}
    ${HARDWARE_CDC}
    ${HARDWARE_HAL}
    ${HARDWARE_HAL_I2C}
    ${MENU}
    ${MENU_PAGES}
    ${MODULES_BME280}
    ${MODULES_CG_ANEM}
    ${MODULES_GY511}
    ${MODULES_HC12}
    ${MODULES_NEO_M8N}
    ${MODULES_ST7735}
    ${MODULES_W25Q80DV}
    ${SCPI}
    ${SETTINGS}
    ${STORAGE}
    ${TESTS}
    ${UTILS}
    ${UTILS_TEXT}
)
