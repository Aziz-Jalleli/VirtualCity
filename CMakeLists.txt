cmake_minimum_required(VERSION 3.16)

project(VirtualCity VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VirtualCity
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        batiment.h batiment.cpp
        ville.h ville.cpp
        maison.h maison.cpp
        usine.h usine.cpp
        parc.h parc.cpp
        simulation.h simulation.cpp
        simulation.h simulation.cpp
        afficherdetails.h afficherdetails.cpp afficherdetails.ui
        addhabitant.h addhabitant.cpp addhabitant.ui
        createmaison.h createmaison.cpp createmaison.ui
        createville.h createville.cpp createville.ui
        createusine.h createusine.cpp createusine.ui
        produireeau.h produireeau.cpp produireeau.ui
        produireelectricite.h produireelectricite.cpp produireelectricite.ui
        createparc.h createparc.cpp createparc.ui
        batimentgraphicsitem.h batimentgraphicsitem.cpp
        graphicswindow.h graphicswindow.cpp
        resources.qrc




    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET VirtualCity APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(VirtualCity SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(VirtualCity
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(VirtualCity PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.VirtualCity)
endif()
set_target_properties(VirtualCity PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS VirtualCity
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VirtualCity)
endif()
