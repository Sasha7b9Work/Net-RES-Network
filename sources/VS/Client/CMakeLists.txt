# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

project (Client)

set(CMAKE_UNITY_BUILD OFF)

include_directories(.
                    ../../VS/ThirdParty/wxWidgets/include 
                    ../../generated/ThirdParty/lib/vc_dll/mswud)

link_directories(../../generated/ThirdParty/lib/vc_dll)

add_definitions(-DSTM32F103xx -DWXUSINGDLL -DGUI -DDEVICE)

if(WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MP -Wall")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    add_compile_options(/wd4365)
    add_compile_options(/wd4625)
    add_compile_options(/wd4626)
    add_compile_options(/wd4774)
    add_compile_options(/wd4820)
    add_compile_options(/wd4996)
    add_compile_options(/wd5026)
    add_compile_options(/wd5027)
    add_compile_options(/wd5039)    # 'xxx': pointer or reference to potentially throwing function passed to extern C
                                    # function under -EHc.
    add_compile_options(/wd5045)
endif()

file(GLOB SRC                *.h *.cpp)
file(GLOB COMMUNICATOR       Communicator/*.*)
file(GLOB COMMUNICATOR_VCP   Communicator/VCP/*.*)
file(GLOB COMMUNICATOR_HC12  Communicator/HC12/*.*)
file(GLOB COMMUNICATOR_RS232 Communicator/RS232/*.*)

source_group(src                FILES ${SRC})
source_group(Communicator       FILES ${COMMUNICATOR})
source_group(Communicator/VCP   FILES ${COMMUNICATOR_VCP})
source_group(Communicator/HC12  FILES ${COMMUNICATOR_HC12})
source_group(Communicator/RS232 FILES ${COMMUNICATOR_RS232})

add_executable( ${PROJECT_NAME}
                ${SRC}
                ${COMMUNICATOR}
                ${COMMUNICATOR_VCP}
                ${COMMUNICATOR_HC12}
                ${COMMUNICATOR_RS232}
                )

target_link_libraries(${PROJECT_NAME} wxbase31ud wxmsw31ud_core)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND copy ..\\..\\ThirdParty\\lib\\vc_dll\\wxbase316ud_vc_custom.dll $(OutputPath) /Y)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND copy ..\\..\\ThirdParty\\lib\\vc_dll\\wxmsw316ud_core_vc_custom.dll $(OutputPath) /Y)
