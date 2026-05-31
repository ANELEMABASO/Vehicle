cmake_minimum_required(VERSION 3.19)
project(Question_3 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(Question_3
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    yeardelegate.h yeardelegate.cpp
    authorvalidator.h authorvalidator.cpp
)

target_link_libraries(Question_3
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(Question_3 PRIVATE Qt6::Quick)

install(TARGETS Question_3
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Question_3
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
