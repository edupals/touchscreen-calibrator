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

add_custom_target(
    po
    COMMAND xgettext -kde -ki18nd:2 ${CMAKE_CURRENT_SOURCE_DIR}/rsrc/*.qml -o ${CMAKE_CURRENT_SOURCE_DIR}/locale/messages.po
    COMMENT "extracting po..." 
)

set(langs es)
find_package(Intl)
find_package(Gettext)

foreach(lang ${langs})
    gettext_process_po_files(${lang} ALL PO_FILES locale/${lang}.po)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${lang}.gmo DESTINATION
            share/locale/${lang}/LC_MESSAGES/ RENAME touchscreen-calibrator.mo)
endforeach()
