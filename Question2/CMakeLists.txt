cmake_minimum_required(VERSION 3.19)
project(Question2 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(Question2
    main.cpp
    filewriter.h filewriter.cpp
    passengervehecle.h passengervehecle.cpp
    vehecles.h vehecles.cpp
    transportvehecle.h transportvehecle.cpp
)

target_link_libraries(Question2
    PRIVATE
        Qt::Core
)

install(TARGETS Question2
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
