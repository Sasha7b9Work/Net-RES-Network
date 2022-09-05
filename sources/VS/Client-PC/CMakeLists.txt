# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (Client-PC)

set(CMAKE_UNITY_BUILD ON)

include_directories(.
                    ../../VS/ThirdParty/wxWidgets/include
                    ../../generated/ThirdParty/lib/vc_dll/mswud)

link_directories(../../generated/ThirdParty/lib/vc_dll)

add_definitions(-DSTM32F103xx -DWXUSINGDLL -DGUI -DDEVICE)

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    add_compile_options(/wd4365)    # 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch
    add_compile_options(/wd4514)    # 'function' : unreferenced inline function has been removed
    add_compile_options(/wd4625)    # 'derived class' : copy constructor was implicitly defined as deleted because a base class copy constructor is inaccessible or deleted
    add_compile_options(/wd4626)    # 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
    add_compile_options(/wd4820)    # 'bytes' bytes padding added after construct 'member_name'
    add_compile_options(/wd4996)    # Your code uses a function, class member, variable, or typedef that's marked deprecated
    add_compile_options(/wd5026)    # move constructor was implicitly defined as deleted
    add_compile_options(/wd5027)    # move assignment operator was implicitly defined as deleted
    add_compile_options(/wd5039)    # 'xxx': pointer or reference to potentially throwing function passed to extern C
                                    # function under -EHc.
    add_compile_options(/wd5045)    # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
endif()

file(GLOB RESOURCES               resources/*.*)
file(GLOB SRC                     *.h *.cpp)
file(GLOB COMMUNICATOR            Communicator/*.*)
file(GLOB COMMUNICATOR_HC12       Communicator/HC12/*.*)
file(GLOB COMMUNICATOR_HC12_RS232 Communicator/HC12/RS232/*.*)
file(GLOB COMMUNICATOR_LAN        Communicator/LAN/*.*)
file(GLOB COMMUNICATOR_LAN_LIBNET Communicator/LAN/libnet/*.*)
file(GLOB COMMUNICATOR_RS232      Communicator/RS232/*.*)
file(GLOB DATA                    Data/*.*)
file(GLOB DISPLAY                 Display/*.*)
file(GLOB DISPLAY_DIAGRAM         Display/Diagram/*.*)
file(GLOB DISPLAY_GRID            Display/Grid/*.*)
file(GLOB UTILS                   Utils/*.*)
file(GLOB UTILS_TEXT              Utils/Text/*.*)

source_group(resources               FILES ${RESOURCES})
source_group(src                     FILES ${SRC})
source_group(Communicator            FILES ${COMMUNICATOR})
source_group(Communicator/HC12       FILES ${COMMUNICATOR_HC12})
source_group(Communicator/HC12/RS232 FILES ${COMMUNICATOR_HC12_RS232})
source_group(Communicator/LAN        FILES ${COMMUNICATOR_LAN})
source_group(Communicator/LAN/libnet FILES ${COMMUNICATOR_LAN_LIBNET})
source_group(Communicator/RS232      FILES ${COMMUNICATOR_RS232})
source_group(Data                    FILES ${DATA})
source_group(Display                 FILES ${DISPLAY})
source_group(Display/Diagram         FILES ${DISPLAY_DIAGRAM})
source_group(Display/Grid            FILES ${DISPLAY_GRID})
source_group(Utils                   FILES ${UTILS})
source_group(Utils/Text              FILES ${UTILS_TEXT})

add_executable( ${PROJECT_NAME}
                ${RESOURCES}
                ${SRC}
                ${COMMUNICATOR}
                ${COMMUNICATOR_HC12}
                ${COMMUNICATOR_HC12_RS232}
                ${COMMUNICATOR_LAN}
                ${COMMUNICATOR_LAN_LIBNET}
                ${COMMUNICATOR_RS232}
                ${DATA}
                ${DISPLAY}
                ${DISPLAY_DIAGRAM}
                ${DISPLAY_GRID}
                ${UTILS}
                ${UTILS_TEXT}
                )

target_link_libraries(${PROJECT_NAME} wxbase31ud wxmsw31ud_core Ws2_32)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND copy ..\\..\\ThirdParty\\lib\\vc_dll\\wxbase316ud_vc_custom.dll $(OutputPath) /Y)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND copy ..\\..\\ThirdParty\\lib\\vc_dll\\wxmsw316ud_core_vc_custom.dll $(OutputPath) /Y)
