
find_package(PkgConfig REQUIRED)

pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11)
pkg_check_modules(XI REQUIRED IMPORTED_TARGET xi)

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Quick)

add_executable(touchscreen-calibrator main.cpp calibrationwindow.cpp)

target_link_libraries(touchscreen-calibrator PkgConfig::X11 PkgConfig::XI Qt5::Core Qt5::Widgets Qt5::Quick)

install(TARGETS touchscreen-calibrator RUNTIME DESTINATION bin)
