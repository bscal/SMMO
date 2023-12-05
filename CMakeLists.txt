cmake_minimum_required(VERSION 3.10)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/build/install)

project(SMMO VERSION 1.0.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Engine/src CACHE FILEPATH "Path to src directory.")

set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor CACHE FILEPATH "Path to vendor directory.")

if (NOT CMAKE_BUILD_TYPE)
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(OUTPUT_DIR windows-x86-64)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY bin/${OUTPUT_DIR}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY bin/${OUTPUT_DIR}/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/${OUTPUT_DIR}/${PROJECT_NAME})

# The COMPONENTS part checks that OGRE was built the way we need it
# The CONFIG flag makes sure we get OGRE instead of OGRE-next
set(OGRE_DIR ${VENDOR_DIR}/ogre/sdk/debug/CMake)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)

file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE SRC_FILES_C ${SRC_DIR}/*.c)
file(GLOB_RECURSE HEADER_FILES ${SRC_DIR}/*.h)
file(GLOB OTHER_FILES
    ${VENDOR_DIR}/flecs/flecs.c
    ${VENDOR_DIR}/enat/enet.h
    ${VENDOR_DIR}/librg/librg.h
    ${VENDOR_DIR}/cmp/cmp.c
    ${VENDOR_DIR}/cmp/cmp.h
)

add_executable(SMMO
    ${SRC_FILES}
    ${SRC_FILES_C}
    ${HEADER_FILES}
    ${OTHER_FILES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES} ${SRC_FILES_C} ${HEADER_FILES} ${OTHER_FILES})

link_directories(SMMO public "C:/Program Files/MySQL/MySQL Server 8.0/lib")

target_include_directories(SMMO PUBLIC ${SRC_DIR} ${VENDOR_DIR})

add_compile_definitions()
    target_link_libraries(SMMO OgreBites) 
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_definitions(SCAL_DEBUG)
    #target_compile_options(SMMO PUBLIC -wd4251)
else()

    add_compile_definitions(SCAL_RELEASE)
endif()

if (MSVC)
    add_compile_definitions(SCAL_PLATFORM_WINDOWS)

    target_compile_options(SMMO PUBLIC 
        -std:c++17 
        -W4
        -WX 
        -wd4100
        -wd4201
        -wd4127
        -wd4701
        -wd4189
        -wd4995
        -wd4244
        #-Oi
        #-GR
        #-GR-
        #-EHs-c-
        #-D_HAS_EXCEPTIONS=0
        -lWs2_32
    )

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SMMO)
endif()

if (UNIX AND NOT APPLE)
    add_compile_definitions(SCAL_PLATFORM_LINUX)
endif()

# For moving assets folder around
#if(MSVC)
#    set_target_properties(Game PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
#else()
#    # Set a symbolic link so exe can find the /assets folder
#    set(link_src "${CMAKE_SOURCE_DIR}/assets")
#    if(UNIX AND NOT APPLE) 
#        set(link_dst "${CMAKE_CURRENT_BINARY_DIR}/assets") 
#    else() 
#        set(link_dst "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/assets") 
#    endif() 
#    add_custom_command( 
#        TARGET Game
#        POST_BUILD COMMAND ${CMAKE_COMMAND} 
#            -E create_symlink ${link_src} ${link_dst} 
#        DEPENDS ${link_dst} 
#        COMMENT "symbolic link ${link_src} => ${link_dst}" 
#    )
#endif()

#add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
#add_dependencies(Game copy_assets)