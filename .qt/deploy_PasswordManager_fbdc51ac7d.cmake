include("C:/Users/Sayus/git_repo/PasswordManager/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/PasswordManager-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE C:/Users/Sayus/git_repo/PasswordManager/PasswordManager.exe
    GENERATE_QT_CONF
)
