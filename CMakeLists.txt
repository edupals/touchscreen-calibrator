cmake_minimum_required(VERSION 3.10)

project(touchscreen-calibrator)
add_subdirectory(src)

install(FILES "rsrc/touchscreen-calibrator.svg"
    DESTINATION "usr/share/icons/hicolor/48x48/apps/"
)

install(FILES "rsrc/touchscreen-calibrator.desktop"
    DESTINATION "usr/share/applications/"
)

install(FILES "rsrc/touchscreen-calibrator-server.desktop"
    DESTINATION "etc/xdg/autostart"
)
