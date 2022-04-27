# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (Device)

set(CMAKE_UNITY_BUILD OFF)

include_directories(Device
                    ../../VS/ThirdParty/wxWidgets/include 
                    ../../generated/ThirdParty/lib/vc_dll/mswud)

link_directories(../../generated/ThirdParty/lib/vc_dll)

add_definitions(-DSTM32F103xx -DWXUSINGDLL -DGUI -DDEVICE)

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")

    add_compile_options(/wd5039)    # 'xxx': pointer or reference to potentially throwing function passed to extern C
                                    # function under -EHc.
endif()

file(GLOB SRC       *.h *.cpp)

source_group(src    FILES ${SRC})

add_executable( ${PROJECT_NAME}
                ${SRC}
                )

target_link_libraries(${PROJECT_NAME} wxbase31ud wxmsw31ud_core)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND copy ..\\..\\ThirdParty\\lib\\vc_dll\\wxbase315ud_vc_custom.dll $(OutputPath) /Y)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND copy ..\\..\\ThirdParty\\lib\\vc_dll\\wxmsw315ud_core_vc_custom.dll $(OutputPath) /Y)
