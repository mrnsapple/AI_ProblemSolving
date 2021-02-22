cmake_minimum_required(VERSION 3.5)

project(AI LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(UI_USAGE 0)
# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()


set(PROJECT_SOURCES
        BackEnd/Private/BreadthFirstSearch/BreadthFirstSearchAlgorithm.cpp
        BackEnd/Private/ProblemGenerators/Puzzle/PuzzleGenerator.cpp
        BackEnd/Private/BreadthFirstSearch/BreadthFirstSearchQueenLogic.cpp
        BackEnd/Private/BreadthFirstSearch/BreadthFirstSearchPuzzleLogic.cpp
        BackEnd/Private/AStar/AStarSearchAlgorithm.cpp
        BackEnd/Private/SimulatedAnnealing/SimulatedAnnealingAlgorithm.cpp
        BackEnd/Private/DepthFirstSearch/DepthFirstSearchAlgorithm.cpp
        BackEnd/Private/Utilities.cpp
)
if (UI_USAGE STREQUAL 1)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
SET(PROJECT_SOURCES   ${PROJECT_SOURCES} 
        QTUI/startUI.cpp
        QTUI/mainwindow.cpp
        QTUI/WorkerThread.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AI
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(AI SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(AI
            ${PROJECT_SOURCES}
        )
    endif()

    target_link_libraries(AI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

endif()
else()
add_definitions( -DONLY_BACK=1 )

SET(PROJECT_SOURCES   ${PROJECT_SOURCES} 
    main.cpp

)
add_executable(AI
            ${PROJECT_SOURCES}
        )
endif()
        #QTUI/mainwindow.h
        #QTUI/mainwindow.ui


