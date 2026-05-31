cmake_minimum_required(VERSION 3.19)
project(Question_4 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(Question_4
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    authorvalidator.h authorvalidator.cpp
    pagesvalidator.h pagesvalidator.cpp
    titlevalidator.h titlevalidator.cpp
    yeardelegate.h yeardelegate.cpp
)

target_link_libraries(Question_4
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(Question_4 PRIVATE Qt6::Quick)

install(TARGETS Question_4
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Question_4
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
