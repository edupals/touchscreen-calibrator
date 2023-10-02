cmake_minimum_required(VERSION 3.10)

project(touchscreen-calibrator)


install(FILES rsrc/touchscreen-calibrator.svg
    DESTINATION share/icons/hicolor/48x48/apps/
)

install(FILES rsrc/touchscreen-calibrator.desktop
    DESTINATION share/applications/
)

install(FILES rsrc/touchscreen-calibrator-server.desktop
    DESTINATION /etc/xdg/autostart
)

set(langs "es-es" "ca-es")
set(locales)
foreach(lang ${langs})
    set(file "/locale/touchscreen-calibrator_" ${lang})
    set(ts ${CMAKE_CURRENT_SOURCE_DIR} ${file} ".ts")
    set(qm ${CMAKE_CURRENT_SOURCE_DIR} ${file} ".qm")
    list(APPEND locales ${qm})
    #message(${qm})
endforeach()
#message(${locales})

add_custom_target(
        locales
        COMMAND lrelease ${locales}
        )

add_subdirectory(src)
