cmake_minimum_required ( VERSION 3.1 )
###################################################################################
#
#   Build wrengame
#
###################################################################################
project ( wrengame VERSION 0.0.1 )

#
set ( VERSION 0.0.1 )
set ( RELEASE_NAME wrengame )

#
# enable features
#
include ( CMakeToolsHelpers OPTIONAL )

#
#   libraries - sources & packages
#
if (EXISTS ${CMAKE_SOURCE_DIR}/data AND NOT DEFINED ZEROG )
    add_subdirectory (data)
    list ( APPEND RESOURCES ${resources_gresource_xml_C_FILE} )
endif ()

#
#   application source
#

list ( APPEND C_SOURCES src/main.c )
#
#   application includes
#
set ( INCLUDES "${INCLUDES};./include" )
set ( INCLUDES "${INCLUDES};/usr/include" )


#
#   compiler options
#
# Libs: 
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL2" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lwren" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm" )


set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -std=c11 -O3" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++17 -O3" )


# definitions 

include_directories(AFTER ${INCLUDES})

link_directories( ${CMAKE_SOURCE_DIR}/lib/ )
#
#   compile ccode & link executable
#
add_executable ( ${PROJECT_NAME} ${C_SOURCES} ${RESOURCES} )
add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD COMMAND 
                   ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> .. )
target_link_libraries ( ${PROJECT_NAME} m SDL2 wren )
install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION . )
include (CPack)

# (generated from template: c. Do not modify. )
