cmake_minimum_required(VERSION 3.16)

project(baskets_and_balls VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Test)


add_library(logcreater STATIC
    logcreater.cpp
    logcreater.h
)
target_link_libraries(logcreater PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

add_library(baskets_lib STATIC
    baskets.cpp
    baskets.h
)
target_link_libraries(baskets_lib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
set_target_properties(baskets_lib PROPERTIES AUTOMOC ON)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    jsonloader.h
    jsonloader.cpp
    parametrs.json
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(baskets_and_balls
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(baskets_and_balls SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(baskets_and_balls
            ${PROJECT_SOURCES}
            guibasket.h guibasket.cpp
        )
    endif()
endif()

add_custom_target(CopyData ALL
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/parametrs.json
    ${CMAKE_CURRENT_BINARY_DIR}/parametrs.json
)

target_link_libraries(baskets_and_balls PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    baskets_lib
)

target_link_libraries(baskets_lib PRIVATE logcreater)
target_link_libraries(baskets_and_balls PRIVATE logcreater)

add_executable(test_baskets test_baskets.cpp)
target_link_libraries(test_baskets PRIVATE
    Qt${QT_VERSION_MAJOR}::Test
    baskets_lib
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.baskets_and_balls)
endif()
set_target_properties(baskets_and_balls PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS baskets_and_balls
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(baskets_and_balls)
endif()
