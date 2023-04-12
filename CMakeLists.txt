cmake_minimum_required(VERSION 3.15)

project("")
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message("CMAKE_CURRENT_SOURCE_DIR =>PROJECT_NAME=> " ${PROJECT_NAME})

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS  Core Widgets Xml Network Core5Compat Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Xml Network Core5Compat Gui REQUIRED)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/icons_app.rc")

set(PROJECT_HEADERS
    include/widget.h
    include/lb_weather.h
    include/downloader.h
    include/xmlparser.h
    include/function.h
    include/maintaf.h
    include/forecast_title.h
    include/forecast_taf.h
    include/forecast.h
    )
set(PROJECT_SOURCES
    source/main.cpp
    source/widget.cpp
    source/lb_weather.cpp
    source/downloader.cpp
    source/xmlparser.cpp
    source/function.cpp
    source/maintaf.cpp
    source/forecast_title.cpp
    source/forecast_taf.cpp
    source/forecast.cpp

    resource.qrc
    icons_app.rc
    .clang-format
   )

add_executable(${PROJECT_NAME} WIN32
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
    ${APP_ICON_RESOURCE_WINDOWS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Core5Compat
    Qt${QT_VERSION_MAJOR}::Gui
 )

SET (MY_RELEASE_DIR ${CMAKE_BINARY_DIR}_Deploy_${PROJECT_NAME})
#SET (MY_RELEASE_DIR ${CMAKE_CURRENT_LIST_DIR}_MyReleaseDir_EXE)
message( "Create Directory:" ${MY_RELEASE_DIR})
file(MAKE_DIRECTORY ${MY_RELEASE_DIR})
message("CopyFile "  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.exe  " to "  ${MY_RELEASE_DIR} )

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.exe ${MY_RELEASE_DIR}
    COMMAND G:\\Qt\\6.2.0\\mingw81_64\\bin\\windeployqt.exe ${MY_RELEASE_DIR}/${PROJECT_NAME}.exe
    #COMMAND ${MY_RELEASE_DIR}/${PROJECT_NAME}.exe
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )


