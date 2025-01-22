cmake_minimum_required(VERSION 3.16)

project(VirtualCity VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 and the necessary components
find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    3DCore
    3DExtras
    3DRender
    Gui
    OpenGL
)

# Set the list of project sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    batiment.h batiment.cpp
    ville.h ville.cpp
    maison.h maison.cpp
    usine.h usine.cpp
    parc.h parc.cpp
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

    citywindow.h citywindow.cpp
)

# Define the executable
qt_add_executable(VirtualCity
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ressources.qrc
)

# Link the necessary Qt libraries
target_link_libraries(VirtualCity PRIVATE
    Qt6::Widgets
    Qt6::Gui
    Qt6::Core
    Qt6::3DCore
    Qt6::3DExtras
    Qt6::3DRender
    Qt6::OpenGL  # Use OpenGL for 3D rendering
)

# If using Qt 6.1 or later, finalize the executable setup
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VirtualCity)
endif()

# Target properties for macOS and Windows
set_target_properties(VirtualCity PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install settings
include(GNUInstallDirs)
install(TARGETS VirtualCity
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
