cmake_minimum_required(VERSION 3.19)
project(PasswordManager LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)
qt_add_executable(PasswordManager
    WIN32 MACOSX_BUNDLE
    main.cpp
    passwordmanager.cpp
    passwordmanager.h
    passwordmanager.ui

    pages/login/loginpage.h pages/login/loginpage.cpp pages/login/loginpage.ui
    pages/signup/createaccount.h pages/signup/createaccount.cpp pages/signup/createaccount.ui

    pages/view/dashboard/dashboard.h pages/view/dashboard/dashboard.cpp pages/view/dashboard/dashboard.ui
    pages/view/passwordGenerator/passwordgeneratorpage.h pages/view/passwordGenerator/passwordgeneratorpage.cpp pages/view/passwordGenerator/passwordgeneratorpage.ui
    pages/view/settings/settingspage.h pages/view/settings/settingspage.cpp pages/view/settings/settingspage.ui

    utility/passwordgenerator.h utility/passwordgenerator.cpp
    utility/authentication.h utility/authentication.cpp
    utility/passwordmanagerio.h utility/passwordmanagerio.cpp
    utility/userdatahandler.h utility/userdatahandler.cpp
    utility/platformaccount.h

    extern/qaesencryption.h extern/qaesencryption.cpp
    utility/userauthdata.h
    resources.qrc

)

target_include_directories(PasswordManager PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(PasswordManager
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS PasswordManager
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET PasswordManager
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
