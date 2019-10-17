
find_package(PkgConfig REQUIRED)

pkg_check_modules(XCB REQUIRED IMPORTED_TARGET xcb)
pkg_check_modules(XCB_XINPUT REQUIRED IMPORTED_TARGET xcb-xinput)

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#find_package(Qt5 REQUIRED COMPONENTS Widgets Core Quick QuickWidgets)
#find_package(KF5CoreAddons REQUIRED)
#find_package(KF5I18n REQUIRED)
#find_package(KF5KCMUtils REQUIRED)

add_executable(touchscreen-calibrator main.cpp)

target_link_libraries(touchscreen-calibrator PkgConfig::XCB PkgConfig::XCB_XINPUT)

install(TARGETS touchscreen-calibrator RUNTIME DESTINATION bin)
