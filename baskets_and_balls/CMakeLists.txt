cmake_minimum_required(VERSION 3.16)

project(baskets_and_balls VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Test)  # Добавлен Test
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Test)  # Добавлен Test

# Создаем библиотеку ПЕРЕД основным таргетом
add_library(baskets_lib STATIC
    baskets.cpp
    baskets.h
)
target_link_libraries(baskets_lib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)  # Линковка для библиотеки
set_target_properties(baskets_lib PROPERTIES AUTOMOC ON)  # Включение AUTOMOC для библиотеки

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
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
        )
    endif()
endif()

target_link_libraries(baskets_and_balls PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    baskets_lib
)

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
