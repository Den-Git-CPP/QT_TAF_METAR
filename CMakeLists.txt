cmake_minimum_required(VERSION 3.15)

project("")
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message("CMAKE_CURRENT_SOURCE_DIR =>PROJECT_NAME=> " ${PROJECT_NAME})

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS  Core Gui Network Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Network Widgets REQUIRED)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resource/icons_app.rc")

set(PROJECT_HEADERS
    include/downloader.h
    include/forecast.h
    include/storage_forecast.h
    include/function.h
    include/widget.h
    include/widget_show_weather_2.h
    #  include/widget_show_weather.h
   )

set(PROJECT_SOURCES
    source/downloader.cpp
    source/forecast.cpp
    source/storage_forecast.cpp
    source/function.cpp
    source/widget.cpp
    source/widget.ui
    source/widget_show_weather_2.cpp
    source/widget_show_weather_2.ui
    resource/resource.qrc
    main.cpp

    # source/widget_show_weather.cpp
       resource/icons_app.rc
    #  .clang-format
   )

add_executable(${PROJECT_NAME} WIN32
  ${PROJECT_HEADERS}
  ${PROJECT_SOURCES}
  ${APP_ICON_RESOURCE_WINDOWS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Widgets
    )

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

add_custom_command(TARGET ${PROJECT_NAME}
COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resource
        ${CMAKE_BINARY_DIR}/resource
)

SET (MY_RELEASE_DIR ${CMAKE_BINARY_DIR}_Deploy_${PROJECT_NAME}) #POST_BUILD
#SET (MY_RELEASE_DIR ${CMAKE_CURRENT_LIST_DIR}_MyReleaseDir_EXE)
message( "Create Directory:" ${MY_RELEASE_DIR})
file(MAKE_DIRECTORY ${MY_RELEASE_DIR})
message("CopyFile "  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.exe  " to "  ${MY_RELEASE_DIR} )
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.exe ${MY_RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/resource ${MY_RELEASE_DIR}/resource
    COMMAND G:\\Qt\\6.5.3\\mingw_64\\bin\\windeployqt6.exe ${MY_RELEASE_DIR}/${PROJECT_NAME}.exe
    #COMMAND ${MY_RELEASE_DIR}/${PROJECT_NAME}.exe
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )



